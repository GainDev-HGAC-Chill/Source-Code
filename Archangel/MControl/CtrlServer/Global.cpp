#include "stdafx.h"
#include "PgServerController.h"

// Getting Main Program path
// [PARAMETER]
// lpszPath : [OUT] main program path ("C:\Game\TheGAME\")
// [RETURN]
// success
bool GetMainDirectory(LPTSTR lpszPath, int iPathLen)
{
	TCHAR chPath[MAX_PATH];
	if (GetModuleFileName(NULL, chPath, MAX_PATH) <= 0)
	{
		return FALSE;
	}
	LPTSTR lpszFind = _tcsrchr(chPath, _T('\\'));
	if (lpszFind == NULL)
	{
		lpszPath[0] = _T('\0');
		return false;
	}
	*(lpszFind+1) = _T('\0');
	_tcscpy_s(lpszPath, iPathLen, chPath);
	return true;

}

bool ReadConfigFile()
{
	TCHAR chFile[MAX_PATH];
	GetMainDirectory(chFile, MAX_PATH);
	_tcscat_s(chFile, MAX_PATH, _T("MControlServer.ini"));
	const BM::vstring SECTION_NAME = _T("SERVER");

	int i = 1;
	TCHAR chValue[500];

	while (GetPrivateProfileString(SECTION_NAME+i,NULL, NULL, chValue, 100, chFile) > 0)
	{
		TBL_SERVERLIST kServer;
		std::wstring kSIP = _T("");
		std::wstring kSNatIP = _T("");
		std::wstring kUIP = _T("");
		std::wstring kUNatIP = _T("");
		WORD wSPort, wSNatPort, wUPort, wUNatPort;
		wSPort = wSNatPort = wUPort = wUNatPort = 0;
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERNO"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%d"), &(kServer.iServerNo));
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("CHANNEL"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%d"), &(kServer.nChannel));
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("NAME"), NULL, chValue, 100, chFile) > 0)
		{
			_tcscpy_s(kServer.szName, 21, chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("TYPE"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%d"), &(kServer.nServerType));
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERBINDIP"), NULL, chValue, 100, chFile) > 0)
		{
			kSIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERBiNDPORT"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%hd"), &wSPort);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERNATIP"), NULL, chValue, 100, chFile) > 0)
		{
			kSNatIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERNATPORT"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%hd"), &wSNatPort);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERBINDIP"), NULL, chValue, 100, chFile) > 0)
		{
			kUIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERBINDPORT"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%hd"), &wUPort);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERNATIP"), NULL, chValue, 100, chFile) > 0)
		{
			kUNatIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERNATPORT"), NULL, chValue, 100, chFile) > 0)
		{
			_stscanf_s(chValue, _T("%hd"), &wUNatPort);
		}
		kServer.addrServerBind.Set(kSIP, wSPort);
		kServer.addrServerNat.Set(kSNatIP, wSNatPort);
		kServer.addrUserBind.Set(kUIP, wUPort);
		kServer.addrUserNat.Set(kUNatIP, wUNatPort);
		kServer.Build();

		g_kProcessCfg.AddServerInfo(&kServer);

		i++;
	}

	// Account information
	GetPrivateProfileString(_T("ACCOUNT"), NULL, NULL, chValue, 500, chFile);
	int iLen = 0;
	int iPos = 0;
	LPTSTR lpszID = &chValue[iPos];
	TCHAR chValue2[100];
	while ((iPos < 500) && ((iLen = _tcslen(lpszID)) > 0))
	{
		if (GetPrivateProfileString(_T("ACCOUNT"), lpszID, NULL, chValue2, 100, chFile) > 0)
		{
			g_kController.AddAccount(lpszID, chValue2);
		}
		iPos += iLen + 1;
		lpszID = &chValue[iPos];
	}

	// ServerFile information
	LPCTSTR lpszType[] = { _T("CENTER"), _T("CONTENTS"), _T("LOGIN"), _T("MAP"), _T("SWITCH"), _T("ITEM"), NULL };
	CEL::E_SESSION_TYPE eType[] = { CEL::ST_CENTER, CEL::ST_CONTENTS, CEL::ST_LOGIN, CEL::ST_MAP, CEL::ST_SWITCH, CEL::ST_ITEM };
	LPCTSTR lpszPath = _T("PATH");
	LPCTSTR lpszParam = _T("PARAM");
	SERVER_FILE kFile;
	int iIndex = 0;
	while (lpszType[iIndex] != NULL)
	{
		if (GetPrivateProfileString(lpszType[iIndex], lpszPath, NULL, kFile.chPath, MAX_PATH, chFile) <= 0)
		{
			iIndex++;
			continue;
		}
		GetPrivateProfileString(lpszType[iIndex], lpszParam, NULL, kFile.chParam, MAX_PATH, chFile);
		g_kController.AddServerFile(eType[iIndex], kFile.chPath, kFile.chParam);

		iIndex++;
	}

	return true;	
}

bool GetPathWithoutFilename(LPCTSTR lpszSource, LPTSTR lpszPathOnly, size_t iPathOnlySize)
{
	if (lpszSource == NULL || lpszPathOnly == NULL)
	{
		return false;
	}

	LPCTSTR lpszFind = _tcsrchr(lpszSource, _T('\\'));
	if (lpszFind == NULL)
	{
		lpszFind = _tcsrchr(lpszSource, _T('/'));
	}
	_tcsncpy_s(lpszPathOnly, iPathOnlySize, lpszSource, lpszFind - lpszSource);
	return true;
}