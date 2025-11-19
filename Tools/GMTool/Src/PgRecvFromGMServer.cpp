#include "stdafx.h"
#include "PgNetwork.h"
#include "GMTool.h"
#include "GMToolDlg.h"
#include "PgUserListMgr.h"
#include "GeneralDlg.h"
#include "PgRecvFromGMServer.h"

BM::GUID g_kGMServerConnectorGuid; //Connector Guid
BM::GUID g_kGMServerSessionGuid;

void ProcessRecvFromGMServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);
void ProcessRecvFromCenter(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);


void CALLBACK OnConnectToGMServer(CEL::CSession_Base *pkSession)
{	//!  세션락
	const bool bIsSucc = pkSession->IsAlive();
	if( bIsSucc )
	{
		g_kGMServerConnectorGuid = pkSession->ParentKey();
		g_kGMServerSessionGuid = pkSession->Key();
		return;
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Connect To GMServer Failed.  Connect Retry!"), _T(__FUNCTION__), __LINE__);
		g_kNetwork.ConnectGMServer();
		g_kNetwork.m_bConnected = false;
		return;
	}
}

void CALLBACK OnDisconnectFromGMServer(CEL::CSession_Base *pkSession)
{//!  세션락
	INFO_LOG(BM::LOG_LV3, _T("[%s]-[%d] 접속 종료"), _T(__FUNCTION__), __LINE__);
	ConsoleCommander.StopSignal(true);
}

void CALLBACK OnRecvFromGMServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{
	static int i = 0;
	INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] 패킷 받음 : %d, %d"), _T(__FUNCTION__), __LINE__, i++, pkPacket->Size());

	unsigned short usType = 0;
	pkPacket->Pop(usType);
	
	switch(usType)
	{
	case PT_A_ENCRYPT_KEY:
		{// 중앙에서 암호키<PT_A_ENCRYPT_KEY>가 도착 했다
			std::vector<char> kKey;
			pkPacket->Pop(kKey);
			
			if(S_OK != pkSession->SetEncodeKey(kKey))
			{
				INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Incoreect EncodeKey Session Terminate"), _T(__FUNCTION__), __LINE__ );
				pkSession->VTerminate();
			}
		}break;
	case PT_A_S_ANS_GREETING:
		{// 중앙 머신컨트롤러로 부터 응답이 왔다.
			//중앙 머신 컨트롤러부터 Greeting 인사를 받았다.
			INFO_LOG(BM::LOG_RED, _T("PT_A_S_ANS_GREETING"));

			//// TODO: 중앙에 서버 리스트 요청 한다.
			//CEL::CPacket kPacket(PT_GMServer_T_C_REQ_SERVERLIST);
			//pkSession->VSend(kPacket);
		}break;
	case PT_G_O_ANS_GMCOMMAND:
		{
			// GM서버에서 답변을 줄때 여기를 온다.
			ProcessRecvFromGMServer(pkSession, pkPacket);
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
	BM::GUID kReqGuid;
	pkPacket->Pop(eCommand);

	INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] 패킷 받음 T[%d] Size[%d]"), _T(__FUNCTION__), __LINE__ , eCommand, pkPacket->Size());

	switch (eCommand)
	{
	case EGMC_MATCH_GMID:
		{
			SReqSwitchReserveMember kMember;
			pkPacket->Pop(kMember);
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Login success. Grade:%d"), _T(__FUNCTION__), __LINE__, kMember.byGrade);

			// GM 툴 실행
			g_kGMTooldlg.ExcuteGM();
		}break;
	case EGMC_GET_USERLIST:
		{
			// GM툴 데이터가 왔다.
			unsigned short usChannel = 0;
			pkPacket->Pop(usChannel);
			unsigned int uiCount = g_kUserListMgr.RefreshUserList(pkPacket);

			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Recv User List. Channel:%d Users:%d"), _T(__FUNCTION__), __LINE__, usChannel, uiCount);
		}break;
	case EGMC_SENDMSG_TO_GM:
		{
			std::wstring kChat;
			pkPacket->Pop(kChat);
			g_kGeneralDlg.GetMainSheet()->m_kPage_QA.AddMsg(kChat);
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Recv User Chat. %s"), _T(__FUNCTION__), __LINE__, kChat.c_str());
		}break;
	default :
		{
			INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] GMServer Send Incorrect SubPacket : %d"), _T(__FUNCTION__), __LINE__, eCommand );
		}break;
	}
}
