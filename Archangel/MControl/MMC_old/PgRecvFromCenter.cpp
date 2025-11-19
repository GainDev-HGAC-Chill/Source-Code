#include "stdafx.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "PgRecvFromCenter.h"
#include "PgRecvFromMonTool.h"
#include "PgRecvFromSMC.h"
#include "PgRecvFromImmigration.h"
#include "PgSendWrapper.h"

//
void CALLBACK OnConnectToCenter(CEL::CSession_Base *pkSession)
{
	bool const bIsSucc = pkSession->IsAlive();
	if( bIsSucc )
	{
		INFO_LOG(BM::LOG_LV3, _T("[%s]-[%d] Connect To Center Server Success"), __FUNCTIONW__, __LINE__);
		return;
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Connect To Center server Failed. Retry!."), __FUNCTIONW__, __LINE__);
		g_kProcessCfg.Locked_OnDisconnectServer(pkSession);
		g_kCenterMgr.ConnectCenterServer();
		return;
	}
}

void CALLBACK OnDisConnectToCenter(CEL::CSession_Base *pkSession)
{
	INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Disconnected Realm Server"), __FUNCTIONW__, __LINE__);
	g_kProcessCfg.Locked_OnDisconnectServer(pkSession);
	g_kCenterMgr.ConnectCenterServer();

}

void CALLBACK OnRecvFromCenter(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{

	unsigned short usType = 0;
	pkPacket->Pop(usType);

	switch(usType)
	{
	case PT_A_ENCRYPT_KEY:
		{
			CProcessConfig::Recv_PT_A_ENCRYPT_KEY(pkSession, pkPacket);
		}break;
	case PT_A_S_ANS_GREETING:
		{
			SERVER_IDENTITY kRecvSI;
			kRecvSI.ReadFromPacket(*pkPacket);
			SetSendWrapper(kRecvSI);
			g_kImmigrationMgr.IsCenterConnected = true;
		}break;
	case PT_MCTRL_A_MMC_ANS_SERVER_COMMAND:
		{
			g_kCenterMgr.RecvManagementServerCommand(pkSession, pkPacket);
		}break;
	default:
		{
			INFO_LOG(BM::LOG_LV1, _T("[%s]-[%d] invalid packet type : [%d]"), __FUNCTIONW__, __LINE__,usType);
		}break;
	}
}

PgCenterMgr::PgCenterMgr()
{
}

PgCenterMgr::~PgCenterMgr()
{
}

bool PgCenterMgr::ConnectCenterServer()
{
	INFO_LOG(BM::LOG_LV1, _T("[%s] Connect to Center Server"), __FUNCTIONW__);
	const CEL::ADDR_INFO& rkAddr = CenterServer();
	return g_kCoreCenter.Connect(rkAddr, m_kSessionKey);
}

////////////////////////
bool PgCenterMgr::ConnectCenterServer(CEL::ADDR_INFO const &rkAddr)
{
/*	CONT_SERVER_HASH kCenter;
	g_kProcessCfg.Locked_GetServerInfo(CEL::ST_CENTER, kCenter);
	if(!kCenter.empty())
	{
		CONT_SERVER_HASH::const_iterator Itr = kCenter.begin();
		while(Itr != kCenter.end())
		{
			CONT_SERVER_HASH::mapped_type kElement = (*Itr).second;
			if(kElement.IP() == rkAddr.IP())
			{
				CenterServer(kElement.addrServerNat);
				ConnectCenterServer();
			}
			Itr++;
		}				
	}
*/
	return true;
}
bool PgCenterMgr::RecvManagementServerCommand(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{
/*	BYTE cCommand = 0;
	SERVER_IDENTITY kServerIden;
	pkPacket->Pop(cCommand);
	pkPacket->Pop(kServerIden);

	switch(cCommand)
	{
	case MCC_Start_Service:
	case MCC_Heart_Beat:
		{
			bool bServer = false;//서비스?
			bool bException = false;//뻣었는가?
			pkPacket->Pop(bServer);
			pkPacket->Pop(bException);

			SChangeStatusPack kServicePack;
			kServicePack.SetServer(bServer);
			kServicePack.SetException(bException);
			bool const bRet = g_kMMCMgr.SetServiceStatus(kServerIden, kServicePack);
			if( bRet )
			{
				Broadcast_ServerListToMonTool();
			}
		}break;
	default:
		{
		}break;
	}
*/
	return true;
}