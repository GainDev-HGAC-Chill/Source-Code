#pragma once

#include "Lohengrin/PacketStruct.h"
#include "Lohengrin/LockUtil.h"
#include "PgCtrlServer.h"


typedef struct tagSIMPLE_ACCOUNT
{
	tagSIMPLE_ACCOUNT() {};
	tagSIMPLE_ACCOUNT(const tagSIMPLE_ACCOUNT& rhs)
	{
		_tcscpy_s(chID, 21, rhs.chID);
		_tcscpy_s(chPW, 21, rhs.chPW);
	}

	TCHAR chID[21];
	TCHAR chPW[21];
} SIMPLE_ACCOUNT;

typedef struct
{
	CEL::E_SESSION_TYPE eType;
	TCHAR chPath[MAX_PATH];
	TCHAR chParam[MAX_PATH];
} SERVER_FILE;

typedef struct
{
	int nChannel;
	SAddrInfo kAddr;
	bool bConnected;
	BM::GUID kConnectGuid;
	BM::GUID kSessionGuid;
	std::list<BM::GUID> kListenClient;
} SIMPLE_CENTER_INFO;

class PgServerController
{
public:
	PgServerController(void);
	~PgServerController(void);

	void AddAccount(LPCTSTR lpszID, LPCTSTR lpszPassword);
	void AddServerFile(CEL::E_SESSION_TYPE eType, LPCTSTR lpszPath, LPCTSTR lpszParam);
	bool GetAccount(LPCTSTR lpszID, SIMPLE_ACCOUNT* pkOut);
	void ConnectedCenter(bool bConnected, const BM::GUID& rkConnector, const BM::GUID& rkSession, SAddrInfo* pkAddr);
	void GetCenter(SAddrInfo* pkAddr, ObjectLock<SIMPLE_CENTER_INFO*>& kFind);

	// Packet hander
	void Login(const BM::GUID& rkSession, SClientTryLogin* pkLogin);
	void StartServer(const BM::GUID& rkSession, TBL_SERVERLIST* pkSInfo, SAddrInfo* pkCenterAddr);
	void ReqServerStatus(const BM::GUID& rkSession, TBL_SERVERLIST* pkSInfo, SAddrInfo* pkCenterAddr);
	void DeleteJob(const BM::GUID& rkClientSession);
	void QueryServerStatus(int iChannelID);
	void ResServerStatus(int iChannelID, CEL::CPacket * const pkPacket);

protected:
	bool AddServer(SERVER_IDENTITY* pkServer);
	void GetServer(int iChannel, int iServerNo, ObjectLock<PgCtrlServer*>& kFind);
	SERVER_FILE* GetServerFileInfo(CEL::E_SESSION_TYPE eType);
	bool MakeExeParameter(TBL_SERVERLIST* pkSInfo, SAddrInfo* pkCenterAddr, LPCTSTR lpszSource, LPTSTR lpszParam);
	void AddCenter(int iChannelID, SAddrInfo* pkAddr);
	void GetCenter(int iChannel, ObjectLock<SIMPLE_CENTER_INFO*>& kFind);
	void AddCenterListener(int iChannelID, const BM::GUID& rkClientSession);
	void SendCenter(int iChannelID, CEL::CPacket& rkPacket);
	void SendChannelInfo(const BM::GUID& rkClientSession, int iChannelID);
	void GetFirstServer(ObjectListIterLoc<PgCtrlServer*>& kFind);
	bool GetNextServer(int iChannelID, ObjectListIterLoc<PgCtrlServer*>& kFind);

public :
	BM::GUID m_kConnectorOrderGuid;
	BM::GUID m_kConnectorObjGuid;

private:

	typedef std::vector<SIMPLE_ACCOUNT> ACCOUNT_VECTOR;
	ACCOUNT_VECTOR m_kAccountInfo;

	typedef std::map<int, SERVER_FILE> SERVERFILE_MAP;
	SERVERFILE_MAP m_kServerFile;

	typedef std::list<PgCtrlServer*> CTRLSERVER_LIST;
	CTRLSERVER_LIST m_kServer;
	BM::TObjectPool< PgCtrlServer > m_kServerPool;
	OBJLOCK_REFCOUNT m_kServerLock;	//Lock (m_kServer)

	typedef std::list<SIMPLE_CENTER_INFO*> SIMPLE_CENTER_LIST;
	SIMPLE_CENTER_LIST m_kCenter;
	BM::TObjectPool< SIMPLE_CENTER_INFO > m_kCenterPool;
	OBJLOCK_REFCOUNT m_kCenterLock;	//Lock (m_kServer)
};

#define g_kController Loki::SingletonHolder<PgServerController>::Instance()

