#pragma once

extern void CALLBACK OnConnectToImmigration(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisConnectToImmigration(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromImmigration(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);
