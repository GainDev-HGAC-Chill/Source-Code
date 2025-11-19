
// Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include "PgTestModule.h"
#include "BM/FileSupport.h"
#include "BM/Common.h"

class PgFileLoadTask
	: public PgTask< std::string >
{
public:
	void Init()
	{
	}

	virtual void HandleMessage(std::string *pkMsg)
	{
		HandleMessage_Float(pkMsg);
//		HandleMessage_SaveCheck(pkMsg);
//		HandleMessage_fstream(pkMsg);
	}

	virtual void HandleMessage_Float(std::string *pkMsg)
	{

	}
	
	virtual bool PutMsg(std::string &rkMsg, unsigned long ulPriority = 0)
	{
		::InterlockedIncrement(&m_kQueuedCount);
		return PgTask< std::string >::PutMsg(rkMsg);
	}

	typedef std::vector< std::string > CONT_FOLDERS;
	CONT_FOLDERS m_kFolders;
	volatile long m_kLoadCount;
	
	volatile long m_kQueuedCount;
	
	typedef std::map<std::string, int> CONT_CANT_LOAD_INFO;
	CONT_CANT_LOAD_INFO m_kContCantLoad;
	Loki::Mutex m_kMutex;
};
PgFileLoadTask g_kTask;

void CALLBACK OnRegist(CEL::SRegistResult const &rkArg)
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] OnRegist Failed"), __FUNCTIONW__, __LINE__);
	}

	if( CEL::RT_FINAL_SIGNAL == rkArg.eType )
	{//추가 등록 완료
		if(g_kCoreCenter.SvcStart())
		{
			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
			INFO_LOG(BM::LOG_LV6, _T("============ CoreCenter Run ======================"));
			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
			printf("start svc");
		}
		else
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================"));
		}
	}
}

void Q_DQT_SAMPLE(CEL::DB_RESULT &rkResult)
{
	BM::GUID kGuid;
	double d1=0, d2=0, d3=0;
	int i;
	__int64 i64;
	short s;
	std::wstring kStr;

	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	while ( itr != rkResult.vecArray.end() )
	{
		
		itr->Pop( kGuid);		++itr;
		itr->Pop( d1);		++itr;
		itr->Pop( d2);		++itr;
		itr->Pop( d3);		++itr;
		itr->Pop( i);		++itr;
		itr->Pop( i64 );		++itr;
		itr->Pop( s );		++itr;
		itr->Pop( kStr );		++itr;
	}
}

HRESULT CALLBACK OnDB_EXECUTE(CEL::DB_RESULT &rkResult)
{
	switch(rkResult.QueryType())
	{
	case 1:	{ Q_DQT_SAMPLE(rkResult); }break;//		{ Q_DQT_WRITE_LOG( rkResult );	}break;
	}
	
	return S_OK;
}

HRESULT CALLBACK OnDB_EXECUTE_TRAN(CEL::DB_RESULT_TRAN &rkResult)
{
	return S_OK;
}

bool CALLBACK OnF1( unsigned short const &rkInputKey)
{
	std::cout<< __FUNCTION__ << std::endl;

	char buffer[_CVTBUFSIZE] = {0,};
	errno_t err = _gcvt_s(buffer, _CVTBUFSIZE, 123456.12345, 20);

	int index = 10000;
	while(index--)
	{
		CEL::DB_QUERY kQuery(1, 1, L"EXEC [dbo].[up_test_insert]");
		BM::GUID kGUid = BM::GUID::Create();

		float d1 = 2509.544f, d2 = 14687.544f, d3 = 30.894547f;
		int i;
		__int64 i64;
		short s;
		std::wstring kStr;
		
		kQuery.PushStrParam(kGUid);
		kQuery.PushStrParam(d1);
		kQuery.PushStrParam(d2);
		kQuery.PushStrParam(d3);
		kQuery.PushStrParam(i);
		kQuery.PushStrParam(i64);
		kQuery.PushStrParam(s);
		kQuery.PushStrParam(kStr);

		g_kCoreCenter.PushQuery(kQuery);
	}
	return true;
}

bool CALLBACK OnF2( unsigned short const &rkInputKey)
{
	std::cout<< __FUNCTION__ << std::endl;

	int index = 1;
	while(index--)
	{
		CEL::DB_QUERY kQuery(1, 1, L"EXEC [dbo].[up_test_select]");
		BM::GUID kGUid = BM::GUID::Create();

		g_kCoreCenter.PushQuery(kQuery);
	}
	return true;
}

bool RegistKeyEvent()
{
//	g_kConsoleCommander.Regist( VK_ESCAPE,	OnEscape );
	g_kConsoleCommander.Regist( VK_F1,	OnF1 );
	g_kConsoleCommander.Regist( VK_F2,	OnF2 );
//	g_kConsoleCommander.Regist( VK_F11, OnTerminateServer );
	
//	g_kConsoleCommander.Regist( VK_END,	OnEnd );
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(!g_kLocal.LoadFromINI( L"./Local.ini"))
	{
		return 0;
	}

	CEL::INIT_CENTER_DESC kCenterInit;
	kCenterInit.eOT = BM::OUTPUT_JUST_TRACE;
	kCenterInit.pOnRegist = OnRegist;
	kCenterInit.bIsUseDBWorker = true;
	kCenterInit.dwProactorThreadCount = __min(kCenterInit.dwProactorThreadCount, 8);//서버가 있긴한데 뭐 빠를 필요는 없고 하니까.

	g_kCoreCenter.Init( kCenterInit );

	CONT_DB_INIT_DESC kContDBInit;

	if(!ReadDBConfig( EConfigType_Ini, _T(""), SERVER_IDENTITY(), kContDBInit ) )
	{
		return 0;
	}

	CONT_DB_INIT_DESC::iterator dbinit_itor = kContDBInit.begin();
	while(dbinit_itor != kContDBInit.end())
	{
		CEL::INIT_DB_DESC &kDBInit = (*dbinit_itor);
		
		kDBInit.dwThreadCount = 5;
		kDBInit.bUseConsoleLog = true;
		kDBInit.OnDBExecute = OnDB_EXECUTE;
		kDBInit.OnDBExecuteTran = OnDB_EXECUTE_TRAN;
		
		//1: 6200 개 남음	25000 개.
		//2: 6100 개 남음	19000 ~ 22000
			// 2번이 약간 더 빠름.
		g_kCoreCenter.Regist(CEL::RT_DB_WORKER, &kDBInit);
		++dbinit_itor;
	}

	CEL::INIT_FINAL_SIGNAL kFinalInit;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	RegistKeyEvent();

	g_kConsoleCommander.MainLoof();

	g_kCoreCenter.Close();

	printf("close");

	return 0;
}



