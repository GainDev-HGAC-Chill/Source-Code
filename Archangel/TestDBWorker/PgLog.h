#pragma once

#include "BM/DebugLog.h"

typedef enum eDBQueryType
{
	DQT_WRITE_LOG = 2,
	DQT_LOG_TYPE = 3,
	DQT_GET_ACTIVE_USER = 4,
	DQT_TEST_PROC1 = 5,
	DQT_TEST_PROC2 = 6,
	DQT_TEST_PROC3 = 7,
	DQT_TEST_PROC4 = 8,
	DQT_TEST_PROC5 = 9,

	DQT_TEST = 10,
	DQT_TEST2 = 11,
};

typedef enum 
	: BYTE
{
	ELogWrite_Database = 0x01,
	ELogWrite_File = 0x02,
}ELogWriteType;

typedef struct tagTblDefLogType
{
	tagTblDefLogType()
	{
		iType = 0;
		cMode = 0;
	}

	bool operator<( tagTblDefLogType const & rkPair )const	
	{	
		return (iType < rkPair.iType);	
	}

	int		iType;
	char	cMode;//ELogWriteType

	DEFAULT_TBL_PACKET_FUNC();
}TBL_DEF_LOGTYPE;

typedef std::map< int, int >	CONT_LOG_TYPE;//key 로그타입, mapped ELogWriteType

class PgLogManager
{
public:
	PgLogManager();
	virtual ~PgLogManager();

public:
	void Init(CONT_LOG_TYPE const &kContLogType);

	void WriteChat(CEL::CPacket* const pkPacket);
	bool CanWrite(ELogType const &eLogType, ELogWriteType const &eWriteType)const;

private:
	CONT_LOG_TYPE m_kContLogType;

	BM::CDebugLog	m_kLog;
	mutable ACE_RW_Thread_Mutex m_kMutex;
};

#define g_kLog SINGLETON_STATIC(PgLogManager)

extern void WriteLog(PgLogWrapper &kLogData);

extern int g_iQueryType;
