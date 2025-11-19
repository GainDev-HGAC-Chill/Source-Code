#pragma once

extern void CALLBACK OnConnectToCenter( CEL::CSession_Base *pkSession );
extern void CALLBACK OnDisconnectFromCenter( CEL::CSession_Base *pkSession );

extern void CALLBACK OnRecvFromCenter( CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket );
