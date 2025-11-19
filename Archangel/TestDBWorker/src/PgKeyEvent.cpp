
#include "stdafx.h"
#include "../PgLog.h"
#include "BM/TimeCheck.h"

#include "CEL/Query.h"

#include "objbase.h"

bool CALLBACK OnEscape( unsigned short const &rkInputKey)
{
	std::cout<< __FUNCTIONW__ << std::endl;
	
	PgTimeCheck kTime(g_aLog[LT_INFO], __FUNCTIONW__, __LINE__);

	int i = 10000;
	while(--i)
	{
		char *pk1 = new char[204800];
		char *pk2 = new char[204800];

		memset(pk1, 0, 204800);
		memset(pk2, 0, 204800);

		delete []pk1;
		delete []pk2;

//		std::vector<char> kVec(204800);
//		kVec.resize(204800);
//		std::vector<char> kVec2(204800);
//		kVec2.resize(204800);

		//std::vector<char> kVec;
		//kVec.reserve(204800);
		//kVec.resize(204800);
		//
		//std::vector<char> kVec2;
		//kVec2.reserve(204800);
		//kVec2.resize(204800);

	}

//	ConsoleCommander.StopSignal(true);
	return true;
}


bool CALLBACK OnF1( unsigned short const &rkInputKey)
{
	std::cout<< __FUNCTIONW__ << std::endl;

	g_kCoreCenter.DisplayState(g_aLog[LT_INFO]);
	g_kProcessCfg.Locked_DisplayState();
/*	
	{
//		std::vector< char > kTemp;
//		kTemp.resize(20480 * 20);
		char* pkData = new char [20480 *10];
		delete []pkData;
	}
	{
		CEL::CDBSession::CONT_DBBINDDATA kData;
		kData.resize(100);
	}
*/
	return true;
}

bool CALLBACK OnF2( unsigned short const &rkInputKey)
{
	std::wcout<< __FUNCTIONW__ << std::endl;
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Test Start"), __FUNCTIONW__, __LINE__ );

	PgTimeCheck kTimeCheck(g_aLog[LT_INFO], __FUNCTIONW__, __LINE__);
/*
create proc dbo.up_worker_test
@guid uniqueidentifier,
@int int
as
begin
	select @guid, @int

end
*/
	std::vector< BM::GUID > kContGuid;
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());

	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());
	kContGuid.push_back(BM::GUID::Create());

	BM::GUID kGuid = BM::GUID::Create();
	int i =  10000;
	while(--i)
	{
		BM::GUID kTempGuid = BM::GUID::Create();
		CEL::DB_QUERY_TRAN kQTran;
//*
//		CEL::DB_QUERY kQuery(DT_PLAYER, DQT_TEST, L"exec up_worker_test ?, ?");
//		kQuery.PushParam(BM::GUID::Create());
//		kQuery.PushParam(i);
//*/
		
/*
		EXEC [dbo].[up_Item_Remove]
		EXEC [dbo].[up_Item_Create]
		EXEC [dbo].[up_Item_Modify]
		EXEC [dbo].[up_Money_Modify]
		EXEC [dbo].[up_CP_Modify]
		*/

		
		CEL::DB_QUERY kQuery2(DT_PLAYER, DQT_TEST2, L"EXEC [dbo].[up_Item_Create]");
		kQuery2.PushStrParam(kTempGuid);
		kQuery2.PushStrParam(BM::GUID::Create());
		kQuery2.PushStrParam(1);
		kQuery2.PushStrParam(1);
		kQuery2.PushStrParam(1);

		kQuery2.PushStrParam(1);
		kQuery2.PushStrParam(1);
		kQuery2.PushStrParam(1);
		kQuery2.PushStrParam(1);
	
		CEL::DB_QUERY kQuery1(DT_PLAYER, DQT_TEST, L"EXEC [dbo].[up_Item_Remove]");
		kQuery1.PushStrParam(kTempGuid);



///*
		CEL::DB_QUERY kQuery(DT_PLAYER, DQT_TEST, L"exec up_worker_test");
		kQuery.PushStrParam(BM::GUID::Create());
		kQuery.PushStrParam(i);
//*/
		int iOwnerCount = BM::Rand_Range(0,9);
//		kQuery.InsertQueryTarget(kContGuid.at(iOwnerCount));
		kQuery.InsertQueryTarget(BM::GUID::Create());
/*		
		int iOwnerCount = 1;
		while(iOwnerCount--)
		{
			int iRet = 0;
			int const iRate = BM::Rand_Range(0,100);
			
			if(iRate < 100)		{			iRet = 4;		}
			if(iRate < 90)		{			iRet = 3;		}
			if(iRate < 70)		{			iRet = 2;		}
			if(iRate < 40)		{			iRet = 1;		}

			kQuery.InsertQueryTarget(kContGuid.at(iRet));
		}
//*/
//		kQuery.InsertQueryTarget(kContGuid.at(BM::Rand_Index(5)));
//		kQuery.InsertQueryTarget(BM::GUID::Create());
//		kQuery.InsertQueryTarget(kGuid);


/*
		CEL::tagDB_QUERY_TRAN *pkTrn = new CEL::tagDB_QUERY_TRAN;
		pkTrn->push_back(kQuery);
		delete pkTrn;
		continue;
*/
		kQTran.QueryType(DQT_TEST);
		kQTran.DBIndex(DT_PLAYER);

		kQTran.push_back(kQuery);
		kQTran.push_back(kQuery);
		

//		g_kCoreCenter.PushQuery(kQuery2, false);
		g_kCoreCenter.PushQuery(kQuery1, false);
//		g_kCoreCenter.PushQuery(kQTran, false);
//		{

//		}
		Sleep(100000);
//		g_kCoreCenter.PushQuery(kQuery, false);
//		Sleep(100000);
		if(!(i%1000))
		{
			OnF1(0);
		}
	}

	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Test Complete"), __FUNCTIONW__, __LINE__ );

	return true;
}

bool CALLBACK OnF3( unsigned short const &rkInputKey)
{
	std::wcout<< __FUNCTIONW__ << std::endl;
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Test Start"), __FUNCTIONW__, __LINE__ );

	int i = 80000;
	while(--i)
	{
		BM::GUID rkMemberGuid;

//		CEL::DB_QUERY kQuery(DT_PLAYER, 1, L"{? = call dbo.up_SelectCharacter2('3510374b-b116-4337-87d4-e94f80ab61b5', 0, 0, 0)}");
//		CEL::DB_QUERY kQuery(DT_PLAYER, 1, L"Exec dbo.up_SelectCharacter2 '3510374b-b116-4337-87d4-e94f80ab61b5', 0, 0, 0");
		CEL::DB_QUERY kQuery(DT_PLAYER, 1, L"exec sp_help sp_help");
		BYTE byCount = 0;
		int iError = 0;
//		kQuery.PushParam( rkMemberGuid );	// 인자값:멤버GUID
//		kQuery.PushParam( (BYTE)0 );		// 인자값:State 0 이면 정상. 1 이면 삭제된놈.
//		kQuery.PushParam(byCount);
//		kQuery.PushParam(iError);
		kQuery.QueryOwner(rkMemberGuid);
	//	kQuery.QueryGuid(kQueryGuid);
	//	kQuery.contUserData.Push(0);

		if(S_OK == g_kCoreCenter.PushQuery(kQuery, true))
		{
		}
	}

	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Test Complete"), __FUNCTIONW__, __LINE__ );

	return true;
}

extern void CheckQResult();

bool CALLBACK OnF4( unsigned short const &rkInputKey)
{
	std::wcout<< __FUNCTIONW__ << std::endl;
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Test Start"), __FUNCTIONW__, __LINE__ );

	CheckQResult();

	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Test Complete"), __FUNCTIONW__, __LINE__ );

	return true;
}


bool CALLBACK OnF5( unsigned short const &rkInputKey)
{
/*    if(FAILED(::CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE | COINIT_SPEED_OVER_MEMORY)))   
        return false;   
  
    const TCHAR* const  connectionString = _T("Provider=SQLNCLI; Data Source=localhost\\SQLEXPRESS; Trusted_Connection=yes; Database=SpaceDB;");   
  
    for(int i=0; i<3; i++)   
    {   
        _ConnectionPtr pConnection1 = NULL;   
  
        // Open a connection using OLE DB syntax.   
        TESTHR(pConnection1.CreateInstance(_T("ADODB.Connection")));      pConnection1->Open(connectionString,"","",adConnectUnspecified);   
  
        pConnection1->Execute(_T("exec sp_help sp_help"), NULL, adCmdText);   
  
        if (pConnection1)   
            if (pConnection1->State == adStateOpen)   
                pConnection1->Close();   
    }   
  
    ::CoUninitialize(); 
*/
	return false;
}  

bool CALLBACK OnTerminateServer(WORD const& rkInputKey)
{
	INFO_LOG(BM::LOG_LV6, _T("==========================================================="));
	INFO_LOG(BM::LOG_LV6, _T("[LogServer] will be shutdown"));
	INFO_LOG(BM::LOG_LV6, _T("\tIt takes some times depens on system....WAITING..."));
	INFO_LOG(BM::LOG_LV6, _T("==========================================================="));
	ConsoleCommander.StopSignal(true);
	INFO_LOG(BM::LOG_LV6, _T("=== Shutdonw END ===="));
	return false;
}


bool CALLBACK OnEnd(WORD const& rkInputKey)
{
	// Ctrl + Shift + HOME
	std::cout << __FUNCTION__ << " / Key:" << rkInputKey << std::endl;
	SHORT sState = GetKeyState(VK_SHIFT);
	if (HIBYTE(sState) == 0)
	{
		return false;
	}
	sState = GetKeyState(VK_CONTROL);
	if (HIBYTE(sState) == 0)
	{
		return false;
	}
	std::cout << "SUCCESS " << __FUNCTION__ << " / Key:" << rkInputKey << std::endl;

	if ( IDOK == ::MessageBoxA(NULL,"[WARNING] Center Server will be CRASHED.. are you sure??","DRAGONICA_Center",MB_OKCANCEL) )
	{
		if ( IDOK == ::MessageBoxA(NULL,"[WARNING][WARNING] Center Server will be CRASHED.. are you sure??","DRAGONICA_Center",MB_OKCANCEL) )
		{
			INFO_LOG(BM::LOG_LV0, _T("[%s] Server crashed by INPUT"), __FUNCTIONW__);
//			::RaiseException(1,  EXCEPTION_NONCONTINUABLE_EXCEPTION, 0, NULL);
			int * p = NULL;
			*p = 1;
		}
	}
	return false;
}

bool RegistKeyEvent()
{
	ConsoleCommander.Regist( VK_ESCAPE,	OnEscape );
	ConsoleCommander.Regist( VK_F1,	OnF1 );
	ConsoleCommander.Regist( VK_F2,	OnF2 );
	ConsoleCommander.Regist( VK_F3,	OnF3 );
	ConsoleCommander.Regist( VK_F4,	OnF4 );
	ConsoleCommander.Regist( VK_F5,	OnF5 );
	ConsoleCommander.Regist( VK_F11, OnTerminateServer );
	
	ConsoleCommander.Regist( VK_END,	OnEnd );
	return true;
}
