#pragma once

#include "BM/GUID.h"

extern BM::GUID g_guidLoginConnector;
extern BM::GUID g_guidSwitchConnector;

extern void CALLBACK OnConnectFromLogin( CEL::CSession_Base *pSession );
extern void CALLBACK OnDisconnectFromLogin( CEL::CSession_Base *pSession );
extern void CALLBACK OnRecvFromLogin( CEL::CSession_Base *pSession, CEL::CPacket * const pPacket );


extern void CALLBACK OnConnectFromSwitch( CEL::CSession_Base *pSession );
extern void CALLBACK OnDisconnectFromSwitch( CEL::CSession_Base *pSession );
extern void CALLBACK OnRecvFromSwitch( CEL::CSession_Base *pSession, CEL::CPacket * const pPacket );