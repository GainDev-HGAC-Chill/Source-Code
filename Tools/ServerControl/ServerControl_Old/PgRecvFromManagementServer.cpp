#include "stdafx.h"
#include "PgNetwork.h"
#include "PgGameServerMgr.h"
#include "GeneralDlg.h"
#include "PgRecvFromManagementServer.h"
#include "PgSendWrapper.h"
#include "Lohengrin/PgRealmManager.h"
#include "ServerControlDlg.h"

//BM::GUID g_kManagementServerConnectorGuid; //Connector Guid
//BM::GUID g_kManagementServerSessionGuid;
CEL::SESSION_KEY g_kManagementServerSeesionKey;

extern std::wstring g_kID;
extern std::wstring g_kPW;

void CALLBACK OnConnectToManagementServer(CEL::CSession_Base *pkSession)
{	//!  세션락
	const bool bIsSucc = pkSession->IsAlive();
	if( bIsSucc )
	{
		//g_kManagementServerConnectorGuid = pkSession->SessionKey().WorkerGuid();
		//g_kManagementServerSessionGuid = pkSession->SessionKey().SessionGuid();
		g_kManagementServerSeesionKey = pkSession->SessionKey();
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Connect To CenterManagementServer Failed.  Connect Retry!"), _T(__FUNCTION__), __LINE__);
		g_kNetwork.Connected(false);
		MessageBox(NULL, _T("Can't Connect Server"), _T("ERROR"), MB_OK);
	}
}

void CALLBACK OnDisconnectFromManagementServer(CEL::CSession_Base *pkSession)
{//!  세션락
	INFO_LOG(BM::LOG_LV3, _T("[%s]-[%d] 접속 종료"), _T(__FUNCTION__), __LINE__);

	g_kGameServerMgr.Clear();
	if( g_pkGeneralDlg )
	{
		g_pkGeneralDlg->SetTreeView();

		if( g_kNetwork.Connected() )
		{
			g_pkGeneralDlg->ShowWindow(SW_HIDE);
		}
	}

	if( g_kNetwork.Connected() )//타의적
	{
		MessageBox(NULL, _T("Connection terminated from ManagementServer server"), _T("ERROR"), MB_OK);
		g_kNetwork.Connected(false);
	}
}

void CALLBACK OnRecvFromManagementServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{
	static int i = 0;
	//INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] 패킷 받음 : %d, %d"), _T(__FUNCTION__), __LINE__, i++, pkPacket->Size());

	unsigned short usType = 0;
	pkPacket->Pop(usType);
	
	switch(usType)
	{
	case PT_A_ENCRYPT_KEY:
		{// 중앙에서 암호키<PT_A_ENCRYPT_KEY>가 도착 했다
			std::vector<char> kKey;
			pkPacket->Pop(kKey);
			
			if(S_OK != pkSession->VSetEncodeKey(kKey))
			{
				INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Incoreect EncodeKey Session Terminate"), _T(__FUNCTION__), __LINE__ );
				pkSession->VTerminate();
			}
			else
			{//인사를 하자.
				INFO_LOG(BM::LOG_RED, _T("SEND GREETING"));

				CEL::CPacket kPacket(PT_A_S_REQ_GREETING);
				kPacket.Push(g_kID);
				kPacket.Push(g_kPW);
				pkSession->VSend(kPacket);

				g_kID.clear();
				g_kPW.clear();
			}
		}break;
	case PT_A_S_ANS_GREETING:
		{// 중앙 머신컨트롤러로 부터 응답이 왔다.
			//중앙 머신 컨트롤러부터 Greeting 인사를 받았다.
			INFO_LOG(BM::LOG_RED, _T("PT_A_S_ANS_GREETING"));

			SERVER_IDENTITY kRecvSI;
			kRecvSI.ReadFromPacket(*pkPacket);
			g_kProcessCfg.Read_ServerList(*pkPacket);
			g_kRealmMgr.ReadFromPacket(*pkPacket);

			if(SetSendWrapper(kRecvSI))
			{
				int hRet = E_FAIL;
				pkPacket->Pop(hRet);
				if( S_OK == hRet )
				{
					if( g_pkGeneralDlg )
					{
						g_pkGeneralDlg->ShowWindow(SW_SHOW);
					}

					// 중앙에 서버 리스트 요청 한다.
					CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_SERVERLIST);
					pkSession->VSend(kPacket);
				}
				else
				{
					MessageBox(NULL, _T("Check Auth Info"), _T("Auth fail"), MB_OK);
					g_kNetwork.DisConnectServer();
				}
				return;
			}
			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s]-[%d] Add Server Session Failed Realm[%d] Chn[%d] No[%d] Type[%d] "), __FUNCTIONW__, __LINE__, kRecvSI.nRealm, kRecvSI.nChannel, kRecvSI.nServerNo, kRecvSI.nServerType);
		}break;
	case PT_MCTRL_MMS_TERMI_ANS_SERVERLIST :
		{
			// 리스트 출력
			g_kGameServerMgr.SetServerList(pkPacket);
			if( g_pkGeneralDlg )
			{
				g_pkGeneralDlg->SetTreeView();
//				g_pkGeneralDlg->ServerRefresh();
			}
		}break;
	default:
		{
		};
	}
}
