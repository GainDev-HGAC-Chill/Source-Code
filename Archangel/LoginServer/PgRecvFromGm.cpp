#include "stdafx.h"
#include "PgRecvFromGm.h"


void CALLBACK OnAcceptFromGM(CEL::CSession_Base *pkSession)
{	//!  세션락
	std::vector<char> kEncodeKey;
	if(S_OK == pkSession->VGetEncodeKey(kEncodeKey))
	{
		INFO_LOG(BM::LOG_LV6, _T("[%s]-[%d] Send EncryptKey"), __FUNCTIONW__, __LINE__);

		CEL::CPacket kPacket(PT_A_ENCRYPT_KEY);
		kPacket.Push(kEncodeKey);

		pkSession->VSend(kPacket, false);
	}
	else
	{
		INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] Get EncryptKey Failed. Session Terminate!"), __FUNCTIONW__, __LINE__);
		pkSession->VTerminate();
	}
}
void CALLBACK OnDisconnectFromGM(CEL::CSession_Base *pkSession)
{//!  세션락
	/*
	if ( FAILED(g_kGMUserMgr.Release(pkSession->SessionKey().SessionGuid())) )
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s] Disconnected(No GMUser) [%s]"), __FUNCTIONW__, pkSession->SessionKey().SessionGuid().str().c_str());
	}
	*/
}

void CALLBACK OnRecvFromGM(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket)
{	// 세션키로 해당 채널을 찾아 메시지를  multiplexing 함.
	unsigned short usType = 0;
	pkPacket->Pop(usType);

	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Recved Start[%d]"), __FUNCTIONW__, __LINE__, usType );

	switch( usType )
	{

		}break;
	default:
		{
		}break;
	}
}


PgGmMgr::PgGmMgr(void)
{

}

PgGmMgr::~PgGmMgr(void)
{

}

HRESULT PgGmMgr::ProcessGmAuth(SClientTryLogin const &kGM, CEL::CSession_Base* pkSession)
{
	BM::CAutoMutex kLock(m_kMutex);

	if( !g_kProcessCfg.CheckVersion( kGM.szVersion ) )
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s] Wrong Version : User[%s-%s], ReqVersion[%s], ServerVersion[%s]"), __FUNCTIONW__, kGM.szID, pkSession->Addr().wstrIP.c_str(), kGM.szVersion, PACKET_VERSION );
		return E_FAIL;
	}

	CONT_GM_USER_MAP_SESSION::const_iterator Itr = m_kGmUser.find(pkSession->SessionKey());
	if(Itr != m_kGmUser.end())
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] Regist Yet ID[%s], Session Guid[%s]"),__FUNCTIONW__,kGM.szID,pkSession->SessionKey().SessionGuid().str().c_str());
		return E_FAIL;
	}

	CONT_GM_USER_MAP_SESSION::_Pairib kPair = m_kGmUser.insert(std::make_pair(pkSession->SessionKey(), kGM));
	if(!kPair.second)
	{
			INFO_LOG(BM::LOG_LV5,_T("[%s] Regist Yet ID[%s], Session Guid[%s]"),__FUNCTIONW__,kGM.szID,pkSession->SessionKey().SessionGuid().str().c_str());
			return E_FAIL;
	}


	SAuthInfo &rkAuthInfo = kPair.first->second;

	rkAuthInfo = SServerTryLogin(kGM);
	rkAuthInfo.dwTryTime = ::timeGetTime();
	rkAuthInfo.SessionKey(pkSession->SessionKey());
	rkAuthInfo.addrRemote	= pkSession->Addr();
	rkAuthInfo.kLoginServer	= g_kProcessCfg.ServerIdentity();

	return S_OK;
}