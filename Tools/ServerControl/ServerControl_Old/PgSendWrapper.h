extern bool SetSendWrapper(const SERVER_IDENTITY &kRecvSI);

extern bool SendToServerType(const CEL::E_SESSION_TYPE eServerType, const CEL::CPacket &rkPacket);
extern bool SendToServer(SERVER_IDENTITY const &kSI, CEL::CPacket const &rkPacket);
extern bool SendToMMS(CEL::CPacket const &rkPacket);
