#pragma once

#include "Loki/singleton.h"
#include "BM/GUID.h"
#include "PgTestModule.h"

class PgTestTask
	:	public ACE_Task_Ex< ACE_MT_SYNCH , BM::GUID* >
{
public:
	PgTestTask();
	~PgTestTask();

	void Begin( int const iForceThreadCount, size_t iDummyCount, std::vector< BM::GUID > &kContID );
	void End();

	bool Put( BM::GUID const &kID );
	virtual int svc (void);
	bool ChangeMode();

protected:
	void Process( BM::GUID const *pkGuid );

	ACE_RW_Thread_Mutex					m_kLock;
	std::map< BM::GUID, PgBaseOfBase* >	m_kContBase;
	volatile LONG						m_lProcessCount;
	int									m_iMode;
	bool								m_bBegin;
};

#define g_kTestTask SINGLETON_STATIC(PgTestTask)