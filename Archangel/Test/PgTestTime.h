#pragma once

class PgTestTime
{
public:
	PgTestTime(void);
	~PgTestTime(void){}

	void InitTime32( DWORD const dwTime );
	DWORD GetTime32(void)const;

protected:
	DWORD m_dwGapTime32;
};