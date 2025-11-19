#include "stdafx.h"
#include "PgRecvFromImmigration.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "PgRecvFromSMC.h"
#include "PgSendWrapper.h"
#include "Lohengrin/PgRealmManager.h"
#include "PgRecvFromMonTool.h"

void CALLBACK OnConnectToImmigration(CEL::CSession_Base *pkSession)
{	//!  技记遏
	bool const bIsSucc = pkSession->IsAlive();
	if(bIsSucc)
	{	
		INFO_LOG(BM::LOG_LV6, __FUNCTIONW__ << _T("Connect to Immigration Server Success [") << pkSession->Addr().ToString().c_str() << _T("]") );
//		INFO_LOG(BM::LOG_LV6, _T("[%s] Connect to Immigration Server Success [%s]"), __FUNCTIONW__, );
	}
	else
	{
//		INFO_LOG(BM::LOG_LV1, __FUNCTIONW__ << _T("Failed Connect to Immigration") );
//		INFO_LOG(BM::LOG_LV1, _T("[%s] Failed Connect to Immigration"), __FUNCTIONW__);
		g_kProcessCfg.Locked_ConnectImmigration();
	}
}

void CALLBACK OnDisConnectToImmigration(CEL::CSession_Base *pkSession)
{//!  技记遏
	INFO_LOG(BM::LOG_LV6, __FL__ << _T("Close Session Success") );
//	INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Close Session Success"), __FUNCTIONW__, __LINE__);
	g_kProcessCfg.Locked_OnDisconnectServer(pkSession);
	g_kProcessCfg.Locked_ConnectImmigration();
}

void CALLBACK OnRecvFromImmigration(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket)
{
	BM::CPacket::DEF_PACKET_TYPE usType = 0;
	pkPacket->Pop(usType);

//	INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Recved Start[%d]"), __FUNCTIONW__, __LINE__, usType );

	switch( usType )
	{
	case PT_A_ENCRYPT_KEY:
		{
			CProcessConfig::Recv_PT_A_ENCRYPT_KEY(pkSession, pkPacket);
		}break;
	case PT_A_S_ANS_GREETING:
		{
			SERVER_IDENTITY kRecvSI;
			kRecvSI.ReadFromPacket(*pkPacket);

			if(S_OK == g_kProcessCfg.Locked_OnGreetingServer(kRecvSI, pkSession))//捞 技记捞 IMMIGRATION 狼 技记
			{
				SetSendWrapper(kRecvSI);
/*				HRESULT const hRet = g_kProcessCfg.Locked_Read_ServerList(*pkPacket);
				if( SUCCEEDED(hRet) )
				{
					g_kRealmMgr.ReadFromPacket(*pkPacket);
					if(S_OK == g_kProcessCfg.Locked_OnGreetingServer(kRecvSI, pkSession))//捞 技记捞 IMMIGRATION 狼 技记
					{
						if(SetSendWrapper(kRecvSI))
						{
							SERVER_IDENTITY const &kSI = g_kProcessCfg.ServerIdentity();
							TBL_SERVERLIST kServerInfo;
							if(S_OK == g_kProcessCfg.Locked_GetServerInfo(kSI, kServerInfo))
							{
								g_kMMCMgr.PrepareStateCont();
								RegistAcceptor(kServerInfo);
								return;
							}
							else
							{
								VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] MAIN Management Server No Acceptor info"), __FUNCTIONW__, __LINE__);
								return;
							}

						}
					}
				}
*/			}
		}break;
	case PT_MCTRL_A_MMC_ANS_SERVER_COMMAND:
		{
			E_IMM_MCC_CMD_TYPE eCmdType;
			pkPacket->Pop(eCmdType);
			g_kMMCMgr.RecvInfoFromImm(pkSession, eCmdType, pkPacket);
		}break;
	default:
		{
			INFO_LOG( BM::LOG_LV0, __FL__ << _T(" Invailed Packet Type [") << usType << _T("]")  );
//			INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Invailed Packet Type [%d]"), __FUNCTIONW__, __LINE__, usType );
		}break;
	}
//	INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Recved End [%d]"), __FUNCTIONW__, __LINE__, usType );
}