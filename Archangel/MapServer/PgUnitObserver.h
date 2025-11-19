#pragma once
#include <list>
#include "loki/Threads.h"

//#pragma pack (1)
class PgUnitSubject;

class PgUnitObserver
{
protected:
	PgUnitObserver(){}

public: 
	virtual ~PgUnitObserver(){}
	virtual void VUpdate( PgUnitSubject *pChangedSubject, const __int32 iNotifyCause, CEL::CPacket * const pkPacket) = 0;
};

class PgUnitSubject//Observer 패턴의 서브젝트 객체.
//	:	public CCS_Thread_Safe
{
protected:
	PgUnitSubject();

public:
	virtual ~PgUnitSubject();

public:	
	virtual void VAttach(PgUnitObserver &rObserver);//VNotify내에서 호출 금지
	virtual void VDetach(const PgUnitObserver *pObserver);//VNotify내에서 호출 금지
	virtual void VNotify(const __int32 iNotifyCause, CEL::CPacket * const pkPacket);//알리기.

public:
	void ClearObserver();

private:
	PgUnitSubject(const PgUnitSubject &lhs);

private://순서가 선언된 메모리 순으로 간다.//List로 변경하자.
	typedef std::list< PgUnitObserver* > OBSERVER_LIST;//List 보다는 중복 삽입이 안되는 map쪽이 좋다.
	typedef OBSERVER_LIST::iterator OBSERVER_ITOR;
	OBSERVER_LIST m_lstObservers;

protected:
	Loki::Mutex m_subject_mutex;
};
//#pragma pack ()
