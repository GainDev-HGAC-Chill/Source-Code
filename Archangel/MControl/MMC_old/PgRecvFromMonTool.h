#pragma once
extern void CALLBACK OnAcceptMonTool(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisConnectToMonTool(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromMonTool(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);

