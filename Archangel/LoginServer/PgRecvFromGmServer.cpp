#include "stdafx.h"
#include "PgRecvFromImmigration.h"
#include "PgRecvFromGM.h"
#include "PgRecvFromUser.h"
#include "PgLoginUserMgr.h"
#include "PgSendWrapper.h"
#include "Variant/PgLogAction.h"
#include "Variant/PgMctrl.h"
#include "Variant/GM_Const.h"

void CALLBACK OnAcceptFromGMServer(CEL::CSession_Base *pkSession)
{	//!  세션락
	std::vector<char> kEncodeKey;
	if(S_OK == pkSession->VGetEncodeKey(kEncodeKey))
	{
		INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Send EncryptKey"), __FUNCTIONW__, __LINE__);

		CEL::CPacket kPacket(PT_A_ENCRYPT_KEY);
		kPacket.Push(kEncodeKey);

		pkSession->VSend(kPacket, false);
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Get EncryptKey Failed. Session Terminate!"), __FUNCTIONW__, __LINE__);
		pkSession->VTerminate();
	}
}
void CALLBACK OnDisConnectToGmServer(CEL::CSession_Base *pkSession)
{//!  세션락
	INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Close Session Success"), __FUNCTIONW__, __LINE__);
	g_kProcessCfg.Locked_OnDisconnectServer(pkSession);
	g_kLoginUserMgr.ClearGmUserData();
}

void CALLBACK OnRecvFromGmServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{	// 세션키로 해당 채널을 찾아 메시지를  multiplexing 함.
	unsigned short usType = 0;
	pkPacket->Pop(usType);

	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Recved Start[%d]"), __FUNCTIONW__, __LINE__, usType );

	switch( usType )
	{
	case PT_A_S_REQ_GREETING:
		{
			SERVER_IDENTITY kRecvSI;
			kRecvSI.ReadFromPacket(*pkPacket);


			std::wstring strVersion;
			pkPacket->Pop(strVersion);
			if(strVersion != PACKET_VERSION)
			{
				//VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s]-[%d] Incorrect Version[%s]"), __FUNCTIONW__, __LINE__, strVersion.c_str());
				INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] Incorrect Version[%s]"), __FUNCTIONW__, __LINE__, strVersion.c_str());
				pkSession->VTerminate();
				return;
			}

			if(S_OK != g_kProcessCfg.Locked_OnGreetingServer(kRecvSI, pkSession))
			{
				//VERIFY_INFO_LOG(false, BM::LOG_LV5, _T("[%s]-[%d] Add Server Session Failed Realm[%d] Chn[%d] No[%d] Type[%d] "), __FUNCTIONW__, __LINE__, kRecvSI.nRealm, kRecvSI.nChannel, kRecvSI.nServerNo, kRecvSI.nServerType);
				INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] Add Server Session Failed Realm[%d] Chn[%d] No[%d] Type[%d] "), __FUNCTIONW__, __LINE__, kRecvSI.nRealm, kRecvSI.nChannel, kRecvSI.nServerNo, kRecvSI.nServerType);
				pkSession->VTerminate();//세션 끊음.
				return;
			}

			if(SetSendWrapper(kRecvSI))
			{
				CEL::CPacket kSendPacket(PT_A_S_ANS_GREETING);
				SERVER_IDENTITY const &kSendSI = g_kProcessCfg.ServerIdentity();
				kSendSI.WriteToPacket(kSendPacket);
				pkSession->VSend(kSendPacket);
			}
		}break;
	case PT_L_O_ANS_TRY_GM_LOGIN:
		{
			g_kLoginUserMgr.ProcessGmLogin(pkPacket);
		}break; 
	case PT_G_O_ANS_GMCOMMAND:
		{
			BM::GUID kReqGuid;
			pkPacket->Pop(kReqGuid);
			CEL::CPacket kPacket(PT_G_O_ANS_GMCOMMAND);
			kPacket.Push(*pkPacket);
			g_kLoginUserMgr.SendToGmUser(kReqGuid, kPacket);			
		}break;	default:
		{
		}break;
	}
}
