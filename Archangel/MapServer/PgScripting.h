#pragma once

class PgScripting
{
protected:
	PgScripting(void);
	~PgScripting(void);

public:
	//! 스크립트 시스템을 초기화한다.
	static HRESULT Initialize();

	//! PG 모듈들을 등록한다.
	static void RegisterModules(lua_State *pkState);
};
