#include "StdAfx.h"
#include "PgMMCMgr.h"
#include "PgRecvFromCenter.h"
#include "PgImmigrationServerMgr.h"
#include "PgSendWrapper.h"

void SendServerCommand(SERVER_IDENTITY const& rkServerID, const EMCtrlCommand eCommand)
{
	CEL::CPacket kPacket(PT_MCTRL_MMS_A_NFY_SERVER_COMMAND);
	kPacket.Push((BYTE)eCommand);
	rkServerID.WriteToPacket(kPacket);
	//등록된 머신 컨트롤러의 목록 중 해당 서버가 접속하는 머신 컨트롤러가 있으면 해당 머신 컨트롤러로 전송 아니면 내꺼다!!
	std::wstring wstrServerIP;
//	if(g_kMMCMgr.IsSMSConnection(rkServerID, wstrServerIP))
	{
//		g_kProcessCfg.Locked_SendToServerType(CEL::ST_SUB_MACHINE_CONTROL, kPacket);
		return ;
	}
//	else
//	{
//		if(g_kMMCMgr.IsImmConnection(rkServerID))
//		{
//			SendToImmigration(kPacket);
//		}
//		else
//		{
//			g_kCoreCenter.Send(g_kCenterMgr.m_kSessionKey, kPacket);
//		}
//	}
}