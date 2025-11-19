// FTPMgr.cpp: implementation of the CFTPMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DragonRaja.h"
#include "FTPMgr.h"
#include "BM/Vstring.h"
#include "resource.h"
#include "PatcherDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CPatcherDlg* g_pDlg;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFTPMgr::CFTPMgr()
{
	m_pFtp				= 0;
	m_pHttp				= 0;
	m_uiReceivedSize	= 0;
	m_bIsState			= true;
}

CFTPMgr::~CFTPMgr()
{
	Close();
}

bool CFTPMgr::Connect(const TCHAR* szServerAddr, const WORD wPort, const TCHAR* szID,const TCHAR* szPW)
{
	try
	{ 
		if (g_pDlg)
		{
			g_pDlg->SetHeadStateText( "Connecting... Active" );
		}
		//성공하면 true리턴 실패하면 GetLastError()이용할것. 기본 인터넷 연결 옵션과 요청 시간을 설정
		m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT |INTERNET_OPTION_CONNECTED_STATE, 10000);	//10초간 접속을 시도
#ifdef FTP_CONNECT
		m_pFtp = m_Session.GetFtpConnection( szServerAddr, szID, szPW, wPort,false );	//액티브로 시도
#else
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] HTTP 로그인 시도"), _T(__FUNCTION__), __LINE__);
		m_pHttp = m_Session.GetHttpConnection( szServerAddr, wPort, szID, szPW );
		CString kStr;
		m_Session.QueryOption(INTERNET_OPTION_CONNECTED_STATE, kStr);
		const HRESULT hRet = GetLastError();

		int asdf = 0;
#endif
	}
	catch(CInternetException *lpEx)
	{
		lpEx->Delete();
		try	
		{
			if (g_pDlg)
			{
				g_pDlg->SetHeadStateText( "Connecting... Passive" );
			}
			m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);		//10초간 접속을 시도...
#ifdef FTP_CONNECT
			m_pFtp = m_Session.GetFtpConnection( szServerAddr, szID, szPW, wPort,true );
#else
			INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 로그인 실패, HTTP 재 로그인 시도"), _T(__FUNCTION__), __LINE__);
			m_pHttp = m_Session.GetHttpConnection( szServerAddr, wPort, szID, szPW );
#endif
		}//패시브로 시도
		catch(CInternetException *lpEx)
		{
			lpEx->Delete();
		}
	}
	
#ifdef FTP_CONNECT
	if(!m_pFtp)
	{
		g_pDlg->SetHeadStateText( "Connecting failed" );
		MessageBox(NULL, L"Connecting failed to server", L"Error", MB_OK);
//		::AfxMessageBox(szConnectionErr);
		return false;
	}
#else
	if(!m_pHttp)
	{
		g_pDlg->SetHeadStateText( "Connecting failed" );
		MessageBox(NULL, L"Connecting failed to server", L"Error", MB_OK);
		return false;
	}
#endif

	return true;
}

void CFTPMgr::Close()
{
#ifdef FTP_CONNECT
	if(m_pFtp)
	{
		m_pFtp->Close();
		delete m_pFtp;
		m_pFtp = NULL;
		m_Session.Close();
	}
#else
	if (m_pHttp)
	{
		m_pHttp->Close();
		delete m_pHttp;
		m_pHttp = 0;
		m_Session.Close();
	}
#endif

}

size_t CFTPMgr::GetFileSize(const std::wstring &wstrLocation, const bool bIsASCII, const bool bIsFailIfExit)
{
#ifndef FTP_CONNECT
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 사이즈 가져오기 : %s"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());
	size_t filesize;

	CHttpFile *pFile = m_pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET, wstrLocation.c_str());
	if (!pFile)
	{
		Sleep(500);
		pFile = m_pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET, wstrLocation.c_str());
		if(!pFile)
		{
			INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 접속 실패."), _T(__FUNCTION__), __LINE__);
			return FALSE;
		}
	}

	pFile->SendRequest(); //전송 요청
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);	//요청 결과 
	if(dwRet == HTTP_STATUS_OK) 
	{
		std::wstring wstrBuffTotal;
		wstrBuffTotal.resize(1024);
		DWORD dwBuffSize = 1024;
		
		if(pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, &wstrBuffTotal.at(0), &dwBuffSize)) 
		{
			  filesize = atoi(MB(wstrBuffTotal)); 
		}
		else
		{
			  filesize = 100000000;
		}
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 사이즈 획득 %ld"), _T(__FUNCTION__), __LINE__, filesize);
	}
	else
	{
		std::wstring wstrCode;
		wstrCode.resize(16);
		wsprintf(&wstrCode.at(0), L"%lu", dwRet);
		std::wstring wstrError = wstrLocation + _T(" get failed, Error code: ") + wstrCode;
		g_pDlg->SetHeadStateText(MB(wstrError));
		
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 접속 실패."), _T(__FUNCTION__), __LINE__);
		return false;
	}

	pFile->Close();
	delete pFile;

	return filesize;
#endif
}

bool CFTPMgr::GetFile(const std::wstring &wstrLocation, const std::wstring &wstrWriteTarget, const bool bIsASCII, const bool bIsFailIfExit)
{
	bool bRet = false;
	try
	{ 
#ifdef FTP_CONNECT
		bRet = GetFile_Ftp(wstrLocation, wstrWriteTarget, bIsASCII, bIsFailIfExit);
#else
		bRet = GetFile_Http(wstrLocation, wstrWriteTarget, bIsASCII, bIsFailIfExit);
		if (!bRet)
		{
			assert(0);
		}
#endif
	}
	catch(CInternetException *lpEx)
	{
		std::wstring wstrBuffer;
		if (lpEx->m_dwError == ERROR_INTERNET_CANNOT_CONNECT)
		{
			wstrBuffer +=  L"Connecting failed. Check internet state.";
			INFO_LOG( BM::LOG_LV1, _T("[%s]-[%d] InternetException : %s"), _T(__FUNCTION__), __LINE__, wstrBuffer.c_str());
			AfxMessageBox( wstrBuffer.c_str() );
		}
		else
		{
			wchar_t wcError[256];
			_i64tow(lpEx->m_dwError, wcError, 10);
			INFO_LOG( BM::LOG_LV1, _T("[%s]-[%d] InternetException : %s"), _T(__FUNCTION__), __LINE__, wcError);
			wstrBuffer += L"Internet Exception error code: ";
			wstrBuffer += wcError;
			AfxMessageBox( wstrBuffer.c_str() );
		}
		g_pDlg->SetHeadStateText( MB(wstrBuffer) );
		lpEx->Delete();
	}

	return bRet;
}

bool CFTPMgr::GetFile_Http(const std::wstring &wstrLocation, const std::wstring &wstrWriteTarget, const bool bIsASCII, const bool bIsFailIfExit)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 가져오기 시도 : %s"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());

	m_uiReceivedSize = 0;
	DWORD time = 0;
	static DWORD openTimeTotal = 0;
	static DWORD openTimeCount = 0;
	static DWORD open2TimeTotal = 0;
	static DWORD open2TimeCount = 0;
	static DWORD readTimeTotal = 0;
	static DWORD readTimeCount = 0;
	static DWORD closeTimeTotal = 0;
	static DWORD closeTimeCount = 0;

	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 가져오기 Step 1"), _T(__FUNCTION__), __LINE__);
	CString buffer(wstrLocation.c_str());	
	/////////////////////////////// 클라이언트쪽에 파일 생성 ////////////////////////////////////
	CFile	DirFile;									//다운로드 받아 저장할 CFile 객체 선언...
	time = ::GetTickCount();
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 가져오기 Step 2"), _T(__FUNCTION__), __LINE__);
	if (DirFile.Open(wstrWriteTarget.c_str(), CFile::modeCreate | CFile::modeWrite, NULL)==FALSE)		//파일 생성 
	{
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 가져오기 Step 3"), _T(__FUNCTION__), __LINE__);
		buffer += " FILE CREATE FAIL";
		AfxMessageBox( buffer );
		g_pDlg->SetHeadStateText("File create failed.");

		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 생성 실패"), _T(__FUNCTION__), __LINE__);

		return FALSE;
	}
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 가져오기 Step 4"), _T(__FUNCTION__), __LINE__);
	openTimeTotal += ::GetTickCount() - time;
	openTimeCount++;
	m_wstrReceivedFileName = wstrWriteTarget;
	/////////////////////////////////////////////////////////////////////////////////////////////
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 생성 완료 : %s"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());

	/////////////////////////////   파일 다운로드 작업  /////////////////////////////////////////
	time = ::GetTickCount();

	CHttpFile *pFile = m_pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET, wstrLocation.c_str());
	if (!pFile)
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 가져오기 실패"), _T(__FUNCTION__), __LINE__);
		Sleep(500);
		pFile = m_pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET, wstrLocation.c_str());
		if(!pFile)
		{
			g_pDlg->SetHeadStateText("Connecting failed.");

			INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 가져오기 실패[2]"), _T(__FUNCTION__), __LINE__);

			return FALSE;
		}
	}
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 가져오기 요청"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());
	if (!pFile->SendRequest())
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 가져오기 요청 실패"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());
		buffer += " GET FILE FAIL";
		AfxMessageBox( buffer );

		return false;
	}

	DWORD dwRet;
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 가져오기 상태 요청"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());
	if (!pFile->QueryInfoStatusCode(dwRet))
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 가져오기 상태 요청 실패"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());
		buffer += " GET FILE STATE FAIL";
		AfxMessageBox( buffer );

		return false;
	}

	open2TimeTotal += ::GetTickCount() - time;
	open2TimeCount++;
	time = ::GetTickCount();

	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 다운로드 시작"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());

	const int DOWNLOAD_BUFFER_SIZE = 40960; 
	//파일 다운로드 시작 
	char Buffer[DOWNLOAD_BUFFER_SIZE]= {0,};	
	unsigned int AmountRead = DOWNLOAD_BUFFER_SIZE;
	unsigned int TotalRead = 0;		

	CString strReceive;
	if(dwRet == HTTP_STATUS_OK) 
	{
		CString strLength; 
		int nTotal = 0; 
		UINT nRead; 
		BYTE szBuff[1024];
		char szBuffTotal[1024];
		DWORD dwBuffSize = 1024;
		std::wstring wstrBuffTotal;
		wstrBuffTotal.resize(1024);

		// 파일 크기 수신
		if(pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, &wstrBuffTotal.at(0), &dwBuffSize)) 
		{
			  nTotal = atoi(MB(wstrBuffTotal)); 
		}
		else
		{
			  nTotal = 100000000;
		}
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 사이즈 : %d"), _T(__FUNCTION__), __LINE__, nTotal);

		int nDown = 0;
		int nPacket = nTotal > 1024 ? 1024 : nTotal;

		// 패킷 단위로 데이터를 받아 파일에 저장
		while (nTotal - nDown > 0) 
		{ 
			// 데이터 수신
			try
			{ 
				nRead = pFile->Read(szBuff, nPacket);
			}
			catch(CInternetException *lpEx)
			{
				lpEx->Delete();

				Sleep(500);
				try
				{ 
					nRead = pFile->Read(szBuff, nPacket);
				}
				catch(CInternetException *lpEx)
				{
					lpEx->Delete();

					g_pDlg->SetHeadStateText("File Server DisConnected.");
					DirFile.Close();
					pFile->Close();
					delete	pFile;
					return false;
				}
			}

			if(nRead == 0)  break;

			DirFile.Write(szBuff, nRead);				//클라이언트 파일에 Write		
			TotalRead += nRead;
			m_uiReceivedSize += nRead;

			if (!m_bIsState)
				break;
		} 
	}
	else
	{
		std::wstring wstrCode;
		wstrCode.resize(16);
		wsprintf(&wstrCode.at(0), L"%lu", dwRet);
		std::wstring wstrError = wstrLocation + _T(" get failed, Error code: ") + wstrCode;
		g_pDlg->SetHeadStateText(MB(wstrError));
		
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] HTTP 상태가 올바르지 않음 : %lu"), _T(__FUNCTION__), __LINE__, dwRet);
		buffer += " HTTP STATE IS INVALID";
		AfxMessageBox( buffer );

		return false;
	}

	readTimeTotal += ::GetTickCount() - time;
	readTimeCount++;
	
	time = ::GetTickCount();
	DirFile.Close();
	pFile->Close();
	delete pFile;	
	closeTimeTotal += ::GetTickCount() - time;
	closeTimeCount++;

#ifdef PG_USE_PERFORM_CHECK
	if (openTimeCount % 1000 == 0)
	{
		TCHAR temp[1024];
		_stprintf(temp, L"open : %d, %f  open2 : %d, %f  read : %d, %f  close : %d %f\n", 
			openTimeCount, (float)openTimeTotal / (float)openTimeCount,
			open2TimeCount, (float)open2TimeTotal / (float)open2TimeCount,
			readTimeCount, (float)readTimeTotal / (float)readTimeCount,
			closeTimeCount, (float)closeTimeTotal / (float)closeTimeCount);
		OutputDebugString(temp);
	}
#endif

	m_wstrReceivedFileName.clear();
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 가져오기 끝 : %s"), _T(__FUNCTION__), __LINE__, wstrLocation.c_str());

	return TRUE;
}

bool CFTPMgr::GetFile_Ftp(const std::wstring &wstrLocation, const std::wstring &wstrWriteTarget, const bool bIsASCII, const bool bIsFailIfExit)
{
	m_uiReceivedSize = 0;
	DWORD time = 0;
	static DWORD openTimeTotal = 0;
	static DWORD openTimeCount = 0;
	static DWORD open2TimeTotal = 0;
	static DWORD open2TimeCount = 0;
	static DWORD readTimeTotal = 0;
	static DWORD readTimeCount = 0;
	static DWORD closeTimeTotal = 0;
	static DWORD closeTimeCount = 0;


	CString buffer(wstrLocation.c_str());	
	/////////////////////////////// 클라이언트쪽에 파일 생성 ////////////////////////////////////
	CFile	DirFile;									//다운로드 받아 저장할 CFile 객체 선언...
	time = ::GetTickCount();
	if (DirFile.Open(wstrWriteTarget.c_str(), CFile::modeCreate | CFile::modeWrite, NULL)==FALSE)		//파일 생성 
	{
		buffer += " FILE CREATE FAIL";
		AfxMessageBox( buffer );
		return FALSE;
	}
	openTimeTotal += ::GetTickCount() - time;
	openTimeCount++;
	m_wstrReceivedFileName = wstrWriteTarget;
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////   파일 다운로드 작업  /////////////////////////////////////////
	time = ::GetTickCount();

	CInternetFile*  pFtpFile = m_pFtp->OpenFile(wstrLocation.c_str());	//FTP상의 다운받을 파일을 연후 그 파일의 포인터를 받아온다.	

	if(!pFtpFile)
	{
		Sleep(500);
		pFtpFile = m_pFtp->OpenFile(wstrLocation.c_str());	//FTP상의 다운받을 파일을 연후 그 파일의 포인터를 받아온다.	
		if(!pFtpFile){return FALSE;}
	}
	open2TimeTotal += ::GetTickCount() - time;
	open2TimeCount++;
	
	const int DOWNLOAD_BUFFER_SIZE = 40960; 
	//파일 다운로드 시작 
	char Buffer[DOWNLOAD_BUFFER_SIZE]= {0,};	
	unsigned int AmountRead = DOWNLOAD_BUFFER_SIZE;
	unsigned int TotalRead = 0;		

	time = ::GetTickCount();
	while (AmountRead = pFtpFile->Read(Buffer,DOWNLOAD_BUFFER_SIZE))
	{
		DirFile.Write(Buffer, AmountRead);				//클라이언트 파일에 Write		
		TotalRead += AmountRead;
		m_uiReceivedSize += AmountRead;

		if (!m_bIsState)
			break;
	}
	readTimeTotal += ::GetTickCount() - time;
	readTimeCount++;
	////////////////////////////////////////////////////////////////////////////////////////////
	
	time = ::GetTickCount();
	DirFile.Close();
	pFtpFile->Close();				//FTP상의 Open된 파일 닫고..
	//pFtpFile->Abort();
	delete pFtpFile;	
	closeTimeTotal += ::GetTickCount() - time;
	closeTimeCount++;

	if (openTimeCount % 1000 == 0)
	{
		TCHAR temp[1024];
		_stprintf(temp, L"open : %d, %f  open2 : %d, %f  read : %d, %f  close : %d %f\n", 
			openTimeCount, (float)openTimeTotal / (float)openTimeCount,
			open2TimeCount, (float)open2TimeTotal / (float)open2TimeCount,
			readTimeCount, (float)readTimeTotal / (float)readTimeCount,
			closeTimeCount, (float)closeTimeTotal / (float)closeTimeCount);
		OutputDebugString(temp);
	}

	m_wstrReceivedFileName.clear();
	return TRUE;
}

size_t CFTPMgr::GetReceiveFileSize()
{
	return m_uiReceivedSize;
}

std::wstring CFTPMgr::GetReceiveFileName()
{
	return m_wstrReceivedFileName;
}

// 하나의 폴더에 대한 데이터를 얻는다. (_FILES.PGH, _FOLDERS.PGH, _ZIPFILES.PGH)
bool CFTPMgr::GetFolderData(const std::wstring &wstrLocation, BM::FolderHash &rkFiles, BM::FolderHash &rkFolders, BM::FolderHash &rkZipFiles)
{
	const std::wstring wstrFiles = _T("_FILES.PGH");
	const std::wstring wstrFolders = _T("_FOLDERS.PGH");
	const std::wstring wstrZipFiles = _T("_ZIPFILES.PGH");

	// Download
	GetFile(wstrLocation + wstrFiles, wstrFiles);
	GetFile(wstrLocation + wstrFolders, wstrFolders);
	GetFile(wstrLocation + wstrZipFiles, wstrZipFiles);

	// Get Header
	BM::PgDataPackManager::ReadHeader(wstrFiles, rkFiles);
	BM::PgDataPackManager::ClearBuffer(wstrFiles);
	BM::PgDataPackManager::ReadHeader(wstrFolders, rkFolders);
	BM::PgDataPackManager::ClearBuffer(wstrFolders);
	BM::PgDataPackManager::ReadHeader(wstrZipFiles, rkZipFiles);
	BM::PgDataPackManager::ClearBuffer(wstrZipFiles);

	// Delete file what downloaded.
	DeleteFile(wstrFiles.c_str());
	DeleteFile(wstrFolders.c_str());
	DeleteFile(wstrZipFiles.c_str());

	return true;
}

