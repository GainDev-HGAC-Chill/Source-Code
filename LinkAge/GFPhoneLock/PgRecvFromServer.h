#pragma once

extern void CALLBACK OnAcceptFromServer( CEL::CSession_Base *pkSession );
extern void CALLBACK OnDisConnectFromServer( CEL::CSession_Base *pkSession );
extern void CALLBACK OnRecvFromServer( CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket );

extern void CALLBACK Timer(DWORD dwUserData);
