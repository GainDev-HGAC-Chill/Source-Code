#include "StdAfx.h"
#include "PgSendWrapper.h"

SERVER_IDENTITY g_kManagementServerSI;

bool SetSendWrapper(const SERVER_IDENTITY &kRecvSI)
{
	switch(kRecvSI.nServerType)
	{
	case CEL::ST_MACHINE_CONTROL:
		{
			g_kManagementServerSI = kRecvSI;
		}break;
	default:
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Incorrect ServerIdentity[%s]"), __FUNCTIONW__, __LINE__);
			return false;
		}break;
	}
	return true;
}

bool SendToServerType(const CEL::E_SESSION_TYPE eServerType, const CEL::CPacket &rkPacket)
{
	return g_kProcessCfg.SendToServerType(eServerType, rkPacket);
}

bool SendToServer(SERVER_IDENTITY const &kSI, CEL::CPacket const &rkPacket)
{
	return g_kProcessCfg.SendToServer(kSI, rkPacket);
}

bool SendToMMS(CEL::CPacket const &rkPacket)
{
//	return SendToServer(g_kManagementServerSI, rkPacket);
	return SendToServerType(CEL::ST_MACHINE_CONTROL, rkPacket);
}

