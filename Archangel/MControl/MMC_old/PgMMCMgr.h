#pragma once

int const g_iSyncAddedPort = 369;

typedef struct tagServerSortInfo
{
	int iServerType;
	int iSortScore;

	tagServerSortInfo(const int iType, const int iScore)
		: iServerType(iType), iSortScore(iScore)
	{}
} SServerSortInfo;

typedef struct tagMonToolInfo
{
	tagMonToolInfo()
	{
	}
	CEL::SESSION_KEY kSessionKey;
	CEL::ADDR_INFO kAddr;
}SMonToolInfo;

typedef enum
{
	MCL_NONE = 0,
	MCL_GM_LOGIN,
	MCL_GM_LOGOUT,
	MCL_SERVER_ON,
	MCL_SERVER_OFF,
	MCL_SERVER_SHUTDOWN,
	MCL_RE_SYNC_START,
	MCL_RESYNC_END,
	MCL_CHANGE_MAX_USER,
}EMMC_Cmd_Log;

typedef std::map< std::wstring, SMonToolInfo > CONT_MON_TOOL_SESSION;

typedef struct TagMMCLog
{
	TagMMCLog()
	{
		eLogType = MCL_NONE;
		iUserMaxCount = 0;
	}

	EMMC_Cmd_Log eLogType;
	std::wstring kID;
	std::wstring kLoginIP;
	SERVER_IDENTITY kSI;
	std::wstring kMachineIP;
	int iUserMaxCount;
}SMMCLog;


class PgMMCMgr
{
public:
	PgMMCMgr(void);
	virtual ~PgMMCMgr(void);

public:
	void PrepareStateCont();
	bool ReadConfigFile();
	bool ReadIni_Path(CEL::E_SESSION_TYPE const &eST, std::wstring const &strCategory, std::wstring const &strFileName);
	void NfyConfig();//모든 SMC 에게 갱신.
	void NfyReSync();
	int CheckAuthInfo(CEL::CSession_Base *pkSession, std::wstring const &kID, std::wstring const &kPW) const;
	
	//SMC 의 응답
	bool RecvAnsFromSMC(CEL::CSession_Base *pkSession, CEL::SESSION_KEY const &kCmdOwner, EMMC_CMD_TYPE const eCmd, BM::CPacket* const pkPacket);//서버 기동
	bool RecvInfoFromSMC(CEL::CSession_Base *pkSession, EMMC_CMD_TYPE const eCmd, BM::CPacket* const pkPacket);//서버 기동
	
	bool RecvInfoFromImm(CEL::CSession_Base *pkSession, E_IMM_MCC_CMD_TYPE const eCmdType, BM::CPacket* const pkPacket);

	//툴 커멘드
	bool RecvMonToolCmd(CEL::CSession_Base *pkSession, EMMC_CMD_TYPE const eCmdType, BM::CPacket* const pkPacket);

	void LogAction(ContServerID const& rkCommandArray, const TCHAR* szActionName) const;
	 
	void GetContState(CONT_SERVER_STATE_EX &outCont)
	{
		BM::CAutoMutex kLock(m_kMutex);
		outCont = m_kTotalServerState;
	}

	bool SendNfyCommandToSMC(CEL::SESSION_KEY const &kCmdOwner, EMMC_CMD_TYPE const eCmdType, ContServerID const &rkCommandArray) const;

	void AddSyncIngSession(CEL::CSession_Base *pkSession);
	void RemoveSyncIngSession(CEL::CSession_Base *pkSession);

	bool SetServiceStatus(SERVER_IDENTITY const &kSI, SExSingleServerStatus const &kServerStatus);
	void CheckServerStatus();
	bool IsSyncIng()const;

	void AddSmcSession(CEL::CSession_Base *pkSession, SERVER_IDENTITY const &kSI);
	void RemoveSmcSession(CEL::CSession_Base *PKSession);

	void WriteToPacketSMCInfo(BM::CPacket &rkPacket) const;
	bool FindRunServers(CEL::CSession_Base *pkSMCSession, ContServerID &rkOut) const;

	bool IsCurrentGmUser(std::wstring const &kID) const;

	HRESULT OnConnectMonTool(CEL::CSession_Base* pkSession, std::wstring const &kID);
	bool OnDisconnectMonTool(CEL::CSession_Base* pkSession);

	void Broadcast(BM::CPacket &kPacket)const;

	bool IsConnectionTool()const;

	bool IsAllowedSessionKey(CEL::SESSION_KEY const &kSessionKey) const; 

	bool FindGmID(CEL::SESSION_KEY const &kSessionKey, std::wstring &rkOut) const;

	void Locked_DisConnectionAll();
	
	void GetSyncPath(CON_SYNC_PATH &kOut)const;

	static bool WriteToFileToolLog(SMMCLog const &kMMCLog);
private:
	void SetOffCommand(CEL::CSession_Base *pkSession, ContServerID &kCommandVec);
	void SetOnCommand(CEL::CSession_Base *pkSession, ContServerID &kCommandVec);
	void ClearCommandStack();
	bool CheckOnCommand();
	bool CheckOffCommand();
	bool IsValidSMC(std::wstring const &kSMCAddr);
	bool FindSuccessVec(SERVER_IDENTITY const &kSI);

private:
	static void ServerInfoToSTR(SERVER_IDENTITY const &kSI, std::wstring &rkOut);
	static BM::CDebugLog	m_kFileLog;
protected:
	mutable Loki::Mutex m_kMutex;

protected:
	typedef std::set< CEL::CSession_Base* > CONT_SYNC_ING_SESSION; //싱크중인 세션.
	typedef std::list<SERVER_IDENTITY> CONT_COMMAND_STACK;
	typedef std::map<CEL::CSession_Base*, SERVER_IDENTITY> CONT_SMC_STATE;	//sessoion, SI
	typedef std::map<CEL::E_SESSION_TYPE, BM::FolderHash> CONT_SYNC_FILE_DATA;

	CONT_SERVER_STATE_EX	m_kTotalServerState;//전체 서버 상황. -> SMC 로 부터 받은 결과가 기준.//exception, 타임아웃 등은 다른걸로 체크.
	CONT_SERVER_STATE_EX	m_kOldTotalServerState;
	CONT_SMC_STATE			m_kSMCState;
	CONT_SYNC_FILE_DATA		m_kContSyncData;
	
	CONT_COMMAND_STACK		m_kContOnCommand;
	CONT_COMMAND_STACK		m_kContOffCommand;
	ContServerID			m_kSuccessVec;
	ContServerID			m_kFailVec;
	CONT_COMMAND_STACK		m_kContSendCommand;

	CONT_SYNC_ING_SESSION	m_kContSyncIng;

	CLASS_DECLARATION_S_NO_SET(CEL::ADDR_INFO, ImmServer);
	
	//ini 로 셋팅
	ContTermianlAuthInfo m_kUserAuthInfo;
	CON_SYNC_PATH m_kSyncPath;
	CONT_MON_TOOL_SESSION m_kMonToolSession;
	
	CLASS_DECLARATION_S(int, IntervalTime);
	CLASS_DECLARATION_S(bool, bUseSMCAutoPatch);
};


#define g_kMMCMgr Loki::SingletonHolder<PgMMCMgr>::Instance()


/////////////////////
inline void WriteSuccessFailVec(ContServerID const& kSuccessVec, ContServerID const& kFailVec, BM::CPacket& kPacket)
{
	PU::TWriteArray_M(kPacket, kSuccessVec);//성공한 목록
	PU::TWriteArray_M(kPacket, kFailVec);//실패 목록
}
inline void ReadSuccessFailVec(ContServerID& kSuccessVec, ContServerID& kFailVec, BM::CPacket& kPacket)
{
	PU::TLoadArray_M(kPacket, kSuccessVec);//성공한 목록
	PU::TLoadArray_M(kPacket, kFailVec);//실패 목록
}
