// Patcher.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "Patcher.h"
#include "PatcherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int __argc;          /* count of cmd line args */
char ** __argv;      /* pointer to table of cmd line args */
wchar_t ** __wargv;  /* pointer to table of wide cmd line args */
bool g_fc = false;
bool g_lc = false;

extern std::wstring g_wstrCRC;

// CPatcherApp

BEGIN_MESSAGE_MAP(CPatcherApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPatcherApp 생성

CPatcherApp::CPatcherApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CPatcherApp 개체입니다.
CPatcherApp theApp;

// 문자열 나누기
void BreakSepW(const std::wstring &rkText, std::vector<std::wstring> &rkVec, const std::wstring kSep)
{
	std::wstring kTemp = rkText;
	wchar_t *pToken = NULL;
	wchar_t *pNextToken = NULL;
	pToken = wcstok_s(&kTemp[0], kSep.c_str(), &pNextToken);
	if(NULL == pToken)
	{
		rkVec.push_back(rkText);
		return;
	}
	rkVec.push_back(pToken);

	while(1)
	{
		pToken = wcstok_s(NULL, kSep.c_str(), &pNextToken);
		if( pToken != NULL )
		{
			rkVec.push_back( pToken );
		}
		else
		{
			break;
		}
	}
}

// 인자 가져오기
std::wstring FindParameter(std::wstring wstrCmd, std::wstring wstrHeader)
{
	std::vector<std::wstring> kVec;
	BreakSepW(wstrCmd, kVec, L" ");

	if (kVec.size() <= 1)
	{
		return L"\0";
	}

	if (!kVec[0].compare(L"patcher.exe"))
	{
		kVec.erase(kVec.begin());
	}

	for(unsigned int ui=0; ui<kVec.size() ; ui+=2)
	{
		if ( kVec.size() > ui+1 &&
			!kVec[ui+0].compare(wstrHeader) )
		{
			return kVec[ui+1];
		}
	}

	return L"\0";
}

// 인자 가져오기
bool CheckParameter(std::wstring wstrCmd, std::wstring wstrHeader)
{
	std::vector<std::wstring> kVec;
	BreakSepW(wstrCmd, kVec, L" ");

	if (kVec.size() > 0)
	{
		for(unsigned int i = 0; i < kVec.size(); ++i)
		{
			if(kVec[i].compare(wstrHeader) == 0)
			{
				return	true;
			}
		}
	}

	
	return	false;
}

bool MakeExeCRC()
{
	//char path[512];
	std::wstring wstrPath;
	wstrPath.resize(512);
	GetModuleFileName(GetModuleHandle(0), &wstrPath.at(0), MAX_PATH);
	if (wstrPath.size()==0)
	{
		return false;
	}

	//std::wstring wstrPath = UNI(path);
	unsigned __int64 iCRC;
	BM::GetFileCRC(wstrPath, iCRC);

	g_wstrCRC.resize(PG_PATCHER_CRC_SIZE);
	_ui64tow(iCRC, &g_wstrCRC.at(0), 10);

	return true;
}

// CPatcherApp 초기화
BOOL CPatcherApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//char path[MAX_PATH];

	//GetModuleFileNameA(GetModuleHandle(0), path, MAX_PATH);
	//if (strlen(path)==0)
	//{
	//	return false;
	//}
	//strrchr( path, '\\' )[1] = 0;
	//SetCurrentDirectoryA(path);

	TCHAR szPath[MAX_PATH];
	HRESULT hModuleName = GetModuleFileName(GetModuleHandle(0), szPath, MAX_PATH);
	std::wstring strPath = szPath;
	strPath = strPath.substr(0,strPath.rfind(_T('\\')));
	SetCurrentDirectory(strPath.c_str());

	// 현재 패쳐의 CRC 버젼 만들기 - 아래 인자가 있으면 버젼 CRC를 만듭니다.
	// g_wstrCRC 에 만든다.
	if (!MakeExeCRC())
	{
		MessageBox(0,L"Make CRC Error",L"Error",0);
		return false;
	}

	// 인자가 있으면 
	if( m_lpCmdLine[0] != _T('\0') )
	{
		// 파일화 하기. (!빌드용!)	인자: -initmake patcher.id
		std::wstring wstrContent = FindParameter(m_lpCmdLine, L"-initmake");
		if(wstrContent.size() != 0 && g_wstrCRC.size() != 0)
		{
			// Version CRC 벡터로 변환.
			std::vector<char> vecCRC;
			vecCRC.resize(g_wstrCRC.size());
			memcpy(&vecCRC.at(0), &g_wstrCRC.at(0), g_wstrCRC.size());
			
			// Patcher ID 암호화 한 후 파일로 만들기
			BM::EncSave(wstrContent, vecCRC);

			std::wstring wstrMessage = L"Succese " + wstrContent;
			return true;
			//MessageBox(0, wstrMessage.c_str(), L"make id", 0);
		}

		// 파일화 하기. (!빌드용!)	인자: -initmake patcher.id
		if(CheckParameter(m_lpCmdLine, L"-fc"))
		{
			g_fc = true;
		}

		// 파일화 하기. (!빌드용!)	인자: -initmake patcher.id
		if(CheckParameter(m_lpCmdLine, L"-lc"))
		{
			g_lc = true;
		}
	}

	TCHAR szOption[MAX_PATH] = {0,};
	const TCHAR CONFIG_FILE_NAME[] =  _T(".\\PatcherConfig.ini");
	::GetPrivateProfileString( _T("LOCAL_INFO"), _T("NATION_NAME"),	_T("KOR"), szOption, sizeof(szOption), CONFIG_FILE_NAME);
	std::wstring	wstrLocal = szOption;
	if(wstrLocal.compare(L"CHS") == 0)
	{
		g_Locale = LS_CHN;
	}

	if(strcmp(MB(szOption), "CHS") == 0)
	{
		g_Locale = LS_CHN;
	}

	if(g_Locale != LS_CHN)
	{
		// 클라이언트가 떠 있으면 패쳐는 실행하지 않게 한다. 
		HANDLE	hMutex = NULL;
		hMutex	= OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"Dragonica_Client");
		if(hMutex != NULL)
		{	
			MessageBox(0, L"Already running Client", L"Error", 0);
			return false;
		}
		else
		{
			CloseHandle(hMutex);
		}
	}

	// 패쳐의 Mutex 생성
	CreateMutex(NULL, true, L"OnePatcherExecute");
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		MessageBox(0,L"Already running Patcher",L"Error",0);
		return false;
	}

	setlocale(LC_ALL, "kor");

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CPatcherDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	MakeExeCRC();
	return FALSE;
}

// 안됨.
int CPatcherApp::Run()
{
	try {
		//int *asdf;
		//*asdf = 1;
		CWinApp::Run();
	} // end of try
	catch (CSystemException* e)
	{
		SETDIR_ERROR_REPORT(TEXT("./Log"));
		TCHAR wcause[256];
		e->GetErrorMessage(wcause, 256);
		//FORMAT_ERROR_REPORT(e->mExceptInfo->ExceptionRecord->ExceptionCode, wcause, TEXT(""), 0);
		e->WriteAdditionalInfo();
		delete e;
	}

	return 0;
}
