#include "stdafx.h"
#include "Bm/TimeCheck.h"
#include "Lohengrin/GMCommand.h"
#include "FCS/AntiHack.h"
#include "variant/GM_const.h"
#include "Variant/PgMission_Report.h"
#include "Variant/defabiltype.h"
#include "Variant/PgEventView.h"
#include "Variant/PgParty.h"
#include "Variant/PgPartyMgr.h"
#include "Variant/PgExpedition.h"
#include "Variant/PgExpeditionMgr.h"
#include "Variant/PgPortalAccess.h"
#include "Variant/PgNoticeAction.h"
#include "Global.h"
#include "PgRecvFromServer.h"
#include "PgLChannelMgr.h"
#include "PgResultMgr.h"
#include "PgGlobalPartyMgr.h"
#include "PgGlobalMarryMgr.h"
#include "variant/pggamblemachine.h"

extern bool CALLBACK OnRecvFromServer3( CEL::CSession_Base *pkSession, unsigned short usType, BM::Stream * const pkPacket );
extern bool CALLBACK OnRecvFromServer2( CEL::CSession_Base *pkSession, unsigned short usType, BM::Stream * const pkPacket );
extern void Recv_PT_A_S_REQ_GREETING(CEL::CSession_Base *pkSession, BM::Stream * const pkPacket);
extern void BuilderCommandProcess(BM::Stream * const pkPacket);
extern bool OnRecvGodCommand( EGMCmdType const eGodCommandType, BM::Stream * const pkPacket );

void CALLBACK OnAcceptFromServer( CEL::CSession_Base *pkSession )
{	//!  세션락
	std::vector<char> kEncodeKey;
	if(S_OK == pkSession->VGetEncodeKey(kEncodeKey))
	{
		INFO_LOG( BM::LOG_LV6, __FL__ << _T("Send EncryptKey Address[") << pkSession->Addr().ToString().c_str() << _T("]") );

		BM::Stream kPacket(PT_A_ENCRYPT_KEY);
		kPacket.Push(kEncodeKey);

		pkSession->VSend(kPacket, false);
	}
	else
	{
		__asm int 3;
		INFO_LOG( BM::LOG_LV0, __FL__ << _T("Get EncryptKey Failed. Session Terminate!") );
		pkSession->VTerminate();
	}
}

void CALLBACK OnConnectFromServer( CEL::CSession_Base *pkSession )
{	//!  세션락
	bool const bIsSucc = pkSession->IsAlive();
	if( bIsSucc )
	{
		INFO_LOG( BM::LOG_LV7, __FL__ << _T("Other Server Connected Address[") << pkSession->Addr().ToString().c_str() << _T("]") );
		return;
	}
	else
	{
		INFO_LOG( BM::LOG_LV7, __FL__ << _T("Other Server Connected Failed") );
	}
}

void CALLBACK OnDisconnectFromServer( CEL::CSession_Base *pkSession )
{//!  세션락
	INFO_LOG( BM::LOG_LV9, __FL__ << _T("Server Connection Close") );
	g_kProcessCfg.Locked_OnDisconnectServer(pkSession);
	
	if(pkSession->m_kSessionData.Size())
	{
		SERVER_IDENTITY kRecvSI;
		kRecvSI.ReadFromPacket(pkSession->m_kSessionData);
		g_kServerSetMgr.Locked_ReqUnregistGnd(kRecvSI);
		//g_kServerSetMgr.Locked_ProcessRemoveUser(kRecvSI);
		g_kSwitchAssignMgr.DisconnectSwitch(kRecvSI);
		if (kRecvSI.nServerType == CEL::ST_SWITCH)
		{
			BM::Stream kGPacket(PT_A_A_SERVER_SHUTDOWN);
			kRecvSI.WriteToPacket(kGPacket);
			SendToContents(kGPacket);
		}
	}
}

void CALLBACK OnRecvFromServer( CEL::CSession_Base *pkSession, BM::Stream * const pkPacket )
{
	PACKET_ID_TYPE usType = 0;
	pkPacket->Pop(usType);
	//std::cout<< "Received Packet Type(" << usType <<") Size["<< pkPacket->Size() << "]"<< std::endl;
	//INFO_LOG(BM::LOG_LV7, _T("OnRecvFromServer PacketType[%hd], Size[%d]"), usType, pkPacket->Size());
	int iLoginServerNo = -1;
	switch( usType )
	{
	case PT_M_C_NFY_GAMBLEMACHINE_MIXUP_RESULT:
	case PT_M_C_NOTI_ACHIEVEMENT_COMPLETE_FIRST:
	case PT_M_C_NFY_GENERIC_ACHIEVEMENT_NOTICE:
	case PT_M_C_NFY_GAMBLEMACHINE_RESULT:
	case PT_M_C_NFY_ITEM_MAKING_SUCCESS:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToServerType(CEL::ST_MAP,kPacket);
		}break;
	case PT_M_C_NOTI_OPEN_GAMBLE:
	case PT_M_C_NOTI_EVENT_ITEM_REWARD:
	case PT_M_C_NOTI_TREASURE_CHEST:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToServerType(CEL::ST_MAP,kPacket);
		}break;
	case PT_M_C_NFY_USEITEM:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToServerType(CEL::ST_MAP,kPacket);
		}break;
	case PT_M_T_ANS_MOVETOSUMMONER:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
	case PT_M_T_REQ_PARTY_BUFF:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
	case PT_M_T_REQ_MOVETOSUMMONER:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
	case PT_M_T_ANS_SUMMONPARTYMEMBER:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
	case PT_M_T_REQ_SUMMONPARTYMEMBER:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
	case PT_M_T_ANS_PARTYMEMBERPOS:
		{
			BM::GUID kOwnerGuid;
			SGroundKey kGndKey;
			pkPacket->Pop(kOwnerGuid);
			pkPacket->Pop(kGndKey);

			BM::Stream kPacket(PT_T_M_ANS_PARTYMEMBERPOS);
			kPacket.Push(kOwnerGuid);
			kPacket.Push(*pkPacket);

			g_kServerSetMgr.Locked_SendToGround(kGndKey,kPacket,true);
		}break;
	case PT_M_T_ANS_PARTYMASTERGROUNDKEY:
		{
			BM::GUID kOwnerGuid;
			SGroundKey kGndKey;
			pkPacket->Pop(kOwnerGuid);
			pkPacket->Pop(kGndKey);

			BM::Stream kPacket(PT_T_M_ANS_PARTYMASTERGROUNDKEY);
			kPacket.Push(kOwnerGuid);
			kPacket.Push(*pkPacket);

			g_kServerSetMgr.Locked_SendToGround(kGndKey, kPacket, true);
		}break;
	case PT_M_T_REQ_PARTYMEMBERPOS:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
	case PT_M_T_REQ_PARTYMASTERGROUNDKEY:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToGlobalPartyMgr(kPacket);
		}break;
/*	case 64000:
		{
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Hold"), __FUNCTIONW__, __LINE__ );
			Sleep(10000);
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Free"), __FUNCTIONW__, __LINE__ );
		}break;
*/	case PT_A_S_REQ_GREETING:
		{
			Recv_PT_A_S_REQ_GREETING(pkSession, pkPacket);
		}break;
	case PT_S_T_ANS_RESERVE_MEMBER:
		{
			g_kServerSetMgr.Recv_PT_S_T_ANS_RESERVE_MEMBER(pkPacket);
		}break;
	case PT_S_T_NFY_USER_CONNECT_SWITCH:
		{
			SERVER_IDENTITY  kRecvSI;
			size_t user_count = 0;

			kRecvSI.ReadFromPacket(*pkPacket);
			pkPacket->Pop(user_count);

			if(S_OK != g_kProcessCfg.Locked_SetPlayerCount(kRecvSI, user_count))
			{
				VERIFY_INFO_LOG( false, BM::LOG_LV0, _T("[ERROR] [") << __FL__ << _T("] Incorrect Server Send Nfy") );
			}
		}break;
	case PT_S_T_NFY_RESERVED_MEMBER_LOGIN:
		{
			INFO_LOG( BM::LOG_LV6, __FL__ << _T("Accept User Login From Switch") );
			SSwitchPlayerData kSPD;
			if (kSPD.ReadFromPacket(*pkPacket))
			{
				if ( g_kSwitchAssignMgr.InsertAssignSwitch( kSPD.kSwitchServer, kSPD.guidMember ) )
				{
					BM::Stream kPacket(PT_T_IM_REQ_SWITCH_USER_ADD);
					kSPD.WriteToPacket(kPacket);
					g_kProcessCfg.Locked_SendToServerType(CEL::ST_CONTENTS, kPacket);//로그인 보고를 올림.
				}
			}
			else
			{
				VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("kSPD is 0") );
				return;
			}
		}break;
	case PT_S_T_TRY_ACCESS_SWITCH_RESULT:
		{
			BM::GUID kMemberGuid;
			SERVER_IDENTITY  kRecvSI;
			pkPacket->Pop(kMemberGuid);
			kRecvSI.ReadFromPacket(*pkPacket);
			
			g_kServerSetMgr.Locked_ProcessRemoveUser(kMemberGuid);
			g_kSwitchAssignMgr.RemoveAssignSwitch( kRecvSI, kMemberGuid );
		}break;
	case PT_S_T_REQ_CHARACTER_LIST:
	case PT_S_T_REQ_FIND_CHARACTOR_EXTEND_SLOT:
		{
			BM::GUID kMemberGuid;
			pkPacket->Pop(kMemberGuid);
			pkPacket->Push(g_kProcessCfg.ChannelNo());//채널 기록

			pkPacket->PosAdjust();
			g_kProcessCfg.Locked_SendToServerType(CEL::ST_CONTENTS, *pkPacket);

			INFO_LOG( BM::LOG_LV6, __FL__ << _T("PT_S_T_REQ_CHARACTER_LIST") );
		}break;
	case PT_C_M_REQ_CLIENT_CUSTOMDATA:
	case PT_C_T_REQ_SAVE_OPTION:
	case PT_M_T_REQ_SAVE_CHARACTER:	// Request to SAVE Character
	case PT_S_T_REQ_CREATE_CHARACTER://컨텐츠 서버로 직통
	case PT_S_T_REQ_DELETE_CHARACTER:	
	case PT_S_T_REQ_SELECT_CHARACTER:	
	case PT_C_N_REQ_REALM_MERGE:
	case PT_C_N_REQ_CHECK_CHARACTERNAME_OVERLAP:
	case PT_S_T_REQ_SAVE_CHARACTOR_SLOT:
		{
			pkPacket->PosAdjust();
			g_kProcessCfg.Locked_SendToServerType(CEL::ST_CONTENTS, *pkPacket);
		}break;
	case PT_M_T_REQ_MAP_MOVE:
		{
			g_kServerSetMgr.Locked_Recv_PT_M_T_REQ_MAP_MOVE(pkPacket);
		}break;
	case PT_T_T_REQ_MAP_MOVE:
		{
			g_kServerSetMgr.Locked_Recv_PT_T_T_REQ_MAP_MOVE(pkPacket);
		}break;
	case PT_T_T_REQ_RECENT_MAP_MOVE:
		{
			g_kServerSetMgr.Locked_Recv_PT_T_T_REQ_RECENT_MAP_MOVE(pkPacket);
		}break;
	case PT_M_T_REQ_MAP_MOVE_COME:
		{
			SReqMapMove_CM kRMMC;
			VEC_GUID kUserList;
			kRMMC.ReadFromPacket(*pkPacket);
			pkPacket->Pop(kUserList);
			g_kServerSetMgr.Locked_Recv_PT_M_T_REQ_MAP_MOVE_COME( kRMMC, kUserList, false );
		}break;
	case PT_M_T_ANS_MAP_MOVE_RESULT:// MapMove의 결과
		{
			g_kServerSetMgr.Locked_Recv_PT_M_T_ANS_MAP_MOVE_RESULT( pkPacket );
		}break;
	case PT_T_T_ANS_MAP_MOVE_RESULT:// PvP에서 온 Join 결과
		{
			SAnsMapMove_MT kAMM;
			if ( pkPacket->Pop(kAMM) )
			{
				BM::GUID kCharGuid;
				pkPacket->Pop( kCharGuid );
				g_kServerSetMgr.Locked_Recv_PT_T_T_ANS_MAP_MOVE_RESULT( kCharGuid, kAMM );
			}
		}break;;
	case PT_M_T_ANS_MAP_MOVE_TARGET_FAILED:
		{
			g_kServerSetMgr.Recv_PT_M_T_ANS_MAP_MOVE_TARGET_FAILED( pkPacket );
		}break;
	case PT_T_N_ANS_KICK_USER:
		{
			g_kServerSetMgr.Locked_Recv_PT_M_T_REQ_Kick_User(pkPacket);
		}break;
	case PT_M_T_REFRESH_LEVELUP:
		{
			g_kServerSetMgr.Locked_Recv_PT_M_T_REFRESH_LEVELUP(pkPacket);
		}break;
	case PT_M_T_REFRESH_CLASS_CHANGE:
		{
			g_kServerSetMgr.Locked_Recv_PT_M_T_REFRESH_CLASS_CHANGE(pkPacket);
		}break;
	case PT_M_T_REQ_USEITEM_CHECK:
		{
			EUseItemServerCheckType kServerCheckType = UISCT_NONE;
			BM::GUID kMemberGuid;
			BM::GUID kCharGuid;
			SGroundKey kCasterGndKey;
			SItemPos kCasterItemPos;
			int iMapNo = 0;
			int iErrorMsg = 0;
			pkPacket->Pop(kServerCheckType);
			pkPacket->Pop(kMemberGuid);
			pkPacket->Pop(kCharGuid);
			pkPacket->Pop(kCasterGndKey);
			pkPacket->Pop(kCasterItemPos);
// 			switch( kServerCheckType )
// 			{
// 			case UISCT_SCROLL:
// 				{
// 					pkPacket->Pop(iMapNo);
// 					switch( g_kServerSetMgr.Locked_UserOpenGround(kMemberGuid,iMapNo) )
// 					{
// 					case S_OK:
// 					case E_ACCESSDENIED:
// 						{
// 							iErrorMsg = 0;
// 						}break;
// // 					case E_ACCESSDENIED:// 한번도 이동하지 않은 그라운드는 못쓰게 해야 할 경우 여기를 풀어라.
// // 						{
// // 							iErrorMsg = 16;
// // 						}break;
// 					default:
// 						{
// 							iErrorMsg = 1;
// 							return;
// 						}break;
// 					}
// 				}break;
// 			default:
// 				{
// 					return;
// 				}break;
// 			}

			BM::Stream kMPacket(PT_T_M_ANS_USEITEM_CHECK,kCharGuid);
			kMPacket.Push(kCasterItemPos);
			kMPacket.Push(iErrorMsg);
			g_kServerSetMgr.Locked_SendToGround(kCasterGndKey,kMPacket,true);
		}break;
	case PT_M_T_NFY_CREATE_GROUND:
		{		
			g_kServerSetMgr.Recv_PT_M_T_NFY_CREATE_GROUND( *pkPacket );
		}break;
	case PT_M_T_NFY_DELETE_GROUND:
		{
			GND_KEYLIST kGndKeyList;
			if( pkPacket->Pop(kGndKeyList) )
			{
				BM::Stream kTPacket( PT_T_N_REQ_DELETE_GROUND, g_kProcessCfg.ChannelNo() );
				kTPacket.Push(kGndKeyList);
				::SendToContents(kTPacket);

				g_kServerSetMgr.Locked_UnregistGnd(kGndKeyList);
			}
		}break;
	case PT_N_T_REQ_MSN_FRIENDCOMMAND:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV3, __FL__ << _T("[PT_N_T_REQ_MSN_FRIENDCOMMAND] This packet must go to Contents Server") );
		}break;
	case PT_N_T_REQ_MSN_FULL_DATA:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV3, __FL__ << _T("[PT_N_T_REQ_MSN_FULL_DATA] This packet must go to Contents Server") );
		}break;
	case PT_C_O_REQ_GMCHAT:
		{
//			BM::Stream kPacket(PT_T_GM_ANS_GMTOOL);
//			kPacket.Push(EGMC_SENDMSG_TO_GM);
//			kPacket.Push(*pkPacket);
//			g_kServerSetMgr.SendToGMServer(kPacket);
		}break;
	case PT_MCTRL_A_MMC_ANS_SERVER_COMMAND:
		{
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToContents(kPacket);
		}break;
 	case PT_C_M_REQ_CHAT:
		{
			INFO_LOG( BM::LOG_LV5, __FL__ << _T("[PT_C_M_REQ_CHAT] not implemented") );
			//pkPacket->PosAdjust();
			//SendToChannelChatMgr(*pkPacket);
		}break;
	case PT_C_GM_REQ_RECEIPT_PETITION:
	case PT_C_GM_REQ_REMAINDER_PETITION:
		{
			//Imm서버로 보낸다.
			BM::Stream kPacket(usType);
			kPacket.Push(*pkPacket);
			SendToContents(kPacket);
		}break;
	case PT_M_T_ANS_CHARACTER_BASEINFO:
		{
//			BM::Stream kPacket(PT_T_GM_ANS_GMCOMMAND, ENC_CHARACTER_INFO);
//			kPacket.Push(*pkPacket);
//			g_kServerSetMgr.SendToGMServer(kPacket);			
		}break;
	case PT_C_M_REQ_MARRY_COMMAND:
		{
			g_kMarryMgr.ProcessMsg(usType, pkPacket);
		}break;
	case PT_M_T_REQ_ENTER_SUPER_GROUND:
		{
			SGroundKey kOrgGndKey;
			BM::GUID kCharGuid;
			int iSuperGroundNo = 0, iSuperGroundMode = 0, iKeyGroundNo = 0, iPlayerLevel = 0, iSpawnNo = 0, iFloorNo = 0;
			bool bReqUseItem = false;
			bool IsElement = false;
			SPMO kReqUseItem;
			kOrgGndKey.ReadFromPacket(*pkPacket);
			pkPacket->Pop( kCharGuid );
			pkPacket->Pop( iPlayerLevel );
			pkPacket->Pop( iSuperGroundNo );
			pkPacket->Pop( iSuperGroundMode );
			pkPacket->Pop( iKeyGroundNo );
			pkPacket->Pop( iSpawnNo );
			pkPacket->Pop( iFloorNo );
			pkPacket->Pop( IsElement );
			pkPacket->Pop( bReqUseItem );
			if( bReqUseItem )
			{
				kReqUseItem.ReadFromPacket( *pkPacket );
			}

			SERVER_IDENTITY kFoundSI;
			HRESULT hRet = g_kServerSetMgr.Locked_GroundLoadBalance( SGroundKey(iSuperGroundNo), kFoundSI );
			if( S_OK != hRet )
			{
				g_kServerSetMgr.Locked_SendWarnMessage( kCharGuid, 6, EL_Warning );
				break;
			}

			SGroundKey const kTargetGndKey(iKeyGroundNo, BM::GUID::Create());
			BM::Stream kOrgMapPacket( PT_T_M_ANS_ENTER_SUPER_GROUND ); // 원 서버로
			kOrgMapPacket.Push(kCharGuid);
			kOrgMapPacket.Push(iSuperGroundNo);
			kOrgMapPacket.Push(iSuperGroundMode);
			kTargetGndKey.WriteToPacket(kOrgMapPacket);
			kOrgMapPacket.Push(iSpawnNo);
			kOrgMapPacket.Push(IsElement);
			kOrgMapPacket.Push(bReqUseItem);
			if( bReqUseItem )
			{
				kReqUseItem.WriteToPacket(kOrgMapPacket);
			}

			BM::Stream kPacket(PT_T_M_NFY_ENTER_SUPER_GROUND); // 입장할 서버로
			kTargetGndKey.WriteToPacket( kPacket );
			kPacket.Push( iPlayerLevel );
			kPacket.Push( iSuperGroundNo );
			kPacket.Push( iSuperGroundMode );
			kPacket.Push( iFloorNo );
			kOrgGndKey.WriteToPacket( kPacket );
			kPacket.Push( kOrgMapPacket.Data() );
			bool const bSendRet = SendToServer( kFoundSI, kPacket );
			if( !bSendRet )
			{
				g_kServerSetMgr.Locked_SendWarnMessage( kCharGuid, 6, EL_Warning );
			}
		}break;
	default:
		{
			if(OnRecvFromServer2(pkSession, usType, pkPacket))	{ return; }
			if(OnRecvFromServer3(pkSession, usType, pkPacket))	{ return; }

			CAUTION_LOG(BM::LOG_LV5, __FL__ << _T("unhandled packet Type[") << usType << _T("]"));
		}break;
	}
}

bool CALLBACK OnRecvFromServer2( CEL::CSession_Base *pkSession, unsigned short usType, BM::Stream * const pkPacket )
{
	switch(usType)
	{
	case PT_A_N_WRAPPED_PACKET:// 맵서버 -> 센터서버 -> 콘텐츠서버
		{
			SendToContents(*pkPacket);
		}break;
	case PT_A_RN_WRAPPED_PACKET:// 맵서버 -> 센터서버 -> 콘텐츠서버의 ContentsTask
		{
			EContentsMessageType eType;
			pkPacket->Pop(eType);
			SendToRealmContents(eType, *pkPacket);
		}break;
	case PT_A_I_WRAPPED_PACKET:
		{//ProcessCfg 에서 이렇게 들어오는데.
			SERVER_IDENTITY kSI;
			SGroundKey kKey;

			kSI.ReadFromPacket(*pkPacket);
			pkPacket->Pop(kKey); //-> 답 음네;..

			SendToItem( kSI, kKey, *pkPacket);
		}break;
	case PT_A_GND_WRAPPED_PACKET:// 콘텐츠(or 맵)서버 -> 센터서버 -> 맵서버
		{//같은코드 두군데임
			SGroundKey kKey;
			pkPacket->Pop(kKey);

			g_kServerSetMgr.Locked_SendToGround(kKey, *pkPacket, true);
		}break;
	case PT_A_A_WRAPPED_PACKET:// 받게 되는 모든 서버마다 해당 프로토콜을 선언해 줘야 함
		{
			short nServerNo = 0;
			pkPacket->Pop(nServerNo);

			BM::Stream kPacket(PT_A_A_WRAPPED_PACKET);
			kPacket.Push(*pkPacket);

//			g_kServerSetMgr.SendToServer(nServerNo, kPacket);
		}break;
	case PT_M_C_REQ_BUILDER_COMMAND:
		{
			// 맵 서버로 부터 빌더 커맨드가 왔다!
			BuilderCommandProcess(pkPacket);
		}break;
/*	case PT_M_T_SND_DISCONNEECT_USER:
		{// (중요)맵서버가 이걸 보낼때 유저정보 제거는 맵서버가 스스로 해야 한다!!!
			BM::GUID kMemberGuid;
			pkPacket->Pop(kMemberGuid);
			g_kServerSetMgr.DisconnectUser(kMemberGuid,SERVER_BIT_NOTMAP_PLAYERINFO);
		}break;
*/	case PT_M_T_NFY_REFRESH_USERCOUNT:
		{
		}break;
	case PT_M_T_REQ_SMS:
		{
			BM::Stream kPacket(PT_T_C_NFY_BULLHORN,*pkPacket);
			SendToServerType(CEL::ST_MAP, kPacket);
		}break;
	case PT_A_SEND_NOTICE:
		{
			PgNoticeAction kNotice;
			kNotice.Recv(pkPacket);
		}break;
	case PT_A_N_REQ_GAMETIME:
		{
			BM::Stream kGPacket(PT_N_A_NFY_GAMETIME);
			g_kEventView.WriteToPacket(false, kGPacket);
			pkSession->VSend(kGPacket);
		}break;
	case PT_T_N_ANS_KICK_USER:
		{
//			g_kServerSetMgr.Locked_ProcessRemoveUser( Locked_ProcessRemoveUserByGmOrder(pkPacket);
		}break;
	case PT_A_CN_WRAPPED_PACKET:
		{
			EContentsMessageType eType = PMET_NONE;
			if ( true == pkPacket->Pop(eType) )
			{
				int iSecondType = 0;
				pkPacket->Pop( iSecondType );
				::SendToChannelContents(eType, *pkPacket, iSecondType);
			}
		}break;
	case PT_S_M_WRAPPED_USER_PACKET:
		{
			SGroundKey kGroundKey;
			kGroundKey.ReadFromPacket( *pkPacket );

			BM::Stream kNfyPacket( PT_S_M_WRAPPED_USER_PACKET );
			kNfyPacket.Push( *pkPacket );
			SendToPvPLobby( kNfyPacket, kGroundKey.GroundNo() );
		}break;
	case PT_T_T_REQ_EXIT_LOBBY:
		{
			g_kServerSetMgr.Locked_PT_T_T_REQ_EXIT_LOBBY( pkPacket );
		}break;
	case PT_T_T_REQ_KICK_ROOM_USER:
		{
			BM::GUID kCharGuid;
			SGroundKey kGndkey;
			pkPacket->Pop( kCharGuid );
			
			g_kServerSetMgr.Locked_PT_T_T_REQ_KICK_ROOM_USER( kCharGuid, kGndkey );
		}break;
	case PT_M_T_ANS_KICK_ROOM_USER_NOTFOUND:
		{
			BM::GUID kCharGuid;
			SGroundKey kGndkey;
			pkPacket->Pop( kCharGuid );
			pkPacket->Pop( kGndkey );
			g_kServerSetMgr.Locked_PT_T_T_REQ_KICK_ROOM_USER( kCharGuid, kGndkey );
		}break;
	case PT_A_IM_WRAPPED_PACKET:
		{
			SendToImmigration(*pkPacket);
		}break;
	case PT_M_A_GODCMD:
		{
			EGMCmdType eGodCommandType = GMCMD_NONE;
			pkPacket->Pop(eGodCommandType);
			OnRecvGodCommand( eGodCommandType, pkPacket );
		}break;
	default:
		{
			//g_kMissionMgr.RecvPacket(usType, pkPacket) ;
			//CAUTION_LOG(BM::LOG_LV5, __FL__ << _T("unhandled packet Type[") << usType << _T("]"));
			return false;
		}break;
	}
	return true;
}

void BuilderCommandProcess(BM::Stream * const pkPacket)
{
	EBuilderCommand eCommand;
	pkPacket->Pop(eCommand);

	switch(eCommand)
	{
	case EBUILDERCOMMAND_ALLSERVER_NOTICE:
		{
			std::wstring wstrContent;
			pkPacket->Pop(wstrContent);

			BM::Stream kPacket(PT_T_C_NFY_NOTICE);
			kPacket.Push(wstrContent);

			// Contents Server에게도 보내자
			SendToContents(kPacket);
			// 모든 맵서버로 패킷을 보내자.
			//SendToServerType(CEL::ST_MAP, kPacket);
		}break;
	case EBUILDERCOMMAND_KICKUSER:
		{
			// TODO : 유저에게 끊어졌다고 패킷을 보낸다.
			//bool bSuccess = g_kServerSetMgr.RemoveSwitchUser(rkMemberGuid, SERVER_BIT_ALL);
		}break;
	}
}

void Recv_PT_A_S_REQ_GREETING(CEL::CSession_Base *pkSession, BM::Stream * const pkPacket)
{
	SERVER_IDENTITY kRecvSI;
	kRecvSI.ReadFromPacket(*pkPacket);
	
	INFO_LOG( BM::LOG_LV6, __FL__ << _T("RecvSI[") << C2L(kRecvSI) << _T("]") );
	std::wstring strVersion;
	pkPacket->Pop(strVersion);
	if( !CProcessConfig::IsCorrectVersion( strVersion, false ) )
	{
		INFO_LOG( BM::LOG_LV4, __FL__ << _T("Incorrect Version Mine[") << PACKET_VERSION_S << _T("] != There[") << strVersion.c_str() << _T("] R[")
			<< kRecvSI.nRealm << _T("]C[") << kRecvSI.nChannel << _T("]N[") << kRecvSI.nServerNo << _T("]T[") << kRecvSI.nServerType << _T("]")
			);
		pkSession->VTerminate();
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Packet_Version"));
		return;
	}

	if ( g_kProcessCfg.IsPublicChannel() && CEL::ST_SWITCH == kRecvSI.nServerType )
	{// 예외 처리

	}
	else if( (	kRecvSI.nRealm != g_kProcessCfg.RealmNo()
			||	kRecvSI.nChannel != g_kProcessCfg.ChannelNo() )
			&& kRecvSI.nServerType != CEL::ST_LOG)
	{
		CAUTION_LOG( BM::LOG_LV5, __FL__ << _T("Add Server Session Failed Realm[") << kRecvSI.nRealm << _T("] Chn[") << kRecvSI.nChannel
			<< _T("] No[") << kRecvSI.nServerNo << _T("] Type[") << kRecvSI.nServerType << _T("]")
			);
		pkSession->VTerminate();
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Add Server Session"));
		return;
	}

	if(S_OK != g_kProcessCfg.Locked_OnGreetingServer(kRecvSI, pkSession))
	{
		CAUTION_LOG( BM::LOG_LV0, __FL__ << _T("Add Server Session Failed Realm[") << kRecvSI.nRealm << _T("] Chn[") << kRecvSI.nChannel
			<< _T("] No[") << kRecvSI.nServerNo << _T("] Type[") << kRecvSI.nServerType << _T("]")
			);
		pkSession->VTerminate();
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Add Server Session"));
		return;
	}
	
	if( !SetSendWrapper(kRecvSI) )
	{
		CAUTION_LOG( BM::LOG_LV0, __FL__ << _T("SetSendWrapper Failed Realm[") << kRecvSI.nRealm << _T("] Chn[") << kRecvSI.nChannel
			<< _T("] No[") << kRecvSI.nServerNo << _T("] Type[") << kRecvSI.nServerType << _T("]")
			);
		pkSession->VTerminate();
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! SetSendWrapper"));
		return;
	}

	kRecvSI.WriteToPacket(pkSession->m_kSessionData);//이 세션의 SERVER_IDENTITY 기록

	BM::Stream kSendPacket(PT_A_S_ANS_GREETING);
	SERVER_IDENTITY const &kSendSI = g_kProcessCfg.ServerIdentity();
	//모든 서버에 보낼 내용
	//나의 서버 구분자.
	//전체 서버 리스트.
	kSendSI.WriteToPacket(kSendPacket);
	g_kProcessCfg.Locked_Write_ServerList( kSendPacket, 0 );
	
	switch(kRecvSI.nServerType)
	{
	case CEL::ST_ITEM:
		{
// 			CONT_DB_INIT_DESC kInitInfo;
// 			if(S_OK == g_kCoreCenter.GetDBInitInfo(kInitInfo))
// 			{
// 				kSendPacket.Push(kInitInfo);
// 				g_kTblDataMgr.DataToPacket(kSendPacket);
// 			}
// 			else
// 			{
				VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("No Use") );
//			}
		}break;
	case CEL::ST_SWITCH:
		{
			g_kSwitchAssignMgr.ConnectSwitch( kRecvSI );
			
			TABLE_LOCK(CONT_DEF_CASH_SHOP) kObjLock1;
			g_kTblDataMgr.GetContDef(kObjLock1);
			CONT_DEF_CASH_SHOP const * pCont = kObjLock1.Get();
			TABLE_LOCK(CONT_DEF_CASH_SHOP_ARTICLE) kObjLock2;
			g_kTblDataMgr.GetContDef(kObjLock2);
			CONT_DEF_CASH_SHOP_ARTICLE const * pCont2 = kObjLock2.Get();
			TABLE_LOCK(CONT_CASH_SHOP_ITEM_LIMITSELL) kObjLock3;
			g_kTblDataMgr.GetContDef(kObjLock3);
			CONT_CASH_SHOP_ITEM_LIMITSELL const * pCont3 = kObjLock3.Get();
			
			INFO_LOG(BM::LOG_LV7, _T("Send StoreKey(Ans Greeting Switch) ::")<< g_kControlDefMgr.StoreValueKey());
			kSendPacket.Push(g_kControlDefMgr.StoreValueKey());
			PU::TWriteTable_MM(kSendPacket, *pCont);
			PU::TWriteTable_MM(kSendPacket, *pCont2);
			PU::TWriteTable_MM(kSendPacket, *pCont3);
			
//			SendToServerType( CEL::ST_MAP, BM::Stream( PT_T_M_CONNECT_NEW_SWITCH ) );
			g_kAntiHackMgr.Locked_WriteToPacket(kSendPacket);
		}break;
	case CEL::ST_CENTER:
	case CEL::ST_LOGIN:
		{
		}break;
	case CEL::ST_MAP:
		{
			INFO_LOG(BM::LOG_LV7, _T("Send StoreKey(Ans Greeting Map) ::")<< g_kControlDefMgr.StoreValueKey());
			//맵 데이터 싱크.
			g_kServerSetMgr.Locked_OnGreetingServer(kRecvSI, pkSession);
			
			kSendPacket.Push(g_kControlDefMgr.StoreValueKey());
			g_kTblDataMgr.DataToPacket(kSendPacket);

			g_kAntiHackMgr.Locked_WriteToPacket(kSendPacket);

			g_kGambleMachine.WriteToPacket(kSendPacket);
			g_kDefPlayTime.WriteToPacket(kSendPacket);
		}break;
	case CEL::ST_LOG:
	case CEL::ST_MACHINE_CONTROL:
		{
		}break;
	default:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Incorrect Server Type [") << kRecvSI.nServerType << _T("]") );
			pkSession->VTerminate();
		}break;
	}

{
	//PgTimeCheck kTime( dynamic_cast<PgLogWorker_Base*>(&g_kLogWorker), LT_CAUTION, __FUNCTIONW__, __LINE__);
	DWORD const dwBegin = BM::GetTime32();
	INFO_LOG( BM::LOG_LV9, __FL__ << _T("Before VSend PacketSize[") << kSendPacket.Size() << _T("]") );
	pkSession->VSend(kSendPacket);
}
//	DWORD const dwEnd = BM::GetTime32();
//	INFO_LOG(BM::LOG_LV9, _T("[%s] End VSend ElapsedTime[%d]"), __FUNCTIONW__, dwEnd-dwBegin);
}

bool OnRecvGodCommand( EGMCmdType const eGodCommandType, BM::Stream * const pkPacket )
{
	switch(eGodCommandType)
	{
	case GMCMD_MAPMOVE_RECALL:
		{
			BM::GUID kReqCharGuid;
			SReqMapMove_CM kRMMC;
			std::wstring wstrCharacterName;
			bool bParty = false;
			pkPacket->Pop( kReqCharGuid );
			kRMMC.ReadFromPacket( *pkPacket );
			pkPacket->Pop( wstrCharacterName );
			pkPacket->Pop( bParty );

			VEC_GUID kUserList;
			SRealmUserInfo kRealmUserInfo;
			if ( true == g_kServerSetMgr.Locked_GetRealmUserByNickname( wstrCharacterName, kRealmUserInfo ) )
			{
				if ( true == bParty )
				{
					g_kPartyMgr.GetPartyMemberList( kUserList, kRealmUserInfo.kCharGuid, false, false );
				}
				else
				{
					kUserList.push_back( kRealmUserInfo.kCharGuid );
				}

				g_kServerSetMgr.Locked_Recv_PT_M_T_REQ_MAP_MOVE_COME( kRMMC, kUserList, false );
			}
			else
			{
				// 다른채널에 있을 수 있다.
				BM::Stream kNPacket( PT_T_N_GODCMD, eGodCommandType );
				kNPacket.Push( kReqCharGuid );
				kNPacket.Push( wstrCharacterName );
				::SendToContents( kNPacket );
			}
		}break;
	case GMCMD_MAPMOVE_TARGET:
		{
			BM::GUID kReqCharGuid;
			std::wstring wstrCharacterName;
			pkPacket->Pop( kReqCharGuid );
			pkPacket->Pop( wstrCharacterName );

			if ( !g_kServerSetMgr.Locked_TargetMapMoveByName( true, kReqCharGuid, wstrCharacterName, false ) )
			{
				// 다른채널에 있을 수 있다.
				BM::Stream kNPacket( PT_T_N_GODCMD, eGodCommandType );
				kNPacket.Push( kReqCharGuid );
				kNPacket.Push( wstrCharacterName );
				::SendToContents( kNPacket );
			}
		}break;
	case GMCMD_MAPMOVE_TARGET_TOMAP:
		{
			BM::GUID kReqCharGuid;
			std::wstring wstrCharacterName;
			bool bParty = false;
			int iTargetGroundNo = 0;
			short nTargetPortalNo = 0;
			pkPacket->Pop( kReqCharGuid );
			pkPacket->Pop( wstrCharacterName );
			pkPacket->Pop( bParty );
			pkPacket->Pop( iTargetGroundNo );
			pkPacket->Pop( nTargetPortalNo );

			VEC_GUID kUserList;
			SRealmUserInfo kRealmUserInfo;
			if ( true == g_kServerSetMgr.Locked_GetRealmUserByNickname( wstrCharacterName, kRealmUserInfo ) )
			{
				// 맵이 이동가능한 곳인지 검증을 해야 한다.
				CONT_DEFMAP const *pkContDefMap = NULL;
				g_kTblDataMgr.GetContDef( pkContDefMap );
				if ( pkContDefMap )
				{
					PgMapMoveChecker kMapMoveChecker( *pkContDefMap );
					EPartyMoveType const kMapMoveType = kMapMoveChecker.GetMoveType( iTargetGroundNo );
					if ( E_MOVE_LOCK != kMapMoveType )
					{
						SReqMapMove_CM kRMMC( MMET_GM );
						kRMMC.kGndKey.Set( iTargetGroundNo );
						kRMMC.nPortalNo = (nTargetPortalNo > 0 ? nTargetPortalNo : 1);

						if ( true == bParty )
						{
							g_kPartyMgr.GetPartyMemberList( kUserList, kRealmUserInfo.kCharGuid, false, false );
						}
						else
						{
							kUserList.push_back( kRealmUserInfo.kCharGuid );
						}

						g_kServerSetMgr.Locked_Recv_PT_M_T_REQ_MAP_MOVE_COME( kRMMC, kUserList, false );
					}
				}
			}
			else
			{
				// 다른채널에 있을 수 있다.
				BM::Stream kNPacket( PT_T_N_GODCMD, eGodCommandType );
				kNPacket.Push( kReqCharGuid );
				kNPacket.Push( wstrCharacterName );
				::SendToContents( kNPacket );
			}
		}break;
	case GMCMD_COMMUNITY_EVENT_START:
		{
			int ChannelNo = 0;
			int MapNo = 0;
			int EventNo = 0;

			pkPacket->Pop(ChannelNo);
			pkPacket->Pop(MapNo);
			pkPacket->Pop(EventNo);

			BM::Stream Packet(PT_T_M_NFY_COERCION_START_EVENT);
			Packet.Push(EventNo);

			::SendToChannelGround(ChannelNo, SGroundKey(MapNo), Packet);
		}break;
	default:
		{
			INFO_LOG( BM::LOG_LV2, __FL__ << _T("Type<") << eGodCommandType << _T("> Error!!") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Invalid CaseType"));
			return false;
		}break;
	}

	return true;
}