#include "stdafx.h"
#include "Lohengrin/PgRealmManager.h"


typedef std::list<int> CONT_NUMBER;
typedef std::map< BM::GUID, CONT_NUMBER > CONT_Q_RESULT;

CONT_Q_RESULT g_kQResult;
static DWORD starttime = 0;
static DWORD lasttime = 0;

HRESULT Q_DQT_TEST( CEL::DB_RESULT &rkResult )
{
	return S_OK;

	static Loki::Mutex kMutex;
	BM::CAutoMutex kLock(kMutex);
	
	if(!starttime)
	{
		starttime = timeGetTime();
	}

	lasttime = timeGetTime();

	int iSize = rkResult.vecArray.size();

	if(iSize != 2)
	{
		__asm int 3;
	}

	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();

	BM::GUID kGuid;
	int iNo = 0;
	itr->Pop(kGuid);	++itr;
	itr->Pop(iNo);		++itr;
//*	
	CEL::CONT_QUERY_TARGET::iterator target_itor =  rkResult.m_kContQueryTarget.begin();
	while(target_itor != rkResult.m_kContQueryTarget.end())
	{
		CONT_Q_RESULT::_Pairib ret = g_kQResult.insert(std::make_pair((*target_itor), CONT_NUMBER()));
		(*ret.first).second.push_back(iNo);

		++target_itor;
	}
//*/

//	std::wstring kStr;
//	itr->Pop(kStr);
	
//	CAUTION_LOG(BM::LOG_LV5,_T("[%s] Result[%s]."),__FUNCTIONW__, kStr.c_str());
	return S_OK;
}

HRESULT Q_DQT_TEST2( CEL::DB_RESULT &rkResult )
{
	return S_OK;
}




void CheckQResult()
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Time [%d]"), __FUNCTIONW__, __LINE__ , lasttime - starttime);

	CONT_Q_RESULT::const_iterator qr_itor = g_kQResult.begin();
	while(qr_itor != g_kQResult.end())
	{
		CONT_NUMBER const &element = (*qr_itor).second;
		CONT_NUMBER::const_iterator list_itor = element.begin();
		
		if(!element.empty())
		{
			int iValue = (*list_itor);
			++list_itor;

			while(list_itor != element.end())
			{
				if(iValue <= *list_itor)
				{
					__asm int 3;
				}
				++list_itor;
			}
		}

		++qr_itor;
	}

	g_kQResult.clear();
}