#include "stdafx.h"
#include "PgTask.h"

PgTestTask::PgTestTask()
:	m_lProcessCount(0)
,	m_iMode(0)
,	m_bBegin(false)
{
	msg_queue()->high_water_mark(1024*256);
}

PgTestTask::~PgTestTask()
{

}

void PgTestTask::Begin( int const iForceThreadCount, size_t iDummyCount, std::vector< BM::GUID > &kContID )
{
	{
		BM::CAutoMutex kLock( m_kLock, true );
		kContID.clear();
		kContID.reserve(iDummyCount);
		for ( size_t i=0; i<iDummyCount; ++i )
		{
			PgBaseOfBase* pkBaseOfBase = new PgBaseOfBase;
			if ( pkBaseOfBase )
			{
				pkBaseOfBase->m_pkBase = new PgBase1;
				if ( pkBaseOfBase->m_pkBase )
				{
					pkBaseOfBase->m_pkBase->Create();
					m_kContBase.insert( std::make_pair(pkBaseOfBase->m_pkBase->m_kID, pkBaseOfBase) );
					kContID.push_back( pkBaseOfBase->m_pkBase->m_kID );
				}
				else
				{
					__asm int 3;
				}
			}
			else
			{
				__asm int 3;
			}
		}

		m_bBegin = true;
	}
	

	this->activate( THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED, iForceThreadCount );
}

void PgTestTask::End()
{
	BM::CAutoMutex kLock( m_kLock, true );
	if ( m_bBegin )
	{
		m_bBegin = false;

		while(!msg_queue()->is_empty())
		{
			BM::GUID** ppkObj = NULL;
			ACE_Time_Value tv(0, 100);	tv += ACE_OS::gettimeofday();
			if( -1 != msg_queue()->dequeue( ppkObj, &tv) )
			{
				BM::GUID* pkObj = (BM::GUID*)ppkObj;
				SAFE_DELETE(pkObj);
			}
		}

		ACE_Thread_Manager::instance()->wait_task( this );

		std::map<BM::GUID,PgBaseOfBase*>::iterator itr = m_kContBase.begin();
		for ( ; itr!=m_kContBase.end() ; ++itr )
		{
			SAFE_DELETE(itr->second);
		}
		m_kContBase.clear();
	}
}

int PgTestTask::svc(void)
{
	while ( m_bBegin )
	{
		BM::CAutoMutex kLock( m_kLock, false );
		BM::GUID** ppkObj = NULL;

		ACE_Time_Value tv(0, 100);
		tv += ACE_OS::gettimeofday();
		if( -1 != msg_queue()->dequeue( ppkObj, &tv ) )
		{
			BM::GUID* pkObj = (BM::GUID*)ppkObj;
			Process( pkObj );
			SAFE_DELETE(pkObj);
		}
		
	}
	
	return 1;
}

bool PgTestTask::ChangeMode()
{
	BM::CAutoMutex kLock( m_kLock, true );

	size_t iRemainCount = 0;
	while(!msg_queue()->is_empty())
	{
		BM::GUID** ppkObj = NULL;
		ACE_Time_Value tv(0, 100);	tv += ACE_OS::gettimeofday();
		if( -1 != msg_queue()->dequeue( ppkObj, &tv) )
		{
			BM::GUID* pkObj = (BM::GUID*)ppkObj;
			SAFE_DELETE(pkObj);
			++iRemainCount;
		}
	}

	std::cout << std::endl;
	std::cout << "EndMode : " << m_iMode << " " << "ProcessCount : " << m_lProcessCount << " / RemainCount : " << iRemainCount << std::endl;
	m_lProcessCount = 0;

	if ( m_iMode < 3 )
	{
		++m_iMode;
		std::cout << "NewMode : " << m_iMode << std::endl;
		return true;
	}
	return false;
}

bool PgTestTask::Put( BM::GUID const &kID )
{
	BM::GUID *pkGuid = new BM::GUID(kID);
	BM::GUID ** ppkObj = (BM::GUID **)pkGuid;

	ACE_Time_Value tv(0, 100);	tv += ACE_OS::gettimeofday();
	if( -1 != msg_queue()->enqueue(ppkObj, &tv) )
	{
		return true;
	}

	SAFE_DELETE(pkGuid);
	return false;
}

void PgTestTask::Process( BM::GUID const *pkGuid )
{
	std::map<BM::GUID,PgBaseOfBase*>::iterator itr = m_kContBase.find( *pkGuid );
	if ( itr!=m_kContBase.end() )
	{
		PgBaseOfBase* pkBaseOfBase = itr->second;
		BM::CAutoMutex kLock2( pkBaseOfBase->m_kMutex );
		PgBase1 *pkBase = itr->second->m_pkBase;
		switch( m_iMode )
		{
		case 0:
			{
				PgBase1 *pkCopy = new PgBase1;
				if ( pkCopy )
				{
					*pkCopy = *(pkBase);
//					Sleep(0);

					itr->second->m_pkBase = pkCopy;
					SAFE_DELETE(pkBase);
					::InterlockedIncrement( &m_lProcessCount );
				}
				else
				{
					__asm int 3;
				}
			}break;
		case 1:
			{
				int iCount = BM::Rand_Range( 5, 2 );
				while ( iCount-- )
				{
					int iType = BM::Rand_Range( 5, 1 );
					size_t const iIndex = BM::Rand_Index(3);
					switch( iType )
					{
					case 1:
						{
							PgModule1 *pkModule = new PgModule1;
							if ( pkModule )
							{
								*pkModule = *(pkBase->m_pkModule1[iIndex]);
								SAFE_DELETE(pkBase->m_pkModule1[iIndex]);
								pkBase->m_pkModule1[iIndex] = pkModule;
							}
						}break;
					case 2:
						{
							PgModule2 *pkModule = new PgModule2;
							if ( pkModule )
							{
								*pkModule = *(pkBase->m_pkModule2[iIndex]);
								SAFE_DELETE(pkBase->m_pkModule2[iIndex]);
								pkBase->m_pkModule2[iIndex] = pkModule;
							}
						}break;
					case 3:
						{
							PgModule3 *pkModule = new PgModule3;
							if ( pkModule )
							{
								*pkModule = *(pkBase->m_pkModule3[iIndex]);
								SAFE_DELETE(pkBase->m_pkModule3[iIndex]);
								pkBase->m_pkModule3[iIndex] = pkModule;
							}
						}break;
					case 4:
						{
							PgModule4 *pkModule = new PgModule4;
							if ( pkModule )
							{
								*pkModule = *(pkBase->m_pkModule4[iIndex]);
								SAFE_DELETE(pkBase->m_pkModule4[iIndex]);
								pkBase->m_pkModule4[iIndex] = pkModule;
							}
						}break;
					case 5:
						{
							PgModule5 *pkModule = new PgModule5;
							if ( pkModule )
							{
								*pkModule = *(pkBase->m_pkModule5[iIndex]);
								SAFE_DELETE(pkBase->m_pkModule5[iIndex]);
								pkBase->m_pkModule5[iIndex] = pkModule;
							}
						}break;
					}
				}
//				Sleep(0);
				::InterlockedIncrement( &m_lProcessCount );
			}break;
		case 2:
			{
				*pkBase = *pkBase;
//				Sleep(0);
				::InterlockedIncrement( &m_lProcessCount );
			}break;
		case 3:
			{
//				Sleep(0);
				::InterlockedIncrement( &m_lProcessCount );
			}break;
		}
	}
}