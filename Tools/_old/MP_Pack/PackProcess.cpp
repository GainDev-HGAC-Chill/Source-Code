//-----------------------------------------------------------------------------
//  폴더를 선택합니다.
//-----------------------------------------------------------------------------
#include "defines.h"
#include "PackProcess.h"

//-----------------------------------------------------------------------------
//  생성자 및 파괴자
//-----------------------------------------------------------------------------
CPackProcess::CPackProcess(void)
{
	
}

CPackProcess::~CPackProcess(void)
{
}

//-----------------------------------------------------------------------------
//  초기화
//-----------------------------------------------------------------------------
void CPackProcess::Init(const std::wstring& CmdLine)
{
	//	팩 옵션을 읽고
	BM::CPackInfo	kPackInfo;
	if(!kPackInfo.Init())
	{
		g_PackProcess.SetStateText(L"Program Init Failed");
	}

	//	매니져롤 초기화
	if(!BM::PgDataPackManager::Init(kPackInfo))
	{
		g_PackProcess.SetStateText(L"Program Manager Init Failed");
	}


	//	옵션
	m_eWork		= eWork_Diff;
	m_eProcess	= eProcess_Prepare;

	m_bIsAuto		= false;
	m_bIsPackToDir	= false;
	m_bIsFullPack	= false;
	m_bIsHeaderList	= false;
	
	m_PackThread	= INVALID_HANDLE_VALUE;

	PackInit();

	if(!CmdParse(CmdLine))
	{
		//	폴더명
		m_wstrOrgDir	= L"Insert Target(Corrected Client) Directory";
		m_wstrCrtDir	= L"Insert Target(Original Client) Directory or Command";
		m_wstrOutDir	= L"Insert Output Directory";

		SetWindowText(GetDlgItem(g_hDlgWnd, IDC_STATIC_STATE), L"Please Push Start.");
		SendMessage(GetDlgItem(g_hDlgWnd, IDC_RDO_DIFF), BM_SETCHECK, BST_CHECKED, 0);
		SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_ORG_DIR), m_wstrOrgDir.c_str());
		SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), m_wstrCrtDir.c_str());
		SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), m_wstrOutDir.c_str());
	}
	else
	{
		StartProcess();
	}
}

//-----------------------------------------------------------------------------
//  자동화
//-----------------------------------------------------------------------------
bool CPackProcess::CmdParse(const std::wstring& CmdLine)
{
	//	커맨드 라인이 없으면 종료
	if(!CmdLine.size())
	{
		return	false;
	}

	//	있다 쪼개라	- 메인 명령어
	typedef	std::list<std::wstring>	CUT_STRING;
	CUT_STRING	kMainList;
	BM::vstring::CutTextByKey(CmdLine, std::wstring(L"@"), kMainList);
	if(kMainList.size() == 2)
	{
		CUT_STRING::iterator	Main_iter = kMainList.begin();

		//	쪼개라 - 서브 명령어
		CUT_STRING	kSubList;
		BM::vstring::CutTextByKey((*Main_iter), std::wstring(L"|"), kSubList);
		CUT_STRING::iterator	Sub_iter = kSubList.begin();
		//	전체냐?
		if(::_tcsicmp((*Sub_iter).c_str(), L"A") == 0)
		{
			++Sub_iter;
			//	옵션은 ?
			if(::_tcsicmp((*Sub_iter).c_str(), L"Pack") == 0)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_PACKOPTION, m_bIsFullPack);
			}
			else if(::_tcsicmp((*Sub_iter).c_str(), L"diff") == 0)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsPackToDir);
			}
			else if(::_tcsicmp((*Sub_iter).c_str(), L"all") == 0)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsPackToDir);
				SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsFullPack);
			}
			++Main_iter;
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_RDO_ALL), BM_SETCHECK, BST_CHECKED, 0);
			m_eWork = eWork_AllProcess;
			_ParseFolder((*Main_iter));
			return	true;
		}
		//	Diff만?
		else if(::_tcsicmp((*Sub_iter).c_str(), L"D") == 0)
		{
			++Sub_iter;
			//	옵션은?
			if(::_tcsicmp((*Sub_iter).c_str(), L"1") == 0)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsPackToDir);
			}
			++Main_iter;
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_RDO_DIFF), BM_SETCHECK, BST_CHECKED, 0);
			m_eWork = eWork_Diff;
			if(!_ParseFolder((*Main_iter)))
			{
				return	false;
			}
			return	true;			
		}
		//	Pack만? (여기부턴 옵션없음)
		else if(::_tcsicmp((*Sub_iter).c_str(), L"P") == 0)
		{
			++Main_iter;
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_RDO_PACK), BM_SETCHECK, BST_CHECKED, 0);
			m_eWork = eWork_Pack;
			if(!_ParseFolder((*Main_iter)))
			{
				return	false;
			}
			return	true;
		}
		//	List만?
		else if(::_tcsicmp((*Sub_iter).c_str(), L"L") == 0)
		{
			++Main_iter;
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_RDO_CREATEHEADER), BM_SETCHECK, BST_CHECKED, 0);
			m_eWork = eWork_CreateHeader;
			if(!_ParseFolder((*Main_iter)))
			{
				return	false;
			}
			return	true;
		}
		//	List Merge만?
		else if(::_tcsicmp((*Sub_iter).c_str(), L"M") == 0)
		{
			++Main_iter;
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_RDO_HEADERMERGE), BM_SETCHECK, BST_CHECKED, 0);
			m_eWork = eWork_HeaderMerge;
			if(!_ParseFolder((*Main_iter)))
			{
				return	false;
			}
			return	true;
		}		
	}

	return	false;
}

//	폴더만 따로.
bool CPackProcess::_ParseFolder(const std::wstring&	CmdLine)
{
	//	문자열이 없네 돌아가자
	if(!CmdLine.size())
	{
		return	false;
	}

	//	문자열 있다 쪼개자
	typedef	std::list<std::wstring>	CUT_STRING;
	CUT_STRING	kMainList;
	BM::vstring::CutTextByKey(CmdLine, std::wstring(L"\""), kMainList);
	
	//	쪼갰는데 이상하다. 돌아가자
	if(!kMainList.size())
	{
		return	false;
	}

	//	정상이다 돌자
	CUT_STRING::iterator	kMain_iter = kMainList.begin();
	while(kMain_iter != kMainList.end())
	{
		//	구분하자 무슨폴더|경로명
		CUT_STRING	kSubList;
		BM::vstring::CutTextByKey((*kMain_iter), std::wstring(L"|"), kSubList);
		if(kSubList.size() == 2)
		{
			CUT_STRING::iterator	Sub_iter = kSubList.begin();
			//	최신 폴더다
			if(::_tcsicmp((*Sub_iter).c_str(), L"dest") == 0)
			{
				++Sub_iter;
				SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_ORG_DIR), (*Sub_iter).c_str());
			}
			//	이전 폴더다
			else if(::_tcsicmp((*Sub_iter).c_str(), L"sour") == 0)
			{
				++Sub_iter;
				SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), (*Sub_iter).c_str());
			}
			//	출력 폴더다
			else if(::_tcsicmp((*Sub_iter).c_str(), L"out") == 0)
			{
				++Sub_iter;
				SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), (*Sub_iter).c_str());
			}
		}

		++kMain_iter;
	}

	//	화면 갱신좀 해주자
	DialogState();

	return	true;
}

//-----------------------------------------------------------------------------
//  콘트롤 입력 처리
//-----------------------------------------------------------------------------
bool CPackProcess::CommandAction(WPARAM wParam, LPARAM lParam)
{
	//	버튼 행동
	switch (LOWORD(wParam))
	{
	case IDCANCEL:					{ EndDialog(g_hDlgWnd, 0);	}return TRUE;
	case IDC_RDO_DIFF:				{ m_eWork = eWork_Diff;	}break;
	case IDC_RDO_PACK:				{ m_eWork = eWork_Pack;	}break;
	case IDC_RDO_ALL:				{ m_eWork = eWork_AllProcess;	}break;
	case IDC_RDO_CREATEHEADER:		{ m_eWork = eWork_CreateHeader; }break;
	case IDC_RDO_HEADERMERGE:		{ m_eWork = eWork_HeaderMerge;	}break;
	case IDC_RDO_BINDPACK:			{ m_eWork = eWork_BindPack;	}break;
	case IDC_RDO_SERIESPATCH:		{ m_eWork = eWork_SeriesPatch;	}break;
	case IDC_CHK_DIFFOPTION:		{ SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsPackToDir);	}break;
	case IDC_CHK_PACKOPTION:		{ SetCheckBox(g_hDlgWnd, IDC_CHK_PACKOPTION, m_bIsFullPack);	}break;
	case IDC_BTN_OPEN_ORG:			{ FolderInput(g_hDlgWnd, IDC_TXT_ORG_DIR);	}break;
	case IDC_BTN_OPEN_CRT:			{ FolderInput(g_hDlgWnd, IDC_TXT_CRT_DIR);	}break;
	case IDC_BTN_OPEN_OUT:			{ FolderInput(g_hDlgWnd, IDC_TXT_OUT_DIR);	}break;
	case IDC_BTN_COMMIT:			{ StartProcess(); }break;
	case IDC_BTN_CREATE_PATCH_ID:	{ CreatePatchID(); }break;
	case IDC_BTN_APPLYDATVER:
		{
			wchar_t	szTemp[MAX_PATH] = {0,};
			std::wstring	kTotal;
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CLIENT_INFO), szTemp, MAX_PATH);
			kTotal = szTemp;
			kTotal += L".";
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_COUNT), szTemp, MAX_PATH);
			kTotal += szTemp;
			kTotal += L".";
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_LIMIT), szTemp, MAX_PATH);
			kTotal += szTemp;

			SetWindowText(GetDlgItem(g_hDlgWnd, IDC_ST_VERSION_NEX), kTotal.c_str());
		}break;
	case IDC_BTN_OPEN_DAT:			
		{ 
			TCHAR	szTemp[MAX_PATH] = {0,};
			if(FileSelect(g_hDlgWnd, szTemp, false))
			{
				SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_DAT_FOLDERDIR), szTemp);
				BM::VersionInfo	Info;
				BM::PgDataPackManager::GetPackVersion(szTemp, Info);
				swprintf_s(szTemp, MAX_PATH, _T("%d.%d.%d"), (int)Info.Version.i16Major, (int)Info.Version.i16Minor, (int)Info.Version.i32Tiny);
				SetWindowText(GetDlgItem(g_hDlgWnd, IDC_ST_VERSION_PRE), szTemp);
			}
		}break;
	case IDC_BTN_VERSWAP:
		{
			std::wstring kFolderInfo;
			BM::VersionInfo	Info;

			kFolderInfo.resize(::GetWindowTextLength(GetDlgItem(g_hDlgWnd, IDC_TXT_DAT_FOLDERDIR)) + 1);
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_DAT_FOLDERDIR), &kFolderInfo.at(0), (int)kFolderInfo.size());

			wchar_t	szTemp[MAX_PATH] = {0,};
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CLIENT_INFO), szTemp, MAX_PATH);
			Info.Version.i16Major = (WORD)_wtoi(szTemp);
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_COUNT), szTemp, MAX_PATH);
			Info.Version.i16Minor = (WORD)_wtoi(szTemp);
			GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_LIMIT), szTemp, MAX_PATH);
			Info.Version.i32Tiny = _wtoi(szTemp);

			UpdateDATVersion(kFolderInfo, Info);
		}break;
	}
	
	DialogState();

	return	FALSE;
}

bool CPackProcess::SetPackVersion(std::wstring const& wstrFileName)
{
	BM::VersionInfo	Info;

	wchar_t	szTemp[MAX_PATH] = {0,};
	GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CLIENT_INFO), szTemp, MAX_PATH);
	Info.Version.i16Major = (WORD)_wtoi(szTemp);
	GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_COUNT), szTemp, MAX_PATH);
	Info.Version.i16Minor = (WORD)_wtoi(szTemp);
	GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_LIMIT), szTemp, MAX_PATH);
	Info.Version.i32Tiny = _wtoi(szTemp);

	return g_PackProcess.UpdateDATVersion(wstrFileName, Info);
}

bool CPackProcess::UpdateDATVersion(std::wstring const& FolderDir, BM::VersionInfo const& Version)
{
	if( _waccess(FolderDir.c_str(), 0) == -1 )
	{
		return false;
	}

	if( !BM::PgDataPackManager::UpdatePackVersion(FolderDir, Version) )
	{
		return false;
	}

	return true;
}

//	버튼 사용 가능 / 불가능 스위치
void CPackProcess::DialogState()
{
	switch(m_eWork)
	{
		case eWork_Diff:
		case eWork_AllProcess:
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), EM_SETREADONLY, 0, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_CRT), true);
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), EM_SETREADONLY, 0, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_OUT), true);
		break;
		case eWork_HeaderMerge:
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), EM_SETREADONLY, 0, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_CRT), true);
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), EM_SETREADONLY, 1, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_OUT), false);
		break;
		case eWork_Pack:
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), EM_SETREADONLY, 1, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_CRT), false);
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), EM_SETREADONLY, 0, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_OUT), true);
		break;
		case eWork_CreateHeader:
		case eWork_BindPack:
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), EM_SETREADONLY, 1, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_CRT), false);
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), EM_SETREADONLY, 1, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_OUT), false);
		break;
		case eWork_SeriesPatch:
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), EM_SETREADONLY, 0, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_CRT), false);
			SendMessage(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), EM_SETREADONLY, 0, 0);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_BTN_OPEN_OUT), true);
		break;
	}

	switch(m_eWork)
	{
		case eWork_Pack:
		case eWork_HeaderMerge:
		case eWork_CreateHeader:
		case eWork_BindPack:
		case eWork_SeriesPatch:
			if(m_bIsFullPack)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_PACKOPTION, m_bIsFullPack);
			}
			if(m_bIsPackToDir)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsPackToDir);
			}

			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_PACKOPTION), false);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_DIFFOPTION), false);
		break;
		case eWork_Diff:
			if(m_bIsFullPack)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_PACKOPTION, m_bIsFullPack);
			}
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_PACKOPTION), false);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_DIFFOPTION), true);
		break;
		default:
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_PACKOPTION), true);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_DIFFOPTION), true);
		break;
	}

	switch(m_eWork)
	{
		case eWork_Pack:
		case eWork_HeaderMerge:
		case eWork_CreateHeader:
		case eWork_BindPack:
		case eWork_SeriesPatch:
			if(m_bIsFullPack)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_PACKOPTION, m_bIsFullPack);
			}
			if(m_bIsPackToDir)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_DIFFOPTION, m_bIsPackToDir);
			}

			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_PACKOPTION), false);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_DIFFOPTION), false);
		break;
		case eWork_Diff:
			if(m_bIsFullPack)
			{
				SetCheckBox(g_hDlgWnd, IDC_CHK_PACKOPTION, m_bIsFullPack);
			}
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_PACKOPTION), false);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_DIFFOPTION), true);
		break;
		default:
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_PACKOPTION), true);
			EnableWindow(GetDlgItem(g_hDlgWnd, IDC_CHK_DIFFOPTION), true);
		break;
	}
}

//-----------------------------------------------------------------------------
//  폴더를 선택
//-----------------------------------------------------------------------------
bool CPackProcess::FolderSelect(const HWND& hWnd, TCHAR* szFolderName, const int& Length)
{
	memset(szFolderName, 0, Length);

	BROWSEINFO			bi;

	bi.hwndOwner		= hWnd;	//부모윈도우핸들
	bi.pidlRoot			= NULL;
	bi.pszDisplayName	= NULL;
	bi.lpszTitle		= L"입력할 폴더를 선택하세요";
	bi.ulFlags			= 0;
	bi.lpfn				= NULL;
	bi.lParam			= 0;
	
	//폴더 선택 창을 만든다
	LPITEMIDLIST pidl	= SHBrowseForFolder(&bi);
	if(pidl == NULL)	return	false;

	//폴더변수에저장한다
	SHGetPathFromIDList(pidl, szFolderName);

	return	true;
}

bool CPackProcess::FileSelect(const HWND& hWnd, TCHAR* szFolderName, bool const IsMulti, const int& Length)
{
	TCHAR	szTemp[MAX_PATH] = {0,};

	OPENFILENAME	OFN;
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner	= hWnd;
	OFN.lpstrFilter = _T(".DAT Files\0*.DAT\0");
	OFN.lpstrFile	= szTemp;
	OFN.Flags		= OFN_EXPLORER | ((!IsMulti)?(0):(OFN_ALLOWMULTISELECT));
	OFN.nMaxFile	= 255;

	if( ::GetOpenFileName(&OFN) == TRUE )
	{	
		memset(szFolderName, 0, Length);
		memcpy(szFolderName, szTemp, sizeof(szTemp));
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//  프로세스 시작
//-----------------------------------------------------------------------------
bool CPackProcess::StartProcess()
{	
	TCHAR		szTemp[MAX_PATH];

	if(m_eProcess == eProcess_Prepare)
	{
		GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_ORG_DIR), szTemp, MAX_PATH);
		m_wstrOrgDir	= szTemp;
		GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CRT_DIR), szTemp, MAX_PATH);
		m_wstrCrtDir	= szTemp;
		GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_OUT_DIR), szTemp, MAX_PATH);
		m_wstrOutDir	= szTemp;

		unsigned	ThreadID;

//		GetList(m_wstrOriDir, L".\\", false);

		m_PackThread	= (HANDLE)_beginthreadex(NULL, 0, &DiffToPack, this, 0, &ThreadID);
	}
	else
	{
		MessageBox(g_hDlgWnd, L"팩 하는 중입니다.", L"알림", MB_OK);
	}

	return	true;
}

//-----------------------------------------------------------------------------
//  상태를 갱신
//-----------------------------------------------------------------------------
void CPackProcess::SetStateText(const std::wstring& wstrState)
{
	SetWindowText(GetDlgItem(g_hDlgWnd, IDC_STATIC_STATE), wstrState.c_str());
}

void CPackProcess::PackInit()
{
	const TCHAR	CONFIG[] = L".\\PackConfig.ini";
	TCHAR			szTemp[MAX_PATH] = {0,};
	BM::VersionInfo	Info;

	::GetPrivateProfileString(L"PATCH", L"CLIENT", L"0", szTemp, MAX_PATH, CONFIG);
	SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CLIENT_INFO), szTemp);
	Info.Version.i16Major = _wtoi(szTemp);

	::GetPrivateProfileString(L"PATCH", L"COUNT", L"0", szTemp, MAX_PATH, CONFIG);
	SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_COUNT), szTemp);
	Info.Version.i16Minor = _wtoi(szTemp);

	m_nPatchCount = ::GetPrivateProfileInt(L"PATCH", L"LIMIT", 0, CONFIG);
	++m_nPatchCount;
	_itot_s(m_nPatchCount, szTemp, MAX_PATH, 10);
	Info.Version.i32Tiny = m_nPatchCount;
	SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_LIMIT), szTemp);

	swprintf_s(szTemp, MAX_PATH, _T("%d.%d.%d"), (int)Info.Version.i16Major, (int)Info.Version.i16Minor, (int)Info.Version.i32Tiny);
	SetWindowText(GetDlgItem(g_hDlgWnd, IDC_ST_VERSION_NEX), szTemp);
}
