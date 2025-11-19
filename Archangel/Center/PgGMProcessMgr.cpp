#include "StdAfx.h"
#include "PgGMProcessMgr.h"
//#include "Variant/PgControlDefMgr.h"

PgGMProcessMgr::PgGMProcessMgr(void)
{
}

PgGMProcessMgr::~PgGMProcessMgr(void)
{
}

void PgGMProcessMgr::FirstAnalysisGmOder(SGmOrder &rkOrderData)
{
	switch(rkOrderData.Type)
	{
	case ORDER_CHANGE_NAME: 
	case ORDER_CHANGE_STATE:
	case ORDER_CHANGE_ITEM_INFO:
	case ORDER_CHANGE_SKILL_INFO:
	case ORDER_CHANGE_POS:
	case ORDER_CHANGE_QUEST_INFO:
	case ORDER_CHANGE_CHARACTER_FACE:
	case ORDER_CHANGE_CP:
		{
			//유저가 접속중인지 확인
			SContentsUser kPlayer;
			if(S_OK == g_kServerSetMgr.Locked_GetPlayerInfo(rkOrderData.kGuid[0], true, kPlayer))
			{
				//Kick 하기 전에 메모리에 오더 데이터를 저장한다.
				if(AddGmOrder(rkOrderData))
				{
					//성공했으면 킥해준다
					CEL::CPacket kPacket(PT_T_M_REQ_KIC_USER);
					kPacket.Push(rkOrderData.kCmdGuid);
					kPacket.Push(rkOrderData.kGuid[1]);
					g_kServerSetMgr.Locked_SendToGround(kPlayer.kGndKey, kPacket);
				} else
				{
					VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s] overlaped GmOrder Data [%s]"), __FUNCTIONW__, rkOrderData.kCmdGuid.str().c_str());
				}
			} else
			{
				//바로 DB에 쓴다.
				AnalysisOderData(rkOrderData);
			}
		}break;
	case ORDER_CHANGE_GUILD_NAME:
		{
			CEL::CPacket kPacket(PT_T_N_ANS_GUILD_COMMAND);
			kPacket.Push(rkOrderData.kGuid[0]);
			kPacket.Push((BYTE) GC_GM_Rename);
			kPacket.Push(rkOrderData.wsString1);
			SendToRealmContents(PMET_GUILD, kPacket);
			SendOrderState(rkOrderData.kCmdGuid, OS_DONE);
		}break;
	case ORDER_CHANGE_PARTY_NAME:
		{
			CEL::CPacket kPacket(PT_C_N_REQ_PARTY_RENAME_GM, (BYTE)rkOrderData.iValue[0]);
			switch(rkOrderData.iValue[0])
			{
			case 1: kPacket.Push(rkOrderData.kGuid[1]);break;
			case 2: kPacket.Push(rkOrderData.kGuid[0]);break;
			case 3: kPacket.Push(rkOrderData.wsString1);break;
			default: break;
			}
			kPacket.Push(rkOrderData.wsString2);
			kPacket.Push(0);
			SendToGlobalPartyMgr(kPacket);
			SendOrderState(rkOrderData.kCmdGuid, OS_DONE);			
		}break;
	case ORDER_CHANGE_GM_LEVEL:
		{
			SContentsUser kUserInfo;
			if(g_kServerSetMgr.Locked_GetPlayerInfo(rkOrderData.kGuid[0], true, kUserInfo) == S_OK)
			{
				if(kUserInfo.kGndKey != 0)
				{
					CEL::CPacket kPacket(PT_T_M_REQ_CHANGE_GM_LEVEL);
					kPacket.Push(rkOrderData.kCmdGuid);
					kPacket.Push(rkOrderData.kGuid[0]);
					kPacket.Push(kUserInfo.kCharGuid);
					kPacket.Push((BYTE)rkOrderData.iValue[0]);
					g_kServerSetMgr.Locked_SendToGround(kUserInfo.kGndKey, kPacket);
				}
			} else
			{
				AnalysisOderData(rkOrderData);
			}
		}break;
	default:
		{
			//이거 외의 넘이 들어왔으면 문제 있는거임.
			INFO_LOG(BM::LOG_LV0, _T("[%s] Invalid OrderType [%d]"), __FUNCTIONW__, rkOrderData.Type);
		}break;
	}
}

bool PgGMProcessMgr::AnalysisOderData(SGmOrder &rkOrderData)
{
	switch(rkOrderData.Type)
	{
	case ORDER_CHANGE_NAME: 
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_CHARACTER_NAME, L"EXEC [dbo].[UP_Change_Character_Name] ?, ?, ?" );
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			kQuery.PushParam(rkOrderData.wsString1);
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ORDER_CHANGE_STATE:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_CHARACTER_STATE, L"EXEC [dbo].[UP_Change_Character_State] ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?" );
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);					//MemberId
			kQuery.PushParam(rkOrderData.kGuid[1]);					//CharacterId
			kQuery.PushParam((BYTE)rkOrderData.iValue[0]);			//Gender
			kQuery.PushParam(rkOrderData.iValue[1]);					//Race
			kQuery.PushParam((BYTE)rkOrderData.iValue[2]);			//Class
			kQuery.PushParam((short)rkOrderData.iValue[3]);			//Lv
			kQuery.PushParam(rkOrderData.biValue[0]);				//Exp
			kQuery.PushParam(rkOrderData.biValue[1]);				//Money
			kQuery.PushParam((int)rkOrderData.biValue[2]);			//HP
			kQuery.PushParam((int)rkOrderData.biValue[3]);			//MP
			kQuery.PushParam((short)rkOrderData.iValue[4]);			//Skill Point
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ORDER_CHANGE_POS:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_CHARACTER_POS, L"EXEC [dbo].[UP_Change_Character_Pos] ?, ?, ?, ?, ?, ?" );
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			kQuery.PushParam(rkOrderData.iValue[0]);
			kQuery.PushParam(rkOrderData.iValue[1]);
			kQuery.PushParam(rkOrderData.iValue[2]);
			kQuery.PushParam(rkOrderData.iValue[3]);
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ORDER_CHANGE_GM_LEVEL:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_GM_LEVEL, L"EXEC [dbo].[UP_Change_GM_Level] ?, ?, ?" );
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			kQuery.PushParam((BYTE)rkOrderData.iValue[0]);
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ORDER_CHANGE_ITEM_INFO:
		{


		}break;
	case ORDER_CHANGE_SKILL_INFO:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_SKILL_INFO, L"EXEC [dbo].[up_Change_Character_Skill] ?, ?, ?, ? ");
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.wsString2);
 			kQuery.PushParam(rkOrderData.wsString1);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ORDER_CHANGE_QUEST_INFO:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_QUEST_INFO, L"EXEC [dbo].[up_Change_Character_IngQuest] ?, ?, ? ");
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			
			kQuery.PushParam(rkOrderData.wsString1);
			g_kCoreCenter.PushQuery(kQuery, true); 
		}break;
	case ORDER_CHANGE_CHARACTER_FACE:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_CHARACTER_FACE, L"EXEC [dbo].[up_Change_Character_Face] ?, ?, ?, ?, ? ");
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			kQuery.PushParam(rkOrderData.iValue[0]);
			kQuery.PushParam(rkOrderData.iValue[1]);
			kQuery.PushParam(rkOrderData.iValue[2]);			
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ORDER_CHANGE_CP:
		{
			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_CHANGE_CP, L"EXEC [dbo].[up_Change_Character_CP] ?, ?, ? ");
			kQuery.QueryOwner(rkOrderData.kCmdGuid);
			kQuery.PushParam(rkOrderData.kGuid[0]);
			kQuery.PushParam(rkOrderData.kGuid[1]);
			kQuery.PushParam(rkOrderData.iValue[0]);
			g_kCoreCenter.PushQuery(kQuery, true);			
		}break;
	default:
		{
			INFO_LOG(BM::LOG_LV0, _T("[%s] Invalid OrderType [%d]"), __FUNCTIONW__, rkOrderData.Type);
		}break;
	}
	return true;
}

bool PgGMProcessMgr::AddGmOrder(SGmOrder &rkOrderData)
{
	SGmOrder* pkGmOrder = new SGmOrder;
	*pkGmOrder = rkOrderData;
	CONT_GMORDER::_Pairib kRet = m_kContGMOrder.insert(std::make_pair(rkOrderData.kCmdGuid, pkGmOrder));
	if(!kRet.second)
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s] Already Registed OrderData [OrderGuid: %s]"), __FUNCTIONW__, rkOrderData.kCmdGuid.str().c_str());
		SAFE_DELETE(pkGmOrder);
		return false;
	}
	
//	INFO_LOG(BM::LOG_LV5, _T("[%s] Regist Success GmOrder Data [OrderGuid: %s]"), __FUNCTIONW__, rkOrderData.kCmdGuid.str().c_str());

	return true;
}

void PgGMProcessMgr::RecvGMCommand(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket )
{
	EGMCommandType eCommand;
	BM::GUID kReqGuid;
	pkPacket->Pop(eCommand);
	pkPacket->Pop(kReqGuid);
//	INFO_LOG(BM::LOG_LV6, _T("[%s] Command[%d], ReqGuid[%s]"), __FUNCTIONW__, eCommand, kReqGuid.str().c_str());
	switch(eCommand)
	{
	case EGMC_MUTE:
		{
			std::wstring wstrName;
			int iTime;
			pkPacket->Pop(wstrName);
			pkPacket->Pop(iTime);

			//DB에 저장(그러나 일단은 Pass)

			SContentsUser kUserInfo;
			if(g_kServerSetMgr.Locked_GetPlayerInfo(wstrName, kUserInfo) == S_OK)
			{
				//동일 채널에 있으면 디버프 걸고....
				if(kUserInfo.kGndKey != 0)
				{
					CEL::CPacket kPacket(PT_T_M_REQ_USER_MUTE);
					kPacket.Push(kUserInfo.kCharGuid);
					kPacket.Push(iTime);
					g_kServerSetMgr.Locked_SendToGround(kUserInfo.kGndKey, kPacket);
				}
			}
		}break;
	case EGMC_KICKUSER:
		{
			int iCase;
			BM::GUID kMemberID;
			pkPacket->Pop(iCase);
			pkPacket->Pop(kMemberID);
			if(g_kServerSetMgr.Locked_ProcessRemoveUser(kMemberID))
			{
				if(iCase == ECK_ORDER)
					SendOrderState(kReqGuid);
				else
				{
					CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, EGMC_KICKUSER);
					kPacket.Push(kReqGuid);
					kPacket.Push(GM_ERR_SUCCESS);
					SendToImmigration(kPacket);
				}
			} else
			{
				if(iCase == ECK_ORDER)
					SendOrderState(kReqGuid, OS_RESERVE);
				else
				{
					CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, EGMC_KICKUSER);
					kPacket.Push(kReqGuid);
					kPacket.Push(GM_ERR_ALREADY_EXIST);
					SendToImmigration(kPacket);
				}
			}
		}break;
	case EGMC_FREEZEACCOUNT:
		{
			CEL::CPacket kPacket(PT_GM_A_REQ_GMCOMMAND, eCommand);
			kPacket.Push(kReqGuid);
			kPacket.Push(*pkPacket);
			SendToImmigration(kPacket);
		}break;
	case EGMC_SENDMSG_TO_USER:
		{
			unsigned short usChannel = 0;
			std::wstring kGmName;
			std::wstring kMsg;
			SOutsidePlayerData kPlayerData;

			pkPacket->Pop(usChannel);
			pkPacket->Pop(kGmName);
			pkPacket->Pop(kMsg);
			pkPacket->Pop(kPlayerData);

			CEL::CPacket kPacket(PT_O_C_NFY_GMCHAT);
			kPacket.Push(kReqGuid);	// GM guid
			kPacket.Push(kGmName);
			kPacket.Push(kMsg);
			g_kServerSetMgr.Locked_SendToUser(kPlayerData.kMembGuid, kPacket);

//			INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] GM Tool was req to server list."), __FUNCTIONW__, __LINE__);
		}break;
	case EGMC_NOTICE:
		{
			std::wstring wstrContent;
			pkPacket->Pop(wstrContent);

			CEL::CPacket kPacket(PT_T_C_NFY_NOTICE);
			kPacket.Push(wstrContent);

			// Contents Server에게도 보내자
			SendToContents(kPacket);

			// 모든 맵서버로 패킷을 보내자.
			//SendToServerType(CEL::ST_MAP, kPacket);
//			INFO_LOG(BM::LOG_LV7, _T("Notice Send to MapServer : %s"), wstrContent.c_str());
		}break;
/*
	case EGMC_CHAT_END:
		{
			SOutsidePlayerData kPlayerData;
			pkPacket->Pop(kPlayerData);
			CEL::CPacket kPacket(EGMC_CHAT_END);
			kPacket.Push(kReqGuid);
			g_kServerSetMgr.Locked_SendToUser(kPlayerData.kMembGuid, kPacket);
//			INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] GM Tool was req to server list."), __FUNCTIONW__, __LINE__);
		}break;
	case EGMC_GET_PETITIONDATA:
		{
			int iMaxcount;
			pkPacket->Pop(iMaxcount);
			CEL::DB_QUERY kQuery( DT_GM, DQT_SELECT_PETITION_DATA, _T("EXEC [dbo].[UP_Select_PetitionData] ?, ?"));
//			CEL::DB_QUERY kQuery( DT_GM, DQT_SELECT_PETITION_DATA, _T("EXEC [dbo].[UP_Select_PetitionData] ?"));
			kQuery.QueryOwner(kReqGuid);
			kQuery.PushParam(iMaxcount);
			kQuery.PushParam(g_kProcessCfg.ChannelNo());
			g_kCoreCenter.PushQuery(kQuery);
		}break;
	case EGMC_MODIFY_PETITIONDATA:
		{
			SPetitionData kModifyData;
			kModifyData.ReadFromPacket(*pkPacket);
			CEL::DB_QUERY kQuery( DT_GM, DQT_MODIFY_PETITION_DATA, _T("EXEC [dbo].[UP_Modify_Petition_Data] ?, ?, ?, ?, ?, ?, ?"));
			kQuery.QueryOwner(kReqGuid);
			kQuery.PushParam(kModifyData.m_PetitionId);
			kQuery.PushParam(kModifyData.m_GmId);
			kQuery.PushParam(kModifyData.m_State);
			kQuery.PushParam(kModifyData.m_Kind);
			kQuery.PushParam(kModifyData.m_Answerkind);
			kQuery.PushParam(kModifyData.m_dtStartTime);
			kQuery.PushParam(kModifyData.m_dtEndTime);
			g_kCoreCenter.PushQuery(kQuery, true);
		}break;
	case ENC_CHARACTER_INFO:
		{
			std::wstring kName;
			pkPacket->Pop(kName);
			CEL::DB_QUERY kQuery( DT_GM, DQT_GM_CHARACTER_INFO, _T("EXEC [dbo].[UP_GMCommand_Select_ChracterInfo] ?"));
			kQuery.QueryOwner(kReqGuid);
			TCHAR chName[MAX_CHARACTERNAME_LEN+1];
			SAFE_STRNCPY(chName, kName.c_str());
			kQuery.PushParam(chName);
			g_kCoreCenter.PushQuery(kQuery);
		}break;
	case ENC_CHARACTER_LIST1:
	case ENC_CHARACTER_LIST2:
		{
			int		iUID = 0;
			BYTE	byOnlyLive = 0;
			pkPacket->Pop(iUID);
			pkPacket->Pop(byOnlyLive);
			CEL::DB_QUERY kQuery( DT_GM, byOnlyLive ? DQT_GM_CHARACTER_LIST1:DQT_GM_CHARACTER_LIST2, _T("EXEC [dbo].[UP_GMCommand_Select_CharacterList] ?, ?"));
			kQuery.PushParam(iUID);
			kQuery.PushParam(byOnlyLive);
			g_kCoreCenter.PushQuery(kQuery);
		}break;
	case ENC_CAN_USING_NAME:
		{
			std::wstring kName;
			pkPacket->Pop(kName);

			if( wcscmp(kName.c_str(), L"") == 0)
			{
				CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, ENC_CAN_USING_NAME);
				kPacket.Push(ENC_CAN_USING_NAME);//동일 코드로 반환되면 일단 입력한 값에 문제가 있는거임				
				g_kServerSetMgr.SendToGMServer(kPacket);
				break;
			}

			BM::PgUnicodeFilter::CONT_ERROR_RESULT kFilterRet;
			if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_KOREA))
			{
				if(!g_kUnicodeFilter.IsCorrect(kName, kFilterRet))
				{
					CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, ENC_CAN_USING_NAME);
					kPacket.Push(ENC_CAN_USING_NAME);//동일 코드로 반환되면 일단 입력한 값에 문제가 있는거임				
					g_kServerSetMgr.SendToGMServer(kPacket);
					break;
				}
			}

			CEL::DB_QUERY kQuery(DT_PLAYER, DQT_GM_CHECK_NAME, L"EXEC [dbo].UP_CheckName ?");
			TCHAR szName[MAX_CHARACTERNAME_LEN + 1] = { 0, };
			SAFE_STRNCPY(szName, kName);
			kQuery.PushParam(szName);
			g_kCoreCenter.PushQuery(kQuery, false);
		}break;
*/
	default:
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s] Unknown GMCommand received CommandType[%d]"), __FUNCTIONW__, eCommand);
		}break;
	}
}


void PgGMProcessMgr::SendOrderState(BM::GUID const &rkOrderId, unsigned short usState)
{
	CEL::CPacket kPacket(PT_A_GM_ANS_GMORDER);
	kPacket.Push(rkOrderId);
	kPacket.Push(usState);
	SendToImmigration(kPacket);
}

bool PgGMProcessMgr::CommonQueryResult( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{ 
//		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
		int iError = S_OK;
		
		CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();
		if(rkResult.vecArray.end() != kIter)
		{
			kIter->Pop(iError);			++kIter;

			unsigned short	usState = OS_DONE;

			if(iError != S_OK)
				usState = OS_RESERVE;
			SendOrderState(rkResult.QueryOwner(), usState);
			return true;
		}
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_CHANGE_CHARACTER_NAME( CEL::DB_RESULT &rkResult )
{
	return CommonQueryResult(rkResult);
}


bool PgGMProcessMgr::Q_DQT_CHANGE_CHARACTER_STATE( CEL::DB_RESULT &rkResult )
{
	return CommonQueryResult(rkResult);
}

bool PgGMProcessMgr::Q_DQT_CHANGE_CHARACTER_POS( CEL::DB_RESULT &rkResult )
{
	return CommonQueryResult(rkResult);
}

bool PgGMProcessMgr::Q_DQT_CHANGE_GM_LEVEL(CEL::DB_RESULT &rkResult)
{
	return CommonQueryResult(rkResult);
}


bool PgGMProcessMgr::Q_DQT_CHANGE_CHARACTER_FACE(CEL::DB_RESULT &rkResult)
{
	return CommonQueryResult(rkResult);
}

bool PgGMProcessMgr::Q_DQT_CHANGE_QUEST_INFO(CEL::DB_RESULT &rkResult)
{
	return CommonQueryResult(rkResult);
}

bool PgGMProcessMgr::Q_DQT_CHANGE_SKILL_INFO(CEL::DB_RESULT &rkResult)
{
	return CommonQueryResult(rkResult);
}

bool PgGMProcessMgr::Q_DQT_CHANGE_CP(CEL::DB_RESULT &rkResult)
{
	return CommonQueryResult(rkResult);
}

/*
bool PgGMProcessMgr::Q_DQT_ITEM_PROCESS_CREATE( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{ 
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
		return true;
	}

	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_ITEM_PROCESS_MODIFY( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{ 
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
		return true;
	}

	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_ITEM_PROCESS_DELETE( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{ 
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
		return true;
	}

	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}

//bool PgGMProcessMgr::Q_DQT_CHANGE_SKILL_INFO( CEL::DB_RESULT &rkResult )
//{
//	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
//	{ 
//		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
//		return true;
//	}
//
//	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
//	return false;
//}
//
//bool PgGMProcessMgr::Q_DQT_CHANGE_QUEST_INFO( CEL::DB_RESULT &rkResult )
//{
//	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
//	{ 
//		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
//		return true;
//	}
//
//	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
//	return false;
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT PgGMProcessMgr::Receipt_Petition(CEL::CPacket &rkPacket)
{
	BM::GUID CharacterId; 
	BM::GUID MemberId;
	std::wstring wsTitle;
	std::wstring wsNote;

	rkPacket.Pop(CharacterId);
	rkPacket.Pop(MemberId);
	rkPacket.Pop(wsTitle);
	rkPacket.Pop(wsNote);

	short sChannelNo = g_kProcessCfg.ChannelNo();

	INFO_LOG(BM::LOG_LV6, _T("[%s] Receipt Petition"), __FUNCTIONW__);
	CEL::DB_QUERY kQuery(DT_GM, DQT_RECEIPT_PETITION, L"EXEC [dbo].[UP_Receipt_Petition] ?, ?, ?, ?, ?" );

	kQuery.PushParam(CharacterId);
	kQuery.PushParam(MemberId);
	kQuery.PushParam(sChannelNo);
	kQuery.PushParam(wsTitle);
	kQuery.PushParam(wsNote);
	
	return g_kCoreCenter.PushQuery(kQuery);
}

HRESULT PgGMProcessMgr::Select_PetitionState(CEL::CPacket &rkPacket)
{
	BM::GUID Guid;
	rkPacket.Pop(Guid);

	INFO_LOG(BM::LOG_LV6, _T("[%s] Select PetitionState"), __FUNCTIONW__);
	CEL::DB_QUERY kQuery(DT_GM, DQT_SELECT_PETITION_STATE, L"EXEC [dbo].[UP_Select_Petition_State] ?" );
	kQuery.PushParam(Guid);
	return g_kCoreCenter.PushQuery(kQuery, true);
} 

HRESULT PgGMProcessMgr::Remainder_Petition(BM::GUID &MemberGuid)
{
	INFO_LOG(BM::LOG_LV6, _T("[%s] Select Remainder Petition"), __FUNCTIONW__);
	CEL::DB_QUERY kQuery(DT_GM, DQT_REMAINDER_PETITION, L"EXEC [dbo].[UP_Select_Remainder_Petition] ?" );
	kQuery.PushParam(MemberGuid);
	return g_kCoreCenter.PushQuery(kQuery, true);
} 


bool PgGMProcessMgr::Q_DQT_RECEIPT_PETITION( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);

		int iReceiptIndex = 0;
		BM::GUID MemberGuid;
		CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();

		while(rkResult.vecArray.end() != kIter)
		{
			kIter->Pop(MemberGuid); ++kIter;
			kIter->Pop(iReceiptIndex); ++kIter;
		} 
		CEL::CPacket kPacket(PT_T_C_ANS_RECEIPT_PETITION, iReceiptIndex);
		SendToUser(MemberGuid, kPacket);
		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_SELECT_PETITION_STATE( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{ 
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
		int iCount = 0;
		BM::GUID MemberGuid;
		CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();

		while(rkResult.vecArray.end() != kIter)
		{
			kIter->Pop(MemberGuid); ++kIter;
			kIter->Pop(iCount); ++kIter;
		}

		//아직 처리되지 않은게 있으니 잠시 기다려라!!
		if (iCount > 0)
		{
			CEL::CPacket kPacket(PT_T_C_ANS_WAIT_RECEIPT, iCount);
			SendToUser(MemberGuid, kPacket);
		} else
			Remainder_Petition(MemberGuid);
			

		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_REMAINDER_PETITION( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{ 
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);
		int iCount = 0;
		BM::GUID MemberGuid;
		CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();

		while(rkResult.vecArray.end() != kIter)
		{
			kIter->Pop(MemberGuid); ++kIter;
			kIter->Pop(iCount); ++kIter;
		}
		CEL::CPacket kPacket(PT_T_C_ANS_REMAINDER_PETITION, iCount);
		SendToUser(MemberGuid, kPacket);

		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Failed"), __FUNCTIONW__, __LINE__);
	return false;
}


bool PgGMProcessMgr::Q_DQT_SELECT_PETITION_DATA( CEL::DB_RESULT &rkResult )
{

	CEL::CPacket kPacket(PT_T_GM_ANS_GMTOOL, EGMC_GET_PETITIONDATA);
	kPacket.Push(rkResult.QueryOwner());
	kPacket.Push(g_kProcessCfg.ChannelNo());

	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);

		if(rkResult.vecArray.size() == 0)
		{
			kPacket.Push(rkResult.vecArray.size());
		} else
		{
			CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();
			//몇개인지 넣고.
			kPacket.Push(rkResult.row_count);
			while(rkResult.vecArray.end() != kIter)
			{
				SPetitionData kNewPetitionData;
				kNewPetitionData.Clear();

				kIter->Pop(kNewPetitionData.m_PetitionId);kIter++;
				kIter->Pop(kNewPetitionData.m_szCharacterName);kIter++;
				kIter->Pop(kNewPetitionData.m_szTitle);kIter++;
				kIter->Pop(kNewPetitionData.m_szPetition);kIter++;
				kIter->Pop(kNewPetitionData.m_GmId);kIter++;
				kIter->Pop(kNewPetitionData.m_ChannelNo);kIter++;
				kIter->Pop(kNewPetitionData.m_State);kIter++;
				kIter->Pop(kNewPetitionData.m_Kind);kIter++;
				kIter->Pop(kNewPetitionData.m_dtReceiptTime);kIter++;
				kIter->Pop(kNewPetitionData.m_ReceiptIndex);kIter++;
				
				kNewPetitionData.WriteToPacket(kPacket);	
			}
		}
		g_kServerSetMgr.SendToGMServer(kPacket);

		INFO_LOG(BM::LOG_LV7, _T("Send Petition Data Success"));
		
		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] TABLE [DQT_SELECT_PETITION_DATA] is row count 0"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_MODIFY_PETITION_DATA( CEL::DB_RESULT &rkResult )
{
	CEL::CPacket kPacket(PT_T_GM_ANS_GMTOOL, EGMC_MODIFY_PETITIONDATA);
	kPacket.Push(rkResult.QueryOwner());

	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);

		CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();

		if(rkResult.vecArray.end() != kIter)
		{
			int iErrorCode;
			BM::GUID MemberId, CharacterId;

			kIter->Pop(iErrorCode);
			kIter->Pop(MemberId);
			kIter->Pop(CharacterId);
		
			kPacket.Push(iErrorCode);
			kPacket.Push(MemberId);
			kPacket.Push(CharacterId);

			g_kServerSetMgr.SendToGMServer(kPacket);
		}
		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] TABLE [DQT_MODIFY_PETITION_DATA] is row count 0"), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_GM_CHARACTER_INFO(CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);

		CEL::DB_DATA_ARRAY::const_iterator Iter = rkResult.vecArray.begin();

		if(rkResult.vecArray.end() != Iter)
		{
			if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_CHINA))
			{
			} else
			if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_KOREA))
			{
				int iErrorCode = ENC_CHARACTER_INFO +1;	//정상
				SNcGMCommandPack kNcPacket;

				Iter->Pop(iErrorCode); Iter++;
				if(iErrorCode != ENC_CHARACTER_INFO +2) //그런넘 없다.
				{
					Iter->Pop(kNcPacket.sValues[0]);		Iter++;		//ChannelNo
					Iter->Pop(kNcPacket.kString1);			Iter++;		//ID
					Iter->Pop(kNcPacket.iValues[0]);		Iter++;		//UID
					Iter->Pop(kNcPacket.iValues[1]);		Iter++;		//Cash
					Iter->Pop(kNcPacket.kString2);			Iter++;		//CharName
					Iter->Pop(kNcPacket.kGuid[0]);			Iter++;		//CharGuid
					Iter->Pop(kNcPacket.byValues[0]);		Iter++;		//GMLevel
					Iter->Pop(kNcPacket.iValues[2]);		Iter++;		//PlayTimePay
					Iter->Pop(kNcPacket.sValues[1]);		Iter++;		//Lv
					Iter->Pop(kNcPacket.byValues[1]);		Iter++;		//Gender
					Iter->Pop(kNcPacket.dtTime[0]);			Iter++;		//Birt Day
					Iter->Pop(kNcPacket.iValues[3]);		Iter++;		//HP
					Iter->Pop(kNcPacket.sValues[2]);		Iter++;		//MAXHP
					Iter->Pop(kNcPacket.iValues[4]);		Iter++;		//MP
					Iter->Pop(kNcPacket.sValues[3]);		Iter++;		//MAXMP
					Iter->Pop(kNcPacket.dtTime[1]);			Iter++;		//LastLoginDate
					Iter->Pop(kNcPacket.dtTime[2]);			Iter++;		//LastLogOutDate
					Iter->Pop(kNcPacket.biValues[0]);		Iter++;		//exp
					Iter->Pop(kNcPacket.sValues[4]);		Iter++;		//SkillPoint
					Iter->Pop(kNcPacket.byValues[2]);		Iter++;		//class
					Iter->Pop(kNcPacket.kGuid[1]);			Iter++;		//GuildId
					Iter->Pop(kNcPacket.kString3);			Iter++;		//GuildName
					Iter->Pop(kNcPacket.iValues[5]);		Iter++;		//MapNo
					Iter->Pop(kNcPacket.iValues[6]);		Iter++;		//Map X
					Iter->Pop(kNcPacket.iValues[7]);		Iter++;		//Map Y
					Iter->Pop(kNcPacket.iValues[8]);		Iter++;		//Map Z
				}
				//접속 여부를 확인하고 접속중이지 않으면 GM서버로 접속중이면 맵서버 데이터를 가져와야 한다.
				UPR(kNcPacket.kString1);
				SGroundKey kGndKey = g_kServerSetMgr.GetPlayerKey(kNcPacket.kString1);
				if(kGndKey.GroundNo() > 0)
				{
					CEL::CPacket kPacket(PT_T_M_REQ_CHARACTER_BASEINFO);
					kPacket.Push(iErrorCode);
					kNcPacket.WriteToPacket(kPacket);
					g_kServerSetMgr.Locked_SendToMap(kGndKey, kPacket, true);
				} else
				{
					CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, ENC_CHARACTER_INFO);
					kPacket.Push(iErrorCode);
					kNcPacket.WriteToPacket(kPacket);
					g_kServerSetMgr.SendToGMServer(kPacket);
				}
			}
		}
		return true;
	}


	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Query Error (UP_GMCommand_Select_ChracterInfo) "), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_GM_CHARACTER_LIST1(CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);

		CEL::DB_DATA_ARRAY::const_iterator Iter = rkResult.vecArray.begin();
		if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_CHINA))
		{
		} else
		if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_KOREA))
		{
			int iErrorCode = ENC_CHARACTER_LIST1 +1;	//정상
			CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, ENC_CHARACTER_LIST1);
			if(rkResult.vecArray.end() == Iter)
			{
				iErrorCode = ENC_CHARACTER_LIST1 +2; //실패
			}
			kPacket.Push(iErrorCode);
			kPacket.Push(rkResult.row_count);
			while(rkResult.vecArray.end() != Iter)
			{
				SNcGMCommandPack kNcPacket;
				Iter->Pop(kNcPacket.kString1);		Iter++;
				Iter->Pop(kNcPacket.kGuid[0]);		Iter++;
				Iter->Pop(kNcPacket.sValues[0]);	Iter++;
				Iter->Pop(kNcPacket.byValues[0]);	Iter++;
				Iter->Pop(kNcPacket.byValues[1]);	Iter++;
				kNcPacket.WriteToPacket(kPacket);
			}
			g_kServerSetMgr.SendToGMServer(kPacket);
		}
		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Query Error (UP_GMCommand_Select_ChracterInfo) "), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_GM_CHARACTER_LIST2(CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS==rkResult.eRet || CEL::DR_NO_RESULT==rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Success"), __FUNCTIONW__, __LINE__);

		CEL::DB_DATA_ARRAY::const_iterator Iter = rkResult.vecArray.begin();
		if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_CHINA))
		{
		} else
		if(g_kLocal.IsAbleNation(LOCAL_MGR::NC_KOREA))
		{
			int iErrorCode = ENC_CHARACTER_LIST2 +1;	//정상
			CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, ENC_CHARACTER_LIST2);
			if(rkResult.vecArray.end() == Iter)
			{
				iErrorCode = ENC_CHARACTER_LIST2 +2; //실패
			}
			kPacket.Push(iErrorCode);
			kPacket.Push(rkResult.row_count);
			while(rkResult.vecArray.end() != Iter)
			{
				SNcGMCommandPack kNcPacket;
				Iter->Pop(kNcPacket.kString1);		Iter++;
				Iter->Pop(kNcPacket.kGuid[0]);		Iter++;
				Iter->Pop(kNcPacket.sValues[0]);	Iter++;
				Iter->Pop(kNcPacket.byValues[0]);	Iter++;
				Iter->Pop(kNcPacket.byValues[1]);	Iter++;
				kNcPacket.WriteToPacket(kPacket);
			}
			g_kServerSetMgr.SendToGMServer(kPacket);
		}
		return true;
	}
	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Query Error (UP_GMCommand_Select_ChracterInfo) "), __FUNCTIONW__, __LINE__);
	return false;
}

bool PgGMProcessMgr::Q_DQT_GM_CHECK_NAME(CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS != rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] Query failed. check name ErrorCode[%d]"), __FUNCTIONW__, __LINE__, rkResult.eRet);
		return false;
	}

	CEL::DB_DATA_ARRAY::const_iterator itor = rkResult.vecArray.begin();
	if(rkResult.vecArray.end() != itor)
	{
		int iCannotUse = 1;// (0 : 사용가능, 1 : 사용불가)
		int iErrorCode = ENC_CAN_USING_NAME;
		std::wstring kName;
		(*itor).Pop(iCannotUse);	++itor;
		(*itor).Pop(kName);			++itor;
		CEL::CPacket kPacket(PT_A_GM_ANS_GMCOMMAND, ENC_CAN_USING_NAME);
		if(iCannotUse == 1)
		{
			iErrorCode++; //캐릭터 중복
		} else
		{
			iErrorCode += 2; //사용가능 
		}
		kPacket.Push(iErrorCode);		
		g_kServerSetMgr.SendToGMServer(kPacket);
	}
	return true;
}

//bool PgGMProcessMgr::Q_DQT_GM_DEATH_OR_ALIVE_CHARACTER(CEL::DB_RESULT &rkResult)
//{
//	if( CEL::DR_SUCCESS != rkResult.eRet )
//	{
//		INFO_LOG(BM::LOG_LV5, _T("[%s]-[%d] Query failed. Delete character ErrorCode[%d]"), __FUNCTIONW__, __LINE__, rkResult.eRet);
//		return false;
//	}
//
//	BM::GUID kCharacterGuid;
//	int iErrNo = 0;// 0 : 삭제성공
//	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
//	if(rkResult.vecArray.end() != itr)
//	{
//		(*itr).Pop(kCharacterGuid);	++itr;
//		(*itr).Pop(iErrNo);			++itr;
//	}
//
//	switch(iErrNo)
//	{
//	case 1: INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d]Change Character state Sucess!! CharacterGUID:[%s]"), __FUNCTION__, __LINE__, kCharacterGuid.str().c_str()); break;
//	case 2: INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d]Character Delete Failed!! CharacterGUID:[%s]"), __FUNCTION__, __LINE__, kCharacterGuid.str().c_str()); break;
//	case 3: INFO_LOG(BM::LOG_LV7, _T("[%s]-[%d] Character Restore Failed!! CharacterGUID:[%s]"), __FUNCTION__, __LINE__, kCharacterGuid.str().c_str()); break;
//	}
//	return true;
//=======
//}


bool PgGMProcessMgr::Q_DQT_GM_SELECT_ALL_GM_MEMBER( CEL::DB_RESULT &rkResult )
{
	if( CEL::DR_SUCCESS == rkResult.eRet || CEL::DR_NO_RESULT == rkResult.eRet )
	{
		CEL::CPacket kPacket(PT_MCTRL_GT_C_ANS_AUTHLIST);
		kPacket.Push(rkResult.row_count);

		CEL::DB_DATA_ARRAY::const_iterator result_iter = rkResult.vecArray.begin();
		while(rkResult.vecArray.end() != result_iter)
		{
			STerminalAuthInfo kNewAuthInfo;

			std::wstring kID, kPW, kIP;

			(*result_iter).Pop(kNewAuthInfo.kID);		++result_iter;
			(*result_iter).Pop(kNewAuthInfo.kPW);		++result_iter;
			(*result_iter).Pop(kNewAuthInfo.kAuthIP);	++result_iter;
			(*result_iter).Pop(kNewAuthInfo.cGrant);	++result_iter;

			kNewAuthInfo.WriteToPacket(kPacket);
		}
		g_kServerSetMgr.SendToMCtrlServer(kPacket);
		return true;
	}
	INFO_LOG(BM::LOG_LV1, _T("[%s]-[%d] Query failed. Ret[%d]"), __FUNCTIONW__, __LINE__, rkResult.eRet);
	return false;
}
*/

bool PgGMProcessMgr::ExecuteGmOrder(BM::GUID const &rkCmdGuid)
{
	CONT_GMORDER::iterator Itr = m_kContGMOrder.find(rkCmdGuid);
	if(Itr == m_kContGMOrder.end())
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s]-[%d] Find not  GmOrder Data [OrderGuid: %s]"), __FUNCTIONW__, __LINE__, rkCmdGuid.str().c_str());
	}
	CONT_GMORDER::mapped_type pkElement = Itr->second;
	if(pkElement)
	{
		SGmOrder kOrder= *pkElement;
		AnalysisOderData(kOrder);
		m_kContGMOrder.erase(rkCmdGuid);
		SAFE_DELETE(pkElement);
		return true;
	}
	return false;
}
