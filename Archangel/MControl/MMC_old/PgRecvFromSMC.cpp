#include "stdafx.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "PgRecvFromSMC.h"
#include "PgRecvFromMonTool.h"
#include "PgSendWrapper.h"
#include "DataPack/Common.h"
#include "BM/TimeCheck.h"
#include "BM/FileSupport.h"
#include "Lohengrin/BuildNumber.h"

extern void Recv_PT_SMC_MMC_REQ_DATA_SYNC_INFO(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);
//extern void Recv_PT_SMC_MMC_REQ_DATA_SYNC_START(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);

void CALLBACK OnAcceptFromSMC(CEL::CSession_Base *pkSession)
{
	std::vector<char> kEncodeKey;//여기는 <중앙> 서브로 암호키(PT_A_ENCRYPT_KEY)를 보내자
	if( S_OK == pkSession->VGetEncodeKey(kEncodeKey) )
	{
		INFO_LOG(BM::LOG_LV6, __FL__ << _T(" Send EncryptKey To Sub") );
//		INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Send EncryptKey To Sub"), __FUNCTIONW__, __LINE__);

		BM::CPacket kPacket(PT_A_ENCRYPT_KEY);
		kPacket.Push(kEncodeKey);

		pkSession->VSend(kPacket, false);
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, __FL__ << _T(" Get EncryptKey Failed. Session Terminate!") );
//		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Get EncryptKey Failed. Session Terminate!"), __FUNCTIONW__, __LINE__);
		pkSession->VTerminate();
	}
}

void CALLBACK OnDisConnectToSMC(CEL::CSession_Base *pkSession)
{
	INFO_LOG(BM::LOG_LV6, __FL__ << _T(" Close Session Success") );
//	INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Close Session Success"), __FUNCTIONW__, __LINE__);
	g_kProcessCfg.Locked_OnDisconnectServer(pkSession);

	g_kMMCMgr.RemoveSyncIngSession(pkSession);
	g_kMMCMgr.RemoveSmcSession(pkSession);
}

void Recv_PT_A_S_REQ_GREETING(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket)
{
 	SERVER_IDENTITY kRecvSI;
	kRecvSI.ReadFromPacket(*pkPacket);
	
	std::wstring wstrVersion;
	pkPacket->Pop(wstrVersion);

	//Packet Version 체크 필요 없음
/*
	if( wstrVersion != PACKET_VERSION )
	{
		INFO_LOG(BM::LOG_LV5, _T("Incorrect Packet Version[%s]"), wstrVersion.c_str());
		return;
	}
*/
	if(S_OK != g_kProcessCfg.Locked_OnGreetingServer(kRecvSI, pkSession))
	{
		INFO_LOG(BM::LOG_LV5, __FL__ << _T("Add Server Session Failed Realm[") <<  kRecvSI.nRealm << _T("] Chn[") 
			<< kRecvSI.nChannel << _T("] No[") << kRecvSI.nServerNo << _T("] Type[") << kRecvSI.nServerType << _T("] ") );
//		INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] Add Server Session Failed Realm[%d] Chn[%d] No[%d] Type[%d] "), __FUNCTIONW__, __LINE__, kRecvSI.nRealm, kRecvSI.nChannel, kRecvSI.nServerNo, kRecvSI.nServerType);
		pkSession->VTerminate();//세션 끊음.
		return;
	}

	g_kMMCMgr.AddSmcSession(pkSession, kRecvSI);

	bool bSendData = false;
	pkPacket->Pop(bSendData);

	kRecvSI.WriteToPacket(pkSession->m_kSessionData);//이 세션의 SERVER_IDENTITY 기록

	BM::CPacket kSendPacket(PT_A_S_ANS_GREETING);

	SERVER_IDENTITY const &kSendSI = g_kProcessCfg.ServerIdentity();
	//모든 서버에 보낼 내용
	//나의 서버 구분자.
	//전체 서버 리스트.
	kSendSI.WriteToPacket(kSendPacket);
	g_kProcessCfg.Locked_Write_ServerList(kSendPacket, kRecvSI.nRealm);

	switch(kRecvSI.nServerType)
	{
	case CEL::ST_SUB_MACHINE_CONTROL:
		{
			CON_SYNC_PATH kContPath;
			g_kMMCMgr.GetSyncPath(kContPath);

			g_kRealmMgr.WriteToPacket(kSendPacket, 0, ERealm_SendType_All);//로그인서버는 렐름정보 붙여줌.
			PU::TWriteTable_MM(kSendPacket, kContPath);
			kSendPacket.Push(g_kProcessCfg.RunMode());			//자신의 실행 모드를 전송.
			kSendPacket.Push(g_kMMCMgr.bUseSMCAutoPatch());
		}break;
	default:
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("Incorrect Server Type") );
//			VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Incorrect Server Type"), __FUNCTIONW__, __LINE__);
			pkSession->VTerminate();//세션 끊음.
			return;
		}break;
	}

	pkSession->VSend(kSendPacket);
}

void CALLBACK OnRecvFromSMC(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket)
{
	BM::CPacket::DEF_PACKET_TYPE usType = 0;
	pkPacket->Pop(usType);
	
	switch(usType)
	{
	case PT_A_S_REQ_GREETING:
		{
			Recv_PT_A_S_REQ_GREETING(pkSession, pkPacket);
		}break;
	case PT_SMC_MMC_ANS_CMD:
		{
			EMMC_CMD_TYPE eCmd;
			CEL::SESSION_KEY kCmdOwner;
			pkPacket->Pop(eCmd);
			pkPacket->Pop(kCmdOwner);

			g_kMMCMgr.RecvAnsFromSMC(pkSession, kCmdOwner, eCmd, pkPacket);
		}break;
	case PT_SMC_MMC_NFY_INFO:
		{
			EMMC_CMD_TYPE eCmd;
			pkPacket->Pop(eCmd);
			g_kMMCMgr.RecvInfoFromSMC(pkSession, eCmd, pkPacket);
		}break;
	case PT_SMC_MMC_REQ_DATA_SYNC_INFO:
		{
			SMMCLog kLog;
			kLog.eLogType = MCL_RE_SYNC_START;
			g_kMMCMgr.FindGmID(pkSession->SessionKey(), kLog.kID);
			kLog.kMachineIP = pkSession->Addr().ToString();
			PgMMCMgr::WriteToFileToolLog(kLog);
			
			Recv_PT_SMC_MMC_REQ_DATA_SYNC_INFO(pkSession, pkPacket);
		}break;
	case PT_SMC_MMC_REQ_GET_FILE:
		{
			std::wstring kFileName;
			pkPacket->Pop(kFileName);
			
			INFO_LOG(BM::LOG_LV2, _T("Recv[") << pkSession->Addr().IP().c_str() 
				<< _T("] GetFile Start[") << kFileName.c_str() << _T("]") );
//			INFO_LOG(BM::LOG_LV2, _T("Recv[%s] GetFile Start[%s]"), pkSession->Addr().IP().c_str(), kFileName.c_str());

			std::vector< char > kFileData;
			BM::FileToMem(kFileName, kFileData);
			
			BM::CPacket kPacket(PT_MMC_SMC_ANS_GET_FILE);
			kPacket.Push(kFileName);
			kPacket.Push(kFileData);
			pkSession->VSend(kPacket);
			
			INFO_LOG(BM::LOG_LV3, _T("Recv[") << pkSession->Addr().IP().c_str()
				<< _T("] GetFile End[") << kFileName.c_str() << _T("]") );
//			INFO_LOG(BM::LOG_LV3, _T("Recv[%s] GetFile End[%s]"), pkSession->Addr().IP().c_str(), kFileName.c_str());

//			Recv_PT_SMC_MMC_REQ_DATA_SYNC_START(pkSession, pkPacket);
		}break;
	case PT_SMC_MMC_ANS_DATA_SYNC_END:
		{
			bool bSMC_Sync = false;
			if(	pkPacket->Pop(bSMC_Sync)
			&&	!bSMC_Sync )
			{
				g_kMMCMgr.RemoveSyncIngSession(pkSession);
			}

			SMMCLog kLog;
			kLog.eLogType = MCL_RESYNC_END;
			g_kMMCMgr.FindGmID(pkSession->SessionKey(), kLog.kID);
			kLog.kMachineIP = pkSession->Addr().ToString();
			PgMMCMgr::WriteToFileToolLog(kLog);
		}break;
	case PT_MCTRL_A_MMC_ANS_SERVER_COMMAND:
		{
			E_IMM_MCC_CMD_TYPE eCmdType;
			pkPacket->Pop(eCmdType);
			g_kMMCMgr.RecvInfoFromImm(pkSession, eCmdType, pkPacket);
		}break;
	default:
		{
		}break;
	}
}

void Recv_PT_SMC_MMC_REQ_DATA_SYNC_INFO(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket)
{
	bool IsSMC_SyncStart = false;
	pkPacket->Pop(IsSMC_SyncStart);	

	PgTimeCheck kTime(g_aLog[0],__FUNCTIONW__, __LINE__);

	HANDLE hProcess = GetCurrentProcess();
	SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);

	BM::CPacket kSendPacket(PT_MMC_SMC_ANS_DATA_SYNC_INFO);
	kSendPacket.Push(IsSMC_SyncStart);
	if(IsSMC_SyncStart)
	{
		CON_SYNC_PATH kContPath;
		g_kMMCMgr.GetSyncPath(kContPath);

		CON_SYNC_PATH::const_iterator Itr = kContPath.find(CEL::ST_SUB_MACHINE_CONTROL);
		if(Itr == kContPath.end())
		{

			INFO_LOG(BM::LOG_LV0, _T("Find not SMC Patch Info in MMC.ini File"));
//			INFO_LOG(BM::LOG_LV0, _T("Find not SMC Patch Info in MMC.ini File"));
			//SMC로 SMC Sync가 실패 했다는걸 알린다.

		}

		CON_SYNC_PATH kSendPath;
		kSendPath.insert(std::make_pair(Itr->first, Itr->second));
		PU::TWriteTable_MM(kSendPacket, kSendPath);
		BM::FolderHash kMMCFolders;
		BM::PgDataPackManager::GetFileList((*Itr).second.kSrcPath, kMMCFolders);
		PU::TWriteTable_AM(kSendPacket, kMMCFolders);
	}
	else
	{
		//동작 금지. -> SMC 락.
		g_kMMCMgr.AddSyncIngSession(pkSession);

		CON_SYNC_PATH kContPath;
		g_kMMCMgr.GetSyncPath(kContPath);

		CON_SYNC_PATH kSendPath;
		ContServerID kSyncList;

		//default로 Config폴더는 항상 들어가야 한다.
		CON_SYNC_PATH::const_iterator Config_Itr = kContPath.find(CEL::ST_NONE);
		kSendPath.insert(std::make_pair(Config_Itr->first, Config_Itr->second));

		//SMC IP와 동일한 서버만 Sync하도록 한다.
		g_kMMCMgr.FindRunServers(pkSession, kSyncList);

		ContServerID::iterator SI_Itr = kSyncList.begin();
		while(SI_Itr != kSyncList.end())
		{
			CON_SYNC_PATH::const_iterator Itr = kContPath.find((CEL::E_SESSION_TYPE)SI_Itr->nServerType);
			if(Itr != kContPath.end())
			{
				kSendPath.insert(std::make_pair(Itr->first, Itr->second));
			}
			++SI_Itr;
		}

		PU::TWriteTable_MM(kSendPacket, kSendPath);


		//	kContPath 내용을 바꾸면 아래 싱크 폴더 정보가 바뀔수 있다.(필요한 것만 가능)
		CON_SYNC_PATH::const_iterator path_itor = kSendPath.begin();
		while(kSendPath.end() != path_itor)
		{
			BM::FolderHash kMMCFolders;
			BM::PgDataPackManager::GetFileList((*path_itor).second.kSrcPath, kMMCFolders);

			PU::TWriteTable_AM(kSendPacket, kMMCFolders);
			++path_itor;
		}
	}

	pkSession->VSend(kSendPacket);

	SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
	CloseHandle(hProcess);
}
/*
void Recv_PT_SMC_MMC_REQ_DATA_SYNC_START(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket)
{
	PgTimeCheck kTime(g_aLog[0],__FUNCTIONW__, __LINE__);

	CON_SYNC_PATH kContPath;
	PU::TLoadTable_MM(*pkPacket, kContPath);

	int iRet = 0;

	//	kContPath 내용을 바꾸면 아래 싱크 폴더 정보가 바뀔수 있다.(필요한 것만 가능)
	CON_SYNC_PATH::const_iterator path_itor = kContPath.begin();
	while(kContPath.end() != path_itor)
	{//받은 페어런트폴더를 기준으로.
		BM::FolderHash kContSyncNeed;
		PU::TLoadTable_AM(*pkPacket, kContSyncNeed);

		BM::FolderHash::const_iterator need_folder_itor = kContSyncNeed.begin();
		while(need_folder_itor != kContSyncNeed.end())
		{//폴더를 돌고
			BM::FileHash const &kFileHash = (*need_folder_itor).second.kFileHash;
			BM::FileHash::const_iterator file_itor = kFileHash.begin();
			while(file_itor != kFileHash.end())
			{//파일을 돌고
				std::vector< char > kFileData;
				std::wstring const strFullPath = (*need_folder_itor).first + file_itor->first;
				
				if(!BM::FileToMem(strFullPath, kFileData))
				{
					CAUTION_LOG(BM::LOG_LV1, _T("Sync Data Can't Read [%s]"), strFullPath.c_str());
					iRet = 1;
					goto __FAILED;
				}

				BM::CPacket kPacket(PT_MMC_SMC_ANS_DATA_SYNC_ELEMENT);
				kPacket.Push(strFullPath);
				kPacket.Push(kFileData);

				if(!pkSession->VSend(kPacket))
				{
					CAUTION_LOG(BM::LOG_LV1, _T("Sync Data Can't Send [%s]"), strFullPath.c_str());
					iRet = 2;
					goto __FAILED;
				}
				++file_itor;
			}
			::Sleep(1);
			++need_folder_itor;
		}
		++path_itor;
	}

__COMPLETE:
__FAILED:
	{
		BM::CPacket kSendPacket(PT_MMC_SMC_ANS_DATA_SYNC_END, iRet);
		pkSession->VSend(kSendPacket);
	}
}
*/
	
//싱크를 시작하면 MMC 가 해당 세션이 커멘드가 가능하다 안하다를 직접 판단 해서
//패킷을 대기큐에 쌓자.