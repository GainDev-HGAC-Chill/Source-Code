#include "stdafx.h"
#include "GFMobileLockPacketDef.h"
#include "PgRecvFromServer.h"
#include "PgPhoneLockMgr.h"

void CALLBACK OnAcceptFromServer( CEL::CSession_Base *pkSession )
{
	std::wcout << L"[AcceptServer] " << pkSession->Addr().ToString().c_str() << std::endl;
	g_kPhoneLockMgr.SetSession( pkSession );
}

void CALLBACK OnDisConnectFromServer( CEL::CSession_Base *pkSession )
{
	std::wcout << L"[DicConnectServer] " << pkSession->Addr().ToString().c_str() << std::endl;
	g_kPhoneLockMgr.SetSession( NULL );
}

void CALLBACK Timer(DWORD dwUserData)	// 100 ms
{
	g_kPhoneLockMgr.OnTick( BM::GetTime32() );
}

void CALLBACK OnRecvFromServer( CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket )
{
	BM::CPacket::DEF_PACKET_TYPE kType = 0;
	pkPacket->Pop( kType );

	switch ( kType )
	{
	case PT_AP_GF_REQ_MOBILE_AUTH:
		{
			S_PT_AP_GF_REQ_MOBILE_AUTH kData;
			pkPacket->Pop( kData );

			g_kPhoneLockMgr.Lock( std::wstring(kData.wszAccount), kData.kSessionID );
		}break;
	default:
		{

		}break;
	}
}
