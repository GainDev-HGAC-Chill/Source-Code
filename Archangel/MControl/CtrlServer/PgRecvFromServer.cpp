#include "stdafx.h"
#include "PgRecvFromServer.h"
#include "Lohengrin/PacketStruct.h"
#include "PgClientMng.h"
#include "PgServerController.h"


void CALLBACK OnConnectFromManager( CEL::CSession_Base *pkSession )
{	//!  세션락
	const bool bIsSucc = pkSession->IsDeadConnection();
	if( bIsSucc )
	{
		std::cout<< "저쪽에서 서버가 접속 성공" << std::endl;

		const BM::GUID& rkGuid = pkSession->ParentKey();
		g_kClientMng.AddClient(pkSession->ParentKey(), pkSession->Key());
		return;
	}
	else
	{
		std::cout<< "접속 실패 쎈터로 접속 재시도" << std::endl;
		g_kProcessCfg.ConnectCenter();
		return;
	}
}

void CALLBACK OnDisconnectFromManager( CEL::CSession_Base *pkSession )
{//!  세션락
	INFO_LOG( BM::LOG_LV9, _T("[%s]-[%d] 서버 접속 종료"), _T(__FUNCTION__), __LINE__ );

	g_kClientMng.DeleteClient(pkSession->Key());
}

void CALLBACK OnRecvFromManager( CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket )
{
	static int i = 0;
	std::cout<< "패킷 받음 (" << i++ <<") Size["<< pkPacket->Size() << "]"<< std::endl;
	
	unsigned short usType = 0;
	pkPacket->Pop(usType);
	switch( usType )
	{
	case PT_CC_CS_REQ_LOGIN:
		{
			SClientTryLogin kLogin;
			pkPacket->Pop(kLogin);
			g_kController.Login(pkSession->Key(), &kLogin);
		}break;
	case PT_CC_CS_REQ_STARTSERVER:
		{
			TBL_SERVERLIST kSInfo;
			SAddrInfo kCenterAddr;
			pkPacket->Pop(kSInfo);
			pkPacket->Pop(kCenterAddr);
			g_kController.StartServer(pkSession->Key(), &kSInfo, &kCenterAddr);
		}break;
	case PT_CC_CS_REQ_SERVERSTATUS:
		{
			TBL_SERVERLIST kSInfo;
			SAddrInfo kCenterAddr;
			pkPacket->Pop(kSInfo);
			pkPacket->Pop(kCenterAddr);
			g_kController.ReqServerStatus(pkSession->Key(), &kSInfo, &kCenterAddr);
		}break;
	default:
		{
		}break;
	}
}
