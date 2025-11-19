#include "stdafx.h"
#include "PgTimer.h"
#include "../PgLog.h"

int g_iQueryType = 0;

void CALLBACK Timer_HeartBeat(DWORD dwUserData)
{
	PgLogWrapper kLogData(LOG_SYSTEM_HEARTBEAT);
	kLogData.ChannelNo(g_kProcessCfg.ChannelNo());
	kLogData.Push((int)g_kProcessCfg.ServerNo());
	WriteLog( kLogData );//스스로 로그.

/*	//테스트코드 -> 쓰려면 앞에 /를 쳐라
	//남은 쿼리 갯수를 알아야한다.
	INFO_LOG(BM::LOG_LV3, _T("Rmain Query Count  Start [%d]"), 
		g_kCoreCenter.GetQueryCount(DT_LOG));
	
	int i = 50000;
	while(i--)
	{
		WriteLog( kLogData );
	}

//	INFO_LOG(BM::LOG_LV3, _T("Rmain Query Count  End [%d]"), 
//		g_kCoreCenter.GetQueryCount(DT_LOG));

//*/
//	INFO_LOG(BM::LOG_LV3, _T("Rmain Query Count End[%d]"), 
//		g_kCoreCenter.GetQueryCount(DT_LOG));
}
#if 0
#if 0
void CALLBACK Timer_TestDB(DWORD dwUserData)
{
	//사용중 유저 수 기록
#if 1
	switch(g_iQueryType)
#else
	switch(rand()%5)
#endif
	{
	case 0:
		{
			CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC1, _T("EXEC [dbo].[testproc]"));
			for(int i = 0;i < 500;i++)
			{
				g_kCoreCenter.PushQuery(kQuery);
			}
		}break;
	case 1:
		{
			CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC2, _T("EXEC [dbo].[testproc2] ?,?,?"));
			kQuery.PushParam(100);
			kQuery.PushParam(std::wstring(L"아하하하하하"));
			kQuery.PushParam(2000);

			for(int i = 0;i < 500;i++)
			{
				g_kCoreCenter.PushQuery(kQuery);
			}
		}break;
	case 2:
		{
			CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC3, _T("exec [dbo].[testproc5]"));
			for(int i = 0;i < 500;i++)
			{
				g_kCoreCenter.PushQuery(kQuery);
			}
		}break;
	case 3:
		{
			CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC4, _T("exec [dbo].[testproc4] ?"));
			BYTE Data[100] = {151};
			kQuery.PushParam(Data,sizeof(Data));

			for(int i = 0;i < 500;i++)
			{
				g_kCoreCenter.PushQuery(kQuery);
			}
		}break;
	case 4:
		{
			CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC5, _T("{? = call [dbo].[testproc3](?,?,?,?,? ,?,?,?,?,? ,?,?,?,?)}"));
			kQuery.PushParam(1);
			kQuery.PushParam(2);
			kQuery.PushParam(3);
			kQuery.PushParam(4);
			kQuery.PushParam(5);
			kQuery.PushParam(6);
			kQuery.PushParam(7);
			kQuery.PushParam(8);
			kQuery.PushParam(9);
			kQuery.PushParam(10);
			kQuery.PushParam(11);
			kQuery.PushParam(12);
			kQuery.PushParam(13);
			kQuery.PushParam(14);

			for(int i = 0;i < 500;i++)
			{
				g_kCoreCenter.PushQuery(kQuery);
			}
		}break;
	}
}
#else
void CALLBACK Timer_TestDB(DWORD dwUserData)
{
	//사용중 유저 수 기록
	for(int i = 0;i < 500;i++)
	{
		switch(rand()%5)
		{
		case 0:
			{
				CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC4, _T("EXEC [dbo].[testproc]"));
				g_kCoreCenter.PushQuery(kQuery);
			}break;
		case 1:
			{
				CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC4, _T("EXEC [dbo].[testproc2] ?,?,?"));
				kQuery.PushParam(100);
				kQuery.PushParam(std::wstring(L"아하하하하하"));
				kQuery.PushParam(2000);
				g_kCoreCenter.PushQuery(kQuery);
			}break;
		case 2:
			{
				CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC4, _T("exec [dbo].[testproc5]"));
				g_kCoreCenter.PushQuery(kQuery);
			}break;
		case 3:
			{
				CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC4, _T("exec [dbo].[testproc4] ?"));
				BYTE Data[100] = {151};
				kQuery.PushParam(Data,sizeof(Data));
				g_kCoreCenter.PushQuery(kQuery);
			}break;
		case 4:
			{
				CEL::DB_QUERY kQuery( DT_LOG, DQT_TEST_PROC4, _T("{? = call [dbo].[testproc3](?,?,?,?,? ,?,?,?,?,? ,?,?,?,?)}"));
				kQuery.PushParam(1);
				kQuery.PushParam(2);
				kQuery.PushParam(3);
				kQuery.PushParam(4);
				kQuery.PushParam(5);
				kQuery.PushParam(6);
				kQuery.PushParam(7);
				kQuery.PushParam(8);
				kQuery.PushParam(9);
				kQuery.PushParam(10);
				kQuery.PushParam(11);
				kQuery.PushParam(12);
				kQuery.PushParam(13);
				kQuery.PushParam(14);
				g_kCoreCenter.PushQuery(kQuery);
			}break;
		}
	}
}
#endif
#else
void CALLBACK Timer_TestDB(DWORD dwUserData)
{
}
#endif