#pragma once

#ifdef PG_USE_ACE

#include "PgPatchThread.h"
#include "ace/Task_ex_t.h"
#include "ace/Message_Queue_t.h"

#pragma pack(1)
typedef struct _CRCInfo
{
	_CRCInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		wstrFilePath = L"\0";
		pkFileInfo = 0;
	}

	std::wstring wstrFilePath;
	BM::PgFIleInfo *pkFileInfo;
}CRCInfo;
#pragma pack()

#pragma pack(1)
typedef struct tagWorkerThreadMessage
{
	tagWorkerThreadMessage()
	{
		Clear();
	}

	tagWorkerThreadMessage(const int iInType, const std::wstring wstrInFileName, const std::wstring wstrInFilePath, BM::PgFIleInfo *pkInFileInfo)
	{
		iType = iInType;
		wstrFileName = wstrInFileName;
		wstrFilePath = wstrInFilePath;
		pkFileInfo = pkInFileInfo;
	}

	void Clear()
	{
		pkFileInfo = NULL;
	}

	int iType;
	std::wstring wstrFileName;
	std::wstring wstrFilePath;
	BM::PgFIleInfo *pkFileInfo;

}SWorkerThreadMessage;
#pragma pack()

typedef enum ePatchThreadMessageType
{
	E_PTMT_CALCCRC = 1,
}EWorkerThreadMessageType;

class PgPatchThread
	:	public	ACE_Task_Ex< ACE_MT_SYNCH , SWorkerThreadMessage >
{
	typedef enum eValue
	{
		E_WATER_MARK	= sizeof(SWorkerThreadMessage) * 400000000,
	}E_VALUE;

public:
	PgPatchThread(void);
	virtual ~PgPatchThread(void);
public:
	bool DoCalcCRC(const std::wstring wstrInFileName, const std::wstring wstrInFilePath, BM::PgFIleInfo *pkInFileInfo);

protected:
	virtual int svc(void);
	
protected:
	CLASS_DECLARATION_S( bool, IsStop );
	typedef BM::TObjectPool< SWorkerThreadMessage > MSG_POOL;
	MSG_POOL m_kMsgPool;
};

#define g_kPatchThread SINGLETON_STATIC(PgPatchThread)

#endif