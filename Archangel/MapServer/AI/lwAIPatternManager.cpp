#include "stdafx.h"
#include "lwAIPatternManager.h"
#include "PgAIPatternManager.h"

using namespace lua_tinker;

void lwAIPatternManager::RegisterWrapper(lua_State *pkState)
{
	LW_REG_CLASS(AIPatternManager)
		LW_REG_METHOD(AIPatternManager, Add)
		LW_REG_METHOD(AIPatternManager, AddActTransit)
		;
}

bool lwAIPatternManager::Add(int iID, char const* pszName)
{
	if( !m_pkAIPatternManager )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV5, _T("[%s] m_pkAIPatternManager == NULL"), __FUNCTIONW__);
		LIVE_CHECK_LOG_NEW(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	return m_pkAIPatternManager->Add((short int)iID, UNI(pszName));
}

bool lwAIPatternManager::AddActTransit(int iID, int iFrom, int iTo, int iWeight)
{
	if( !m_pkAIPatternManager )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV5, _T("[%s] m_pkAIPatternManager == NULL"), __FUNCTIONW__);
		LIVE_CHECK_LOG_NEW(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	return m_pkAIPatternManager->AddActTransit((short int)iID, iFrom, iTo, iWeight);
}