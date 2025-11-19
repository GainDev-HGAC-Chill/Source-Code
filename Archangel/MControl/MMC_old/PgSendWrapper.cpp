#include "stdafx.h"
#include "PgSendWrapper.h"

SERVER_IDENTITY g_kImmigrationSI;
SERVER_IDENTITY g_kLogSI;
SERVER_IDENTITY g_kManagementServerSI;
SERVER_IDENTITY g_kCenterSI;


bool SetSendWrapper(SERVER_IDENTITY const &kRecvSI)
{
	switch(kRecvSI.nServerType)
	{
	case CEL::ST_IMMIGRATION:
		{
			g_kImmigrationSI = kRecvSI;
		}break;
	case CEL::ST_LOG:
		{
			g_kLogSI = kRecvSI;
		}break;
	case CEL::ST_MACHINE_CONTROL:
		{
			g_kManagementServerSI = kRecvSI;
		}
	case CEL::ST_CENTER:
		{
			g_kCenterSI = kRecvSI;
		}break;
	default:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T(" Incorrect ServerIdentity[") << C2L(kRecvSI) << _T("]") );
			return false;
		}break;
	}
	return true;
}

bool SendToServerType(const CEL::E_SESSION_TYPE eServerType, BM::CPacket const &rkPacket)
{
	return g_kProcessCfg.Locked_SendToServerType(eServerType, rkPacket);
}

bool SendToServer(SERVER_IDENTITY const &kSI, BM::CPacket const &rkPacket)
{
	return g_kProcessCfg.Locked_SendToServer(kSI, rkPacket);
}

bool SendToImmigration(BM::CPacket const &rkPacket)
{	
	return SendToServer(g_kImmigrationSI, rkPacket);
}

bool SendToLog(BM::CPacket const &rkPacket)
{	
	return SendToServer(g_kLogSI, rkPacket);
}

bool SendToManagerServer(BM::CPacket const &rkPacket)
{	
	return SendToServer(g_kManagementServerSI, rkPacket);
}

bool SendToCenter(BM::CPacket const &rkPacket)
{
	return SendToServer(g_kCenterSI, rkPacket);
}