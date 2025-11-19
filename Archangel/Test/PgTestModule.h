#pragma once


class PgModule1
{
public:
	PgModule1();
	~PgModule1();
	PgModule1( PgModule1 const &rhs );

	PgModule1& operator=( PgModule1 const &rhs );

protected:
	int m_i[20];
};

class PgModule2
{
public:
	PgModule2();
	~PgModule2();
	PgModule2( PgModule2 const &rhs );

	PgModule2& operator=( PgModule2 const &rhs );

protected:
	std::vector<BYTE>	m_kCont;
};

class PgModule3
{
public:
	PgModule3();
	~PgModule3();
	PgModule3( PgModule3 const &rhs );

	PgModule3& operator=( PgModule3 const &rhs );

protected:
	std::map< int, PgModule1 >	m_kCont;
};

class PgModule4
{
public:
	PgModule4();
	~PgModule4();
	PgModule4( PgModule4 const &rhs );

	PgModule4& operator=( PgModule4 const &rhs );

protected:
	PgModule1	m_kData1;
	PgModule2	m_kData2;
	PgModule3	m_kData3;

};

class PgModule5
{
public:
	PgModule5();
	~PgModule5();
	PgModule5( PgModule5 const &rhs );

	PgModule5& operator=( PgModule5 const &rhs );

protected:
	std::vector<BYTE>			m_kCont1;
	std::vector<int>			m_kCont2;
	std::map< int, __int64 >	m_kCont3;

};

class PgBase1
{
public:
	PgBase1();
	~PgBase1();

	void Create();

	PgBase1& operator=(PgBase1 const &rhs );

	BM::GUID  m_kID;
	PgModule1 *m_pkModule1[3];
	PgModule2 *m_pkModule2[3];
	PgModule3 *m_pkModule3[3];
	PgModule4 *m_pkModule4[3];
	PgModule5 *m_pkModule5[3];
};

class PgBaseOfBase
{
public:
	PgBaseOfBase()
		:	m_pkBase(NULL)
	{}

	~PgBaseOfBase()
	{
		SAFE_DELETE(m_pkBase);
	}

	Loki::Mutex m_kMutex;
	PgBase1 *m_pkBase;
};
