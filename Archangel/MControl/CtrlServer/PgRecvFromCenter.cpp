#include "stdafx.h"
#include "PgRecvFromCenter.h"
#include "PgServerController.h"


void CALLBACK OnConnectToCenter( CEL::CSession_Base *pkSession )
{	//!  세션락
	const bool bIsSucc = pkSession->IsDeadConnection();
	if( bIsSucc )
	{
		SAddrInfo kAddr;
		kAddr.Set(pkSession->Addr().wstrIP, pkSession->Addr().wPort);
		g_kController.ConnectedCenter(true, pkSession->ParentKey(), pkSession->Key(), &kAddr);

		g_kProcessCfg.SendMyInfo(pkSession);
		return;
	}
	else
	{
		std::cout<< "fail to connect CENTER" << std::endl;
		return;
	}
}

void CALLBACK OnDisconnectFromCenter( CEL::CSession_Base *pkSession )
{//!  세션락
	SAddrInfo kAddr;
	kAddr.Set(pkSession->Addr().wstrIP, pkSession->Addr().wPort);
	g_kController.ConnectedCenter(false, pkSession->ParentKey(), pkSession->Key(), &kAddr);
}

void CALLBACK OnRecvFromCenter( CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket )
{
	WORD wkType = 0;
	pkPacket->Pop(wkType);

	std::cout<< "패킷 받음 T:[" << wkType <<"] Size["<< pkPacket->Size() << "]"<< std::endl;
	switch( wkType )
	{
	case PT_A_S_ANS_GREETING:
		{
			SAddrInfo kAddr;
			kAddr.Set(pkSession->Addr().wstrIP, pkSession->Addr().wPort);
			ObjectLock<SIMPLE_CENTER_INFO*> kFind;
			g_kController.GetCenter(&kAddr, kFind);
			if (kFind.m_pkObject == NULL)
			{
				INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer Session Addr[%s:%hd]"), _T(__FUNCTION__), kAddr.StrIP().c_str(), kAddr.wPort);
				return;
			}
			g_kController.QueryServerStatus(kFind.m_pkObject->nChannel);
		}break;
	case PT_T_CS_RES_SERVERSTATUS:
		{
			SAddrInfo kAddr;
			kAddr.Set(pkSession->Addr().wstrIP, pkSession->Addr().wPort);
			ObjectLock<SIMPLE_CENTER_INFO*> kFind;
			g_kController.GetCenter(&kAddr, kFind);
			if (kFind.m_pkObject == NULL)
			{
				INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer Session Addr[%s:%hd]"), _T(__FUNCTION__), kAddr.StrIP().c_str(), kAddr.wPort);
				return;
			}
			g_kController.ResServerStatus(kFind.m_pkObject->nChannel, pkPacket);
		}break;
	default:
		{
		}break;
	}
}


