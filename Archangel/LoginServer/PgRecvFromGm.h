#pragma once

extern void CALLBACK OnAcceptFromGM(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisconnectFromGM(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromGM(CEL::CSession_Base *pkSession, BM::Stream * const pkPacket);
