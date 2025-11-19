#include "StdAfx.h"
#define IP_ADDRESS	_T("")
#define PORTNUMBER	_T("")
#define CHANNEL		_T("")
#define LOCALE		_T("KOR")

PgProcessInfoMgr::PgProcessInfoMgr(void)
{
}

PgProcessInfoMgr::~PgProcessInfoMgr(void)
{
	ClearGmUser();
}

void PgProcessInfoMgr::ReqRefreshGmList()
{
	BM::CAutoMutex kLock(m_kMutex);

	ClearGmUser();

	//접속중인 GM리스트 요청
	CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_GET_GMLIST);
	kPacket.Push(m_kMyInfo.kMemberGuid);
	g_kNetwork.SendToLoginServer(kPacket);
}

unsigned int PgProcessInfoMgr::RecvGmList(CEL::CPacket *const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);

	if(pkPacket == NULL)
	{
		INFO_LOG(BM::LOG_LV4,_T("Packet is NULL"));
		return 0;
	}

	size_t iSize = 0;
	pkPacket->Pop(iSize);

	while(iSize > 0)
	{
		SAuthInfo kData;
		pkPacket->Pop(kData);		
		//만약 자기 자신이면 추가하지 않느다.
		if( wcscmp(kData.szID, m_kMyInfo.szID) != 0)
		{
			SAuthInfo* pData =  new SAuthInfo;
			pData =  &kData;
			std::wstring kGmName = kData.szName;
			CONT_GM_AUTH_DATA_ID::_Pairib Ret = m_kGmUsers.insert(std::make_pair(kGmName, pData));
			if(!Ret.second)
			{
				SAFE_DELETE(pData);
			}
		}
		--iSize;
	}
	return (int)iSize;
}

bool PgProcessInfoMgr::GetMainDir(LPTSTR lpszPath, int iPathLen)
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

bool PgProcessInfoMgr::ReadIniFile(wchar_t* FileName)
{
	if(FileName == NULL)
	{
		INFO_LOG(BM::LOG_LV4,_T("FileName is NULL"));
		return false;
	}

	std::wstring wstrTerminal = _T("PetitionTool");

	wchar_t chFile[MAX_PATH];
	GetMainDir(chFile, MAX_PATH);
	_tcscat_s(chFile, MAX_PATH, FileName);

	wchar_t chValue[500];
	if(!GetPrivateProfileString(wstrTerminal.c_str(), NULL, NULL, chValue, 100, chFile))
	{
		WritePrivateProfileString(NULL, NULL, NULL, chFile);
		WritePrivateProfileString(_T("PetitionTool"), _T("LOGIN_IP"), IP_ADDRESS, chFile);
		WritePrivateProfileString(_T("PetitionTool"), _T("LOGIN_PORT"), PORTNUMBER, chFile);
		WritePrivateProfileString(_T("LOCALE"), _T("CODE"), CHANNEL, chFile);


		INFO_LOG(BM::LOG_RED, _T("Create config.ini file"));
		INFO_LOG(BM::LOG_RED, _T("Now setting file and restart!!"));

		return false;
	}	

	if (GetPrivateProfileString(wstrTerminal.c_str(), _T("LOGIN_IP"), NULL, chValue, 100, chFile) > 0)
	{
		kLoginServerIP(chValue);
	}
	dwLoginServerPort(GetPrivateProfileInt(wstrTerminal.c_str(), _T("LOGIN_PORT"), 0, chFile));

	TCHAR szLocale[100];
	::GetPrivateProfileString( _T("LOCALE"), _T("CODE"),	_T(""), szLocale, sizeof(szLocale), chFile);

	setlocale(LC_ALL, MB(szLocale));

	return true;
}

void PgProcessInfoMgr::GetServerTime(BM::DBTIMESTAMP_EX &rkOut) const
{
	SYSTEMTIME kNowTime;
	g_kEventView.GetLocalTime(&kNowTime);
	rkOut = kNowTime;
}

void PgProcessInfoMgr::ClearGmUser()
{
	CONT_GM_AUTH_DATA_ID::iterator user_itor = m_kGmUsers.begin();
	while(user_itor != m_kGmUsers.end())
	{
		SAFE_DELETE(user_itor->second);
		++user_itor;
	}

	m_kGmUsers.clear();
}