#pragma once

extern void CALLBACK OnAcceptFromGMServer(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisConnectToGmServer(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromGmServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);
