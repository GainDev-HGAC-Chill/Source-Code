#include "stdafx.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "Lohengrin/PgRealmManager.h"
#include "PgRecvFromMonTool.h"
#include "PgRecvFromSMC.h"

void CALLBACK OnAcceptMonTool(CEL::CSession_Base *pkSession)
{
	{//여기는 <중앙> 터미널로 암호키(PT_A_ENCRYPT_KEY)를 보내자
		std::vector<char> kEncodeKey;
		if(S_OK == pkSession->VGetEncodeKey(kEncodeKey))
		{
			INFO_LOG(BM::LOG_LV6, __FL__ << _T("Send EncryptKey To MonTool") );
//			INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Send EncryptKey To MonTool"), __FUNCTIONW__, __LINE__);

			BM::CPacket kPacket(PT_A_ENCRYPT_KEY);
			kPacket.Push(kEncodeKey);

			pkSession->VSend(kPacket, false);
		}
		else
		{
			INFO_LOG(BM::LOG_LV6, __FL__ << _T("Get EncryptKey Failed. Session Terminate!") );
//			INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Get EncryptKey Failed. Session Terminate!"), __FUNCTIONW__, __LINE__);
			pkSession->VTerminate();
		}
	}
}

void CALLBACK OnDisConnectToMonTool(CEL::CSession_Base *pkSession)
{

	INFO_LOG(BM::LOG_LV3, __FL__ << _T("MonTool Disconnect [") << pkSession->Addr().ToString().c_str() << _T("]") );
//	INFO_LOG(BM::LOG_LV3, _T("[%s]-[%d] MonTool Disconnect [%s]"), __FUNCTIONW__, __LINE__, pkSession->Addr().ToString().c_str());
	g_kMMCMgr.OnDisconnectMonTool(pkSession);
}

void CALLBACK OnRecvFromMonTool(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket)
{
	static int i = 0;
	//std::cout<< "패킷 받음 (" << i++ <<") Size["<< pkPacket->Size() << "]"<< std::endl;

	BM::CPacket::DEF_PACKET_TYPE usType = 0;
	pkPacket->Pop(usType);
	
	switch(usType)
	{
	case PT_A_S_REQ_GREETING:
		{//여기는 <중앙> 터미널로 부터 인사가 왔다.

			std::wstring kID, kPW;
			pkPacket->Pop(kID);
			pkPacket->Pop(kPW);

			int const iCorrect = g_kMMCMgr.CheckAuthInfo(pkSession, kID, kPW);

			if(iCorrect)
			{
				BM::CPacket kPacket(PT_A_S_ANS_GREETING);
				SERVER_IDENTITY const &kSendSI = g_kProcessCfg.ServerIdentity();
				
				kSendSI.WriteToPacket(kPacket);
			//	g_kProcessCfg.Locked_Write_ServerList(kPacket);
				g_kRealmMgr.WriteToPacket(kPacket, 0, ERealm_SendType_All);
				g_kMMCMgr.WriteToPacketSMCInfo(kPacket);
				kPacket.Push((int)( (iCorrect)? S_OK: E_FAIL ));
				if(iCorrect == USE_COMMAND_LEVEL)
					kPacket.Push(true);
				else 
					kPacket.Push(false);
				pkSession->VSend(kPacket);
				if(S_OK == g_kMMCMgr.OnConnectMonTool(pkSession, kID))
				{
					SMMCLog kLog;
					kLog.eLogType = MCL_GM_LOGIN;
					kLog.kID = kID;
					kLog.kLoginIP = pkSession->Addr().ToString();
					PgMMCMgr::WriteToFileToolLog(kLog);

					return;
				}
			} 
			else
			{		
				INFO_LOG(BM::LOG_LV3, __FL__ << _T("invalid connect from [") << pkSession->Addr().ToString().c_str() << _T("]") );
				BM::CPacket kPacket(PT_ANS_MMC_TOOL_CMD_RESULT);
				int iErrorCode = 2;
				kPacket.Push(iErrorCode);
				pkSession->VSend(kPacket);
				pkSession->VTerminate();//끊자
			}
		}break;
	case PT_REQ_TOOL_MON_CMD:
		{
			EMMC_CMD_TYPE eCmdType;
			pkPacket->Pop(eCmdType);
			g_kMMCMgr.RecvMonToolCmd(pkSession, eCmdType, pkPacket);//커멘드와 응답은 별개.
		}break;
	default:
		{
		}break;;
	}
}