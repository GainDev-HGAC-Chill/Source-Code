#include "stdafx.h"
#include "PgTestTime.h"

PgTestTime::PgTestTime(void)
:	m_dwGapTime32(0)
{
}

void PgTestTime::InitTime32( DWORD const dwTime )
{
	DWORD const dwCurTime = BM::GetTime32();
	m_dwGapTime32 = dwTime - dwCurTime;
}

DWORD PgTestTime::GetTime32(void)const
{
	return BM::GetTime32() + m_dwGapTime32;
}
