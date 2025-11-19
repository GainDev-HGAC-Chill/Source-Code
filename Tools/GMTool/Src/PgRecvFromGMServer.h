void CALLBACK OnConnectToGMServer(CEL::CSession_Base *pkSession);
void CALLBACK OnDisconnectFromGMServer(CEL::CSession_Base *pkSession);
void CALLBACK OnRecvFromGMServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);

extern BM::GUID g_kGMServerConnectorGuid; //Connector Guid
extern BM::GUID g_kGMServerSessionGuid;
