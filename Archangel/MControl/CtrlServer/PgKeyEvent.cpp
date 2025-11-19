#include "stdafx.h"

bool CALLBACK OnEscape( const WORD &InputKey)
{
	std::cout<< "END" << std::endl;
	ConsoleCommander.StopSignal(true);
	return false;
}

//! extern CDBConnection g_Conn;

bool CALLBACK OnF1( const WORD &InputKey)
{
	MAIN_LOG( BM::LOG_LV0, _T("=========================================="));

	return false;
}

bool CALLBACK OnF2(const WORD &InputKey)
{
	std::cout<< __FUNCTION__ << std::endl;
	return false;
}

bool CALLBACK OnF5(const WORD &InputKey)
{
	std::cout<< __FUNCTION__ << std::endl;

	return false;
}

bool CALLBACK OnPlus(const WORD &InputKey)
{
	std::cout<< __FUNCTION__ << std::endl;

	return true;
}

bool CALLBACK OnMinus(const WORD &InputKey)
{
	std::cout<< __FUNCTION__ << std::endl;
	
	return true;
}

bool RegistKeyEvent()
{
	ConsoleCommander.Regist( VK_ESCAPE,	OnEscape );
	ConsoleCommander.Regist( VK_F1,		OnF1 );
	ConsoleCommander.Regist( VK_F2,		OnF2 );
	ConsoleCommander.Regist( VK_F5,		OnF5 );

	ConsoleCommander.Regist( VK_ADD,		OnPlus );//숫자판
	ConsoleCommander.Regist( VK_SUBTRACT,	OnMinus );//숫자판
	return true;
}
