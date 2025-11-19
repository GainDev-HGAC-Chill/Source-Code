
// Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include "PgTestModule.h"
#include "BM/FileSupport.h"
#include "BM/Common.h"

#include <iostream>
#include <fstream>

using namespace std;

class IFStream
{
public:
	explicit IFStream()
	{	
		m_hFileHandle = INVALID_HANDLE_VALUE;
	}

	explicit IFStream(std::wstring const & kFilename)
	{
		m_hFileHandle = INVALID_HANDLE_VALUE;
		Open(kFilename);
	}

	virtual  ~IFStream()
	{	
		Close();
	}

	void Open(std::wstring const & kFilename)
	{	// open wide-named file (old style) -- EXTENSION
		BM::CAutoMutex kLock(m_kMutex);
		Close();
		
		HANDLE const hRetHandle = CreateFileW(kFilename.c_str(), FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS | FILE_ATTRIBUTE_READONLY,NULL);

		if(INVALID_HANDLE_VALUE != hRetHandle)
		{
			m_kFileName = kFilename;
			m_hFileHandle = hRetHandle;
			return;
		}
	}

	bool IsOpen() const
	{	// test if C stream has been opened
		BM::CAutoMutex kLock(m_kMutex);
		if(INVALID_HANDLE_VALUE != m_hFileHandle)
		{
			return true;
		}
		return false;
	}

	void  Close()
	{	// close the C stream
		BM::CAutoMutex kLock(m_kMutex);
		if(INVALID_HANDLE_VALUE != m_hFileHandle)
		{
			CloseHandle(m_hFileHandle);
		}
	}

	DWORD Read(size_t const offset, void * const pBuf, size_t const copy_size)
	{//읽은 사이즈를 리턴함
		BM::CAutoMutex kLock(m_kMutex);
		if(INVALID_HANDLE_VALUE != m_hFileHandle)
		{
			DWORD const dwFilePtr = SetFilePointer(m_hFileHandle, offset, NULL, FILE_BEGIN);
			if(INVALID_SET_FILE_POINTER != dwFilePtr)
			{
				DWORD dwReaded = 0;
				BOOL const bRet = ReadFile(m_hFileHandle, pBuf, copy_size, &dwReaded, NULL);
				
				return dwReaded;
			}
		}
		
		__asm int 3;//잘못된 포인트 지정.
		return 0;
	}

private:
	HANDLE m_hFileHandle;
	mutable Loki::Mutex m_kMutex;
	std::wstring m_kFileName;
};

class PgFileLoadTask
	: public PgTask< std::string >
{
public:
	void Init()
	{

	}

	virtual void HandleMessage(std::string *pkMsg)
	{
		HandleMessage_Float(pkMsg);
//		HandleMessage_SaveCheck(pkMsg);
//		HandleMessage_fstream(pkMsg);
	}

	virtual void HandleMessage_Float(std::string *pkMsg)
	{
		IFStream kFile(_T("Test.ini"));

		char szBuf[MAX_PATH] = {0,};
		kFile.Read(0, szBuf, 5);
	}
	
	virtual bool PutMsg(std::string &rkMsg, unsigned long ulPriority = 0)
	{
		::InterlockedIncrement(&m_kQueuedCount);
		return PgTask< std::string >::PutMsg(rkMsg);
	}

	typedef std::vector< std::string > CONT_FOLDERS;
	CONT_FOLDERS m_kFolders;
	volatile long m_kLoadCount;
	
	volatile long m_kQueuedCount;
	
	typedef std::map<std::string, int> CONT_CANT_LOAD_INFO;
	CONT_CANT_LOAD_INFO m_kContCantLoad;
	Loki::Mutex m_kMutex;
};

PgFileLoadTask g_kTask;

bool CALLBACK OnEscape( unsigned short const &rkInputKey)
{
	g_kConsoleCommander.StopSignal(true);
	return false;
}

bool CALLBACK OnF1( unsigned short const &rkInputKey)
{
	std::cout<< __FUNCTION__<< std::endl;
	IFStream kFile(_T("Test.ini"));
	char szBuf[MAX_PATH] = {0,};
	kFile.Read(0, szBuf, 200);

	int i = 10000;
	while(i--)
	{
		std::string kstr = "Test.ini";
		g_kTask.PutMsg(kstr);
	}

	Sleep(10000);

	std::cout<< __FUNCTION__<< std::endl;
	return true;
}

bool CALLBACK OnF2( unsigned short const &rkInputKey)
{
	std::cout<< __FUNCTION__ << std::endl;

	return true;
}

bool RegistKeyEvent()
{
	g_kConsoleCommander.Regist( VK_ESCAPE,	OnEscape );
	g_kConsoleCommander.Regist( VK_F1,	OnF1 );
	g_kConsoleCommander.Regist( VK_F2,	OnF2 );
//	g_kConsoleCommander.Regist( VK_F11, OnTerminateServer );
	
//	g_kConsoleCommander.Regist( VK_END,	OnEnd );
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ACE::init();
//	CEL::INIT_FINAL_SIGNAL kFinalInit;
//	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	RegistKeyEvent();

	g_kTask.StartSvc(4);

	g_kConsoleCommander.MainLoof();

//	g_kCoreCenter.Close();

	printf("close");

	return 0;
}



