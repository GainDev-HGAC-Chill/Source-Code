// PackDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Pack.h"
#include "PackDlg.h"
#include "./EXT/FolderDlg.h"
#include "BM/FileSupport.h"
#include "PackWork.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern LPTSTR g_lpCmdLine;
bool g_bIsAutoRecovery = false;
bool g_bIsAutoOnePack = false;
extern CPackDlg* g_pDlg;



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CPackDlg 대화 상자

CPackDlg::CPackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPackDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_DIR, m_edtTargetDir);
	DDX_Control(pDX, IDC_EDT_RESULT_FILENAME, m_edtResultFileName);
	DDX_Control(pDX, IDC_EDIT_VERSION_NUM, m_edtVersionNum);
	DDX_Control(pDX, IDC_EDT_OUTPUT_DIR, m_edtOutputDir);
	DDX_Control(pDX, IDC_STATIC_PACK_STATE, m_stcPackState);
	DDX_Control(pDX, IDC_EDIT_PACKMERGE_ORG, m_edtPackMerge_OrgFile);
	DDX_Control(pDX, IDC_EDIT_PACKMERGE_DIR, m_edtPackMerge_Dir);
	DDX_Control(pDX, IDC_EDIT_MAKEONEPACK_ORG, m_edtMakeOnePack_OrgDir);
	DDX_Control(pDX, IDC_EDIT_MAKEONEPACK_NEW, m_edtMakeOnePack_NewDir);
	DDX_Control(pDX, IDC_EDIT_MAKEONEPACK_OUT, m_edtMakeOnePack_OutDir);
	DDX_Control(pDX, IDC_EDIT_MAKEONEPACK_VERSION, m_edtMakeOnePack_Version);
	DDX_Control(pDX, IDC_EDIT_MAKEONEPACK_VERLIST, m_edtMakeOnePack_VerList);
	DDX_Control(pDX, IDC_COMBO_MAKEONEPACK_OPTION, m_cmbMakeOnePack_Option);
	DDX_Control(pDX, IDC_EDIT_PACKMERGE_OUT, m_edtPackMerge_OutFile);
	DDX_Control(pDX, IDC_COMBO_PACKMERGE_OPTION, m_cmbPackMerge_Option);
	DDX_Control(pDX, IDC_CHECK_PARTPACK, m_checkPartPack);
	DDX_Control(pDX, IDC_EDIT_HEADERMERGE_TGTDIR, m_edtHeaderMerge_Dir);
	DDX_Control(pDX, IDC_EDIT_HEADERMERGE_OUTFILE, m_edtHeaderMerge_File);
	DDX_Control(pDX, IDC_EDIT_DATFILEDIR, m_edtDatFileDir);
	DDX_Control(pDX, IDC_EDIT_NEW_VERSION, m_edtDatNewVersion);
}

BEGIN_MESSAGE_MAP(CPackDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SET_TARGET_DIR, &CPackDlg::OnBnClickedBtnSetTargetDir)
	ON_BN_CLICKED(IDC_BTN_ONLY_TARGET_PACK, &CPackDlg::OnBnClickedBtnOnlyTargetPack)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CPackDlg::OnBnClickedBtnOpenFile)
	ON_BN_CLICKED(IDC_BTN_UPDATEFILEVER, &CPackDlg::OnBnClickedBtnUpdateFileVer)
	ON_BN_CLICKED(IDC_BTN_RECURSIVE_PACK, &CPackDlg::OnBnClickedBtnRecursivePack)
	ON_EN_CHANGE(IDC_EDT_DIR, &CPackDlg::OnEnChangeEdtDir)
	ON_BN_CLICKED(IDC_BTN_MAKE_VER, &CPackDlg::OnBnClickedBtnMakeVer)
	ON_BN_CLICKED(IDC_BTN_PACKMERGE_SET_ORGFILE, &CPackDlg::OnBnClickedBtnPackMerge_OrgFile)
	ON_BN_CLICKED(IDC_BTN_PACKMERGE_SET_DIR, &CPackDlg::OnBnClickedBtnPackMerge_Dir)
	ON_BN_CLICKED(IDC_BTN_PACKMERGE_MERGE, &CPackDlg::OnBnClickedBtnPackMerge_Merge)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_SET_OUTPUT_DIR, &CPackDlg::OnBnClickedBtnSetOutputDir)
	ON_BN_CLICKED(IDC_BTN_MAKEONEPACK_MAKE, &CPackDlg::OnBnClickedBtnMakeOnePack_Make)
	ON_BN_CLICKED(IDC_BTN_MAKEONEPACK_ORG, &CPackDlg::OnBnClickedBtnMakeOnePack_Org)
	ON_BN_CLICKED(IDC_BTN_MAKEONEPACK_NEW, &CPackDlg::OnBnClickedBtnMakeOnePack_New)
	ON_BN_CLICKED(IDC_BTN_MAKEONEPACK_OUT, &CPackDlg::OnBnClickedBtnMakeOnePack_Out)
	ON_BN_CLICKED(IDC_BTN_MAKEONEPACK_VERLIST, &CPackDlg::OnBnClickedBtnMakeOnePack_VerList)
	ON_CBN_SELCHANGE(IDC_COMBO_MAKEONEPACK_OPTION, &CPackDlg::OnCbnSelchangeComboMakeonepackOption)
	ON_BN_CLICKED(IDC_BTN_PACKMERGE_SET_OUTFILE, &CPackDlg::OnBnClickedBtnPackmergeSetOutfile)
	ON_CBN_SELCHANGE(IDC_COMBO_PACKMERGE_OPTION, &CPackDlg::OnCbnSelchangeComboPackmergeOption)
	ON_BN_CLICKED(IDC_BTN_HEADERMERGE_MAKE, &CPackDlg::OnBnClickedBtnHeaderMerge_Make)
	ON_EN_CHANGE(IDC_EDIT_HEADERMERGE_TGTDIR, &CPackDlg::OnEnChangeEdtHeaderMergeDir)
	ON_BN_CLICKED(IDC_BTN_HEADERMERGE_SET_DIR, &CPackDlg::OnBnClickedBtnHeaderMerge_Dir)
	ON_BN_CLICKED(IDC_BTN_HEADERMERGE_SET_FILE, &CPackDlg::OnBnClickedBtnHeaderMerge_File)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// Convert Rela to Real
// ex) C:\\Windows\\System, ../Data/Bin/Test.exe
// out -> C:\\Windows\\Data\\Bin\\Test.exe
std::wstring RelativeToAbsoluteDir(std::wstring strAbsDir, std::wstring strRelDir)
{
    if (strAbsDir.size() <= 0 || strRelDir.size() <= 0)
    {
        return strRelDir;
    }

	size_t iCur = -1;
	while( (iCur = strAbsDir.find(L"/")) != -1 )
		strAbsDir = strAbsDir.replace(iCur, 1, L"\\");
	while( (iCur = strRelDir.find(L"/")) != -1 )
		strRelDir = strRelDir.replace(iCur, 1, L"\\");

	if (strRelDir.find(L".\\") == -1)
	{
		return strRelDir;
	}

    if (strRelDir.find(L".\\") == 0)
    {
		strRelDir = strRelDir.erase(0, 2);
    }

	// 끝에 \\ 없으면 붙인다음 \\ 지우기
	if (strAbsDir.size() != strAbsDir.rfind(L"\\"))
	{
		strAbsDir += L"\\";
	}
	strAbsDir.erase(strAbsDir.rfind(L"\\"), 1);

	while(1)
    {
		// Rela에 ..\\ 이 있으면 Abs 끝을 하나 없애자.
		if (strRelDir.find(L"..\\") == 0)
        //if (strRelDir.Substring(0, 3).Equals("..\\"))
        {
            strRelDir = strRelDir.erase(0, 3);
            int iIdx = strAbsDir.rfind(L"\\");
            strAbsDir = strAbsDir.erase(iIdx, strAbsDir.size() - iIdx);
        }
        else
        {
            break;
        }
    }

	// Rel에 남은 디렉토리를 Abs에 붙이기.
    while (strRelDir.find(L"\\") != -1)
    {
        int iIdx = strRelDir.find(L"\\");
		std::wstring strFolder;
		strFolder.resize(iIdx);
		strFolder = strRelDir.substr(0, iIdx);
        strRelDir = strRelDir.erase(0, iIdx + 1);

        strAbsDir += L"\\";
        strAbsDir += strFolder;
    }
    strAbsDir += L"\\";
    strAbsDir += strRelDir;

    return strAbsDir;
}

// CPackDlg 메시지 처리기
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
		return L"\0";

	std::wstring kTemp = kVec[0];
	UPR(kTemp);
	if (!kTemp.compare(L"PACK.EXE"))
		kVec.erase(kVec.begin());
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

void setLocalDirectory()
{
	char path[MAX_PATH];

	GetModuleFileNameA(GetModuleHandle(0), path, MAX_PATH);
	if (strlen(path)==0)
	{
		return;
	}
	strrchr( path, '\\' )[1] = 0;
	SetCurrentDirectoryA(path);
}

BOOL CPackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	setLocalDirectory();

	//m_edtTargetDir.SetWindowText(_T("C:\\Out\\AutoTest\\SFreedom_Dev"));
	//m_edtOutputDir.SetWindowText(_T("C:\\Out\\AutoTest\\Output"));
	m_edtTargetDir.SetWindowText(_T("D:\\Temp\\PackTest\\Org\\ToolBin"));
	m_edtOutputDir.SetWindowText(_T("D:\\Temp\\PackTest\\OutTest"));

	m_edtMakeOnePack_OrgDir.SetWindowText(_T("C:\\Out\\AutoTest\\SFreedom_Old"));
	m_edtMakeOnePack_NewDir.SetWindowText(_T("C:\\Out\\AutoTest\\SFreedom_New"));
	m_edtMakeOnePack_OutDir.SetWindowText(_T("C:\\Out\\AutoTest\\Output_OnePack"));
	m_edtMakeOnePack_Version.SetWindowText(_T("1.0.0.0"));
	m_edtMakeOnePack_VerList.SetWindowText(_T("C:\\Out\\AutoTest\\Output_OnePack\\VERSION.LST"));

	m_cmbMakeOnePack_Option.AddString(_T("Normal Version"));
	m_cmbMakeOnePack_Option.AddString(_T("Assem Version"));
	m_cmbMakeOnePack_Option.AddString(_T("Full Version"));
	m_cmbMakeOnePack_Option.SelectString(0, _T("Normal Version"));

	m_cmbPackMerge_Option.AddString(_T("PackFile And Directory"));
	m_cmbPackMerge_Option.AddString(_T("PackFile And PackFile"));
	m_cmbPackMerge_Option.SelectString(0, _T("PackFile And Directory"));

	m_edtVersionNum.SetWindowText(_T("0.0.1"));
	
	InitPack();

	// 인자: -automake_recovery 목표경로?결과경로
	if( g_lpCmdLine[0] != _T('\0') )
	{
		// 자동 리커버리 만들기
		// -automake_recovery C:\Out\AutoTest\SFreedom_Dev?C:\Out\AutoTest\Outputzzzzz
		std::wstring wstrContent = FindParameter(g_lpCmdLine, L"-automake_recovery");
		std::wstring wstrOnePack = FindParameter(g_lpCmdLine, L"-automake_onepack");
		if (wstrContent.size() != 0 &&
			wstrContent.find(L"?") != -1)
		{
			size_t div = wstrContent.find(L"?");
			std::wstring kTargetDir = wstrContent.substr(0, div);
			std::wstring kOutputDir = wstrContent.substr(div+1, wstrContent.size() - (div+1));

			std::wstring kCurDir;
			kCurDir.resize(512);
			::GetCurrentDirectory(512, &kCurDir.at(0));
			kTargetDir = RelativeToAbsoluteDir(kCurDir, kTargetDir);
			kOutputDir = RelativeToAbsoluteDir(kCurDir, kOutputDir);

			if (::GetFileAttributes(kTargetDir.c_str()) == INVALID_FILE_ATTRIBUTES)
			{
				return false;
			}
			
			// 자동으로 Recovery 만들기.
			m_edtTargetDir.SetWindowText(kTargetDir.c_str());
			m_edtOutputDir.SetWindowText(kOutputDir.c_str());

			g_bIsAutoRecovery = true;
			DoMakeVersion(this);
		}
		// 자동 원 팩
		// -automake_onepack C:\Out\AutoTest\SFreedom_Dev\XML
		else if(wstrOnePack.size() != 0)
		{
			if (!g_pDlg)
			{
				g_pDlg = this;
			}

			g_bIsAutoOnePack = true;

			std::vector<std::wstring> kVec;
			BreakSepW(g_lpCmdLine, kVec, L" ");
			m_edtTargetDir.SetWindowText(kVec.at(1).c_str());
			if(kVec.size()>2)
			{
				m_edtVersionNum.SetWindowText(kVec.at(2).c_str());
			}

			OnEnChangeEdtDir();
			SetTimer(2, 1, 0);
		}
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//
void CPackDlg::OnTimer(UINT_PTR nIDEvent)
{
	// Run Auto One Pack
	if (nIDEvent == 2)
	{
		KillTimer(2);
		OnBnClickedBtnOnlyTargetPack();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPackDlg::OnEnChangeEdtDir()
{
	UpdateData(FALSE);
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정하고  마스크에 OR 연산하여 설정된
	// ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출해야만
	// 해당 알림 메시지를 보냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString kTargetDir;
	m_edtTargetDir.GetWindowText(kTargetDir);

	std::wstring wstrDir(kTargetDir);

	std::wstring wstrFileName = BM::GetLastFolderName(wstrDir);
	wstrFileName += _T(".dat");
	m_edtResultFileName.SetWindowText( wstrFileName.c_str() );

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnSetTargetDir()
{	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
	// create and initialize a new object
	CFolderDlg dlg(TRUE, _T(""), this);

	// set the text that is displayed above the tree view control
	dlg.SetTitle(_T("팩킹할 타켓을 지정하십시오."));

	// show dialog
	if (dlg.DoModal() == IDCANCEL) return;

	// get selected folder
	m_edtTargetDir.SetWindowText(dlg.GetFolderName());

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnSetOutputDir()
{	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
	// create and initialize a new object
	CFolderDlg dlg(TRUE, _T(""), this);

	// set the text that is displayed above the tree view control
	dlg.SetTitle(_T("결과물이 나갈 곳을 지정하십시오."));

	// show dialog
	if (dlg.DoModal() == IDCANCEL) return;

	// get selected folder
	m_edtOutputDir.SetWindowText(dlg.GetFolderName());

	UpdateData(TRUE);
}


void CPackDlg::OnBnClickedBtnOnlyTargetPack()
{
	UpdateData(FALSE);
	
	CString kTargetDir;
	m_edtTargetDir.GetWindowText(kTargetDir);
	CString kResultFileName;
	m_edtResultFileName.GetWindowText(kResultFileName);
	std::wstring wstrResult(kResultFileName);

	std::wstring wstrOutput = _T("merge header file") + wstrResult;
	if (g_pDlg)
	{
		g_pDlg->m_stcPackState.SetWindowText(wstrOutput.c_str());
	}

	CString kDir;
	m_edtTargetDir.GetWindowText(kTargetDir);

	CString kPatchVer;
	m_edtVersionNum.GetWindowText(kPatchVer);

	OneFilePackWork(kTargetDir, kResultFileName, kPatchVer);

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnOpenFile()
{
	UpdateData(FALSE);

	CFileDialog dlg(TRUE,
		L"dat",
		NULL,
		OFN_CREATEPROMPT | OFN_HIDEREADONLY,
		L"Headerfolders Files (*.dat)|*.dat|Version List Files (*.DAT)|*.DAT|",
		NULL);
	if (dlg.DoModal() == IDCANCEL) return;

	m_edtDatFileDir.SetWindowText(dlg.GetPathName());
	BM::VersionInfo Info;
	std::wstring kTemp = dlg.GetPathName();
	BM::PgDataPackManager::GetPackVersion(kTemp, Info);
	
	CString	Str;
	wchar_t Temp[MAX_PATH] = {0,};
	_itow_s(Info.Version.i16Major, Temp, MAX_PATH, 10);
	Str = Temp;
	Str+=L".";
	_itow_s(Info.Version.i16Minor, Temp, MAX_PATH, 10);
	Str += Temp;
	Str+=L".";
	_itow_s(Info.Version.i32Tiny, Temp, MAX_PATH, 10);
	Str += Temp;
	GetDlgItem(IDC_ST_VERSION)->SetWindowText(Str);
	
	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnUpdateFileVer()
{
	UpdateData(FALSE);

	std::wstring kTemp;
	kTemp.resize(m_edtDatNewVersion.GetWindowTextLengthW()+1);
	m_edtDatNewVersion.GetWindowTextW(&kTemp.at(0), kTemp.size());

	typedef std::list< std::wstring > CUT_STRING;
	CUT_STRING	kList;
	BM::vstring::CutTextByKey(kTemp, std::wstring(L"."), kList);

	BM::VersionInfo	Info;

	if( kList.size() != 3 )
	{
		return;
	}

	CUT_STRING::iterator	iter = kList.begin();
	Info.Version.i16Major = _wtoi(iter->c_str());	iter++;
	Info.Version.i16Minor = _wtoi(iter->c_str());	iter++;
	Info.Version.i32Tiny = _wtoi(iter->c_str());

	kTemp.clear();
	kTemp.resize(m_edtDatFileDir.GetWindowTextLengthW() + 1);
	m_edtDatFileDir.GetWindowTextW(&kTemp.at(0), kTemp.size());
	BM::PgDataPackManager::UpdatePackVersion(kTemp, Info);

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnRecursivePack()
{
	UpdateData(FALSE);
	
	CString kTargetDir;
	m_edtTargetDir.GetWindowText(kTargetDir);

	RecursivePackWork(kTargetDir);

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnMakeVer()
{
	CString kTargetDir;
	m_edtTargetDir.GetWindowText(kTargetDir);
	CString kOutputDir;
	m_edtOutputDir.GetWindowText(kOutputDir);

	DoMakeVersion(this);
}

void CPackDlg::OnBnClickedBtnPackMerge_OrgFile()
{
	UpdateData(FALSE);

	CFileDialog dlg(TRUE,
		L"dat",
		NULL,
		OFN_CREATEPROMPT | OFN_HIDEREADONLY,
		L"Pack Files (*.dat)|*.dat|Pack Files (*.DAT)|*.DAT|",
		NULL);
	if (dlg.DoModal() == IDCANCEL) return;

	m_edtPackMerge_OrgFile.SetWindowText(dlg.GetPathName());

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnPackMerge_Dir()
{
	UpdateData(FALSE);

	if(m_cmbPackMerge_Option.GetCurSel() == 0)
	{
		CFolderDlg dlg(TRUE, _T(""), this);
		dlg.SetTitle(_T("합쳐질 폴더를 지정합니다."));
		if (dlg.DoModal() == IDCANCEL) return;
		m_edtPackMerge_Dir.SetWindowText(dlg.GetFolderName());
	}
	else if(m_cmbPackMerge_Option.GetCurSel() == 1)
	{
		CFileDialog dlg(TRUE,
			L"dat",
			NULL,
			OFN_CREATEPROMPT | OFN_HIDEREADONLY,
			L"Pack Files (*.dat)|*.dat|Pack Files (*.DAT)|*.DAT|",
			NULL);
		if (dlg.DoModal() == IDCANCEL) return;

		m_edtPackMerge_Dir.SetWindowText(dlg.GetPathName());
	}

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnPackMerge_Merge()
{
	DoMergeFile(this);
}

void CPackDlg::OnBnClickedBtnMakeOnePack_Make()
{
	DoMakeOnePack(this);
}

void CPackDlg::OnBnClickedBtnMakeOnePack_Org()
{
	UpdateData(FALSE);

	CFolderDlg dlg(TRUE, _T(""), this);
	dlg.SetTitle(_T("원본 폴더를 지정합니다."));
	if (dlg.DoModal() == IDCANCEL) return;
	m_edtMakeOnePack_OrgDir.SetWindowText(dlg.GetFolderName());

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnMakeOnePack_New()
{
	UpdateData(FALSE);

	CFolderDlg dlg(TRUE, _T(""), this);
	dlg.SetTitle(_T("새 버젼 폴더를 지정합니다."));
	if (dlg.DoModal() == IDCANCEL) return;
	m_edtMakeOnePack_NewDir.SetWindowText(dlg.GetFolderName());

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnMakeOnePack_Out()
{
	UpdateData(FALSE);

	CFolderDlg dlg(TRUE, _T(""), this);
	dlg.SetTitle(_T("결과물이 출력될 폴더를 지정합니다."));
	if (dlg.DoModal() == IDCANCEL) return;
	m_edtMakeOnePack_OutDir.SetWindowText(dlg.GetFolderName());

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnMakeOnePack_VerList()
{
	UpdateData(FALSE);

	CFileDialog dlg(TRUE,
		L"lst",
		NULL,
		OFN_CREATEPROMPT | OFN_HIDEREADONLY,
		L"Version List Files (*.lst)|*.lst|Version List Files (*.LST)|*.LST|",
		NULL);
	if (dlg.DoModal() == IDCANCEL) return;

	m_edtMakeOnePack_VerList.SetWindowText(dlg.GetPathName());

	UpdateData(TRUE);
}

void CPackDlg::OnCbnSelchangeComboMakeonepackOption()
{
	int iVer = m_cmbMakeOnePack_Option.GetCurSel();
	if (iVer == 2)
	{
		m_edtMakeOnePack_OrgDir.EnableWindow(false);
	}
	else
	{
		m_edtMakeOnePack_OrgDir.EnableWindow(true);
	}
}

void CPackDlg::OnBnClickedBtnPackmergeSetOutfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPackDlg::OnCbnSelchangeComboPackmergeOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_cmbPackMerge_Option.GetCurSel() == 0)
	{
		SetDlgItemTextW(IDC_BTN_PACKMERGE_SET_DIR, _T("SetDir"));
	}
	else if(m_cmbPackMerge_Option.GetCurSel() == 1)
	{
		SetDlgItemTextW(IDC_BTN_PACKMERGE_SET_DIR, _T("SetFile"));
	}

}

void CPackDlg::OnBnClickedBtnHeaderMerge_Make()
{
	UpdateData(FALSE);
	
	CString kTargetDir;
	m_edtHeaderMerge_Dir.GetWindowText(kTargetDir);
	CString kResultFileName;
	m_edtHeaderMerge_File.GetWindowText(kResultFileName);

	HeaderMerge(kTargetDir, kResultFileName);

	UpdateData(TRUE);
}

void CPackDlg::OnEnChangeEdtHeaderMergeDir()
{
	UpdateData(FALSE);

	CString kTargetDir;
	m_edtHeaderMerge_Dir.GetWindowText(kTargetDir);
	std::wstring wstrDir(kTargetDir);

	BM::AddFolderMark(wstrDir);
	std::wstring wstrFileName = wstrDir + _T("HEADFOLDERS.DAT");
	m_edtHeaderMerge_File.SetWindowText( wstrFileName.c_str() );

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnHeaderMerge_Dir()
{
	UpdateData(FALSE);

	CFolderDlg dlg(TRUE, _T(""), this);
	dlg.SetTitle(_T("헤더를 만들 최상위 폴더를 지정합니다."));
	if (dlg.DoModal() == IDCANCEL) return;
	m_edtHeaderMerge_Dir.SetWindowText(dlg.GetFolderName());

	UpdateData(TRUE);
}

void CPackDlg::OnBnClickedBtnHeaderMerge_File()
{
	UpdateData(FALSE);

	CFileDialog dlg(TRUE,
		L"dat",
		NULL,
		OFN_CREATEPROMPT | OFN_HIDEREADONLY,
		L"Headerfolders Files (*.dat)|*.dat|Version List Files (*.DAT)|*.DAT|",
		NULL);
	if (dlg.DoModal() == IDCANCEL) return;

	m_edtHeaderMerge_File.SetWindowText(dlg.GetPathName());

	UpdateData(TRUE);
}
