#include "stdafx.h"
#include <algorithm>
#include "PgUnitObserver.h"
#include "BM/ThreadObject.h"

//#pragma pack(1)

class UnitNotifyElement
{
public:
	UnitNotifyElement(PgUnitSubject *pSubject, const __int32 iNotifyCause, CEL::CPacket * const pkPacket)
		:	m_pSubject(pSubject)
		,	m_iNotifyCause(iNotifyCause)
		,	m_pkPacket(pkPacket)
	{
	}
public:
	template<typename T_ELEMENT>
	void operator ()(T_ELEMENT &TElement)
	{
		TElement->VUpdate( m_pSubject, m_iNotifyCause, m_pkPacket);
	}
	PgUnitSubject *m_pSubject;
	CEL::CPacket * const m_pkPacket;

	const __int32 m_iNotifyCause;
};

//#pragma pack()

PgUnitSubject::PgUnitSubject()
{
	ClearObserver();
}

PgUnitSubject::~PgUnitSubject()
{
	ClearObserver();
}

void PgUnitSubject::ClearObserver()
{
	BM::CAutoMutex Lock( m_subject_mutex );
	
	OBSERVER_ITOR Itor = m_lstObservers.begin();
	while(m_lstObservers.end() != Itor)
	{
		m_lstObservers.erase(Itor++);
	}

	m_lstObservers.clear();
}

void PgUnitSubject::VAttach(PgUnitObserver &rObserver)
{
	BM::CAutoMutex Lock( m_subject_mutex );
	
	m_lstObservers.push_back(&rObserver);
}

void PgUnitSubject::VDetach(const PgUnitObserver *pObserver)
{
	BM::CAutoMutex Lock( m_subject_mutex );

	OBSERVER_ITOR Itor = find( m_lstObservers.begin(), m_lstObservers.end(), pObserver);

	m_lstObservers.erase(Itor++);
}

void PgUnitSubject::VNotify(CEL::CPacket * const pkPacket)//¾Ë¸®±â.
{
	BM::CAutoMutex Lock( m_subject_mutex );

	OBSERVER_ITOR Itor = m_lstObservers.begin();
	for_each( m_lstObservers.begin(), m_lstObservers.end(), NotifyElement( this, iNotifyCause) );
}