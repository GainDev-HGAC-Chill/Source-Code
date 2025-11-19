#include "stdafx.h"
#include "variant/GM_const.h"
#include "PgChnRpcModule.h"
#include "informer_h.h"
#include "PgMsgHolder.h"
#include "PgGmTask.h"
#include "PgGmUserMgr.h"

#ifdef _DEBUG
#define RPC_WAIT_TIME_MAX	9999000
#else
#define RPC_WAIT_TIME_MAX	20000
#endif

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

//	태스크는. 메세지 홀더를 알 필요가 없고...
/*
	문제는 리턴이 안되어야 하는데.. => 네트웍을 싱글로 물려놓다니 -_-;..
	메세지 콜 -> 홀더준비 -> 디스패쳐에 등록 -> 결과 나오면 홀더에 던짐(홀더를 알 방법은??) 
	
	디스패쳐에다. 홀더 컨트롤러를 붙일까??
	-> 홀더 컨테이너 락을 잡으면 성능에 극심한 정체.
	-> 홀더는 외부 개체로 잡아야하고.
*/

std::wstring ErrCodeToStr(int const iErrorCode)
{
	std::wstring strMsg = _T("No");
	switch(iErrorCode)
	{
	case GE_SUCCESS:		{strMsg = _T("SUCCESS");			}break;
	case GE_INCORRECT_ID:	{strMsg = _T("GE_INCORRECT_ID");	}break;
	case GE_SYSTEM_ERR:		{strMsg = _T("GE_SYSTEM_ERR");		}break;
	case GE_ALREADY_EXIST:	{strMsg = _T("GE_ALREADY_EXIST");	}break;
	case GE_USING_ID:		{strMsg = _T("GE_USING_ID");		}break;
	case GE_UNKNOWN_ERROR:	{strMsg = _T("GE_UNKNOWN_ERROR");	}break;
	case GE_NOT_ONLINE:		{strMsg = _T("GE_NOT_ONLINE");		}break;
	case GE_CLOSE_ACCOUNT:	{strMsg = _T("GE_CLOSE_ACCOUNT");	}break;
	case GE_NOT_ALLOW_IP:	{strMsg = _T("GE_NOT_ALLOW_IP");	}break;
	case GE_WORNG_ID_OR_PW:	{strMsg = _T("GE_WORNG_ID_OR_PW");	}break;
	case GE_LOGINED_ID:		{strMsg = _T("GE_LOGINED_ID");		}break;
	case GE_NOT_IMPLEMENTED:{strMsg = _T("GE_NOT_IMPLEMENTED");	}break;
	case GE_TIMEOUT:		{strMsg = _T("GE_TIMEOUT");			}break;
	default:				{strMsg = _T("FAILED");				}break;
	}
	return strMsg;
}

int ProcessRPCMsg_Sub(PgMsgQue* pkMsgQueue)
{//pkMsgQueue 를 쥐고있는 매세지 객체는 스레드 실행중 파괴 될 수 있기 때문에. 함수에서 접근하는 것을 방지하기위해 함수를 분리한다.
	PgMsgQue::MsgType kResponseMsg;
	int iErrorCode = 0;
	if(!pkMsgQueue->WaitMsg(RPC_WAIT_TIME_MAX, kResponseMsg))
	{//메세지 시간 오버임.
		iErrorCode = GE_TIMEOUT;
	}
	else
	{
		std::wstring kAccountID;
		short sEmpty = 0;
		int iCash = 0;
		kResponseMsg.Pop(sEmpty);//패킷 타입이네.
		kResponseMsg.Pop(kAccountID);
		kResponseMsg.Pop(iErrorCode);
	
		if(kResponseMsg.Pop(iCash))
		{//뽑기 성공이면 값 넣는다.
			pkMsgQueue->SetRetrunValue(iCash);
		}
	}

	INFO_LOG(BM::LOG_LV7, _T("RPC[")<< pkMsgQueue->FunctionName() <<_T("] ") << pkMsgQueue->AccountID() <<_T(" :ErrCode=") << HEX(iErrorCode) << _COMMA_ << ErrCodeToStr(iErrorCode) );//로그를 왜 계속 찍지??
	return iErrorCode;
}

int ProcessRPCMsg(SGMEventOrder *pkOrderMsg)
{//pkOrderMsg는 스레드 실행중 파괴 될 수 있기 때문에. 
// 함수에서 접근하는 것을 방지하기위해 함수를 분리한다.
// VPush 라인 이후로 pkOrderMsg의 생명 보장이 안되므로, 참조자 뽑는건 VPush 이전에 시행.
	PgMsgQue* pkMsgQueue = reinterpret_cast<PgMsgQue*>(pkOrderMsg->m_pkMsgQue);//pkMsgQueue 이것만 살아있는것.
	int iReturnCode = GE_SYSTEM_ERR;
	if(S_OK == g_kGMTask.VPush(pkOrderMsg))//넣는거 성공해야 웨이팅.
	{
		iReturnCode = ProcessRPCMsg_Sub(pkMsgQueue);
	}

	g_kGMTask.VCompleteMsg(pkMsgQueue->MsgGuid());

	return iReturnCode;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int KickPlayer(handle_t hBinding, wchar_t const *szAccountID)
{
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);
	pkMsg->ePriMsgType = GOET_KICK_USER;
	pkMsg->InsertTarget(szAccountID);

	return ProcessRPCMsg(pkMsg);
}

int ChangePassword(handle_t hBinding, wchar_t const *szAccountID, wchar_t const *szPassword)
{
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);
	pkMsg->ePriMsgType = GOET_CHANGE_PW;
	pkMsg->InsertTarget(szAccountID);

	pkMsg->Push((std::wstring)szPassword);

	return ProcessRPCMsg(pkMsg);
}

int CreateAccount(handle_t hBinding, wchar_t const *szAccountID, wchar_t const *szPassword, wchar_t const *szBirthday)
{
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);
//hold 
	pkMsg->ePriMsgType = GOET_CREATE_ACCOUNT;
	pkMsg->InsertTarget(szAccountID);

	pkMsg->Push((std::wstring)szPassword);
	pkMsg->Push((std::wstring)szBirthday);

	return ProcessRPCMsg(pkMsg);
}

int AddPoint(handle_t hBinding, wchar_t const *szPayId, wchar_t const *szAccountID, const int iPoints)
{//Thread safe. => 
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);

	pkMsg->ePriMsgType = GOET_ADD_POINT;
	pkMsg->InsertTarget(szAccountID);

	pkMsg->Push(iPoints);

	return ProcessRPCMsg(pkMsg);
}

int FreezeAccount(handle_t hBinding, wchar_t const *szAccountID, int iNewState)
{
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);

	pkMsg->ePriMsgType = GOET_FREEZE_ACCOUNT;
	pkMsg->InsertTarget(szAccountID);

	pkMsg->Push(iNewState);

	return ProcessRPCMsg(pkMsg);
}


int GetPoint(handle_t hBinding, wchar_t const *szAccountID, int* piReturnCode)
{
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);
	kMsgQue.SetRetrunPtr(piReturnCode);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);

	pkMsg->ePriMsgType = GOET_GET_POINT;
	pkMsg->InsertTarget(szAccountID);

	return ProcessRPCMsg(pkMsg);
}

int ChangeBirthday(handle_t hBinding, wchar_t const *szAccountID, wchar_t const *szBirthday)
{
	PgMsgQue kMsgQue(szAccountID, __FUNCTIONW__);

	SGMEventOrder *pkMsg = new SGMEventOrder(&kMsgQue);

	pkMsg->ePriMsgType = GOET_CHANGE_BIRTH;
	pkMsg->InsertTarget(szAccountID);

	pkMsg->Push((std::wstring)szBirthday);

	return ProcessRPCMsg(pkMsg);
}

//not used
int AuxiliaryPassword(handle_t hBinding, wchar_t const *szCharName, wchar_t const *szAuxiliaryPassword, int iSetType)
{
	return GE_NOT_IMPLEMENTED;
}

int GiveItem(handle_t hBinding, wchar_t const *szAccountID, int iItemID, const int iCount)
{
	return GE_NOT_IMPLEMENTED;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
PgChnRpcModule::PgChnRpcModule(void)
{
	if(StartRPC())
	{
		INFO_LOG(BM::LOG_LV5, __FL__ << _T("RPC Start Success") );
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, __FL__ << _T("RPC Start Failed") );
	}
	
}

PgChnRpcModule::~PgChnRpcModule(void)
{
	StopRPC();
}

bool PgChnRpcModule::StartRPC()
{
	if(	RPC_S_OK==RpcServerUseAllProtseqsIf(RPC_C_PROTSEQ_MAX_REQS_DEFAULT, informer_v1_0_s_ifspec, NULL)
	&&	RPC_S_OK==RpcServerRegisterIfEx(informer_v1_0_s_ifspec, NULL, NULL, RPC_IF_AUTOLISTEN, RPC_C_LISTEN_MAX_CALLS_DEFAULT, NULL))
	{
		return true;
	}
	return false;
}

void PgChnRpcModule::StopRPC()
{
	RpcServerUnregisterIf(informer_v1_0_s_ifspec, NULL, TRUE);
}

void PgChnRpcModule::LocaleGMCommandProcess(BM::Stream * const pkPacket)
{
	EGMCommandType eCommand;
	BM::GUID kReqGuid;
	pkPacket->Pop(eCommand);
	pkPacket->Pop(kReqGuid);

	std::wstring kAccountID;
	m_kMsgHolder.MsgOwner(kReqGuid, kAccountID);

	switch (eCommand)
	{
	case EGMC_KICKUSER:
	case EGMC_CHANGEPASSWORD:
	case EGMC_CREATE_USER_ACCOUNT:
	case EGMC_FREEZEACCOUNT:
	case EGMC_CHN_ADDCASH:
	case EGMC_CHN_CHANGE_BIRTHDAY:
		{
			int iErrorCode;
			pkPacket->Pop(iErrorCode);

			VPostErrorMsg(kReqGuid, kAccountID, 0, iErrorCode);
		}break;
	case EGMC_CHN_GETCASH:
		{
			int iErrorCode, iCash;
			pkPacket->Pop(iErrorCode);
			pkPacket->Pop(iCash);

			VPostErrorMsg(kReqGuid, kAccountID, 0, iErrorCode, iCash);
		}break;
	default:
		{
			INFO_LOG( BM::LOG_LV0, __FL__ << _T("Unknown GMCommand received CommandType[") << (int)eCommand << _T("]") );
		}break;
	}
}

bool PgChnRpcModule::ReqKickUser(BM::GUID const &rkReqKey, wchar_t const *szString)
{
	if(szString == NULL)
	{
		INFO_LOG( BM::LOG_LV0, _T("szString is Null") );
		return false;
	}

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_KICKUSER);
	kPacket.Push(rkReqKey);
	kPacket.Push(ECK_CHN);
	std::wstring wstrID = szString;
	UPR(wstrID);
	kPacket.Push(wstrID);
	return SendToImmigration(kPacket);
}

bool PgChnRpcModule::ReqChangePassWord(BM::GUID const &rkReqKey, wchar_t const *szAccountId, wchar_t const *szNewPassword, void const *Input)
{
	if((szAccountId == NULL) || (szNewPassword == NULL))
	{
		INFO_LOG( BM::LOG_LV0, _T("szAccountId or szNewPassword is Null") );
		return false;
	}

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_CHANGEPASSWORD);
	kPacket.Push(rkReqKey);
	std::wstring wID = szAccountId;

	std::wstring wPassword = szNewPassword;
	kPacket.Push(wID);
	kPacket.Push(wPassword);
	return SendToImmigration(kPacket);
}

bool PgChnRpcModule::ReqCreateAccount(BM::GUID const &rkReqKey, wchar_t const *szAccountId, wchar_t const *szPassword, void const *Input)
{
	if((szAccountId == NULL) || (szPassword == NULL))
	{
		INFO_LOG( BM::LOG_LV0, _T("szAccountId or szPassword is Null") );
		return false;
	}

	wchar_t *szBirthday = (wchar_t *)Input;

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_CREATE_USER_ACCOUNT);
	kPacket.Push(rkReqKey);
	std::wstring kID = szAccountId;
	std::wstring kPassword = szPassword;
	std::wstring kBirthday = szBirthday;

	kPacket.Push(kID);
	kPacket.Push(kPassword);
	kPacket.Push(kBirthday);
	return SendToImmigration(kPacket);
}

bool PgChnRpcModule::ReqFreezeAccount(BM::GUID const &rkReqKey, wchar_t const *szAccountId, int iValue, void*)
{
	if(szAccountId == NULL)
	{
		INFO_LOG( BM::LOG_LV0, __FL__ << _T("szAccountId is Null") );
		return false;
	}

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_FREEZEACCOUNT);
	kPacket.Push(rkReqKey);
	kPacket.Push(ECK_CHN);
	std::wstring wID = szAccountId;
	UPR(wID);
	int iBlock = iValue;
	BM::DBTIMESTAMP_EX kStart, kEnd;
	kPacket.Push(wID);
	kPacket.Push(iBlock);
	kPacket.Push(kStart);
	kPacket.Push(kEnd);
	return SendToImmigration(kPacket);
}

bool PgChnRpcModule::ReqAddPoint(BM::GUID const &rkReqKey, wchar_t const *szAccountId, int iAddPoint)
{
	if(szAccountId == NULL)
	{
		INFO_LOG( BM::LOG_LV0, _T("szAccountId is Null") );
		return false;
	}

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_CHN_ADDCASH);
	kPacket.Push(rkReqKey);
	std::wstring wID = szAccountId;
	UPR(wID);
	kPacket.Push(wID);
	kPacket.Push(iAddPoint);
	return SendToImmigration(kPacket);
}

bool PgChnRpcModule::ReqGetPoint(BM::GUID const &rkReqKey, wchar_t const *szAccountId)
{
	if(szAccountId == NULL)
	{
		INFO_LOG( BM::LOG_LV0, _T("szAccountId is Null") );
		return false;
	}

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_CHN_GETCASH);
	kPacket.Push(rkReqKey);
	std::wstring wID = szAccountId;
	UPR(wID);
	kPacket.Push(wID);
 	return SendToImmigration(kPacket);
}

bool PgChnRpcModule::ReqChangeBirthday(BM::GUID const &rkReqKey, wchar_t const *szAccount, wchar_t const *szBirthDay)
{
	if(szAccount == NULL || szBirthDay == NULL)
	{
		INFO_LOG( BM::LOG_LV0, _T("szAccount or szBirthday is Null") );
	}

	BM::Stream kPacket(PT_GM_A_REQ_GMCOMMAND, EGMC_CHN_CHANGE_BIRTHDAY);
	kPacket.Push(rkReqKey);
	std::wstring kID = szAccount;
	UPR(kID);
	std::wstring kBirthday = szBirthDay;
	kPacket.Push(kID);
	kPacket.Push(kBirthday);
	return SendToImmigration(kPacket);
}

HRESULT PgChnRpcModule::VHookVPush(void const* pkPtr)
{//위험한걸 알고 있는데. 
//	MSG_QUE를 내부 생성하면, 호출한곳에서 알 수 없고
//	외부껄 가져오면 내부에서 쓸때 박살 날 수 있어서 걱정임.
	SGMEventOrder const* pkWorkData = reinterpret_cast<SGMEventOrder const*>(pkPtr);
	
	PgMsgQue *pkMsgQue = reinterpret_cast<PgMsgQue*>(pkWorkData->m_pkMsgQue);

	if(pkMsgQue)
	{
		m_kMsgHolder.MsgReady(pkWorkData->MsgGuid(), *pkMsgQue);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT PgChnRpcModule::VPostErrorMsg(BM::GUID const &kMsgGuid, std::wstring const& kAccountID, short const nType, int const iErrorCode, int const iCash)
{
	PgMsgQue::MsgType kRPacket(nType);
	kRPacket.Push(kAccountID);
	kRPacket.Push(iErrorCode);
	kRPacket.Push(iCash);
	
	return m_kMsgHolder.SignalMsg(kMsgGuid, kRPacket);//에러 발송과 동시에 삭제.
}

HRESULT PgChnRpcModule::VCompleteMsg(BM::GUID const &kMsgGuid)
{
	PgMsgQue::MsgType kRPacket(0);
	return m_kMsgHolder.SignalMsg(kMsgGuid, kRPacket);//이게 지우는것.
}
