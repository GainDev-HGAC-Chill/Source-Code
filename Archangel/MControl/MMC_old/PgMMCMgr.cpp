#include "StdAfx.h"
#include "PgRecvFromSMC.h"
#include "PgRecvFromImmigration.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "PgRecvFromMonTool.h"
#include "PgSendWrapper.h"

const TCHAR* szProcInfoFile = _T("ProcInfo.dat");

void LogLastError()
{
#ifdef _DEBUG
	DWORD const dwErrorCode = GetLastError();
	TCHAR szMsg[2048] = {0, };
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErrorCode, 0, szMsg, 2048, NULL);
	std::cout << MB(szMsg) << std::endl;
#endif
}
void InfoLogLastError(const TCHAR* szLog, const TCHAR* szFunc, DWORD const dwLine)
{
	DWORD const dwErrorCode = GetLastError();
	TCHAR szMsg[2048] = {0, };
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErrorCode, 0, szMsg, 2048, NULL);
//	INFO_LOG(BM::LOG_LV1, __FL__ << szLog _T("- ErrorCode: ") << dwErrorCode << _T("(") << MB(szMsg) << _T(")") );
//	INFO_LOG(BM::LOG_LV1, _T("[%s]-[%u] %s - ErrorCode: %u (%s)"), szFunc, dwLine, szLog, dwErrorCode, MB(szMsg));
}

bool CompareOffCommand(ContServerID::value_type& rkLeft, ContServerID::value_type& rkRight)
{
	//1.       MCtrl 툴의 Login Close 기능으로 새로운 유저 접속을 맊는다.
	//2.       모든 사용자 연결 Disconnect
	//3.       Login
	//4.       Map
	//5.       Switch
	//6.       Center
	//7.	   Contents 자신이 가지고 있는 저장되지 않은 사용자 정보가 모두 저장 될 때 까지 기다리고 나서 Off
	//8.	   IMM
	//9.	   GM
	//10.      Log	이건 제일 마지막에 내리던가 아싸리 계속 유지하던가

	static const SServerSortInfo kSortInfo[] =//아래 순서 바꾸지 말것
	{
		SServerSortInfo(CEL::ST_NONE, 999),
		SServerSortInfo(CEL::ST_CENTER, 6),
		SServerSortInfo(CEL::ST_MAP, 4),
		SServerSortInfo(CEL::ST_LOGIN, 3),
		SServerSortInfo(CEL::ST_SWITCH, 5),
		SServerSortInfo(CEL::ST_MACHINE_CONTROL, 999),
		SServerSortInfo(0, 999),
		SServerSortInfo(0, 999),
		SServerSortInfo(CEL::ST_ITEM, 999),
		SServerSortInfo(CEL::ST_CONTENTS, 7),
		SServerSortInfo(CEL::ST_LOG, 9),	//	off커맨드로 못죽이도록 수정
		SServerSortInfo(0, 999),
		SServerSortInfo(CEL::ST_GMSERVER, 8),
		SServerSortInfo(CEL::ST_GHOST_LOGIN, 999),
		SServerSortInfo(CEL::ST_IMMIGRATION, 10),
		SServerSortInfo(CEL::ST_SUB_MACHINE_CONTROL, 999),
		SServerSortInfo(CEL::ST_AP, 11),
	};

	if( CEL::ST_NONE >= rkLeft.nServerType
	||	CEL::ST_MAX < rkLeft.nServerType
	||	CEL::ST_NONE >= rkRight.nServerType
	||	CEL::ST_MAX < rkRight.nServerType )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("Can't identify server type") << rkLeft.nServerType << _T(" or ") << rkRight.nServerType );
//		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Can't identify server type %d or %d"), __FUNCTIONW__, __LINE__, rkLeft.nServerType, rkRight.nServerType);
		return false;
	}

	const SServerSortInfo& rkLeftScore = kSortInfo[rkLeft.nServerType];
	const SServerSortInfo& rkRightScore = kSortInfo[rkRight.nServerType];

	return  rkLeftScore.iSortScore < rkRightScore.iSortScore;
}

bool CompareOnCommand(ContServerID::value_type& rkLeft, ContServerID::value_type& rkRight)
{
	//1.	  MCTRL
	//2.       Imm
	//3.       Log
	//4.       Contents
	//5.       Channel
	//6.       Switch
	//7.       Map
	//8.	   Login
	//9.	   GM

	static const SServerSortInfo kSortInfo[] =//아래 순서 바꾸지 말것
	{
		SServerSortInfo(CEL::ST_NONE, 999),
		SServerSortInfo(CEL::ST_CENTER, 5),
		SServerSortInfo(CEL::ST_MAP, 7),
		SServerSortInfo(CEL::ST_LOGIN, 8),
		SServerSortInfo(CEL::ST_SWITCH, 6),
		SServerSortInfo(CEL::ST_MACHINE_CONTROL, 999),
		SServerSortInfo(0, 999),
		SServerSortInfo(0, 999),
		SServerSortInfo(CEL::ST_ITEM, 999),
		SServerSortInfo(CEL::ST_CONTENTS, 4),
		SServerSortInfo(CEL::ST_LOG, 3),	//	off커맨드로 못죽이도록 수정
		SServerSortInfo(0, 999),
		SServerSortInfo(CEL::ST_GMSERVER, 9),
		SServerSortInfo(CEL::ST_GHOST_LOGIN, 999),
		SServerSortInfo(CEL::ST_IMMIGRATION, 2),
		SServerSortInfo(CEL::ST_SUB_MACHINE_CONTROL, 999),
		SServerSortInfo(CEL::ST_AP, 10),
	};

	if( CEL::ST_NONE >= rkLeft.nServerType
	||	CEL::ST_MAX < rkLeft.nServerType
	||	CEL::ST_NONE >= rkRight.nServerType
	||	CEL::ST_MAX < rkRight.nServerType )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("Can't identify server type") << rkLeft.nServerType << _T(" or ") << rkRight.nServerType );
//		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Can't identify server type %d or %d"), __FUNCTIONW__, __LINE__, rkLeft.nServerType, rkRight.nServerType);
		return false;
	}

	const SServerSortInfo& rkLeftScore = kSortInfo[rkLeft.nServerType];
	const SServerSortInfo& rkRightScore = kSortInfo[rkRight.nServerType];

	return rkLeftScore.iSortScore < rkRightScore.iSortScore;
}
//<<

//1 seconds

BM::CDebugLog	PgMMCMgr::m_kFileLog;

PgMMCMgr::PgMMCMgr(void)
{
	m_kFileLog.Init(BM::OUTPUT_JUST_FILE, BM::LFC_WHITE, L"./MonToolLog", L"MonToolLog.txt");
	ClearCommandStack();
}

PgMMCMgr::~PgMMCMgr(void)
{
	ClearCommandStack();
}

bool PgMMCMgr::ReadIni_Path(CEL::E_SESSION_TYPE const &eST, std::wstring const &strCategory, std::wstring const &strFileName)
{
	BM::CAutoMutex kLock(m_kMutex);

	static std::wstring const kSync = L"SYNC";

	TCHAR szSrcFolder[MAX_PATH] = {0, };
	TCHAR szDestFolder[MAX_PATH] = {0, }, szExe[MAX_PATH] = {0, };

	std::wstring strExeElement = _T("EXE_") + strCategory;
	std::wstring strSrcElement = _T("SRC_") + strCategory;
//	std::wstring strDstElement = _T("DEST_") + strCategory;
	
	if( 0 < GetPrivateProfileString(kSync.c_str(), strSrcElement.c_str(), _T(""), szSrcFolder, MAX_PATH, strFileName.c_str()) 
	&&	0 < GetPrivateProfileString(kSync.c_str(), strExeElement.c_str(), _T(""), szExe, MAX_PATH, strFileName.c_str())	)
//	&&  0 < GetPrivateProfileString(kSync.c_str(), strDstElement.c_str(), _T(""), szDestFolder, MAX_PATH, strFileName.c_str()) )
	{
		CON_SYNC_PATH::_Pairib ret = m_kSyncPath.insert(std::make_pair(eST, SGameServerPath(szSrcFolder, szExe)));
		return ret.second;
	}
	else if(eST == CEL::ST_NONE && strCategory == L"CONFIG")
	{
		CON_SYNC_PATH::_Pairib ret = m_kSyncPath.insert(std::make_pair(eST, SGameServerPath(szSrcFolder, szExe)));
		return ret.second;
	} 
	return false;
}

bool PgMMCMgr::ReadConfigFile()
{
	BM::CAutoMutex kLock(m_kMutex);
	std::wstring const kMain = L"MMC";
	
	TCHAR chFile[MAX_PATH] = {0, };
	_tcscat_s(chFile, MAX_PATH, _T("./MMC.ini"));

	if(!PathFileExists(chFile) )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("ManagementServer.ini isn't exist") );
//		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] ManagementServer.ini isn't exist"), __FUNCTIONW__, __LINE__);
		return false;
	}

	m_kSyncPath.clear();

	TCHAR chValue[500] = {0, };

	//set interval Time
	IntervalTime(GetPrivateProfileInt(kMain.c_str(), _T("INTERVAL_TIME "), 0, chFile));
	bUseSMCAutoPatch(GetPrivateProfileInt(kMain.c_str(), _T("SMC_AUTO_PATCH "), 0, chFile));
	 

	ReadIni_Path(CEL::ST_CENTER, _T("CENTER"), chFile);
	ReadIni_Path(CEL::ST_CONTENTS, _T("CONTENTS"), chFile);
	ReadIni_Path(CEL::ST_LOGIN, _T("LOGIN"), chFile);
	ReadIni_Path(CEL::ST_MAP, _T("MAP"), chFile);
	ReadIni_Path(CEL::ST_SWITCH, _T("SWITCH"), chFile);
	ReadIni_Path(CEL::ST_IMMIGRATION, _T("IMMIGRATION"), chFile);
	ReadIni_Path(CEL::ST_LOG, _T("LOG"), chFile);
	ReadIni_Path(CEL::ST_GMSERVER, _T("GM"), chFile);
	ReadIni_Path(CEL::ST_NONE, _T("CONFIG"), chFile);
	ReadIni_Path(CEL::ST_SUB_MACHINE_CONTROL, _T("SMC"), chFile);
	ReadIni_Path(CEL::ST_CONSENT, _T("CONSENT"), chFile);


	//User인증 정보 처리
	std::wstring const wstrUserInfo = L"USER_INFO";
	
	int iUserCount = 0;
	if(GetPrivateProfileString(wstrUserInfo.c_str(), L"MAX_USER", NULL, chValue, 500, chFile) > 0)
	{
		iUserCount = _ttoi(chValue);
	}

	for(int i = 0; i < iUserCount; ++i)
	{
		STerminalAuthInfo kAuthInfo;
		wsprintf((LPWSTR)wstrUserInfo.c_str(), L"USER_INFO_%d", i+1);
		if(GetPrivateProfileString(wstrUserInfo.c_str(), L"ID", NULL, chValue, 500, chFile) > 0)
		{
			kAuthInfo.kID = chValue;
		}

		if(GetPrivateProfileString(wstrUserInfo.c_str(), L"PW", NULL, chValue, 500, chFile) > 0)
		{
			kAuthInfo.kPW = chValue;
		}

		if(GetPrivateProfileString(wstrUserInfo.c_str(), L"IP", NULL, chValue, 500, chFile) > 0)
		{
			kAuthInfo.kAuthIP = chValue;
		}

		kAuthInfo.cGrant = static_cast<BYTE>(GetPrivateProfileInt(wstrUserInfo.c_str(), L"GRADE", 0, chFile));
		
		m_kUserAuthInfo.insert(std::make_pair(kAuthInfo.kID, kAuthInfo));
	}
	return true;
}


void PgMMCMgr::NfyConfig()
{
	BM::CAutoMutex kLock(m_kMutex);
	SendNfyCommandToSMC(CEL::SESSION_KEY(), MCT_REFRESH_CFG, ContServerID());
}

void PgMMCMgr::NfyReSync()
{
	BM::CAutoMutex kLock(m_kMutex);
	SendNfyCommandToSMC(CEL::SESSION_KEY(), MCT_RE_SYNC, ContServerID());
}

#include <tlhelp32.h>
//<<
int PgMMCMgr::CheckAuthInfo(CEL::CSession_Base *pkSession, std::wstring const &kID, std::wstring const &kPW) const
{
	if( !pkSession )
	{
		return 0;
	}

	BM::CAutoMutex kLock(m_kMutex);
	
	ContTermianlAuthInfo::const_iterator Itr = m_kUserAuthInfo.find(kID);
	if(Itr == m_kUserAuthInfo.end())
	{
		return 0;
	}

	const ContTermianlAuthInfo::mapped_type& rkElement = Itr->second;
	if(!rkElement.IsEqual(kID, kPW, pkSession->Addr().IP()))
	{
		INFO_LOG(BM::LOG_LV6, __FL__ << _T("Wrong Auth Info[") 	<< rkElement.kID.c_str() << _T("][") 
			<< rkElement.kAuthIP.c_str() << _T("] != [") << kID.c_str() 	
			<< _T("][") << pkSession->Addr().IP().c_str() << _T("])") );

//		INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Wrong Auth Info[%s][%s] != [%s][%s]"), __FUNCTIONW__, __LINE__,
//			rkElement.kID.c_str(), rkElement.kAuthIP.c_str(), kID.c_str(), pkSession->Addr().IP().c_str());
		return 0;
	}
	return static_cast<int>(rkElement.cGrant);
}

void PgMMCMgr::LogAction(ContServerID const& rkCommandArray, const TCHAR* szActionName) const
{
	BM::CAutoMutex kLock(m_kMutex);
	if( !szActionName )
	{
		szActionName = _T("Null");
	}

	ContServerID::const_iterator iter = rkCommandArray.begin();
	while(rkCommandArray.end() != iter)
	{
		ContServerID::value_type const& rkServerID = (*iter);
		INFO_LOG(BM::LOG_LV7, _T("[Ch:") << rkServerID.nChannel << _T(" Ty:") << rkServerID.nServerType 
			<< _T("Sn:") << rkServerID.nServerNo << _T("] Action:") << szActionName);
//		INFO_LOG(BM::LOG_LV7, _T("[Ch:%3d Ty:%3d Sn:%3d] Action:%s"),
//			rkServerID.nChannel, rkServerID.nServerType, rkServerID.nServerNo, szActionName );
		++iter;
	}
}


void PgMMCMgr::PrepareStateCont()
{
	BM::CAutoMutex kLock(m_kMutex);

	m_kTotalServerState.clear();
	m_kOldTotalServerState.clear();

	CONT_SERVER_HASH kContSerer;
	g_kProcessCfg.Locked_GetServerInfo(CEL::ST_NONE, kContSerer);

	CONT_SERVER_HASH::const_iterator server_itor = kContSerer.begin();
	while(server_itor != kContSerer.end())
	{
		CONT_SERVER_STATE_EX::mapped_type kServerState;
		kServerState.kTbl = (*server_itor).second;
		m_kTotalServerState.insert(std::make_pair((*server_itor).first, kServerState));
		++server_itor;
	}
}

bool PgMMCMgr::SendNfyCommandToSMC(CEL::SESSION_KEY const &kCmdOwner, EMMC_CMD_TYPE const eCmdType, ContServerID const &rkCommandArray) const
{
	BM::CAutoMutex kLock(m_kMutex);

	BM::CPacket kPacket(PT_MMC_SMC_NFY_CMD, eCmdType);
	kPacket.Push(kCmdOwner);//오더내리는사람 KEY

	if(eCmdType == MCT_REFRESH_CFG)
	{
		PU::TWriteTable_MM(kPacket, m_kSyncPath);
		g_kProcessCfg.Locked_SendToServerType(CEL::ST_SUB_MACHINE_CONTROL, kPacket);
	}
	else
	{
		PU::TWriteArray_M(kPacket, rkCommandArray);
	}
	bool const bSendRet = g_kProcessCfg.Locked_SendToServerType(CEL::ST_SUB_MACHINE_CONTROL, kPacket);
	if( !bSendRet )
	{
	}
	return true;
}

bool PgMMCMgr::RecvMonToolCmd(CEL::CSession_Base *pkSession, EMMC_CMD_TYPE const eCmdType, BM::CPacket* const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);
	if(IsSyncIng())
	{
		BM::CPacket kPacket(PT_ANS_MMC_TOOL_CMD_RESULT);
		int iErrorCode = 1;
		kPacket.Push(iErrorCode);
		pkSession->VSend(kPacket);
		return false;
	}

	if(!IsAllowedSessionKey(pkSession->SessionKey()))
	{
		BM::CPacket kPacket(PT_ANS_MMC_TOOL_CMD_RESULT);
		int iErrorCode = 2;
		kPacket.Push(iErrorCode);
		pkSession->VSend(kPacket);
		return false;
	}

	switch(eCmdType)
	{
	case MCT_REFRESH_STATE:
	case MCT_REFRESH_LIST:
		{
			CONT_SERVER_STATE_EX kContServerState;
			GetContState(kContServerState);

			BM::CPacket kPacket(PT_MMC_TOOL_NFY_INFO, eCmdType);
			PU::TWriteTable_MM(kPacket, kContServerState);
			g_kRealmMgr.WriteToPacket(kPacket, 0, ERealm_SendType_All);//렐름정보 보냄.

			pkSession->VSend(kPacket);
		}break;
	case MCT_SERVER_ON:
		{
			ContServerID kCommandVec;
			PU::TLoadArray_M(*pkPacket, kCommandVec);

			SetOnCommand(pkSession, kCommandVec);
		}break;
	case MCT_SERVER_OFF:
		{
			ContServerID kCommandVec;
			PU::TLoadArray_M(*pkPacket, kCommandVec);
			SetOffCommand(pkSession, kCommandVec);
		}break;
	case MCT_SERVER_SHUTDOWN:
		{
			ClearCommandStack();
			ContServerID kCommandVec;
			PU::TLoadArray_M(*pkPacket, kCommandVec);
			SendNfyCommandToSMC(pkSession->SessionKey(), eCmdType, kCommandVec);

			ContServerID::iterator Itr = kCommandVec.begin();
			while(Itr != kCommandVec.end())
			{
				CONT_SERVER_STATE_EX::iterator state_Itr = m_kTotalServerState.find(*Itr);
				if(state_Itr != m_kTotalServerState.end())
				{
					CONT_SERVER_STATE_EX::mapped_type kElement = state_Itr->second;

					SMMCLog kLog;
					kLog.eLogType = MCL_SERVER_SHUTDOWN;
					FindGmID(pkSession->SessionKey(), kLog.kID);
					kLog.kLoginIP = pkSession->Addr().ToString();
					kLog.kSI = (*Itr);
					kLog.kMachineIP = kElement.kTbl.strMachinIP;
					PgMMCMgr::WriteToFileToolLog(kLog);
				}
				++Itr;
			}
		}break;
	case MCT_CHANGE_MAXUSER:
		{
			BM::CPacket kPacket(PT_MCTRL_MMC_A_NFY_SERVER_COMMAND, MCC_CHANGE_MAXUSER);
			kPacket.Push(*pkPacket);
			g_kProcessCfg.Locked_SendToServerType(CEL::ST_IMMIGRATION, kPacket);
		}break;
	default:
		{
			ContServerID kCommandVec;
			PU::TLoadArray_M(*pkPacket, kCommandVec);
			
			bool const bSendRet = SendNfyCommandToSMC(pkSession->SessionKey(), eCmdType, kCommandVec);
		}break;
	}
	return true;
}

bool PgMMCMgr::RecvAnsFromSMC(CEL::CSession_Base *pkSession, CEL::SESSION_KEY const &kCmdOwner, EMMC_CMD_TYPE const eCmd, BM::CPacket* const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);

//	bool bChanged = false;
	ContServerID kSuccessVec, kFailVec;
	PU::TLoadArray_M(*pkPacket, kSuccessVec);
	PU::TLoadArray_M(*pkPacket, kFailVec);

	ContServerID::iterator Success_Itr = kSuccessVec.begin();
	if(Success_Itr != kSuccessVec.end())
		m_kSuccessVec.insert(m_kSuccessVec.end(), *Success_Itr);

	ContServerID::iterator Fail_Itr = kFailVec.begin();
	if(Fail_Itr != kFailVec.end())
		m_kFailVec.insert(m_kFailVec.end(), *Fail_Itr);

/*
	ContServerID::iterator Fail_Itr = kFailVec.begin();
	while(Fail_Itr != kFailVec.end())
	{
		m_kFailVec.push_back(*Fail_Itr);
		++Fail_Itr;
	}
*/

//	SChangeStatusPack kSuccessPack;
//	kSuccessPack.SetHandle(true);

//	BM::CPacket kPacket(PT_ANS_MON_TOOL_CMD);
//	PU::TWriteArray_M(*pkPacket, kSuccessVec);
//	PU::TWriteArray_M(*pkPacket, kFailVec);

//	g_kCoreCenter.Send(kCmdOwner, kPacket);
	
	// off
	//kSuccessPack.SetAll(false, false, false); --> Terminate
//	bChanged = UpdateStatus(kSuccessVec, kSuccessPack) || bChanged;
//	SChangeStatusPack kFailPack;
//	bChanged = UpdateStatus(kFailVec, kFailPack) || bChanged;//변화 없음
	
//	FailPrevCommand(kFailVec);//On 명령어 실패 처리
	
	return false;
}

bool PgMMCMgr::RecvInfoFromSMC(CEL::CSession_Base *pkSession, EMMC_CMD_TYPE const eCmd, BM::CPacket* const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);
	switch(eCmd)
	{
	case MCT_REFRESH_STATE:
		{
			CONT_SERVER_PROCESS kRunServers;
			PU::TLoadTable_MM(*pkPacket, kRunServers);

			CONT_SERVER_PROCESS::const_iterator proc_itor = kRunServers.begin();
			while(proc_itor != kRunServers.end())
			{
				CONT_SERVER_STATE_EX::iterator state_itor = m_kTotalServerState.find((*proc_itor).first);

				if(state_itor != m_kTotalServerState.end())
				{
					(*state_itor).second.kProcessInfo = (*proc_itor).second;//프로세스 정보만 갱신.
				}
				else
				{
					VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("Incorect Process Info"));
//					VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("Incorect Process Info"));
				}
				++proc_itor;
			}
		}break;
	default:
		{
			return false;
		}break;
	}
	return true;
}

bool PgMMCMgr::RecvInfoFromImm(CEL::CSession_Base *pkSession, E_IMM_MCC_CMD_TYPE const eCmdType, BM::CPacket* const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);

	switch(eCmdType)
	{
	case IMCT_STATE_NFY:
		{
			bool bIsConnect = false;
			bool bIsExecption = false;
			int iMaxUsers = 0;
			int iConnectionUsers = 0;

			SERVER_IDENTITY kSI;

			kSI.ReadFromPacket(*pkPacket);
			pkPacket->Pop(bIsConnect);
			pkPacket->Pop(bIsExecption);
			pkPacket->Pop(iConnectionUsers);
			pkPacket->Pop(iMaxUsers);

			CONT_SERVER_STATE_EX::iterator state_itor = m_kTotalServerState.find(kSI);
			if(state_itor == m_kTotalServerState.end())
			{
				return false;
			}

			CONT_SERVER_STATE_EX::iterator Old_state_itr = m_kOldTotalServerState.find(kSI);
			if(Old_state_itr == m_kOldTotalServerState.end())
			{
				return false;
			}

			if( Old_state_itr->second.bIsException != bIsExecption
			|| Old_state_itr->second.bReadyToService != bIsConnect
			|| Old_state_itr->second.uiMaxUsers != iMaxUsers
			|| Old_state_itr->second.uiConnectionUsers != iConnectionUsers)
			{
				state_itor->second.bReadyToService = bIsConnect;
				state_itor->second.bIsException = bIsExecption;
				state_itor->second.uiMaxUsers = iMaxUsers;
				state_itor->second.uiConnectionUsers = iConnectionUsers;
			} 
			else
			{
				state_itor->second.bReadyToService = Old_state_itr->second.bReadyToService;
				state_itor->second.bIsException = Old_state_itr->second.bIsException;				
				state_itor->second.uiMaxUsers =  Old_state_itr->second.uiMaxUsers;
				state_itor->second.uiConnectionUsers = Old_state_itr->second.uiConnectionUsers;
			}
		}break;
	default:break;
	}

	return true;
}

void PgMMCMgr::AddSyncIngSession(CEL::CSession_Base *pkSession)
{
	if( !pkSession )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Session is NULL");
		return ;
	}

	BM::CAutoMutex kLock(m_kMutex);
	m_kContSyncIng.insert(pkSession);

	S_STATE_LOG(BM::LOG_LV1, L"SyncStart["<<C2L(pkSession->Addr())<<L"]");
}

void PgMMCMgr::RemoveSyncIngSession(CEL::CSession_Base *pkSession)
{
	if( !pkSession )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Session is NULL");
		return ;
	}

	BM::CAutoMutex kLock(m_kMutex);
	CONT_SYNC_ING_SESSION::iterator Itr = m_kContSyncIng.find(pkSession);
	if(Itr != m_kContSyncIng.end())
	{
		m_kContSyncIng.erase(pkSession);
		S_STATE_LOG(BM::LOG_LV1, L"SyncEnd["<<C2L(pkSession->Addr())<<L"]");
	}
}

bool PgMMCMgr::IsSyncIng()const
{
	BM::CAutoMutex kLock(m_kMutex);
	if(m_kContSyncIng.size())
	{
		return true;
	}
	return false;
}

bool PgMMCMgr::SetServiceStatus(const SERVER_IDENTITY &kSI, const SExSingleServerStatus &kServerStatus)
{
	BM::CAutoMutex kLock(m_kMutex);

	CONT_SERVER_STATE_EX::iterator Itr = m_kTotalServerState.find(kSI);
	if(Itr == m_kTotalServerState.end())
	{
		return false;
	}

	Itr->second.Set(kServerStatus);

	return true;
}

void PgMMCMgr::CheckServerStatus()
{
	BM::CAutoMutex kLock(m_kMutex);

	//상태 초기화
	{
		CONT_SERVER_STATE_EX::iterator Itr = m_kTotalServerState.begin();
		while(Itr != m_kTotalServerState.end())
		{
			CONT_SERVER_STATE_EX::mapped_type kElement = Itr->second;
			CONT_SERVER_STATE_EX::key_type kKey = Itr->first;
			CONT_SERVER_STATE_EX::_Pairib kRet =  m_kOldTotalServerState.insert(std::make_pair(kKey, kElement));
			if(!kRet.second)
			{
				kRet.first->second.kProcessInfo = Itr->second.kProcessInfo;
				kRet.first->second.bIsException = Itr->second.bIsException;
				kRet.first->second.bReadyToService = Itr->second.bReadyToService;
				kRet.first->second.uiMaxUsers = Itr->second.uiMaxUsers;
				kRet.first->second.kTbl.nPlayerCount = Itr->second.kTbl.nPlayerCount;
			}

			Itr->second.bIsException = false;
			Itr->second.bReadyToService = false;

			if( kElement.kTbl.nServerType != CEL::ST_MACHINE_CONTROL			
				&& kElement.kTbl.nServerType != CEL::ST_SUB_MACHINE_CONTROL)
			{
				BM::CPacket kPacket(PT_MCTRL_MMC_A_NFY_SERVER_COMMAND, MCC_Heart_Beat);
				kKey.WriteToPacket(kPacket);
				g_kProcessCfg.Locked_SendToServerType(CEL::ST_IMMIGRATION, kPacket);
			}
/*			
			else 
			if( kElement.kTbl.nServerType != CEL::ST_MACHINE_CONTROL
				&& kElement.kTbl.nServerType == CEL::ST_SUB_MACHINE_CONTROL)
			{
				BM::CPacket kPacket(PT_MCTRL_MMC_A_NFY_SERVER_COMMAND, MCC_Heart_Beat);
				kKey.WriteToPacket(kPacket);
				g_kProcessCfg.Locked_SendToServer(kKey, kPacket);
			}
*/
			++Itr;
		}
	}

//	CheckOnCommand();
	CheckOffCommand();
}

void PgMMCMgr::SetOffCommand(CEL::CSession_Base *pkSession, ContServerID &kCommandVec)
{
	BM::CAutoMutex kLock(m_kMutex);

	if( !m_kContOnCommand.empty()
		|| !m_kContOffCommand.empty()
		|| kCommandVec.empty() )
	{
		return ;
	}

//	m_kSuccessVec.clear();
//	m_kFailVec.clear();

	//SMC가 실행중이지 않는 넘은 제거한다.
	ContServerID kOffCommandVec;
	ContServerID::iterator Itr = kCommandVec.begin();
	while(Itr != kCommandVec.end())
	{
		CONT_SERVER_STATE_EX::iterator state_Itr = m_kTotalServerState.find(*Itr);
		if(state_Itr != m_kTotalServerState.end())
		{
			CONT_SERVER_STATE_EX::mapped_type kElement = state_Itr->second;
			if(IsValidSMC(kElement.kTbl.strMachinIP))
			{
				kOffCommandVec.push_back(*Itr);

				SMMCLog kLog;
				kLog.eLogType = MCL_SERVER_OFF;
				FindGmID(pkSession->SessionKey(), kLog.kID);
				kLog.kLoginIP = pkSession->Addr().ToString();
				kLog.kSI = (*Itr);
				kLog.kMachineIP = kElement.kTbl.strMachinIP;
				PgMMCMgr::WriteToFileToolLog(kLog);
			}
		}
		++Itr;
	}

	std::sort(kOffCommandVec.begin(), kOffCommandVec.end(), CompareOffCommand);
	m_kContOffCommand.insert(m_kContOffCommand.end(), kOffCommandVec.begin(), kOffCommandVec.end());}

void PgMMCMgr::SetOnCommand(CEL::CSession_Base *pkSession, ContServerID &kCommandVec)
{
	BM::CAutoMutex kLock(m_kMutex);

	if( !m_kContOnCommand.empty()
		|| !m_kContOffCommand.empty()
		|| kCommandVec.empty() )
	{
		return ;
	}

	m_kSuccessVec.clear();
	m_kFailVec.clear();

	//SMC가 실행중이지 않는 넘은 제거한다.
	ContServerID kOnCommandVec;
	ContServerID::iterator Itr = kCommandVec.begin();
	while(Itr != kCommandVec.end())
	{
		CONT_SERVER_STATE_EX::iterator state_Itr = m_kTotalServerState.find(*Itr);
		if(state_Itr != m_kTotalServerState.end())
		{
			CONT_SERVER_STATE_EX::mapped_type kElement = state_Itr->second;
			if(IsValidSMC(kElement.kTbl.strMachinIP))
			{
				kOnCommandVec.push_back(*Itr);

				SMMCLog kLog;
				kLog.eLogType = MCL_SERVER_ON;
				FindGmID(pkSession->SessionKey(), kLog.kID);
				kLog.kLoginIP = pkSession->Addr().ToString();
				kLog.kSI = (*Itr);
				kLog.kMachineIP = kElement.kTbl.strMachinIP;
				PgMMCMgr::WriteToFileToolLog(kLog);
			}
		}
		++Itr;
	}

	std::sort(kOnCommandVec.begin(), kOnCommandVec.end(), CompareOnCommand);
//	m_kContOnCommand.insert(m_kContOnCommand.end(), kOnCommandVec.begin(), kOnCommandVec.end());
	CEL::SESSION_KEY kSession;	
	SendNfyCommandToSMC(kSession, MCT_SERVER_ON, kOnCommandVec);

}

bool PgMMCMgr::CheckOnCommand()
{
	BM::CAutoMutex kLock(m_kMutex);

	if( m_kContOnCommand.empty() )
	{
		return false;
	}

	ContServerID kCommandList;
	CONT_COMMAND_STACK::iterator Itr = m_kContOnCommand.begin();
	if(Itr != m_kContOnCommand.end())
	{
		if( m_kSuccessVec.size() > 0)
		{
			if( FindSuccessVec(*Itr) )
			{
				CONT_SERVER_STATE_EX::iterator state_Itr = m_kOldTotalServerState.find(*Itr);
				if(state_Itr != m_kOldTotalServerState.end())
				{		
					if(state_Itr->second.kProcessInfo.IsCorrect())
					{
						if( state_Itr->second.bIsException == false
							&& state_Itr->second.bReadyToService == true )
						{
							m_kContOnCommand.pop_front();
							if(m_kContOnCommand.begin() != m_kContOnCommand.end())
								kCommandList.push_back(*m_kContOnCommand.begin());
						}
					} 
					else
					{
						SERVER_IDENTITY kSI =  *Itr;
						switch(kSI.nServerType)
						{
						case CEL::ST_MAP:
							{
								//무시하고 담꺼 진행한다.
								m_kContOnCommand.pop_front();
								if(m_kContOnCommand.begin() != m_kContOnCommand.end())
									kCommandList.push_back(*m_kContOnCommand.begin());
							}break;
						default:
							{
								//스텍 초기화
								ClearCommandStack();
								return false;
							}break;
						}
						//어떤 서버에 문제가 생겼는지 알려준다.
						BM::CPacket kPacket(PT_MMC_TOOL_NFY_INFO, MCT_ERR_CMD);
						kSI.WriteToPacket(kPacket);
						Broadcast(kPacket);
					}
				}
			} 
		} 
		else
		{
			if(!FindSuccessVec(*Itr))
			{
				kCommandList.push_back(*Itr);
			}
		}
	} 
	else
	{
		m_kSuccessVec.clear();
		m_kFailVec.clear();
	}

	CEL::SESSION_KEY kSession;	
	return SendNfyCommandToSMC(kSession, MCT_SERVER_ON, kCommandList);
}

bool PgMMCMgr::CheckOffCommand()
{
	BM::CAutoMutex kLock(m_kMutex);

	if( m_kContOffCommand.empty() )
	{
		return false;
	}

	ContServerID kCommandList;
	CONT_COMMAND_STACK::iterator Itr = m_kContOffCommand.begin();
	if(Itr != m_kContOffCommand.end())
	{
		CONT_SERVER_STATE_EX::iterator state_Itr = m_kOldTotalServerState.find(*Itr);
		if(state_Itr != m_kOldTotalServerState.end())
		{
			if( state_Itr->second.kProcessInfo.IsCorrect())
			{
				if( state_Itr->second.bIsException == false
					&& state_Itr->second.bReadyToService == true )
				{
					kCommandList.push_back(*Itr);
					if(m_kContOffCommand.size() > 1)
						m_kContOffCommand.pop_front();
					else m_kContOffCommand.clear();
				}				
			} 
			else
			{
				if(m_kContOffCommand.size() > 1)
					m_kContOffCommand.pop_front();
				else m_kContOffCommand.clear();
				return false;
			}
		}
	}

	BM::CPacket kPacket(PT_MCTRL_MMC_A_NFY_SERVER_COMMAND, MCC_Shutdown_Service);
	ContServerID::iterator Send_Itr = kCommandList.begin();
	while(Send_Itr != kCommandList.end())
	{
		Send_Itr->WriteToPacket(kPacket);
		g_kProcessCfg.Locked_SendToServerType(CEL::ST_IMMIGRATION, kPacket);
		++Send_Itr;
	}
	return true;	
}


void PgMMCMgr::ClearCommandStack()
{
	BM::CAutoMutex Lock(m_kMutex);

	m_kContOnCommand.clear();
	m_kContOffCommand.clear();
	m_kContSendCommand.clear();
	m_kSuccessVec.clear();
	m_kFailVec.clear();
}

void PgMMCMgr::AddSmcSession(CEL::CSession_Base *pkSession, SERVER_IDENTITY const &kSI)
{
	BM::CAutoMutex Lock(m_kMutex);
	m_kSMCState.insert(std::make_pair(pkSession, kSI));
}

void PgMMCMgr::RemoveSmcSession(CEL::CSession_Base *PKSession)
{
	BM::CAutoMutex Lock(m_kMutex);
	CONT_SMC_STATE::iterator Itr = m_kSMCState.find(PKSession);
	if(Itr != m_kSMCState.end())
	{
		m_kSMCState.erase(Itr);
	}
}

bool PgMMCMgr::IsValidSMC(const std::wstring &kSMCAddr)
{
	BM::CAutoMutex Lock(m_kMutex);

	CONT_SMC_STATE::iterator Itr = m_kSMCState.begin();
	while(Itr != m_kSMCState.end())
	{
		CONT_SMC_STATE::key_type const &kKey = Itr->first;
		if(kSMCAddr == kKey->Addr().IP())
			return true;
		++Itr;
	}

	return false;
}

bool PgMMCMgr::FindSuccessVec(const SERVER_IDENTITY &kSI)
{
	BM::CAutoMutex Lock(m_kMutex);
	ContServerID::iterator Itr = m_kSuccessVec.begin();
	while(Itr != m_kSuccessVec.end())
	{
		SERVER_IDENTITY kValue = *Itr;
		if(kValue == kSI)
		{
			return true;
		}
		++Itr;
	}

	return false;
}

void PgMMCMgr::WriteToPacketSMCInfo(BM::CPacket &rkPacket) const
{
	BM::CAutoMutex Lock(m_kMutex);

	rkPacket.Push( (int)m_kSMCState.size() );
	CONT_SMC_STATE::const_iterator Itr = m_kSMCState.begin();
	while(Itr != m_kSMCState.end())
	{
		CONT_SMC_STATE::key_type const &kKey = Itr->first;
		CONT_SMC_STATE::mapped_type const &kElement = Itr->second;
		rkPacket.Push(kKey->Addr().IP());
		kElement.WriteToPacket(rkPacket);
		++Itr;
	}
}

bool PgMMCMgr::FindRunServers(CEL::CSession_Base *pkSMCSession, ContServerID  &rkOut) const
{
	BM::CAutoMutex kLock(m_kMutex);

	CONT_SERVER_HASH kContSerer;
	std::wstring kSMC_IP = pkSMCSession->Addr().IP();
	g_kProcessCfg.Locked_GetServerInfo(CEL::ST_NONE, kContSerer);

	CONT_SMC_STATE::const_iterator SMC_Itr =  m_kSMCState.find(pkSMCSession);
	CONT_SERVER_HASH::const_iterator server_itor = kContSerer.begin();

	if( SMC_Itr == m_kSMCState.end() || server_itor == kContSerer.end() )
	{
		rkOut.clear();
		return false;
	}

	while(server_itor != kContSerer.end())
	{
		CONT_SERVER_HASH::mapped_type kElement = server_itor->second;
		CONT_SERVER_HASH::key_type kKey = server_itor->first;
		if(kSMC_IP == kElement.strMachinIP
			&& kElement.nServerType != CEL::ST_SUB_MACHINE_CONTROL
			&& kElement.nServerType != CEL::ST_MACHINE_CONTROL)
		{
			rkOut.push_back(kKey);
		}
		++server_itor;
	}
	
	return true;
}

bool PgMMCMgr::IsCurrentGmUser(const std::wstring &kID) const
{
	bool bRet = true;

	BM::CAutoMutex kLock(m_kMutex);
	ContTermianlAuthInfo::const_iterator Itr = m_kUserAuthInfo.find(kID);
	if(Itr == m_kUserAuthInfo.end())
	{
		bRet = false;
	}

	ContTermianlAuthInfo::mapped_type kElement = Itr->second;
	if(kElement.cGrant == 0)
	{
		bRet = false;
	}

	return bRet;
}




HRESULT PgMMCMgr::OnConnectMonTool(CEL::CSession_Base* pkSession, std::wstring const &kID)
{
	if( !pkSession )
	{
		return E_FAIL;
	}

	BM::CAutoMutex kLock(m_kMutex);

	SMonToolInfo kMonToolInfo;
	kMonToolInfo.kSessionKey = pkSession->SessionKey();
	kMonToolInfo.kAddr = pkSession->Addr();
	
	CONT_MON_TOOL_SESSION::_Pairib kRet = m_kMonToolSession.insert( std::make_pair(kID, kMonToolInfo) );
	if( kRet.second )
	{
		pkSession->m_kSessionData.Push(kID);//ID 기록
		return S_OK;
	}
	return E_FAIL;
}

bool PgMMCMgr::OnDisconnectMonTool(CEL::CSession_Base* pkSession)
{
	BM::CAutoMutex kLock(m_kMutex);
	
	std::wstring kID;
	pkSession->m_kSessionData.Pop(kID);

	m_kMonToolSession.erase(kID);

	SMMCLog kLog;
	kLog.eLogType = MCL_GM_LOGOUT;
	kLog.kID = kID;
	kLog.kLoginIP = pkSession->Addr().ToString();
	WriteToFileToolLog(kLog);

	return true;
}

void PgMMCMgr::Broadcast(BM::CPacket &kPacket)const
{
	BM::CAutoMutex kLock(m_kMutex);
	CONT_MON_TOOL_SESSION::const_iterator tool_itor = m_kMonToolSession.begin();
	
	while(tool_itor != m_kMonToolSession.end())
	{
		g_kCoreCenter.Send((*tool_itor).second.kSessionKey, kPacket);
		++tool_itor;
	}
}

bool PgMMCMgr::IsConnectionTool() const
{
	BM::CAutoMutex kLock(m_kMutex);

	if(m_kMonToolSession.size() > 0)
	{
		return true;
	}
	return false;
}

void PgMMCMgr::Locked_DisConnectionAll()
{
	BM::CAutoMutex kLock(m_kMutex);

	CONT_MON_TOOL_SESSION::iterator Itr = m_kMonToolSession.begin();
	while(Itr != m_kMonToolSession.end())
	{
		BM::CPacket kPacket;
		kPacket.SetStopSignal(true);
		g_kCoreCenter.Send(Itr->second.kSessionKey, kPacket);		
		++Itr;
	}
	m_kMonToolSession.clear();
}

void PgMMCMgr::GetSyncPath(CON_SYNC_PATH &kOut)const
{
	BM::CAutoMutex kLock(m_kMutex);
	kOut = m_kSyncPath;
}

bool PgMMCMgr::FindGmID(CEL::SESSION_KEY const &kSessionKey, std::wstring &rkOut) const
{
	BM::CAutoMutex kLock(m_kMutex);

	CONT_MON_TOOL_SESSION::const_iterator Itr = m_kMonToolSession.begin();
	while(Itr != m_kMonToolSession.end())
	{
		CONT_MON_TOOL_SESSION::mapped_type kElement = Itr->second;
		CONT_MON_TOOL_SESSION::key_type const &kKey = Itr->first;
		if(kElement.kSessionKey == kSessionKey)
		{
			rkOut = kKey;
			return true;
		}
		++Itr;
	}
	return false;
}

bool PgMMCMgr::IsAllowedSessionKey(CEL::SESSION_KEY const &kSessionKey) const
{
	BM::CAutoMutex kLock(m_kMutex);

	std::wstring kID;
	if(FindGmID(kSessionKey, kID))
	{
		if(IsCurrentGmUser(kID))
		{
			return true;
		} 
		else
		{
			return false;
		}
	} 
	else
	{
		return false;
	}
}

bool PgMMCMgr::WriteToFileToolLog(SMMCLog const &kMMCLog)
{
	std::wstring kLogData;
	kLogData = kMMCLog.kID + L", " + kMMCLog.kLoginIP + L", ";

	switch(kMMCLog.eLogType)
	{
	case MCL_GM_LOGIN:
		{
			kLogData += L"GM_LOGIN";
		}break;
	case MCL_GM_LOGOUT:
		{
			kLogData += L"GM_LOGOUT";
		}break;
	case MCL_SERVER_ON:
		{
			std::wstring kServerInfo;
			ServerInfoToSTR(kMMCLog.kSI, kServerInfo);
			kLogData += L"SERVER_ON, " + kServerInfo + L"," + kMMCLog.kMachineIP;
		}break;
	case MCL_SERVER_OFF:
		{
			std::wstring kServerInfo;
			ServerInfoToSTR(kMMCLog.kSI, kServerInfo);
			kLogData += L"SERVER_OFF, " + kServerInfo + L"," + kMMCLog.kMachineIP;
		}break;
	case MCL_SERVER_SHUTDOWN:
		{
			std::wstring kServerInfo;
			ServerInfoToSTR(kMMCLog.kSI, kServerInfo);
			kLogData += L"SERVER_SHUTDOWN, " + kServerInfo + L"," + kMMCLog.kMachineIP;
		}break;
	case MCL_RE_SYNC_START:
		{
			kLogData += L"RE_SYNC_START, " + kMMCLog.kMachineIP;
		}break;
	case MCL_RESYNC_END:
		{
			kLogData += L"RE_SYNC_END" + kMMCLog.kMachineIP;
		}break;
	case MCL_CHANGE_MAX_USER:
		{
			std::wstring kServerInfo;
			ServerInfoToSTR(kMMCLog.kSI, kServerInfo);
			wchar_t buff[50];
			wsprintf(buff, L"Change User Count = %d", kMMCLog.iUserMaxCount);

			kLogData += L"CHANGE_MAXUSER, " + kServerInfo + L"," + buff;
		}break;
	default:{}break;
	}

	m_kFileLog.Log(BM::LOG_LV5,  kLogData.c_str());

	return true;
}

void PgMMCMgr::ServerInfoToSTR(SERVER_IDENTITY const &kSI, std::wstring &rkOut)
{
	wchar_t buff[50];
	wsprintf(buff, L"RealmNo: %d, ChannelNo: %d, ServerNo: %d", kSI.nRealm, kSI.nChannel, kSI.nServerNo);

	rkOut = buff;

	switch(kSI.nServerType)
	{
	case CEL::ST_IMMIGRATION:
		{
			rkOut += L", ServerType: Immigration Server, ";
		}break;
	case CEL::ST_CONTENTS:
		{
			rkOut += L", ServerType: Contents Server, ";
		}break;
	case CEL::ST_CENTER:
		{
			rkOut += L", ServerType: Center Server, ";
		}break;
	case CEL::ST_SWITCH:
		{
			rkOut += L", ServerType: Switch Server, ";
		}break;
	case CEL::ST_LOGIN:
		{
			rkOut += L", ServerType: Login Server, ";
		}break;
	case CEL::ST_LOG:
		{
			rkOut += L", ServerType: Log Server, ";
		}break;
	case CEL::ST_MAP:
		{
			rkOut += L", ServerType: Map Server, ";
		}break;
	case CEL::ST_GMSERVER:
		{
			rkOut += L", ServerType: GM Server, ";
		}break;
	case CEL::ST_AP:
		{
			rkOut += L", ServerType: AP Server, ";
		}break;
	default:
		{
			rkOut.clear();
		}break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
