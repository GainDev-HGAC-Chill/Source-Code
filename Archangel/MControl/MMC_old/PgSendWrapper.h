#pragma once
extern bool SetSendWrapper(SERVER_IDENTITY const &kRecvSI);

extern bool SendToServerType(const CEL::E_SESSION_TYPE eServerType, BM::CPacket const &rkPacket);
extern bool SendToServer(SERVER_IDENTITY const &kSI, BM::CPacket const &rkPacket);
extern bool SendToImmigration(BM::CPacket const &rkPacket);
extern bool SendToLog(BM::CPacket const &rkPacket);
extern bool SendToManagerServer(BM::CPacket const &rkPacket);
extern bool SendToCenter(BM::CPacket const &rkPacket);

