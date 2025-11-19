#pragma once

extern void CALLBACK OnConnectToJapanCash(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisConnectToJapanCash(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromJapanCash(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);


extern void CALLBACK OnConnectFromGame(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisConnectFromGame(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromGame(CEL::CSession_Base *pkSession, BM::CPacket * const pkPacket);
