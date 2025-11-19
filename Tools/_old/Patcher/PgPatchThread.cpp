#include "StdAfx.h"
#include "resource.h"
#include "PatcherDlg.h"
#include "PgPatchThread.h"

//extern int g_iCRCCount;
extern volatile long g_iCRCCount;
extern CPatcherDlg* g_pDlg;

volatile long getCrcTime;
volatile long getCrcTotalTime;
volatile long getCrcCount;

#ifdef PG_USE_ACE
PgPatchThread::PgPatchThread()
	:m_kMsgPool(100)
{
	msg_queue()->high_water_mark(E_WATER_MARK);
}

PgPatchThread::~PgPatchThread(void)
{
}

bool PgPatchThread::DoCalcCRC(const std::wstring wstrInFileName, const std::wstring wstrInFilePath, BM::PgFIleInfo *pkInFileInfo)
{
	static int g_iDoCount = 0;

	if (pkInFileInfo == 0)
		return false;

	CRCInfo info;
	info.wstrFilePath = wstrInFilePath;
	info.pkFileInfo = pkInFileInfo;

	SWorkerThreadMessage *pkMsg = m_kMsgPool.New();
	pkMsg->Clear();
	pkMsg->iType = E_PTMT_CALCCRC;
	pkMsg->wstrFileName = wstrInFileName;
	pkMsg->wstrFilePath = wstrInFilePath;
	pkMsg->pkFileInfo = pkInFileInfo;

	if(-1 != msg_queue()->enqueue(pkMsg))
	{
		g_iDoCount += 1;
		return true;
	}

	return false;
}

int PgPatchThread::svc(void)
{
	//try {
	while( !IsStop() &&
			g_pDlg->GetIsProcess())//! stop 시그날 걸어서 꺼줄것.
	{
		SWorkerThreadMessage *pkMsg = NULL;

		ACE_Time_Value tv(1, 1000);	tv += ACE_OS::gettimeofday();
		if( -1 != msg_queue()->dequeue( pkMsg, &tv ) )
		{
			switch(pkMsg->iType)
			{
			case E_PTMT_CALCCRC:
				{
					BM::PgFIleInfo *pkFileInfo = pkMsg->pkFileInfo;
					std::wstring wstrFileName = pkMsg->wstrFileName;
					std::wstring wstrFilePath = pkMsg->wstrFilePath;

					DWORD time = ::GetTickCount();
					if (BM::GetFileCRC(wstrFilePath, pkFileInfo->iOrgCRC))
					{
						::InterlockedExchange(&getCrcTime, ::GetTickCount() - time);
						::InterlockedExchangeAdd(&getCrcTotalTime, getCrcTime);
						::InterlockedIncrement(&getCrcCount);

						INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Create CRC : %s %d"), _T(__FUNCTION__), __LINE__, wstrFilePath.c_str(), g_iCRCCount-1);
						INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Data : %lu, %f, %lu, %f"),
							_T(__FUNCTION__), __LINE__,
							getCrcTime, (float)getCrcTime / (float)getCrcCount, getCrcTotalTime, (float)getCrcTotalTime / (float)getCrcCount
							);

						if (g_pDlg)
						{
							std::wstring wstrText = L"Get File State : " + wstrFileName;
							g_pDlg->SetHeadStateText(MB(wstrText), false);
						}

						::InterlockedDecrement(&g_iCRCCount);
					}
					else
					{
						INFO_LOG( BM::LOG_LV1 , _T("[%s]-[%d] Create CRC ERROR : %s %d"), _T(__FUNCTION__), __LINE__, wstrFilePath.c_str(), g_iCRCCount-1);
						IsStop(false);
						g_pDlg->SetIsProcess(false);
						assert(0);
						MessageBox(0, wstrFilePath.c_str(), L"Create CRC ERROR", 0);

						return 0;
					}
				}
				break;
			default:
				{
					INFO_LOG( BM::LOG_LV1 , _T("[%s]-[%d] Thread Type invalid  %d"), _T(__FUNCTION__), __LINE__, pkMsg->iType);
					assert(0);
				}break;
			}
			pkMsg->Clear();
			m_kMsgPool.Delete(pkMsg);//메세지 풀로 돌림.
		}
	}
	//catch (CSystemException* e)
	//{
	//	SETDIR_ERROR_REPORT(TEXT("./Log"));
	//	TCHAR wcause[256];
	//	e->GetErrorMessage(wcause, 256);
	//	//FORMAT_ERROR_REPORT(e->mExceptInfo->ExceptionRecord->ExceptionCode, wcause, TEXT(""), 0);
	//	e->WriteAdditionalInfo();
	//	SAFE_DELETE(e);
	//}

	return 0;
}

#endif