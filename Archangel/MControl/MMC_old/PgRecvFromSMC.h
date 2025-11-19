#pragma once 
extern void CALLBACK OnAcceptFromSMC(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisConnectToSMC(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromSMC(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);
