#include "stdafx.h"
#include "PgTestModule.h"

PgModule1::PgModule1()
{
	int i = BM::Rand_Index(255);
	::memset( m_i, i, sizeof(m_i) );
}

PgModule1::~PgModule1()
{

}

PgModule1::PgModule1( PgModule1 const &rhs )
{
	*this = rhs;
}

PgModule1& PgModule1::operator=( PgModule1 const &rhs )
{
	::memcpy( m_i, rhs.m_i, sizeof(m_i) );
	return *this;
}

PgModule2::PgModule2()
{
	m_kCont.resize(1000);

	int i = BM::Rand_Index(255);
	::memset( &(m_kCont.at(0)), i, sizeof(BYTE)*m_kCont.size() );
}

PgModule2::~PgModule2()
{
}

PgModule2::PgModule2( PgModule2 const &rhs )
{
	*this = rhs;
}

PgModule2& PgModule2::operator=( PgModule2 const &rhs )
{
	m_kCont = rhs.m_kCont;
	return *this;
}

PgModule3::PgModule3()
{
	int i = 50;
	while ( i-- )
	{
		m_kCont.insert( std::make_pair( i, PgModule1() ) );
	}
}

PgModule3::~PgModule3()
{
}

PgModule3::PgModule3( PgModule3 const &rhs )
{
	*this = rhs;
}

PgModule3& PgModule3::operator=( PgModule3 const &rhs )
{
	m_kCont = rhs.m_kCont;
	return *this;
}

PgModule4::PgModule4()
{
}

PgModule4::~PgModule4()
{
}

PgModule4::PgModule4( PgModule4 const &rhs )
{
	*this = rhs;
}

PgModule4& PgModule4::operator=( PgModule4 const &rhs )
{
	m_kData1 = rhs.m_kData1;
	m_kData2 = rhs.m_kData2;
	m_kData3 = rhs.m_kData3;
	return *this;
}

PgModule5::PgModule5()
{
	m_kCont1.resize(500);
	m_kCont2.resize(100);

	int i = 70;
	while ( i-- )
	{
		__int64 i64 = BM::Rand_Range(0,10000000000);
		m_kCont3.insert( std::make_pair( i, i64 ) );
	}
}

PgModule5::~PgModule5()
{
}

PgModule5::PgModule5( PgModule5 const &rhs )
{
	*this = rhs;
}

PgModule5& PgModule5::operator=( PgModule5 const &rhs )
{
	m_kCont1 = rhs.m_kCont1;
	m_kCont2 = rhs.m_kCont2;
	m_kCont3 = rhs.m_kCont3;
	return *this;
}

PgBase1::PgBase1()
:	m_kID(BM::GUID::Create())
{
	for ( int i=0; i<3; ++i )
	{
		m_pkModule1[i] = NULL;
		m_pkModule2[i] = NULL;
		m_pkModule3[i] = NULL;
		m_pkModule4[i] = NULL;
		m_pkModule5[i] = NULL;
	}
}

PgBase1::~PgBase1()
{
	for ( int i=0; i<3; ++i )
	{
		SAFE_DELETE(m_pkModule1[i]); 
		SAFE_DELETE(m_pkModule2[i]);
		SAFE_DELETE(m_pkModule3[i]); 
		SAFE_DELETE(m_pkModule4[i]);
		SAFE_DELETE(m_pkModule5[i]);
	}
}

void PgBase1::Create()
{
	for ( int i=0; i<3; ++i )
	{
		if ( !m_pkModule1[i] )
		{
			m_pkModule1[i] = new PgModule1;
		}

		if ( !m_pkModule2[i] )
		{
			m_pkModule2[i] = new PgModule2;
		}

		if ( !m_pkModule3[i] )
		{
			m_pkModule3[i] = new PgModule3;
		}

		if ( !m_pkModule4[i] )
		{
			m_pkModule4[i] = new PgModule4;
		}

		if ( !m_pkModule5[i] )
		{
			m_pkModule5[i] = new PgModule5;
		}
	}
}

PgBase1& PgBase1::operator=( PgBase1 const &rhs )
{
	m_kID = rhs.m_kID;

	for ( int i=0; i<3; ++i )
	{
		if ( !m_pkModule1[i] )
		{
			m_pkModule1[i] = new PgModule1(*(rhs.m_pkModule1[i]));
		}
		else
		{
			*(m_pkModule1[i]) = *(rhs.m_pkModule1[i]);
		}


		if ( !m_pkModule2[i] )
		{
			m_pkModule2[i] = new PgModule2(*(rhs.m_pkModule2[i]));
		}
		else
		{
			*(m_pkModule2[i]) = *(rhs.m_pkModule2[i]);
		}

		if ( !m_pkModule3[i] )
		{
			m_pkModule3[i] = new PgModule3(*(rhs.m_pkModule3[i]));
		}
		else
		{
			*(m_pkModule3[i]) = *(rhs.m_pkModule3[i]);
		}
		

		if ( !m_pkModule4[i] )
		{
			m_pkModule4[i] = new PgModule4(*(rhs.m_pkModule4[i]));
		}
		else
		{
			*(m_pkModule4[i]) = *(rhs.m_pkModule4[i]);
		}
		
		if ( !m_pkModule5[i] )
		{
			m_pkModule5[i] = new PgModule5(*(rhs.m_pkModule5[i]));
		}
		else
		{
			*(m_pkModule5[i]) = *(rhs.m_pkModule5[i]);
		}
	}
	return *this;
}
