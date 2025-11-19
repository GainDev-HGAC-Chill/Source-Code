// FTPMgr.h: interface for the CFTPMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPMGR_H__C853DC5B_F0F4_44C3_825D_749D5DB23064__INCLUDED_)
#define AFX_FTPMGR_H__C853DC5B_F0F4_44C3_825D_749D5DB23064__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxinet.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include <string>

class CFTPMgr
{
public:
	CFTPMgr();
	virtual ~CFTPMgr();

	bool Connect(const TCHAR* szServerAddr, const WORD wPort /*INTERNET_DEFAULT_FTP_PORT*/, const TCHAR* szID,const TCHAR* szPW);
	void Close();
	size_t GetFileSize(const std::wstring &wstrLocation, const bool bIsASCII=false, const bool bIsFailIfExit = false);
	bool GetFile(const std::wstring &wstrLocation, const std::wstring &wstrWriteTarget, const bool bIsASCII=false, const bool bIsFailIfExit = false);
	bool GetFile_Http(const std::wstring &wstrLocation, const std::wstring &wstrWriteTarget, const bool bIsASCII = false, const bool bIsFailIfExit = false);
	bool GetFile_Ftp(const std::wstring &wstrLocation, const std::wstring &wstrWriteTarget, const bool bIsASCII = false, const bool bIsFailIfExit = false);
	size_t GetReceiveFileSize();
	std::wstring GetReceiveFileName();

	void ConnectionState(bool bState) { m_bIsState = bState; }

	// 하나의 폴더에 대한 데이터를 얻는다. (_FILES.PGH, _FOLDERS.PGH, _ZIPFOLDERS.PGH)
	bool GetFolderData(const std::wstring &wstrLocation, BM::FolderHash &rkFiles, BM::FolderHash &rkFolders, BM::FolderHash &rkZipFiles);

private:
	CFtpConnection *m_pFtp;
	CHttpConnection *m_pHttp;
	CInternetSession m_Session;
	size_t m_uiReceivedSize;
	std::wstring m_wstrReceivedFileName;
	bool m_bIsState;
};

#endif // !defined(AFX_FTPMGR_H__C853DC5B_F0F4_44C3_825D_749D5DB23064__INCLUDED_)
