#include "stdafx.h"
#include "RecvFromUser.h"

BM::GUID g_guidLoginConnector;
BM::GUID g_guidSwitchConnector;

BM::GUID g_guidSwitchSession;
SSwitchReserveResult g_SRR;

void CALLBACK OnConnectFromLogin( CEL::CSession_Base *pSession )
{	//!  세션락
	INFO_LOG( BM::LOG_LV5, _T("로그인으로 접속 성공! [%s:%d]"), pSession->Addr().wstrIP.c_str(), pSession->Addr().wPort);

	SClientTryLogin CTL;
//	CTL.guidVersion = 
	CTL.SetID( _T("test") );
	CTL.SetPW( _T("test") );

	CEL::CPacket Packet(PT_C_L_TRY_LOGIN, CTL);
	
	pSession->VSend( Packet );
}

void CALLBACK OnDisconnectFromLogin( CEL::CSession_Base *pSession )
{//!  세션락
	std::cout<< "접속 종료 ["<< 0 <<  "]"<< pSession << std::endl;
}

//유저 세션은 pSession->pData 에다가 현재 정보를 셋팅 해 줄것이다. OnDisconnect 에서 delete 해주면 된다.
void CALLBACK OnRecvFromLogin( CEL::CSession_Base *pSession, CEL::CPacket * const pPacket )
{
	WORD wType = 0;
	pPacket->Pop(wType);

	std::cout<< "패킷 받음 T:[" << wType <<"] Size["<< pPacket->Size() << "]"<< std::endl;
	switch( wType )
	{
	case PT_L_C_TRY_LOGIN_RESULT:
		{//
			ETryLoginResult eResult;
			pPacket->Pop( eResult );
			INFO_LOG( BM::LOG_LV6, _T("로그인 실패 관련 메세지 ! [%d]"), eResult );

		}break;
	case PT_L_C_NFY_RESERVED_SWITCH_INFO:
		{
			SSwitchReserveResult &SRR = g_SRR;
			pPacket->Pop(SRR);

			CEL::ADDR_INFO SwitchAddr;
			
			std::string strIP = inet_ntoa(SRR.addrSwitch.ip);

			SwitchAddr.Set( UNI(strIP), SRR.addrSwitch.wPort );

			INFO_LOG( BM::LOG_LV6, _T("스위치 정보 받음! [%s:%d]"), SwitchAddr.wstrIP.c_str(), SwitchAddr.wPort);

			BM::GUID guid;
			CoreCenter.Connect( g_guidSwitchConnector, SwitchAddr,  guid);
		}break;
	default:
		{
			pSession->VTerminate();
		}break;
	}
}


void CALLBACK OnConnectFromSwitch( CEL::CSession_Base *pSession )
{	//!  세션락
	INFO_LOG( BM::LOG_LV5, _T("스위치로 접속 성공! [%s:%d]"), pSession->Addr().wstrIP.c_str(), pSession->Addr().wPort);

	g_guidSwitchSession = pSession->Key();

	STryAccessSwitch TAS;
//	CTL.guidVersion = 
	TAS.SetID( _T("test") );
	TAS.SetPW( _T("test") );
	TAS.guidSwitchKey = g_SRR.guidSwitchKey;

	CEL::CPacket Packet(PT_C_S_TRY_ACCESS_SWITCH, TAS);
	
	pSession->VSend( Packet );
}

void CALLBACK OnDisconnectFromSwitch( CEL::CSession_Base *pSession )
{//!  세션락
	std::cout<< "접속 종료 ["<< 0 <<  "]"<< pSession << std::endl;
}

//유저 세션은 pSession->pData 에다가 현재 정보를 셋팅 해 줄것이다. OnDisconnect 에서 delete 해주면 된다.
void CALLBACK OnRecvFromSwitch( CEL::CSession_Base *pSession, CEL::CPacket * const pPacket )
{
	WORD wType = 0;
	pPacket->Pop(wType);

	std::cout<< "패킷 받음 T:[" << wType <<"] Size["<< pPacket->Size() << "]"<< std::endl;
	switch( wType )
	{
	case PT_S_C_TRY_ACCESS_SWITCH_RESULT:
		{//
			ETryLoginResult eRet = E_TLR_NONE;

			pPacket->Pop( eRet );
			
			INFO_LOG( BM::LOG_LV5, _T("스위치로 접속 결과[%d]"), eRet);
			if( E_TLR_SUCCESS == eRet )
			{//내 Player 정보를 달라고 하자.
//				CEL::CPacket Packet(PT_C_S_REQ_CHARACTER_LIST);
//				pSession->VSend(Packet);
			}
		}break;
	case PT_S_C_ANS_CHARACTER_LIST:
		{
			VEC_PLAYER vecPlayer;
			pPacket->Pop( vecPlayer );

			INFO_LOG( BM::LOG_LV5, _T("캐릭터 리스트 받음[%d]"), vecPlayer.size());
			if( vecPlayer.size() )
			{
				VEC_PLAYER::value_type &element = vecPlayer.at( 0 );

				CEL::CPacket Packet(PT_C_S_REQ_SELECT_CHARACTER, element.guidCharacter);
				pSession->VSend(Packet);
			}
		}break;
	case PT_S_C_ANS_SELECT_CHARACTER:
		{	//캐릭터 받았으면 맵 선택.
			VEC_PLAYER::value_type Player;
			pPacket->Pop( Player );

			SReqSelectMapServer RSMS;
			RSMS.iMapServer = 5;

			CEL::CPacket Packet(PT_C_S_REQ_ENTER_MAP_SERVER, RSMS);
			INFO_LOG( BM::LOG_LV5, _T("캐릭터 선택 성공, 맵서버 선택") );
			pSession->VSend(Packet);
		}break;
	case PT_T_C_ANS_RESERVE_PLAYER:
		{
			//맵서버 들어가라. --> 데이터 로딩 하시고.
			INFO_LOG( BM::LOG_LV5, _T("맵으로 이동하면 됨.") );
		}break;
	default:
		{
			pSession->VTerminate();
		}break;
	}
}

