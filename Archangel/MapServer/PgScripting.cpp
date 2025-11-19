#include "StdAfx.h"
#include "PgScripting.h"

#include "lwBase.h"
#include "lwGuid.h"
#include "lwXml.h"
#include "lwGroundResource.h"
#include "lwGround.h"
#include "lwPacket.h"
#include "lwUnit.h"
#include "lwItem.h"
#include "lwInventory.h"
#include "lwPacket.h"
#include "lwSkill.h"
#include "lwActArg.h"
#include "lwPoint3.h"
#include "lwEffect.h"
#include "lwSkillDef.h"
#include "lwEffectDef.h"
#include "lwActionResult.h"
#include "lwUNIT_PTR_ARRAY.h"
#include "lwObjectMgr_UnitIterator.h"
#include "lwVector.h"
#include "lwLocalPartyMgr.h"
#include "lwVecGuid.h"
#include ".\AI\lwAIPatternManager.h"
#include "lwGroundDecorator.h"
#include "lwStage.h"
#include "lwStageAction.h"
#include "lwUnitEffectMgr.h"

int const g_iLuaStateMaxCount = 3;

using namespace lua_tinker;

#ifdef _DEBUG
CPgLuaDebugger *g_pkScriptDebug = NULL;
#endif


PgScripting::PgScripting(void)
{
#ifdef _DEBUG
	g_pkScriptDebug = NULL;
#endif
}

PgScripting::~PgScripting(void)
{
#ifdef _DEBUG
	if (g_pkScriptDebug)
	{
		g_pkScriptDebug->Terminate();
		delete g_pkScriptDebug;
		g_pkScriptDebug = NULL;
	}
#endif
}

void PgScripting::RegisterModules(lua_State *pkState)
{
	RegisterBase(pkState);
	LW_REG_WRAPPER(GUID);

	RegisterXml(pkState);

	LW_REG_WRAPPER(GroundResource);
	LW_REG_WRAPPER(Ground);
	//LW_REG_WRAPPER(Quest);
	LW_REG_WRAPPER(Unit);
	LW_REG_WRAPPER(Packet);
	LW_REG_WRAPPER(Skill);
	LW_REG_WRAPPER(ActArg);
	LW_REG_WRAPPER(Point3);
	LW_REG_WRAPPER(Effect);
	LW_REG_WRAPPER(SkillDef);
	//LW_REG_WRAPPER(SkillDefLock);
	LW_REG_WRAPPER(EffectDef);
	//LW_REG_WRAPPER(EffectDefLock);
	LW_REG_WRAPPER(ActionResult);
	LW_REG_WRAPPER(ActionResultVector);
	LW_REG_WRAPPER(UNIT_PTR_ARRAY);
	LW_REG_WRAPPER(ObjectMgr_UnitIterator);
	LW_REG_WRAPPER(Vector);
	//LW_REG_WRAPPER(LocalPartyMgr);
	LW_REG_WRAPPER(VecGuid);
	LW_REG_WRAPPER(AIPatternManager);
//	LW_REG_WRAPPER(GroundDecorator);
//	LW_REG_WRAPPER(Stage);
//	LW_REG_WRAPPER(StageAction);
	LW_REG_WRAPPER(UnitEffectMgr);
}



HRESULT PgScripting::Initialize()
{
	INFO_LOG(BM::LOG_LV7, _T("[%s] [Begin] Lua Scripting Initializing ...."), __FUNCTIONW__);
	// 루어 환경을 생성한다.
	if(!g_iLuaStateMaxCount)
	{
		LIVE_CHECK_LOG_NEW(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
		return E_FAIL;
	}
	
	g_kLuaTinker.open();

	lua_wrapper_user kLua(g_kLuaTinker);
	// PG에서 생성한 모듈들을 등록한다.
	RegisterModules(*kLua);

	
#ifdef _DEBUG
	g_pkScriptDebug = new CPgLuaDebugger;
	
	{//괄호 없에면 데드락 가능성 있음
	bool bReturn = g_pkScriptDebug->Initialize(
		*kLua,						// 루아 스테이트
		5001,							// 포트
		"127.0.0.1",						// char *IP
		NULL,	// 윈도우 핸들
		NULL					// 함수포인터 DoFile(char const *)
		);
	}
#endif

	lua_tinker::dofile(*kLua, "Script/init.lua");
	int const iConfirmRet = lua_tinker::call<int>("ConfirmInitScript");
	if( !iConfirmRet )
	{
		INFO_LOG(BM::LOG_LV7, _T("[%s] [CHECK] Lua Scripting Confirm....... FAILED"), __FUNCTIONW__);
		LIVE_CHECK_LOG_NEW(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
		return E_FAIL;
	}

	INFO_LOG(BM::LOG_LV7, _T("[%s] [CHECK] Lua Scripting Confirm....... OK"), __FUNCTIONW__);
	INFO_LOG(BM::LOG_LV7, _T("[%s] [END] Lua Scripting Initialized"), __FUNCTIONW__);

	return S_OK;
}
