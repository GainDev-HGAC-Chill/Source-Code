#include "StdAfx.h"
#include "GameGuard/ggsrv25.h"

#ifdef HACKSHIELD_AUTO	//중국/일본용
#include "HackShield_AUTO/AntiCpXSvr.h"
#else	//기본 설정
#include "HackShield_UNAUTO/AntiCpXSvr.h"
#endif


#include "Variant/Global.h"
#include "helldart/PgProtocolFilter.h"
#include "PgHub.h"
#include "PgReloadableDataMgr.h"

#pragma comment(lib, "GameGuard/ggsrvlib25_win32_MT.lib")

#ifdef HACKSHIELD_AUTO	//중국/일본용
#pragma comment(lib, "HackShield_AUTO/AntiCpXSvr.lib")
#else	//기본 설정
#pragma comment(lib, "HackShield_UNAUTO/AntiCpXSvr.lib")
#endif
// AntiHack 용 HellDart 함수
void CheckAntiHackPacket(bool& bRet, BM::Stream& kPacket)
{
	if( bRet )
	{
		switch( g_kHub.AntiHackType() )
		{
		case ANTIHACK_DUMMY:
			{
			}break;
		case ANTIHACK_GAMEGUARD:
			{
				GG_AUTH_DATA kAuthData;
				bRet = (bRet && kPacket.Pop( kAuthData ));
			}break;
		case ANTIHACK_AHN_HACKSHIELD:
			{
				AHNHS_TRANS_BUFFER kBuffer;
				bRet = (bRet && kPacket.Pop( kBuffer.nLength ));
				bRet = (bRet && kPacket.PopMemory( kBuffer.byBuffer, static_cast< size_t >(kBuffer.nLength) ));
			}break;
		}
	}
}

HRESULT CALLBACK Check_PT_C_S_TRY_ACCESS_SWITCH_SECOND(BM::Stream &kPacket)
{
	BM::GUID kTempGuid;
	unsigned long ulTemp = 0;

	bool bRet = kPacket.Pop( kTempGuid );
	bRet = (bRet && kPacket.Pop( ulTemp ));

	CheckAntiHackPacket(bRet, kPacket);

	if( bRet
	&&	0 == kPacket.RemainSize() )
	{
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CALLBACK Check_PT_C_S_ANS_GAME_GUARD_CHECK(BM::Stream &kPacket)
{
	unsigned long ulTemp = 0;
	bool bRet = kPacket.Pop( ulTemp );

	CheckAntiHackPacket(bRet, kPacket);

	if( bRet
	&&	0 == kPacket.RemainSize() )
	{
		return S_OK;
	}
	return E_FAIL;
}


//
namespace PgHubUtil
{
	typedef unsigned long MsgType;
	MsgType const iNoMessage = 0;
	MsgType const iBaseMsgType = 700145; // 서버로 부터 응답이 없습니다. / GM에게 문의해주시기 바랍니다.
	MsgType const iMaxMsgType = 700400; // iBaseMsgType + 255

	inline void DefaultSendToGround(TCHAR const* szFunc, size_t const iFuncLine, PgReserveMemberData const &rkRMD, CEL::CSession_Base *pkSession, BM::Stream * const pkPacket, unsigned short usType, int const iValue = 0)
	{
#ifdef _GROUNDKEY_CHECK
		if (rkRMD.kClientGroundKey.GroundNo() == rkRMD.kGroundKey.GroundNo())
#endif
		{
			pkPacket->PosAdjust();
			SendToGround(rkRMD.guidCharacter, rkRMD.kSI, rkRMD.kGroundKey, *pkPacket);
		}
#ifdef _GROUNDKEY_CHECK
		else
		{
			LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
			INFO_LOG( BM::LOG_LV8, __FL__ << _T(" Cannot forwarding packet["<<usType<<L", "<<iValue<<L"], User[Guid: ") << rkRMD.guidCharacter.str().c_str() << _T("] ClientGroundNo[") << rkRMD.kClientGroundKey.GroundNo() << _T("], ServerGroundNo[") << rkRMD.kGroundKey.GroundNo() << _T("]") );
		}
#endif
	}

	HRESULT UserDisconnectedLog(TCHAR const* szFunc, size_t const iFuncLine, int const iCause, PgReserveMemberData const& rkRMD, CEL::CSession_Base* pkSession, BM::vstring const& rkExtern, BYTE byReason)
	{
		MsgType iMsgNo = iNoMessage;
		HRESULT hReturn = S_OK;	// S_OK 이면 정말로 Disconnect 시킨다.
		switch( iCause )
		{
		case CDC_Normal:
		case CDC_ChangeChannel:
			{
			}break;
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_SpeedHack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_SuspectedSpeedHack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_LaziPing, rkRMD, iBaseMsgType + iCause, /*(true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL*/ S_OK, rkExtern)
//		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_ChangeChannel, rkRMD, 0, rkExtern)// 채널이동은 클라이언트 한테 메세지를 전송할 필요가 없다.
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_MapServerDown, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_MapServerClear, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_CenterRemoveUserByGnd, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_CharInfoErr, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_CharMapErr, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_NetworkErr, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_GM_CmdKick, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_GM_ToolKick, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_GM_CharEdit_Kick, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_GM_AccountBlock, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_GM_RPCKick, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_Invalid_Macro_Time, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_MoveSpeed_Hack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_HyperMove_Hack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_MaxTarget_Hack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_Projectile_Hack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_Blowup_Hack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_ClientNotify_Hack, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_RandomSeedCallCounter, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK(szFunc, iFuncLine, CDC_CheckAntiHack, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern) // GameGuard / HackShield 연동 관련해서 무조건 접속을 종료 시킨다
		CASE_USER_DISCONNECT_HACK(szFunc, iFuncLine, CDC_CheckAntiHack_C, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern) // GameGuard / HackShield
		CASE_USER_DISCONNECT_HACK(szFunc, iFuncLine, CDC_CheckAntiHack_NoReply, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern) // GameGuard / HackShield
		CASE_USER_DISCONNECT_CAUSE(szFunc, iFuncLine, CDC_TryLoginFromOther, rkRMD, iBaseMsgType + iCause, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_ActionCount_Hack_A, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_ActionCount_Hack_B, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_ActionCount_Hack_C, rkRMD, iBaseMsgType + iCause, (true == PgHub::ms_bDisconnectHackUser) ? S_OK : E_FAIL, rkExtern)
		CASE_USER_DISCONNECT_HACK(szFunc, iFuncLine, CDC_CheckAntiHack_NoReply2, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern) // GameGuard / HackShield
		CASE_USER_DISCONNECT_HACK(szFunc, iFuncLine, CDC_CheckHellDart, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern) // HellDart
		CASE_USER_DISCONNECT_HACK(szFunc, iFuncLine, CDC_CheckAntiHack_Format, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern) // GameGuard / HackShield 패킷 포멧 틀려
		CASE_USER_DISCONNECT_HACK_CAUSE(szFunc, iFuncLine, CDC_NotAuthSession, rkRMD, iBaseMsgType + iCause, S_OK, rkExtern)

		default:
			{
				LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
				iMsgNo = iBaseMsgType + iCause;
				CAUTION_LOG( BM::LOG_LV1, __FL__ << _T(" general error disconnected user[Cause: ") << iCause << _T("] user[M-G: ") << rkRMD.guidMember.str().c_str()
					<< _T(", C-G: ") << rkRMD.guidCharacter.str().c_str() << _T(", A-N: ") << rkRMD.ID() << _T(", IP: ") << rkRMD.addrRemote.ToString().c_str() << _T("] force disconnected") );
			}break;
		}

		if( S_OK == hReturn && pkSession && iMsgNo )
		{
			BM::Stream kDPacket( PT_A_S_NFY_USER_DISCONNECT, iMsgNo );
			kDPacket.Push(byReason);
			pkSession->VSend(kDPacket);
		}
		return hReturn;
	}

	bool IsCanTwiceCheckRegion()
	{
		switch( g_kLocal.ServiceRegion() )
		{
		case LOCAL_MGR::NC_TAIWAN:
			{
				// 사양(PC 또는 회선)이 안좋은 국가는 2중 체크를 하지 않는다
				return false;
			}break;
		default:
			{
			}break;
		}
		return true;
	}

	bool MakeCheckAntiHackQuery(BM::Stream &rkOut, PgReserveMemberData* pkRMD, DWORD const dwTime, wchar_t const* szFunc, size_t const iLine)
	{
		if( !pkRMD )
		{
			CAUTION_LOG( BM::LOG_LV5, __FL2__(szFunc, iLine) << _T("PgReserveMemberData* pkRMD = NULL") );
			return false;
		}

		HRESULT const hRet = pkRMD->MakePacket_CheckAntiHack(rkOut);
		if( ERROR_SUCCESS != hRet )
		{
			if( !pkRMD->IsCheckAntiHack() )
			{
				return false;
			}
			CAUTION_LOG( BM::LOG_LV5, __FL2__(szFunc, iLine) << _T("Make Failed ID<") << pkRMD->ID() << _T("> ErrorCode=") << hRet );
		}

//		INFO_LOG( BM::LOG_LV5, __FL__ );

		//SendPacketToUser( pkRMD->guidMember, kAHPacket ); // 외부에서 전송한다
		pkRMD->m_dwLastAntiHackCheckTime = dwTime;
		//pkRMD->m_dwNextAntiHackCheckTime = // Next는 설정하지 않는다
		pkRMD->m_bWaitAntiHackCheck = true;
		return true;
	}

	bool RecvAntiHackCheck( CEL::CSession_Base *pkSession, BM::Stream &kPacket, PgReserveMemberData* pkRMD, wchar_t const* szFunc, size_t const iLine )
	{
		unsigned long ulClientRet = ERROR_SUCCESS;
		if ( true == kPacket.Pop( ulClientRet ) )
		{
			if ( ERROR_SUCCESS == ulClientRet )
			{
				HRESULT const hRet = pkRMD->CheckAntiHack( kPacket );
				if( ERROR_SUCCESS == hRet )
				{
					DWORD const dwTime = BM::GetTime32();
					if( 0 == pkRMD->m_dwNextAntiHackCheckTime
					&&	IsCanTwiceCheckRegion() )
					{
						// 성공시 첫 성공이면 두번째 인증을 보내야 하지만, 지금이 아닌 m_kReserveMember(대기자)에서 m_kContMemberSession(접속자)로 변할 때 보낸다
					}
					else
					{
						pkRMD->m_dwLastAntiHackCheckTime = dwTime; // 그 다음부턴 일정 간격으로 확인
						pkRMD->m_bWaitAntiHackCheck = false;
					}
					pkRMD->m_dwNextAntiHackCheckTime = static_cast<DWORD>( BM::Rand_Range( PgHub::ms_iAntiHackCheck_Min, PgHub::ms_iAntiHackCheck_Max ) );
					return true;
				}
				else
				{
					PgHubUtil::UserDisconnectedLog( szFunc, iLine, CDC_CheckAntiHack, *pkRMD, pkSession, BM::vstring(L" CheckAntiHack() Ret:")<<hRet);
					pkSession->VTerminate(); // 클라이언트 변조
				}
			}
			else
			{
				PgHubUtil::UserDisconnectedLog( szFunc, iLine, CDC_CheckAntiHack_C, *pkRMD, pkSession, BM::vstring(L" Client Ret:")<<ulClientRet );
				pkSession->VTerminate(); // 클라이언트 인증에서 실패(모듈에러 또는 변조된 모듈)
			}
		}
		else
		{
			PgHubUtil::UserDisconnectedLog( szFunc, iLine, CDC_CheckAntiHack_Format, *pkRMD, pkSession );
			pkSession->VTerminate(); //포맷이 안맞은것이므로 무조건 접속 종료.
		}
		return false;
	}

	bool CheckAntiHackResponseTime(PgReserveMemberData& rkElement, CEL::CSession_Base* pkSession)
	{
		if( ANTIHACK_NONE == g_kHub.AntiHackType() )
		{
			return true;
		}

		DWORD const dwTime = BM::GetTime32();
		if( true == rkElement.m_bWaitAntiHackCheck )
		{
			DWORD const dwDiffTime = ::DifftimeGetTime(rkElement.m_dwLastAntiHackCheckTime, dwTime);
			if( dwDiffTime > PgHub::ms_iAntiHackCheck_Wait ) // 응답 시간이 지났으면
			{
				// 강제 연결 종료
				PgHubUtil::UserDisconnectedLog(__FUNCTIONW__, __LINE__, CDC_CheckAntiHack_NoReply, rkElement, pkSession, BM::vstring(L" Latest:")<<rkElement.m_dwLastAntiHackCheckTime<<L" Now:"<<dwTime<<L" Diff:"<<dwDiffTime<<L" Limit:"<<PgHub::ms_iAntiHackCheck_Wait);
				if( PgHub::ms_bUseAntiHackDisconnect2nd )
				{
					pkSession->VTerminate();
					return false;
				}
			}
		}
		else
		{
			if( (true == PgHub::ms_bUseAntiHackServerBind)
			&&	(::DifftimeGetTime(rkElement.m_dwLastAntiHackCheckTime, dwTime) > rkElement.m_dwNextAntiHackCheckTime) )
			{
				BM::Stream kAHPacket(PT_S_C_REQ_GAME_GUARD_CHECK);
				if( PgHubUtil::MakeCheckAntiHackQuery(kAHPacket, &rkElement, dwTime, __FUNCTIONW__, __LINE__) )
				{
					pkSession->VSend(kAHPacket);
				}
			}
		}
		return true;
	}


};

////////////////////

int PgHub::ms_iAntiHackCheck_Min = 300000;
int PgHub::ms_iAntiHackCheck_Max = 900000;
int PgHub::ms_iAntiHackCheck_Wait = 60000;
bool PgHub::ms_bDisconnectHackUser = false;
bool PgHub::ms_bUseAntiHackServerBind = false;
bool PgHub::ms_bUseAntiHackDisconnect2nd = false;

PgHub::PgHub(void)
:	m_kAntiHackType(ANTIHACK_NONE)
,	m_kHackShieldHandle(ANTICPX_INVALID_HANDLE_VALUE)
{
}

PgHub::~PgHub(void)
{
	if ( ANTICPX_INVALID_HANDLE_VALUE != m_kHackShieldHandle )
	{
		::_AhnHS_CloseServerHandle( m_kHackShieldHandle );
		m_kHackShieldHandle = ANTICPX_INVALID_HANDLE_VALUE;
	}

	CONT_SWITCH_PLAYER::iterator member_itr = m_kContMemberSession.begin();
	for ( ; member_itr!=m_kContMemberSession.end() ; ++member_itr )
	{
		SAFE_DELETE(member_itr->second);
	}

	CONT_SWITCH_RESERVER::iterator reserve_itr = m_kReserveMember.begin();
	for ( ; reserve_itr!=m_kReserveMember.end() ; ++reserve_itr )
	{
		SAFE_DELETE(reserve_itr->second);
	}
}

HRESULT PgHub::InitAntiHack( E_ANTIHACK_TYPE const kAntiHackType )
{
	m_kAntiHackType = kAntiHackType;
	switch ( m_kAntiHackType )
	{
	case ANTIHACK_DUMMY:
		{
			INFO_LOG(BM::LOG_LV2, __FL__ << _T("Dummy AntiHack ServerBind Init Success !!!!!!!"));
		}break;
	case ANTIHACK_GAMEGUARD:
		{
			DWORD dwNumActive = 50;
			int iLogType = NPLOG_ERROR;
			if( g_kProcessCfg.RunMode() & CProcessConfig::E_RunMode_Debug )
			{
				iLogType = NPLOG_DEBUG | NPLOG_ERROR;
				dwNumActive = 10;
			}

			DWORD const dwRet = InitGameguardAuth("./GameGuard/", dwNumActive, true, iLogType);
			if( ERROR_SUCCESS != dwRet )
			{
				CAUTION_LOG(BM::LOG_LV1, __FL__ << _T("GamuGuard InitFail Ret : ") << dwRet);
				return E_FAIL;
			}

			if( g_kProcessCfg.RunMode() & CProcessConfig::E_RunMode_Debug )
			{
				SetUpdateCondition(5, 50); // 5분동안 50% 이상
			}
			else
			{
				SetUpdateCondition(30, 50); // 30분동안 50% 이상
			}
			INFO_LOG(BM::LOG_LV2, __FL__ << _T("GamuGuard ServerBind Init Success !!!!!!!"));
		}break;
	case ANTIHACK_AHN_HACKSHIELD:
		{
			m_kHackShieldHandle = ::_AhnHS_CreateServerObject( "./HackShield/ShieldPack.hsb" );
			if ( ANTICPX_INVALID_HANDLE_VALUE == m_kHackShieldHandle )
			{
				CAUTION_LOG(BM::LOG_LV1, __FL__ << _T("Ahn HackShield CreateServerObject Failed") );
				return E_FAIL;
			}
			INFO_LOG(BM::LOG_LV2, __FL__ << _T("AntiHack ServerBind Init Success !!!!!!!"));
		}break;
	}
	return S_OK;
}

void PgHub::Locked_OnDisconnectUser(CEL::CSession_Base *pkSession)
{//할당 안된 유저는 ClearTimeOverPlayer가 센터로 날려주니 괜찮아
	// **** 주의 :: WRITE LOCK 사용
	if( pkSession )
	{
		PgReserveMemberData* pkData1 = NULL;
		PgReserveMemberData* pkData2 = NULL;

		BM::GUID const &kCustomKey = pkSession->CustomKey();
		CONT_SWITCH_RESERVER::key_type kReserveKey;
		pkSession->m_kSessionData.Pop(kReserveKey);
		pkSession->m_kSessionData.PosAdjust();

		{
			BM::CAutoMutex kLock(m_kMutex, true);// Write Lock 잡았다!!
			CONT_SWITCH_PLAYER::iterator member_itor = m_kContMemberSession.find(kCustomKey);
			if( member_itor != m_kContMemberSession.end() )
			{
				if ( member_itor->second->SessionKey() == pkSession->SessionKey() )
				{
					INFO_LOG( BM::LOG_LV6, __FL__ << L" Disconnected.....MemberID[" << (*member_itor).second->ID() << L"," << (*member_itor).second->guidMember << L"]" );

					BM::Stream kPacket(PT_A_NFY_USER_DISCONNECT, member_itor->second->guidMember);
					kPacket.Push( member_itor->second->guidCharacter );
					g_kProcessCfg.ServerIdentity().WriteToPacket( kPacket );
					SendToContents(kPacket);

					pkData1 = member_itor->second;
					m_kContMemberSession.erase(kCustomKey);//보내기전 지워
					SendNfyPlayerCount();
				}
				else
				{
					CAUTION_LOG( BM::LOG_LV5, __FL__ << L" Disconnected.....MemberID[" << (*member_itor).second->ID() << L"," << (*member_itor).second->guidMember << L"] But Different SessionKey" );
				}
			}
			else
			{
				LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
			}

			CONT_SWITCH_RESERVER::iterator reserve_itor = m_kReserveMember.find(kReserveKey);
			if(reserve_itor != m_kReserveMember.end())
			{
				pkData2 = reserve_itor->second;
				if ( pkData2 )
				{
					if ( true == pkData2->m_bWaitAntiHackCheck )
					{// 안티핵 체크중인데 접속을 끊어 버렸네
						DWORD const dwCurTime = BM::GetTime32();
						DWORD const dwGapTime = ::DifftimeGetTime( pkData2->m_dwLastAntiHackCheckTime, dwCurTime );

						PgHubUtil::UserDisconnectedLog(__FUNCTIONW__, __LINE__, CDC_CheckAntiHack_NoReply2, *pkData2, NULL, (BM::vstring(L" Disconnected before, Is Hacking or Crash, GapTime[Base:") << RESERVEMEMBER_TIMEOUT << L" > CurTime:" << dwGapTime << L"]")); // 세션이 없다
					}
				}
				m_kReserveMember.erase(kReserveKey);//지우는 키가 틀렸었다.//kCustomKey로 지우믄 안됨. 버그 나게 해보자. // SAFE_DELETE()는 밑에서
			}
			else
			{
				LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
			}

			pkSession->CustomKey(BM::GUID::NullData());
			pkSession->m_kSessionData.Reset();
		}

		if ( pkData1 == pkData2 )
		{
			pkData2 = NULL;
		}

		SAFE_DELETE(pkData1);
		SAFE_DELETE(pkData2);
	}
	else
	{
		LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
	}
}

void PgHub::Locked_OnDisconnectFromCenter( bool const bPublic )
{
	BM::CAutoMutex kLock( m_kMutex, !bPublic );

	BM::Stream kPacket;
	kPacket.SetStopSignal(true);

	if( bPublic )
	{
		CONT_SWITCH_PLAYER::const_iterator member_itr = m_kContMemberSession.begin();
		for (  ; member_itr!=m_kContMemberSession.end() ; ++member_itr )
		{
			// 여기서는 지우면 안된다.
			// 유저가 접속종료 했다는게 와서 정상적으로 처리 된다.
			if(	CProcessConfig::IsPublicChannel(member_itr->second->kSI.nChannel) )
			{
				CAUTION_LOG( BM::LOG_LV0, _T("* MemberID[") << member_itr->second->ID() << _T(",") << member_itr->second->guidMember.str().c_str() << _T("] Character[") << member_itr->second->guidCharacter.str().c_str()
					<< _T("] Ground[") << member_itr->second->kGroundKey.GroundNo() << _T("] CHECK ROLLBACK") );
				g_kCoreCenter.Send( member_itr->second->SessionKey(), kPacket );
			}
		}
	}
	else
	{
		// 다 지워야 해.
		{
			CONT_SWITCH_PLAYER::iterator member_itr = m_kContMemberSession.begin();
			for ( ; member_itr!=m_kContMemberSession.end() ; ++member_itr )
			{
				CAUTION_LOG( BM::LOG_LV0, __FL__ << _T("* MemberID[") << member_itr->second->ID() << _T(",") << member_itr->second->guidMember.str().c_str() << _T("] Character[") << member_itr->second->guidCharacter.str().c_str()
					<< _T("] Ground[") << member_itr->second->kGroundKey.GroundNo() << _T("] CHECK ROLLBACK") );
				g_kCoreCenter.Send( member_itr->second->SessionKey(), kPacket );

				SAFE_DELETE(member_itr->second);
			}
			m_kContMemberSession.clear();
		}

		{
			CONT_SWITCH_RESERVER::iterator member_itr = m_kReserveMember.begin();
			for ( ; member_itr!=m_kReserveMember.end() ; ++member_itr )
			{
				CAUTION_LOG( BM::LOG_LV0, __FL__ << _T("* MemberID[") << member_itr->second->ID() << _T(",") << member_itr->second->guidMember.str().c_str() << _T("] ReserveMember") );
				g_kCoreCenter.Send( member_itr->second->SessionKey(), kPacket );
				SAFE_DELETE(member_itr->second);
			}
			m_kReserveMember.clear();
		}
	}
}

bool PgHub::TryAccessSwitch2( CEL::CSession_Base *pkSession, BM::GUID const &guidSwitchKey, BM::Stream * const pkPacket )
{// 리턴값의 의미는 오직 m_kReserveMember에 있느냐 없느냐이다.
	CONT_SWITCH_RESERVER::iterator itr = m_kReserveMember.find( guidSwitchKey );
	if ( itr != m_kReserveMember.end() )
	{
		PgReserveMemberData *pkRMD = itr->second;

		bool bRet = false;
		if ( true == pkRMD->m_bWaitAntiHackCheck )
		{
			if ( pkPacket )
			{
				bRet = PgHubUtil::RecvAntiHackCheck( pkSession, *pkPacket, pkRMD, __FUNCTIONW__, __LINE__ );
			}
		}
		else
		{
			BM::Stream kAHPacket( PT_S_C_ANS_ACCESS_SWITCH_SECOND, guidSwitchKey );

			if( (true == PgHub::ms_bUseAntiHackServerBind)
			&&	(true == PgHubUtil::MakeCheckAntiHackQuery( kAHPacket, pkRMD, BM::GetTime32(), __FUNCTIONW__, __LINE__))
			)
			{
				pkSession->VSend( kAHPacket );
			}
			else
			{
				bRet = true;// 이렇게 해야 한다.
			}
		}

		if ( true == bRet )
		{

			pkRMD->SessionKey(pkSession->SessionKey());
			pkRMD->m_pkSession = pkSession;
			pkRMD->kSI.Clear();

			pkSession->CustomKey( pkRMD->guidMember );//Set CustomKey

			BM::Stream kServerPacket(PT_S_T_NFY_RESERVED_MEMBER_LOGIN);
			pkRMD->WriteToPacket(kServerPacket);

			::SendToCenter( kServerPacket, false/*Reserve 관련은 내채널 센터한테만 통보해야 한다!!*/ );
			INFO_LOG( BM::LOG_LV6, L"[TryAccessSwitch]" << pkSession->Addr().ToString() );
		}

		return true;// 여기서는 리턴 true
	}

	return false;
}

bool PgHub::Locked_SendPacketToUser(BM::GUID const &rkMemberGuid, BM::Stream const &rkPacket) const
{
	BM::CAutoMutex kLock(m_kMutex);
	return SendPacketToUser(rkMemberGuid, rkPacket);
}

bool PgHub::SendPacketToUser(BM::GUID const &rkMemberGuid, BM::Stream const &rkPacket) const
{
	CONT_SWITCH_PLAYER::const_iterator itor = m_kContMemberSession.find(rkMemberGuid);//메인에 할당되어 있으면 안됨.
	if(m_kContMemberSession.end() != itor)
	{
		CONT_SWITCH_PLAYER::mapped_type const &pkElement = (*itor).second;

		pkElement->m_pkSession->VSend(rkPacket);
		return true;
//		return g_kCoreCenter.Send( member->SessionKey(), rkPacket );
	}
	else
	{
		BM::Stream::DEF_STREAM_TYPE usPacketType = 0;
		BM::Stream::STREAM_DATA const &kPacketData = rkPacket.Data();
		if ( kPacketData.size() >= sizeof(BM::Stream::DEF_STREAM_TYPE) )
		{
			::memcpy( &usPacketType, &(kPacketData.at(0)), sizeof(BM::Stream::DEF_STREAM_TYPE) );
		}

		CAUTION_LOG( BM::LOG_LV5, __FL__ << _T("Cannot find MemberGUID=") << rkMemberGuid << _T(" PacketType=") << usPacketType );
	}
	LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
	return false;
}

bool PgHub::Locked_ChangeMemberMapServerNo( SERVER_IDENTITY const &kSI, SGroundKey const &kGndKey, BM::GUID const& kMemberGuid, BM::GUID const& kCharGuid )
{
	// **** 주의 :: WRITE LOCK 사용
	BM::CAutoMutex kLock(m_kMutex, true);

	CONT_SWITCH_PLAYER::iterator user_itr = m_kContMemberSession.find(kMemberGuid);
	if( m_kContMemberSession.end() != user_itr )
	{
		CONT_SWITCH_PLAYER::mapped_type &pkSwitchMember = user_itr->second;
		
		pkSwitchMember->kGroundKey = kGndKey;
		pkSwitchMember->guidCharacter = kCharGuid;
		pkSwitchMember->kSI = kSI;
		pkSwitchMember->m_bPublicConnect = CProcessConfig::IsPublicChannel( kSI.nChannel );

		if ( pkSwitchMember->kSI.nServerType == CEL::ST_CENTER )
		{
			pkSwitchMember->kClientGroundKey = pkSwitchMember->kGroundKey;
		}
		return true;
	}
	else
	{
		CAUTION_LOG( BM::LOG_LV1, __FL__ << _T(" [") << kMemberGuid.str().c_str() << _T("]Member is not found") );
	}

	LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
	return false;
}

bool PgHub::Locked_RemoveMember(SERVER_IDENTITY const &kSI)
{//절대 itor 를 erase 하지마라.
	// **** 주의 :: WRITE LOCK 사용
	BM::CAutoMutex kLock(m_kMutex, true);

	CONT_SWITCH_PLAYER::iterator itor = m_kContMemberSession.begin();
	while( m_kContMemberSession.end() != itor )
	{
		CONT_SWITCH_PLAYER::mapped_type const &pkElement = (*itor).second;
		if( pkElement->kSI == kSI )
		{
			__RemoveMember(CDC_MapServerDown, pkElement->guidMember);
		}
		++itor;
	}
	return true;
}

bool PgHub::Locked_RemoveMember(EClientDisconnectedCause const eCause, BM::GUID const &rkMemberGuid, BYTE byReason )
{
	// **** 주의 :: WRITE LOCK 사용
	BM::CAutoMutex kLock(m_kMutex, true);

	CONT_SWITCH_PLAYER::iterator itor = m_kContMemberSession.find(rkMemberGuid);
	if( m_kContMemberSession.end() != itor )
	{
		BM::Stream kCPacket;
		return __RemoveMember(eCause, rkMemberGuid, kCPacket, byReason);
	}
	return false;
}

bool PgHub::Locked_RemoveMember(EClientDisconnectedCause const eCause, BM::GUID const &rkMemberGuid, BM::Stream &kCPacket )
{
	// **** 주의 :: WRITE LOCK 사용
	BM::CAutoMutex kLock(m_kMutex, true);

	CONT_SWITCH_PLAYER::iterator itor = m_kContMemberSession.find(rkMemberGuid);
	if( m_kContMemberSession.end() != itor )
	{
		return __RemoveMember(eCause, rkMemberGuid, kCPacket );
	}
	return false;
}

bool PgHub::Locked_SendPacketToUserFromMap(CONT_GUID_LIST const &kContTarget, BM::Stream const &rkPacket) const
{
	BM::CAutoMutex kLock(m_kMutex);
	
	CONT_GUID_LIST::const_iterator target_itor = kContTarget.begin();

	while(kContTarget.end() != target_itor)
	{
		CONT_SWITCH_PLAYER::const_iterator itor = m_kContMemberSession.find((*target_itor));//메인에 할당되어 있으면 안됨.
		if(m_kContMemberSession.end() != itor)
		{
			CONT_SWITCH_PLAYER::mapped_type const &pkSwitchMember = (*itor).second;

			pkSwitchMember->m_pkSession->VSend(rkPacket);
			// 가끔 맵서버에서 유저가 접속 끊은 것을 모르는 경우가 발생한다.
			// 그 유저가 다시 접속하게 되면(맵서버에 접속하지 않은 상태에서), 맵서버는 맵서버의 동기화 패킷을 클라이언트로 전송하려 한다.
			// 이것을 막기 위한 코드
//			g_kCoreCenter.Send( pkSwitchMember->SessionKey(), rkPacket );
		}
		++target_itor;
	}
	return true;
}

void PgHub::Locked_DisplayState() const
{
	BM::CAutoMutex kLock(m_kMutex);

	INFO_LOG( BM::LOG_LV1, _T("------------ Conntected Switch User List -----------") );
	CONT_SWITCH_PLAYER::const_iterator user_iter = m_kContMemberSession.begin();
	size_t iCur = 1;
	
	CEL::SSessionStatistics kTotalStattistics;
	CEL::SSessionStatistics kStattistics;

	while( m_kContMemberSession.end() !=  user_iter )
	{
		CONT_SWITCH_PLAYER::mapped_type const &pkElement = (*user_iter).second;

		int const iLoginNo = pkElement->kLoginServer.nServerNo;
		SERVER_IDENTITY const &kMapServer = pkElement->kSI;
		SERVER_IDENTITY const& kSwitchServer = pkElement->kSwitchServer;
		int const iGroundNo = pkElement->kGroundKey.GroundNo();

		g_kCoreCenter.Statistics(pkElement->SessionKey(), kStattistics);
		kTotalStattistics += kStattistics;
		INFO_LOG( BM::LOG_LV1, iCur << _T(" Account[") << pkElement->ID() << _T("], L[") << iLoginNo << _T("], SS[") << kSwitchServer.nServerNo << _T("], Map[R:") << kMapServer.nRealm
			<< _T(", C:") << kMapServer.nChannel << _T(", S:") << kMapServer.nServerNo << _T("]-G[") << iGroundNo << _T("]") );

		++iCur;
		++user_iter;
	}
	INFO_LOG( BM::LOG_LV1, _T("--------------------- Cut Line ---------------------") );
	
	int const iSessionCount = (int)m_kContMemberSession.size();
	int const iAvgTotal = (int)((kTotalStattistics.TotalSendCount())?kTotalStattistics.TotalSendBytes()/kTotalStattistics.TotalSendCount():0);
	int const iAvgPerSession = ((iSessionCount && iAvgTotal)?iAvgTotal/iSessionCount:0);

	INFO_LOG( BM::LOG_LV1, _T("Byte Avg/Session[") << iAvgPerSession << _T("] AvgTotal[") << iAvgTotal << _T("]") );//세션당. 
	INFO_LOG( BM::LOG_LV1, _T("Total User[") << iSessionCount << _T("] Count[") << kTotalStattistics.TotalSendCount() << _T("], Bytes[") << kTotalStattistics.TotalSendBytes() << _T("]") );

	INFO_LOG( BM::LOG_LV1, _T("--------------------- Cut Line ---------------------") );
}

void CALLBACK PgHub::ProcessUserPacketForLogined( PgReserveMemberData const &rkRMD, unsigned short usType, CEL::CSession_Base *pkSession, BM::Stream * const pkPacket )
{//protected:

	// 핵 체크 이후, 패킷 처리
	switch(usType)
	{
	case PT_C_M_CS_REQ_SIMPLE_ENTER_CASHSHOP:
	case PT_C_M_CS_REQ_ENTER_CASHSHOP:
		{
			BM::GUID kStoreValueKey;

			if(	true == pkPacket->Pop(kStoreValueKey) )
			{
				g_kReloadMgr.ReqSyncDataFromUser(kStoreValueKey, pkSession);
				PgHubUtil::DefaultSendToGround(__FUNCTIONW__, __LINE__, rkRMD, pkSession, pkPacket, usType);
			}
		}break;
	case PT_C_L_TRY_LOGIN:
		{
			// 여기서 오면 채널변경 or 케릭터 재선택을 하고 싶다는 거다.
			BM::Stream kMapPacket( PT_S_A_REQ_AUTOLOGIN );
			rkRMD.SReqSwitchReserveMember::WriteToPacket( kMapPacket );
			short channelNrealm = 0;
			pkPacket->Pop(channelNrealm);
			pkPacket->Pop(channelNrealm);
			kMapPacket.Push(*pkPacket);
			PgHubUtil::DefaultSendToGround(__FUNCTIONW__, __LINE__, rkRMD, pkSession, &kMapPacket, usType);
		}break;
	case PT_C_S_REQ_CHARACTER_LIST:
		{
			BM::Stream kPacket(PT_S_T_REQ_CHARACTER_LIST, rkRMD.guidMember);
			::SendToCenter( kPacket, rkRMD.m_bPublicConnect );//여러번 부르면 어떻게 되나?
		}break;
	case PT_C_S_REQ_CREATE_CHARACTER:
		{
			BM::Stream kCPacket(PT_S_T_REQ_CREATE_CHARACTER, rkRMD.guidMember);
			kCPacket.Push(*pkPacket);
			::SendToCenter( kCPacket, rkRMD.m_bPublicConnect );
		}break;
	case PT_C_N_REQ_CHECK_CHARACTERNAME_OVERLAP:
		{
			BM::Stream kPacket(PT_C_N_REQ_CHECK_CHARACTERNAME_OVERLAP, rkRMD.guidMember);
			kPacket.Push(*pkPacket);
			::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
		}break;
	case PT_C_S_REQ_DELETE_CHARACTER:
		{
			BM::GUID kCharacterGuid;// 삭제할 캐릭터의 캐릭터GUID
			pkPacket->Pop(kCharacterGuid);

			BM::Stream kPacket(PT_S_T_REQ_DELETE_CHARACTER);
			kPacket.Push(rkRMD.guidMember);//소유자만이 지울 수 있으므로. 
			kPacket.Push(kCharacterGuid);
			::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
		}break;
	case PT_C_N_REQ_REALM_MERGE:
		{
			BM::Stream kPacket(PT_C_N_REQ_REALM_MERGE);
			kPacket.Push(rkRMD.guidMember);
			kPacket.Push(*pkPacket);
			::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
		}break;
	case PT_C_S_REQ_SELECT_CHARACTER:
		{
			BM::GUID kCharacterGuid;
			if(pkPacket->Pop(kCharacterGuid))
			{//내가 현재 들어간 맵서버가 없어야 가능하다.(두번 클릭 방지 필요)
				if(!rkRMD.kGroundKey.GroundNo())
				{
					BM::Stream kPacket(PT_S_T_REQ_SELECT_CHARACTER);
					kPacket.Push(rkRMD.guidMember);
					kPacket.Push(kCharacterGuid);
					kPacket.Push(*pkPacket);

					::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
					return;
				}
			}

			CAUTION_LOG( BM::LOG_LV6, __FL__ << _T(" Can't Character Selection State[") << kCharacterGuid.str().c_str() << _T("]") );
			LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
			pkSession->VTerminate();
		}break;
	case PT_C_T_REQ_SELECT_CHARACTER_OTHERMAP:
		{
			int iOtherMap = 0;
			if ( pkPacket->Pop(iOtherMap) )
			{
				if(!rkRMD.kGroundKey.GroundNo())
				{
					BM::Stream kPacket(PT_C_T_REQ_SELECT_CHARACTER_OTHERMAP);
					kPacket.Push(rkRMD.guidMember);
					kPacket.Push(iOtherMap);
					::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
					return;
				}
			}
			
			LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
		}break;
	case PT_C_S_ANS_ONLY_PING:
		{
			PgReserveMemberData* pkRMD = const_cast<PgReserveMemberData*>(&rkRMD);

			BM::GUID kPingGuid;
			pkPacket->Pop(kPingGuid);

			if(S_OK != pkRMD->RecvPing(kPingGuid/*, dwClientTime*/))
			{
				BM::Stream kStopPacket;
				kStopPacket.SetStopSignal(true);

				if (S_OK == PgHubUtil::UserDisconnectedLog(__FUNCTIONW__, __LINE__, CDC_SpeedHack, rkRMD, pkSession))
				{
					pkSession->VSend(kStopPacket);
				}
			}
		}break;
	case PT_C_S_NFY_UNIT_POS:
		{
			PgReserveMemberData* pkRMD = const_cast<PgReserveMemberData*>(&rkRMD);

			BM::GUID kPingGuid;
			POINT3 ptPos;
			DWORD dwLatency;
			bool bIncludeScPos;
			POINT3 ptScPos;

			pkPacket->Pop(kPingGuid);
			pkPacket->Pop(ptPos);
			pkPacket->Pop(bIncludeScPos);
			if(bIncludeScPos)
			{
				pkPacket->Pop(ptScPos);
			}

			if(pkRMD->DropLastRecvPing(kPingGuid, dwLatency))
			{
#ifdef _GROUNDKEY_CHECK
				if ( rkRMD.kSI.nServerType == CEL::ST_MAP
				&& rkRMD.kClientGroundKey.GroundNo() == rkRMD.kGroundKey.GroundNo() )
#else
				if ( rkRMD.kSI.nServerType == CEL::ST_MAP )
#endif
				{
					BM::Stream kToMapPacket(PT_C_S_NFY_UNIT_POS);
					kToMapPacket.Push(dwLatency);// 여기에 레이턴시 계산값이 들어가야함.
					kToMapPacket.Push(ptPos);
					kToMapPacket.Push(bIncludeScPos);
					if(bIncludeScPos)
					{
						kToMapPacket.Push(ptScPos);
					}

					SendToGround( rkRMD.guidCharacter, rkRMD.kSI, rkRMD.kGroundKey, kToMapPacket );
				}
			}
		}break;
	case PT_C_T_REQ_CHANNLE_INFORMATION:
		{
			if ( !rkRMD.m_bPublicConnect )
			{
				::SendToCenter( BM::Stream( PT_C_T_REQ_CHANNLE_INFORMATION, rkRMD.guidMember ), rkRMD.m_bPublicConnect );
				return;
			}

			LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
		}break;
	case PT_C_M_REQ_CHAT:	// CT_NORMAL만 그라운드로 보내고 나머지는 콘텐츠로 보낸다
		{
			BYTE cChatMode = 0;
			pkPacket->Pop( cChatMode );
			switch( cChatMode )
			{
			case CT_NORMAL:
			case CT_TEAM:
				{
#ifdef _GROUNDKEY_CHECK
					if (rkRMD.kClientGroundKey.GroundNo() == rkRMD.kGroundKey.GroundNo())
#endif
					{
						pkPacket->PosAdjust();
						SendToGround(rkRMD.guidCharacter, rkRMD.kSI, rkRMD.kGroundKey, *pkPacket);
					}
				}break;
			case CT_PARTY:
				{
					pkPacket->PosAdjust();
					SendToGround(rkRMD.guidCharacter, rkRMD.kSI, rkRMD.kGroundKey, *pkPacket);

					/*BM::Stream kTPacket( usType, rkRMD.guidCharacter );
					kTPacket.Push( cChatMode );
					kTPacket.Push(*pkPacket);
					SendToChannelChatMgr( kTPacket, rkRMD.bPublicConnect);*/
				}break;
			//case CT_WHISPER_BYNAME:
			//case CT_FRIEND:
			//case CT_GUILD:
			//case CT_EVENT:
			//case CT_EVENT_SYSTEM:
			//case CT_EVENT_GAME:
			//case CT_NOTICE:
			//case CT_BATTLE:
			//case CT_ITEM:
			//case CT_COMMAND:
			default:
				{
					pkPacket->PosAdjust();
					SendToGround(rkRMD.guidCharacter, rkRMD.kSI, rkRMD.kGroundKey, *pkPacket);

					/*BM::Stream kTPacket( usType, rkRMD.guidCharacter );
					kTPacket.Push( cChatMode );
					kTPacket.Push(*pkPacket);
					SendToRealmChatMgr( kTPacket );*/
				}break;
			}
		}break;
	case PT_C_S_ANS_GAME_GUARD_CHECK:
		{
			if( true == rkRMD.m_bWaitAntiHackCheck )
			{
				PgReserveMemberData *pkRMD = const_cast<PgReserveMemberData*>(&rkRMD);
				if ( pkRMD )
				{
					PgHubUtil::RecvAntiHackCheck( pkSession, *pkPacket, pkRMD, __FUNCTIONW__, __LINE__ );
				}
			}
		}break;
	case PT_C_N_REQ_EMPORIA_STATUS_LIST:
		{//
			BM::Stream kPacket( usType, rkRMD.guidCharacter );
			kPacket.Push( *pkPacket );
			SendToRealmContents( PMET_EMPORIA, kPacket );
		}break;
	case PT_C_N_REQ_GUILD_COMMAND:
		{
			BYTE cCmdType = 0;
			if( pkPacket->Pop(cCmdType) )
			{
				switch( cCmdType )
				{
				case GC_PreCreate_Test:
				case GC_PreCreate:
				case GC_Create:
					{
						PgHubUtil::DefaultSendToGround(__FUNCTIONW__, __LINE__, rkRMD, pkSession, pkPacket, usType);
					}break;
				default:
					{
						BM::Stream kPacket( usType, rkRMD.guidCharacter );
						kPacket.Push( cCmdType );
						kPacket.Push( *pkPacket );
						SendToRealmContents( PMET_GUILD, kPacket );
					}break;
				}
			}
		}break;
	case PT_C_M_NFY_HACKSHIELD_CALLBACK:
		{
			long lCode = 0;
			std::wstring kMsg;

			pkPacket->Pop( lCode );
			pkPacket->Pop( kMsg );

			BM::vstring const kLogMsg = BM::vstring() << __FL__ << _T("[HackShield][ClientNotify] Detection Hack Account[N: ") << rkRMD.ID() << _T(", G: ") << rkRMD.guidMember << L"] Character[G: " << rkRMD.guidCharacter << L"] Type[HackShield] CallBack Code:" << lCode << L" Msg:" << kMsg;
			CAUTION_LOG( BM::LOG_LV0, kLogMsg );
			//HACKING_LOG(BM::LOG_LV5, kNewLog);
		}break;
	case PT_C_M_NFY_MAPLOADED:
		{
			BYTE cMapMoveCause = 0;
			SGroundKey kGroundKey;
			pkPacket->Pop(cMapMoveCause);
			kGroundKey.ReadFromPacket(*pkPacket);
			PgReserveMemberData* pkRMD = const_cast<PgReserveMemberData*>(&rkRMD);
			pkRMD->kClientGroundKey = kGroundKey;

			PgHubUtil::DefaultSendToGround(__FUNCTIONW__, __LINE__, rkRMD, pkSession, pkPacket, usType);
		}break;
	case PT_C_N_REQ_REGIST_PVPLEAGUE_TEAM:
	case PT_C_N_REQ_GIVEUP_PVPLEAGUE_TEAM:
	case PT_C_N_REQ_QUERY_PVPLEAGUE_TEAM:
		{
			BM::Stream kPacket( usType );
			kPacket.Push( *pkPacket );
			SendToRealmContents( PMET_PVP_LEAGUE, kPacket );
		}break;
	case PT_C_S_REQ_SAVE_CHARACTOR_SLOT:
		{
			BM::GUID kCharacterGuid;//저장 할 캐릭터의 캐릭터GUID
			int iSlot = 0;			//저장 할 슬롯 번호
			pkPacket->Pop(kCharacterGuid);
			pkPacket->Pop(iSlot);

			BM::Stream kPacket(PT_S_T_REQ_SAVE_CHARACTOR_SLOT);
			kPacket.Push(rkRMD.guidMember);
			kPacket.Push(kCharacterGuid);
			kPacket.Push(iSlot);
			::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
		}break;
	case PT_C_S_REQ_FIND_CHARACTOR_EXTEND_SLOT:
		{
			BM::Stream kPacket(PT_S_T_REQ_FIND_CHARACTOR_EXTEND_SLOT);
			kPacket.Push(rkRMD.guidMember);
			::SendToCenter( kPacket, rkRMD.m_bPublicConnect );
		}break;
	case PT_C_L_TRY_LOGIN_CHANNELMAPMOVE:
		{
			// 채널 이동하면서 맵 변경.
			CONT_CHANNEL_MAPMOVE_PLAYER::iterator iter = m_ContMapMoveUser.find(rkRMD.guidCharacter);
			if( iter != m_ContMapMoveUser.end() )
			{
				BM::Stream MapPacket( PT_S_A_REQ_AUTOLOGIN );
				rkRMD.SReqSwitchReserveMember::WriteToPacket( MapPacket );
				MapPacket.Push(*pkPacket);					// 렐름번호.
				MapPacket.Push(iter->second.iChannelNo);	// 원정대 채널.
				MapPacket.Push(iter->second.iGroundNo);		// 원정대 맵.
				PgHubUtil::DefaultSendToGround(__FUNCTIONW__, __LINE__, rkRMD, pkSession, &MapPacket, usType);
				m_ContMapMoveUser.erase(iter);
			}
			else
			{
				BM::Stream Packet( PT_M_C_NFY_LOGIN_CHANNELMAPMOVE );
				pkSession->VSend(Packet);
			}
		}break;
	default:
		{
			PgHubUtil::DefaultSendToGround(__FUNCTIONW__, __LINE__, rkRMD, pkSession, pkPacket, usType);
		}break;
	}
}

void CALLBACK PgHub::ProcessUserPacketForNotLogin( unsigned short usType, CEL::CSession_Base *pkSession, BM::Stream * const pkPacket )
{//protected:
	switch(usType)
	{
	case PT_C_S_TRY_ACCESS_SWITCH:
		{
			STryAccessSwitch kTAS;
			if(kTAS.ReadFromPacket(*pkPacket))
			{
				if(!pkPacket->RemainSize())
				{
					kTAS.MakeCorrect();//스트링 깨졌을 경우를 위한 가드
					TryAccessSwitch(pkSession, kTAS);
					return;
				}
			}

			CAUTION_LOG(BM::LOG_LV5, __FL__ << _T("PT_C_S_TRY_ACCESS_SWITCH Format Fault IP:")<< pkSession->Addr().IP());
			pkSession->VTerminate();//포맷이 안맞은것이므로 무조건 접속 종료.
		}break;
	case PT_C_S_TRY_ACCESS_SWITCH_SECOND:
		{
			BM::GUID guidSwitchKey;
			pkPacket->Pop( guidSwitchKey );
			if ( !TryAccessSwitch2( pkSession, guidSwitchKey, pkPacket ) )
			{
				HACKING_LOG( BM::LOG_LV5, _T("[TryAccessSwitch] IP<") << pkSession->Addr().ToString() << _T("> No Reserved") );

				BM::Stream kUserPacket(PT_S_C_TRY_ACCESS_SWITCH_RESULT);
				kUserPacket.Push(E_TLR_NOR_RESERVED_USER);
				kUserPacket.SetStopSignal(true);
				pkSession->VSend(kUserPacket);//끊어야됨
			}
		}break;
	case PT_C_L_TRY_LOGIN:
		{
			CAUTION_LOG(BM::LOG_LV1, __FL__ << _T("PT_C_L_TRY_LOGIN Recved [")<< pkSession->Addr().IP()<<L"]");
		}break;
	case PT_C_L_TRY_LOGIN_CHANNELMAPMOVE:
		{
			CAUTION_LOG(BM::LOG_LV1, __FL__ << _T("PT_C_L_TRY_LOGIN_CHANNELMAPMOVE Recved [")<< pkSession->Addr().IP()<<L"]");
		}break;
	default:
		{
			LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
			CAUTION_LOG(BM::LOG_LV5, __FL__ << _T("unhandled packet Type[") << usType << _T("]"));
			pkSession->VTerminate();//스위치 접속 시도 패킷 외에는 모두 켄슬
		}break;
	}
}

void PgHub::Locked_OnRecvFromUser(CEL::CSession_Base *pkSession, BM::Stream * const pkPacket)
{
	BM::GUID const &kCustomKey = pkSession->CustomKey();

//	BM::Stream kFilterPacket(*pkPacket);
//	kFilterPacket = *pkPacket;
	BM::Stream::DEF_STREAM_TYPE usType = 0;
	pkPacket->Pop(usType);
	
	size_t const rd_pos = pkPacket->RdPos();
	if( BM::GUID::IsNotNull(kCustomKey) )
	{
		BM::CAutoMutex kLock(m_kMutex);
		CONT_SWITCH_PLAYER::const_iterator member_itor = m_kContMemberSession.find(kCustomKey);
		if(member_itor != m_kContMemberSession.end())
		{// 값이 변할 수 있는 부분이 있다.
			CONT_SWITCH_PLAYER::mapped_type pkElement = (*member_itor).second;
			if ( pkElement->m_pkSession == pkSession )
			{
				if(S_OK != g_kProtocolFilter.FilterProtocol((*pkPacket)))
				{
					PgHubUtil::UserDisconnectedLog(__FUNCTIONW__, __LINE__, CDC_CheckHellDart, *pkElement, pkSession, BM::vstring(L" PacketType: ") << usType); // 무조건 끊는다
					pkSession->VTerminate();
					return;
				}

				pkPacket->RdPos(rd_pos);//포지션 롤백.

				// 핵 응답 체크
				if( PgHubUtil::CheckAntiHackResponseTime(*pkElement, pkSession) )
				{
					ProcessUserPacketForLogined(*pkElement, usType, pkSession, pkPacket);
				}
			}
			else
			{
				PgHubUtil::UserDisconnectedLog( __FUNCTIONW__, __LINE__, CDC_NotAuthSession, *pkElement, pkSession, BM::vstring(L" PacketType: ") << usType); // 무조건 끊는다
				pkSession->VTerminate();
			}
		}
	}
	else
	{
		BM::CAutoMutex kLock(m_kMutex, true);
		ProcessUserPacketForNotLogin(usType, pkSession, pkPacket);
	}
}

bool PgHub::__RemoveMember(EClientDisconnectedCause const eCause, BM::GUID const &rkMemberGuid, BM::Stream& rkPacket, BYTE byReason)
{//protected:
	////////// 외부 전용 함수.
	// Lock은 외부에서 걸어 주고 들어와야 한다.
	//////////
	CONT_SWITCH_PLAYER::iterator itor = m_kContMemberSession.find(rkMemberGuid);
	if( m_kContMemberSession.end() != itor )
	{
		CONT_SWITCH_PLAYER::mapped_type &pkElement = (*itor).second;
		pkElement->dwTimeLimit = BM::GetTime32();
		INFO_LOG(BM::LOG_LV7, __FL__<< _T(" ID= ") << pkElement->ID() << _T(" MemberGUID= ")<< rkMemberGuid << _T(", CAUSE=") << eCause);

		if( pkElement )
		{
			if (S_OK == PgHubUtil::UserDisconnectedLog(__FUNCTIONW__, __LINE__, eCause, *pkElement, pkElement->m_pkSession,  BM::vstring(), byReason))
			{
				rkPacket.SetStopSignal(true);
				g_kCoreCenter.Send(pkElement->SessionKey(), rkPacket);//스톱 시그널을 보냄.

				// 여기서 바로 m_kContMemberSession.erase 호출 하면, Center로 유저 정보 삭제 패킷을 못 보내게 된다.
				// OnDisconnectUser 에서 지워주자.
				// 하지만 Channel 변경일때는 이미 모두 지우고 왔다.
				// 여기서 안지워 주면 다시 지우라는게 올라가(다른데는 괜찮지만 새로 접속해온 정보로.. 이미그레이션에서 로그아웃 처리가 되어 버릴 수 있다)
				if ( CDC_ChangeChannel == eCause )
				{
					SAFE_DELETE(pkElement);// 메모리 해제 했다.
					m_kContMemberSession.erase(itor);// 지웠다.
				}
			}
		}
		return true;
	}
//	else	//정상 종료시 콜이 되기 때문에. -> 센터가 PT_A_NFY_USER_DISCONNECT를 보내서 강제 콜을 시킨다.
//	{
//		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__<< _T("No MemberGUID= ") << rkMemberGuid);
//	}
	
	LIVE_CHECK_LOG(BM::LOG_LV0, __FL__);
	return false;
}

void PgHub::Locked_OnTimer_CheckPing()
{
	// **** 주의 :: WRITE LOCK 사용
	//ACE_Time_Value const kNowTime = ACE_OS::gettimeofday();
	//static ACE_Time_Value const kInterval(5, 0);//5초
	//static ACE_Time_Value const kKeepAliveTime(60, 0);//60초

//	LV-00,22:45:35,[KeepAlive] Order Disconnect User[DTEST100] Last Ping Before 60953msec

	BM::CAutoMutex kLock(m_kMutex);
	// Ready User
	CONT_SWITCH_PLAYER::iterator member_itor = m_kContMemberSession.begin();
	//DWORD const dwNow = BM::GetTime32();
	while( m_kContMemberSession.end() != member_itor )
	{
		CONT_SWITCH_PLAYER::mapped_type pkElement = (*member_itor).second;

		if(S_OK != pkElement->DoSendPing(1))
		{
			if( pkElement->m_pkSession->IsAlive() )
			{
				if (S_OK == PgHubUtil::UserDisconnectedLog(__FUNCTIONW__, __LINE__, CDC_LaziPing, *pkElement, pkElement->m_pkSession))
				{
					INFO_LOG(BM::LOG_LV0, _T("[KeepAlive] Order Disconnect User[")<< pkElement->ID() );
					pkElement->m_pkSession->VTerminate();
				}
			}
		}
		++member_itor;
	}
}

int PgHub::Locked_GetSwitchConnectionPlayerCount() const
{
	BM::CAutoMutex kLock(m_kMutex);

	return (int)m_kContMemberSession.size();
}

void PgHub::Locked_RegistChannelMapMoveUser(BM::Stream * const pPacket)
{
	BM::CAutoMutex Lock(m_kMutex);

	BM::GUID CharGuid;
	SChannelMapMove MoveInfo;

	pPacket->Pop(CharGuid);
	pPacket->Pop(MoveInfo);

	std::pair<CONT_CHANNEL_MAPMOVE_PLAYER::iterator, bool> Ret = m_ContMapMoveUser.insert( std::make_pair(CharGuid, MoveInfo) );
	if( false == Ret.second )
	{
		INFO_LOG(BM::LOG_LV0, _T("Duplecate : ") << CharGuid );
	}
}