#include "stdafx.h"
#include "constant.h"

bool Q_DQT_LOAD_DEF_SOULTRADE(CEL::DB_RESULT& rkResult)
{
	if (CEL::DR_SUCCESS != rkResult.eRet
		&&	CEL::DR_NO_RESULT != rkResult.eRet)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__ << _T("Load Fail!!"));
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	CEL::DB_DATA_ARRAY const &rkVec = rkResult.vecArray;
	CEL::DB_DATA_ARRAY::const_iterator result_iter = rkVec.begin();

	CONT_DEF_SOULTRADE map;
	CEL::DB_RESULT_COUNT::const_iterator count_iter = rkResult.vecResultCount.begin();

	if (count_iter == rkResult.vecResultCount.end())
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__ << _T("Load Fail!!"));
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	int const iCount = (*count_iter); ++count_iter;

	for (int i = 0; i < iCount; ++i)
	{
		CONT_DEF_SOULTRADE::key_type			kKey;
		CONT_DEF_SOULTRADE::mapped_type		kValue;
		int iTempValue = 0;

		result_iter->Pop(kKey);										++result_iter;
		result_iter->Pop(kValue.iItemNo);							++result_iter;
		result_iter->Pop(kValue.iMaterialNo);						++result_iter;
		result_iter->Pop(kValue.iMaterialNeedsCount);			++result_iter;

		std::pair<CONT_DEF_SOULTRADE::iterator, bool> kRet = map.insert(std::make_pair(kKey, kValue));
		if (!kRet.second)
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__ << _T("Data Error!!!"));
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Insert Failed DefSoulTrade"));
			return false;
		}
	}

	if (!map.empty())
	{
		g_kCoreCenter.ClearQueryResult(rkResult);
		g_kTblDataMgr.SetContDef(map);
		return true;
	}

	VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << L"row count 0");
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	return false;
}

bool LoadDB()
{
	std::wstring kStrQuery;
	bool bIsImmidiate = true;
	{
		CEL::DB_QUERY kQuery(DT_DEF, DQT_LOAD_DEF_SOULTRADE, _T("EXEC [dbo].[up_LoadDefItemDefSoulTrade]"));
		if (S_OK != g_kCoreCenter.PushQuery(kQuery, bIsImmidiate))
		{ 
			kStrQuery = kQuery.Command();
			goto __RECORVER; 
		}
	}
	return true;
__RECORVER:
	{
		INFO_LOG(BM::LOG_LV1, _T("Query Fail Data Recovery... Cause = ") << kStrQuery);
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

}

HRESULT CALLBACK OnDB_EXECUTE(CEL::DB_RESULT &rkResult)
{
	switch(rkResult.QueryType())
	{
		case DQT_LOAD_DEF_SOULTRADE: {Q_DQT_LOAD_DEF_SOULTRADE(rkResult); }break;
	}
	return E_FAIL;
}

HRESULT CALLBACK OnDB_EXECUTE_TRAN(CEL::DB_RESULT_TRAN &rkResult)
{
	return S_OK;
}
