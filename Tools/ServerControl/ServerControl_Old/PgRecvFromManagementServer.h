extern void CALLBACK OnConnectToManagementServer(CEL::CSession_Base *pkSession);
extern void CALLBACK OnDisconnectFromManagementServer(CEL::CSession_Base *pkSession);
extern void CALLBACK OnRecvFromManagementServer(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);

extern void GetServerListFromManagementServer(CEL::CPacket * const pkPacket);


extern BM::GUID g_kManagementServerConnectorGuid; //Connector Guid
extern BM::GUID g_kManagementServerSessionGuid;
