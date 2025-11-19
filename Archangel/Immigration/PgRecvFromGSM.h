#pragma once

extern void CALLBACK OnAcceptFromGsm(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisconnectFromGsm(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromGsm(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);