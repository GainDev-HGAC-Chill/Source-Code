#pragma once

extern void CALLBACK OnAcceptFromManager( CEL::CSession_Base *pkSession );
extern void CALLBACK OnConnectFromManager( CEL::CSession_Base *pkSession );
extern void CALLBACK OnDisconnectFromManager( CEL::CSession_Base *pkSession );

extern void CALLBACK OnRecvFromManager( CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket );