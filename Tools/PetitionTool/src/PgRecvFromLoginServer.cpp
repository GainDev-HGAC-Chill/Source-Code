#include "stdafx.h"


UINT g_nRegMsg;
//BM::GUID g_kGMServerConnectorGuid; //Connector Guid
//BM::GUID g_kGMServerSessionGuid;

void ProcessRecvFromGMServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);


void CALLBACK OnConnectLoginServer(CEL::CSession_Base *pkSession)
{	//!  세션락
	const bool bIsSucc = pkSession->IsAlive();
	if( bIsSucc )
	{
		INFO_LOG(BM::LOG_LV6, _T("[%s] Connect Success [%s:%d]"), __FUNCTIONW__, pkSession->Addr().IP().c_str(), pkSession->Addr().wPort);
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Connect To LoginServer Failed. "), _T(__FUNCTION__), __LINE__);
		g_kNetwork.Connected(false);
		ShowMessageBox(NULL, 19996, 10001);
	}
}

void CALLBACK OnDisconnectFromLoginServer(CEL::CSession_Base *pkSession)
{//!  세션락 
	if(g_kNetwork.Connected())
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] DisConnect From LoginServer "), _T(__FUNCTION__), __LINE__);
		g_kNetwork.Connected(false);
//		ShowMessageBox(NULL, 19997, 10001);
	}

	if(theApp.m_pkPetitionDlg)
	{
		SendMessage(HWND_BROADCAST, g_nRegMsg, (WPARAM)MSG_DISCONNECTED_SERVER, 0);
	}
}

void CALLBACK OnRecvFromLoginServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{
	static int i = 0;
	INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] 패킷 받음 : %d, %d"), _T(__FUNCTION__), __LINE__, i++, pkPacket->Size());

	unsigned short usType = 0;
	pkPacket->Pop(usType);
	
	switch(usType)
	{
	case PT_A_ENCRYPT_KEY:
		{
			std::vector<char> kKey;
			pkPacket->Pop(kKey);
			
			if(S_OK != pkSession->VSetEncodeKey(kKey))
			{
				INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Incoreect EncodeKey Session Terminate"), _T(__FUNCTION__), __LINE__ );
				pkSession->VTerminate();
			}
			else
			{
				//Auth정보 전달
				CEL::CPacket kPacket(PT_O_L_REQ_TRY_GM_LOGIN);
				kPacket.Push(g_kProcessInfoMgr.m_kMyInfo);
				g_kNetwork.SendToLoginServer(kPacket);				
			}
		}break;
	case PT_G_O_ANS_GMCOMMAND:
		{
			// GM서버에서 답변을 줄때 여기를 온다.
			ProcessRecvFromGMServer(pkSession, pkPacket);
		}break;
	case PT_L_O_ANS_TRY_GM_LOGIN:
		{
			int iErrorCode = 0;

			pkPacket->Pop(iErrorCode);

			switch(iErrorCode)
			{
			//오예~~ 성공이다!!
			case GM_ERR_SUCCESS:
				{
					SAuthInfo kGmInfo;
					pkPacket->Pop(kGmInfo);
					INFO_LOG( BM::LOG_LV7, _T(" Login success. Grade:%d"),  kGmInfo.byGrade);
					//자신의 정보를 저장한다.
					g_kProcessInfoMgr.m_kMyInfo = kGmInfo;
					//랠름정보를 받고 서버 및 채널 정보를 셋팅하자.
					if(g_kRealmMgr.ReadFromPacket(*pkPacket))
					{
						//theApp.m_pkNoticDlg->StartNoticeDlg();
						theApp.m_pkPetitionDlg->StartPetitionDlg();
					}
				}break;
			//아이디 또는 패스워드가 틀렸구나!!
			case GM_ERR_WORNG_ID_OR_PW:
				{
					SAuthInfo kGmInfo;
					pkPacket->Pop(kGmInfo);
					INFO_LOG( BM::LOG_LV5, _T("[%s] is not register Id or Wrong Password"), kGmInfo.szID, kGmInfo.szPW);
					ShowMessageBox(NULL, 10004, 10001);
					OnDisconnectFromLoginServer(pkSession);
				}break;
			case GM_ERR_LOGINED_ID:
				{
					ShowMessageBox(NULL, 10010, 10001);
//					INFO_LOG( BM::LOG_LV5, _T("already exist Id"));
					OnDisconnectFromLoginServer(pkSession);
				}break;
			default:break;
			}
		}break;
	case PT_N_O_ANS_CHECK_LOGINED_USER:
		{
			bool bIsLogined = false;
			BM::GUID kPetitionGuid;
			pkPacket->Pop(bIsLogined);
			pkPacket->Pop(kPetitionGuid);

			if(bIsLogined)
			{
				CONT_PETITION_DATA rkAssingnData;
				g_kPetitionDataMgr.GetMyAssignData(rkAssingnData);

				CONT_PETITION_DATA::iterator Itr = rkAssingnData.begin();
				while(Itr != rkAssingnData.end())
				{
					if(Itr->m_PetitionId == kPetitionGuid)
					{
						CONT_PETITION_DATA::value_type * pkElement = &(*Itr);
						SendMessage(HWND_BROADCAST, g_nRegMsg, (WPARAM)MSG_CREATE_CHAT, (LPARAM)pkElement);
					}
					++Itr;
				}
			} 
			else
			{
				ShowMessageBox(NULL, 10007, 10001); 
			}
		}break;
	case PT_C_O_ANS_SEND_GM_CHAT:
		{
//			SendMessage(HWND_BROADCAST, g_nRegMsg, (WPARAM)MSG_RECV_USER_CHAT, (LPARAM)pkPacket);
			BM::GUID kPetitionGuid;
			std::wstring kSender;
			std::wstring kMsg;

			pkPacket->Pop(kPetitionGuid);
			pkPacket->Pop(kSender);
			pkPacket->Pop(kMsg);
			kSender += L":";
			kSender += kMsg;

			theApp.m_pkPetitionDlg->SendChatMessage(kPetitionGuid, kSender);
		}break;
	case PT_G_O_ANS_SERVER_ERROR:
		{
			CEL::eSessionType eType;
			pkPacket->Pop(eType);
			switch(eType)
			{
			case CEL::ST_GMSERVER:
				{
					ShowMessageBox(NULL, 19998, 10001);
				}break;
			default:
				{
					INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] UnKnown Server Type"), _T(__FUNCTION__), __LINE__, eType );					
				}break;
			}
			OnDisconnectFromLoginServer(pkSession);
		}break;
	default:
		{
			INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] GMServer Send Incorrect Packet : %d"), _T(__FUNCTION__), __LINE__, usType );
		};
	}
}

void ProcessRecvFromGMServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{
	EGMCommandType eCommand;
	pkPacket->Pop(eCommand);

	INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] 패킷 받음 T[%d] Size[%d]"), _T(__FUNCTION__), __LINE__ , eCommand, pkPacket->Size());

	switch (eCommand)
	{
	case EGMC_GET_GMLIST:
		{
			unsigned int uiCount = g_kProcessInfoMgr.RecvGmList(pkPacket);
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Recv GM User List. GM Users:%d"), _T(__FUNCTION__), __LINE__, uiCount);
		}break;
	case EGMC_GET_PETITIONDATA:
		{
			g_kPetitionDataMgr.RecvPetitionData(pkPacket);
			theApp.m_pkPetitionDlg->ReflashAll();
		}break;
	case EGMC_MODIFY_PETITIONDATA:
		{	
			g_kPetitionDataMgr.RecvUpdatePetitionData(pkPacket);
			theApp.m_pkPetitionDlg->ReflashAll();
		}break;
	case EGMC_CREATE_GM_ACCOUNT:
		{
			int iErrorCode;
			pkPacket->Pop(iErrorCode);
			switch (iErrorCode)
			{
			case GM_ERR_SUCCESS:
				{
					INFO_LOG( BM::LOG_LV6, _T("Success Create GM ID"));
					theApp.m_pkLoginDlg->m_pkAccountDlg->SendMessage(WM_CLOSE, 0, 0);
				}break;
			case GM_ERR_USING_ID:
				{
					ShowMessageBox(theApp.m_pkLoginDlg->m_pkAccountDlg->m_hWnd, 10008, 10001);
					INFO_LOG( BM::LOG_LV5, _T("already exist Id"));
					OnDisconnectFromLoginServer(pkSession);
				}break;
			case GM_ERR_USING_NAME:
				{
					ShowMessageBox(theApp.m_pkLoginDlg->m_pkAccountDlg->m_hWnd, 10009, 10001);
					INFO_LOG( BM::LOG_LV5, _T("already exist Id"));
					OnDisconnectFromLoginServer(pkSession);
				}break;
			default:break;
			}
		}break;
/*
	case EGMC_DISCONNECT_TOOL:
		{
			int iErrorCode = 0;
			pkPacket->Pop(iErrorCode);
			OnDisconnectFromLoginServer(pkSession);	
		}break;
*/
	default :
		{
			INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] GMServer Send Incorrect SubPacket : %d"), _T(__FUNCTION__), __LINE__, eCommand );
		}break;
	}
}
