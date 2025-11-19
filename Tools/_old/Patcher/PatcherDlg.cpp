// PatcherDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include <afxpriv.h>
#include "Patcher.h"
#include "BM/FileSupport.h"
#include "PatchProcess.h"
#include "PgPatchThread.h"
#include "PatcherDlg.h"
#include "ConfigXml.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// 응용 프로그램 정보에 사용되는 COptionDlg 대화 상자입니다.

class COptionDlg : public CDialog
{
public:
	COptionDlg();

	CConfigXml	m_Option;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPTION };

	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnRdoFullScr();
	afx_msg void OnBnClickedBtnRdoWinScr();
	afx_msg void OnBnClickedBtnRdoGraphicLow();
	afx_msg void OnBnClickedBtnRdoGraphicHigh();
	afx_msg void OnBnClickedBtnRdoGraphicUse();

	afx_msg void COptionDlg::OnBnClickedBtnRdoWQLow();
	afx_msg void COptionDlg::OnBnClickedBtnRdoWQHigh();
	afx_msg void COptionDlg::OnBnClickedBtnRdoVDLow();
	afx_msg void COptionDlg::OnBnClickedBtnRdoVDHigh();
	afx_msg void COptionDlg::OnBnClickedBtnRdoWSLow();
	afx_msg void COptionDlg::OnBnClickedBtnRdoWSHigh();
	afx_msg void COptionDlg::OnBnClickedBtnRdoGELow();
	afx_msg void COptionDlg::OnBnClickedBtnRdoGEHigh();
	afx_msg void COptionDlg::OnBnClickedBtnRdoAALow();
	afx_msg void COptionDlg::OnBnClickedBtnRdoAAHigh();

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	void COptionDlg::UpdateGraphicRdo();
	void COptionDlg::UpdateAttrRdo();
	void COptionDlg::UpdateRdo();
};

COptionDlg::COptionDlg() : CDialog(COptionDlg::IDD)
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &COptionDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &COptionDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_RDO_SCREEN_FULL, &COptionDlg::OnBnClickedBtnRdoFullScr)
	ON_BN_CLICKED(IDC_RDO_SCREEN_WIN, &COptionDlg::OnBnClickedBtnRdoWinScr)
	ON_BN_CLICKED(IDC_RDO_GRAPHICLOW, &COptionDlg::OnBnClickedBtnRdoGraphicLow)
	ON_BN_CLICKED(IDC_RDO_GRAPHICHIGH, &COptionDlg::OnBnClickedBtnRdoGraphicHigh)
	ON_BN_CLICKED(IDC_RDO_GRAPHICUSE, &COptionDlg::OnBnClickedBtnRdoGraphicUse)

	ON_BN_CLICKED(IDC_RDO_WQLOW, &COptionDlg::OnBnClickedBtnRdoWQLow)
	ON_BN_CLICKED(IDC_RDO_WQHIGH, &COptionDlg::OnBnClickedBtnRdoWQHigh)
	ON_BN_CLICKED(IDC_RDO_VDLOW, &COptionDlg::OnBnClickedBtnRdoVDLow)
	ON_BN_CLICKED(IDC_RDO_VDHIGH, &COptionDlg::OnBnClickedBtnRdoVDHigh)
	ON_BN_CLICKED(IDC_RDO_WSLOW, &COptionDlg::OnBnClickedBtnRdoWSLow)
	ON_BN_CLICKED(IDC_RDO_WSHIGH, &COptionDlg::OnBnClickedBtnRdoWSHigh)
	ON_BN_CLICKED(IDC_RDO_GELOW, &COptionDlg::OnBnClickedBtnRdoGELow)
	ON_BN_CLICKED(IDC_RDO_GEHIGH, &COptionDlg::OnBnClickedBtnRdoGEHigh)
	ON_BN_CLICKED(IDC_RDO_AALOW, &COptionDlg::OnBnClickedBtnRdoAALow)
	ON_BN_CLICKED(IDC_RDO_AAHIGH, &COptionDlg::OnBnClickedBtnRdoAAHigh)
END_MESSAGE_MAP()

BOOL COptionDlg::OnInitDialog()
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

	UpdateRdo();
	UpdateGraphicRdo();
	UpdateAttrRdo();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COptionDlg::UpdateRdo()
{
	SendDlgItemMessage(IDC_RDO_SCREEN_FULL, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_RDO_SCREEN_WIN, BM_SETCHECK, BST_UNCHECKED, 0);

	//	화면 모드
	if(m_Option.GetUseScreenMode())
	{ 
		SendDlgItemMessage(IDC_RDO_SCREEN_FULL, BM_SETCHECK, BST_CHECKED, 0);
	}
	else
	{
		SendDlgItemMessage(IDC_RDO_SCREEN_WIN, BM_SETCHECK, BST_CHECKED, 0);
	}
	Invalidate(FALSE);
}

void COptionDlg::UpdateGraphicRdo()
{
	SendDlgItemMessage(IDC_RDO_GRAPHICLOW, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_RDO_GRAPHICHIGH, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_RDO_GRAPHICUSE, BM_SETCHECK, BST_UNCHECKED, 0);

	int	nWinID = 0;
	//	그래픽 모드
	switch(m_Option.GetUseGraphicMode())
	{
		case 0:	{ nWinID = IDC_RDO_GRAPHICLOW; } break;
		case 1:	{ nWinID = IDC_RDO_GRAPHICHIGH; } break;
		case 2:	{ nWinID = IDC_RDO_GRAPHICUSE; } break;
	}
	SendDlgItemMessage(nWinID, BM_SETCHECK, BST_CHECKED, 0);

	Invalidate(FALSE);
}

void COptionDlg::UpdateAttrRdo()
{
	int	nWinID = 0;

	for(int i = IDC_RDO_WQLOW; i <= IDC_RDO_AAHIGH; ++i)
	{
		SendDlgItemMessage(i, BM_SETCHECK, BST_UNCHECKED, 0);
	}

	for(int i = SET_USE_BACKGROUND; i <= SET_USE_GLOW; ++i)
	{
		EConfigOption	Option = (EConfigOption)i;
		//	세부 설정
		if(!m_Option.GetUseConElement(Option))
		{
			//	Low다
			switch(Option)
			{
				case SET_USE_BACKGROUND:	{ nWinID = IDC_RDO_WQLOW; }	break;
				case SET_USE_VISION:		{ nWinID = IDC_RDO_VDLOW; }	break;
				case SET_USE_SHADER:		{ nWinID = IDC_RDO_WSLOW; }	break;
				case SET_USE_SOFT_OUTLINE:	{ nWinID = IDC_RDO_AALOW; }	break;
				case SET_USE_GLOW:			{ nWinID = IDC_RDO_GELOW; }	break;
				default:	{ MessageBox(L"아직 작업안했네", L"알림", MB_OK); }	break;
			}
		}
		else
		{
			//	High다
			switch(Option)
			{
				case SET_USE_BACKGROUND:	{ nWinID = IDC_RDO_WQHIGH; }	break;
				case SET_USE_VISION:		{ nWinID = IDC_RDO_VDHIGH; }	break;
				case SET_USE_SHADER:		{ nWinID = IDC_RDO_WSHIGH; }	break;
				case SET_USE_SOFT_OUTLINE:	{ nWinID = IDC_RDO_AAHIGH; }	break;
				case SET_USE_GLOW:			{ nWinID = IDC_RDO_GEHIGH; }	break;
				default:	{ MessageBox(L"아직 작업안했네", L"알림", MB_OK); }	break;
			}
		}
		SendDlgItemMessage(nWinID, BM_SETCHECK, BST_CHECKED, 0);
	}

	Invalidate(FALSE);
}

//	함수들~
void COptionDlg::OnBnClickedBtnOk()
{
	m_Option.Save();
	OnOK();
}

void COptionDlg::OnBnClickedBtnCancel()
{
	OnCancel();
}

void COptionDlg::OnBnClickedBtnRdoFullScr()
{
	m_Option.UpDate(SET_SCREEN_MODE, TRUE);
}

void COptionDlg::OnBnClickedBtnRdoWinScr()
{
	m_Option.UpDate(SET_SCREEN_MODE, FALSE);
}

void COptionDlg::OnBnClickedBtnRdoGraphicLow()
{
	m_Option.UpDate(SET_GRAPHIC_MODE, 0);
	UpdateAttrRdo();
}

void COptionDlg::OnBnClickedBtnRdoGraphicHigh()
{
	m_Option.UpDate(SET_GRAPHIC_MODE, 1);
	UpdateAttrRdo();
}

void COptionDlg::OnBnClickedBtnRdoGraphicUse()
{
	m_Option.UpDate(SET_GRAPHIC_MODE, 2);
}

void COptionDlg::OnBnClickedBtnRdoWQLow()
{
	m_Option.UpDate(SET_USE_BACKGROUND, 0);
	UpdateGraphicRdo();
}

void COptionDlg::OnBnClickedBtnRdoWQHigh()
{
	m_Option.UpDate(SET_USE_BACKGROUND, 1);
	UpdateGraphicRdo();
}

void COptionDlg::OnBnClickedBtnRdoVDLow()
{									
	m_Option.UpDate(SET_USE_VISION, 0);
	UpdateGraphicRdo();
}									
									
void COptionDlg::OnBnClickedBtnRdoVDHigh()
{
	m_Option.UpDate(SET_USE_VISION, 1);
	UpdateGraphicRdo();
}

void COptionDlg::OnBnClickedBtnRdoWSLow()
{									
	m_Option.UpDate(SET_USE_SHADER, 0);
	UpdateGraphicRdo();
}									
									
void COptionDlg::OnBnClickedBtnRdoWSHigh()
{
	m_Option.UpDate(SET_USE_SHADER, 1);
	UpdateGraphicRdo();
}

void COptionDlg::OnBnClickedBtnRdoGELow()
{									
	m_Option.UpDate(SET_USE_GLOW, 0);
	UpdateGraphicRdo();
}									
									
void COptionDlg::OnBnClickedBtnRdoGEHigh()
{
	m_Option.UpDate(SET_USE_GLOW, 1);
	UpdateGraphicRdo();
}

void COptionDlg::OnBnClickedBtnRdoAALow()
{									
	m_Option.UpDate(SET_USE_SOFT_OUTLINE, 0);
	UpdateGraphicRdo();
}									
									
void COptionDlg::OnBnClickedBtnRdoAAHigh()
{
	m_Option.UpDate(SET_USE_SOFT_OUTLINE, 1);
	UpdateGraphicRdo();
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// CPatcherDlg 대화 상자
CPatcherDlg::CPatcherDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK(CPatcherDlg::IDD, pParent)
	, m_strProgressText1(_T(""))
	, m_strProgressText2(_T(""))
	, m_strStateText(_T(""))
	, m_strHeadState(_T(""))
	, m_strRemainTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROGRESS_TEXT1, m_strProgressText1);
	DDX_Text(pDX, IDC_PROGRESS_TEXT2, m_strProgressText2);
	DDX_Text(pDX, IDC_STATIC_PATCH_STATE, m_strStateText);
	DDX_Control(pDX, IDC_BTN_ACTION, m_btnCancelAction);	
	DDX_Text(pDX, IDC_STATIC_PATCH_STATE_HEAD, m_strHeadState);
	DDX_Control(pDX, IDC_BTN_PATCH_PROCESS, m_btnPatch);
	DDX_Text(pDX, IDC_REMAIN_TIME, m_strRemainTime);
	DDX_Control(pDX, IDC_BTN_OPTION, m_btnOption);
	DDX_Control(pDX, IDC_BTN_RECOVERY, m_btnRecovery);
}

BEGIN_MESSAGE_MAP(CPatcherDlg, CDialogSK)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_BN_CLICKED(IDC_BTN_PATCH_PROCESS, &CPatcherDlg::OnBnClickedBtnPatchProcess)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CPatcherDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPTION, &CPatcherDlg::OnBnClickedBtnOption)
	ON_BN_CLICKED(IDC_BTN_RECOVERY, &CPatcherDlg::OnBnClickedBtnRecovery)
END_MESSAGE_MAP()


// CPatcherDlg 메시지 처리기

BOOL CPatcherDlg::OnInitDialog()
{
	CDialogSK::OnInitDialog();

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
	ReadIni_UiText();

	SetWindowText(L"Dragonica patcher");
	//SetDlgItemText(IDD_PATCHER_DIALOG, L"Patcher");

	// Font
	VERIFY(m_kFont.CreateFont(
	   12,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_NORMAL,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   _T("MS Shell Dlg")));         // lpszFacename

	m_bIsRecovery			= false;
	m_bIsProcessing			= false;
	m_fCurrentPercent		= 0.0f;
	m_fTotalPercent			= 0.0f;
	m_bChangeCurrentPercent	= false;

	m_wstrTargetDir.resize(512);
	::GetCurrentDirectory(300, &m_wstrTargetDir.at(0));
	//m_wstrTargetDir = _T("C:\\Out\\AutoTest\\SFreedom_Dev_PatchTarget");

	m_CurrentFileTotalSize	= 0;
	m_TotalFileSize			= 0;
	m_ReceiveTotalFileSize	= 0;
	m_fPassTime				= 0;

	m_strHeadState			= "";
	m_strProgressText1		= "0.0%";
	m_strProgressText2		= "0.0%";
	m_strRemainTime			= "";

	// 이쁜 다이얼로그
	EnableEasyMove();                    // enable moving of the dialog by clicking anywhere in the dialog
	if(g_Locale == LS_CHN)
	{
		SetBitmap(IDB_BITMAP_BGCHN);           // set background bitmap
	}
	else
	{
		SetBitmap(IDB_BITMAP_BG);           // set background bitmap
		//m_WB.CreateWB("http://psp.ruliweb.com", m_hWnd, AfxGetInstanceHandle());
	}
	SetStyle(LO_RESIZE);                 // resize dialog to the size of the bitmap
	SetTransparentColor(RGB(0, 255, 0)); // set green as the transparent color

	// 이쁜 버튼 : 옵션 ( 일단 가림 )
	ImgButtonSetup(m_btnOption, m_strOption, 10, 364, 65, 23);
	SetDlgItemTextW(IDC_BTN_OPTION, m_strOption);

	// 리커버리
	ImgButtonSetup(m_btnRecovery, m_strRecovery, 76, 364, 65, 23);	// 76, 364, 65, 23
	SetDlgItemTextW(IDC_BTN_RECOVERY, m_strRecovery);
	
	ImgButtonSetup(m_btnPatch, m_strPatch, 377, 364, 65, 23);
	SetDlgItemTextW(IDC_BTN_PATCH_PROCESS, m_strPatch);
	
	ImgButtonSetup(m_btnCancelAction, m_strCancel, 443, 364, 65, 23);
	SetDlgItemTextW(IDC_BTN_ACTION, m_strCancel);

	m_eActionState = eActionState_Prepare;
	SetActionState(eActionState_Prepare);

	// 컨트롤 위치 맞추기
	GetDlgItem(IDC_STATIC_PATCH_STATE_HEAD)->SetWindowPos(0, 24, 271, 390 , 15, SWP_NOZORDER);
	GetDlgItem(IDC_STATIC_PATCH_STATE)->SetWindowPos(0, 24, 271, 650, 15, SWP_NOZORDER);
	GetDlgItem(IDC_REMAIN_TIME)->SetWindowPos(0, 24, 336, 450, 15, SWP_NOZORDER);	
	
	// 현재/전체 프로그래스
	GetDlgItem(IDC_PROGRESS_TEXT1)->SetWindowPos(0, 253, 293, 200, 15, SWP_NOZORDER);	
	GetDlgItem(IDC_PROGRESS_TEXT2)->SetWindowPos(0, 253, 308, 200, 15, SWP_NOZORDER);	

	OnBnClickedBtnPatchProcess();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPatcherDlg::ImgButtonSetup(CButtonST& Btn, CString text, int x, int y, int width, int height)
{
	Btn.SetIcon(IDI_EMPTY);
	Btn.DrawTransparent();
	Btn.DrawBorder(FALSE);
	Btn.EnableBalloonTooltip();
	Btn.SetTooltipText(text);
	Btn.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	Btn.SetWindowPos(0, x, y, width, height, SWP_NOZORDER);
}

void CPatcherDlg::ReadIni_UiText()
{
	const TCHAR PACK_CONFIG_FILE_NAME[] =  _T(".\\PatcherConfig.ini");

	TCHAR szPatch[MAX_PATH]		= {0,};
	TCHAR szExcute[MAX_PATH]	= {0,};
	TCHAR szCancel[MAX_PATH]	= {0,};
	TCHAR szExit[MAX_PATH]		= {0,};
	TCHAR szRecovery[MAX_PATH]	= {0,};
	TCHAR szOption[MAX_PATH]	= {0,};
	
	::GetPrivateProfileString( _T("UI_TEXT"), _T("PATCH"),	_T(""), szPatch, sizeof(szPatch), PACK_CONFIG_FILE_NAME);
	::GetPrivateProfileString( _T("UI_TEXT"), _T("EXCUTE"),	_T(""), szExcute, sizeof(szExcute), PACK_CONFIG_FILE_NAME);
	::GetPrivateProfileString( _T("UI_TEXT"), _T("CANCEL"),	_T(""), szCancel, sizeof(szCancel), PACK_CONFIG_FILE_NAME);
	::GetPrivateProfileString( _T("UI_TEXT"), _T("EXIT"),	_T(""), szExit, sizeof(szExit), PACK_CONFIG_FILE_NAME);
	::GetPrivateProfileString( _T("UI_TEXT"), _T("RECOVERY"),	_T(""), szRecovery, sizeof(szRecovery), PACK_CONFIG_FILE_NAME);
	::GetPrivateProfileString( _T("UI_TEXT"), _T("OPTION"),	_T(""), szOption, sizeof(szOption), PACK_CONFIG_FILE_NAME);

	char _szPatch[MAX_PATH];
	char _szExcute[MAX_PATH];
	char _szCancel[MAX_PATH];
	char _szExit[MAX_PATH];
	char _szRecovery[MAX_PATH];
	char _szOption[MAX_PATH];
	
	size_t CharactersConverted = 0;
	wcstombs_s(&CharactersConverted,	_szPatch,		szPatch,	sizeof(szPatch)		);
	wcstombs_s(&CharactersConverted,	_szExcute,		szExcute,	sizeof(szExcute)	);
	wcstombs_s(&CharactersConverted,	_szCancel,		szCancel,	sizeof(szCancel)	);
	wcstombs_s(&CharactersConverted,	_szExit,		szExit,		sizeof(szExit)		);
	wcstombs_s(&CharactersConverted,	_szRecovery,	szRecovery,	sizeof(szRecovery)	);
	wcstombs_s(&CharactersConverted,	_szOption,		szOption,	sizeof(szOption)	);

	SetUIText(_szPatch, _szCancel, _szExit, _szExcute, _szRecovery, _szOption);
}

size_t CPatcherDlg::GetReceiveCurrentFileSize()
{
	return m_ReceiveCurrentFileSize; 
}

void CPatcherDlg::SetReceiveCurrentFileSize(size_t receive_file_size)
{
	m_ReceiveCurrentFileSize = receive_file_size;
}

void CPatcherDlg::SetTotalFileSize(size_t total_size)
{
	m_TotalFileSize = total_size;

	Invalidate(FALSE);
}

void CPatcherDlg::SetActionState(EActionState eState)
{
	m_eActionState = eState;

	// 버튼 글자 바꾸자.
	if (m_eActionState == eActionState_Prepare)
	{
		SetDlgItemTextW(IDC_BTN_ACTION, m_strExit);
		m_btnCancelAction.SetTooltipText(m_strExit);
	}
	else if (m_eActionState == eActionState_Downloading)
	{
		SetDlgItemTextW(IDC_BTN_ACTION, m_strCancel);
		m_btnCancelAction.SetTooltipText(m_strCancel);
	}
	else if (m_eActionState == eActionState_Patching)
	{
		SetDlgItemTextW(IDC_BTN_ACTION, m_strCancel);
		m_btnCancelAction.SetTooltipText(m_strCancel);
	}
	else if (m_eActionState == eActionState_Complete)
	{
		SetDlgItemTextW(IDC_BTN_ACTION, m_strExit);
		m_btnCancelAction.SetTooltipText(m_strExit);

		SetDlgItemTextW(IDC_BTN_PATCH_PROCESS, m_strExecute);
		m_btnPatch.SetTooltipText(m_strExecute);
	}
}

void CPatcherDlg::PatchComplete()
{
	m_ReceiveCurrentFileSize	= m_CurrentFileTotalSize;
	m_ReceiveTotalFileSize		= m_TotalFileSize;
}

void CPatcherDlg::SetCurrentDownloadFile(const std::wstring wstrFilename, size_t file_size)
{
	m_ReceiveTotalFileSize += m_CurrentFileTotalSize;

	m_wstrCurrentFileName	= wstrFilename;
	m_CurrentFileTotalSize	= file_size;
	m_bChangeCurrentPercent = true;

	Invalidate(FALSE);
}

#define PROGRESS_SIZEX		(446)
void CPatcherDlg::DrawProgressBar(int iIdx, float fPercent)
{
	// 현재 프로그래스는 쓰지 않음.

	RECT rtRect;
	GetWindowRect(&rtRect);
	int iMaxWidth	= rtRect.right - rtRect.left;
	float fSX		= fPercent / 100.0f * (float)PROGRESS_SIZEX;
	float fSX2		= (100.0f - fPercent) / 100.0f * (float)PROGRESS_SIZEX;

	int iBarHeight	= 12;
	int iIdx_X		= 49;
	int iIdx_Y		= 0;

	if (iIdx == 0)
	{
		iIdx_Y = 294;
	}
	else if (iIdx == 1)
	{
		iIdx_Y = 309;
	}

	// 게이지 중앙의 퍼센트
	char buf[256];
	sprintf_s(buf, "%3.1f%%", fPercent);
	if (iIdx == 0)
	{
		SetProgressText1(buf);
		m_fCurrentPercent = fPercent;
	}
	else if (iIdx == 1)
	{
		SetProgressText2(buf);
		m_fTotalPercent = fPercent;
	}

	Invalidate(FALSE);
}

void CPatcherDlg::DrawProgressBar(int iIdx, float fPercent, CDC *pkBufferDC, CDC *pkMemDC)
{
	RECT rtRect;
	GetWindowRect(&rtRect);
	
	int		iMaxWidth	= rtRect.right - rtRect.left;
	float	fSX			= fPercent / 100.0f * (float)PROGRESS_SIZEX;
	float	fSX2		= (100.0f - fPercent) / 100.0f * (float)PROGRESS_SIZEX;

	int		iBarHeight	= 12;
	int		iIdx_X		= 49;
	int		iIdx_Y		= 0;

	CBitmap bitmap;
	if (iIdx == 0)
	{
		iIdx_Y = 294;
		bitmap.LoadBitmapW(IDB_PROGRESS1);
	}
	else if (iIdx == 1)
	{
		iIdx_Y = 309;
		bitmap.LoadBitmapW(IDB_PROGRESS2);
	}
	CBitmap *pOldBitmap = (CBitmap *)pkMemDC->SelectObject(&bitmap);
	pkBufferDC->BitBlt(iIdx_X, iIdx_Y, (int)fSX, iBarHeight, pkMemDC, 0, 0, SRCCOPY);

	// 게이지 중앙의 퍼센트
	char buf[256];
	sprintf_s(buf, "%3.1f%%", fPercent);
	if (iIdx==0)
		SetProgressText1(buf);
	else if (iIdx==1)
		SetProgressText2(buf);
}

void CPatcherDlg::SetProgressText1(char *szText1)
{
	m_strProgressText1 = szText1;
}

void CPatcherDlg::SetProgressText2(char *szText2)
{
	m_strProgressText2 = szText2;
}

void CPatcherDlg::SetHeadStateText(const char *szText, bool bDoInvalidate)
{
	if (!m_strStateText)
		return;

	m_strStateText = szText;

	if (bDoInvalidate)
	{
		Invalidate(FALSE);
	}
}

void CPatcherDlg::SetHeadStateText(char *szText, bool bDoInvalidate)
{
	if (!m_strStateText)
		return;

	m_strStateText = szText;

	if (bDoInvalidate)
	{
		Invalidate(FALSE);
	}
}

void CPatcherDlg::SetStateText(char *szText)
{
	m_strStateText = szText;
}

void CPatcherDlg::SetRemainTimeText(char *szText)
{
	size_t iSize	= strlen("Remain: ") + strlen(szText) + 1;
	char *szResult	= new char[iSize];
	sprintf_s(szResult, iSize, "Remain: %s", szText);
	m_strRemainTime	= szResult;
	delete[] szResult;

	Invalidate(FALSE);
}

void CPatcherDlg::InitClock()
{
	m_StartTime = clock();
}

void CPatcherDlg::SetUIText(char *pkPatch, char *pkCancel, char *pkExit, char *pkExcute, char *pkRecovery, char *pkOption)
{
	m_strPatch		= pkPatch;
	m_strExecute	= pkExcute;
	m_strCancel		= pkCancel;
	m_strExit		= pkExit;
	m_strRecovery	= pkRecovery;
	m_strOption		= pkOption;
}

void CPatcherDlg::UiUpdate()
{
	if (m_wstrCurrentFileName.size() > 1)
	{
		if (m_CurrentFileTotalSize)
		{
			size_t get_file_size = m_ReceiveCurrentFileSize;

			float fPercent		= ((float)get_file_size / (float)m_CurrentFileTotalSize) * 100.0f;
			m_fCurrentPercent	= fPercent;
			if (m_fCurrentPercent > 100.0f) m_fCurrentPercent = 100.0f;
		}
		else
		{
			m_fCurrentPercent	= 100;
		}

		m_bChangeCurrentPercent = false;

		// 텍스트를 이쁘게. 바꾸자.
		if (m_ReceiveCurrentFileSize > m_CurrentFileTotalSize)
			m_ReceiveCurrentFileSize = m_CurrentFileTotalSize;

		char szFileSize[100];
		char szTotalSize[100];

		CalcCapacityText(szFileSize, m_ReceiveCurrentFileSize);
		CalcCapacityText(szTotalSize, m_CurrentFileTotalSize);

		char szText[256];
		char szFilename[256];

		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, szFilename, m_wstrCurrentFileName.c_str(), m_wstrCurrentFileName.size());

		sprintf_s(szText, "%s ( %s / %s )",	szFilename,	szFileSize,	szTotalSize);
		SetStateText( szText );
	}
	
	if (m_wstrCurrentFileName.size())
	{
		char szFileSize[100];
		char szTotalSize[100];
		char szText[256];

		// total draw
		float fDownloadSize = (float)(m_ReceiveTotalFileSize + m_ReceiveCurrentFileSize);
		m_fTotalPercent		= fDownloadSize / (float)m_TotalFileSize * 100.0f;
		if (m_fTotalPercent > 100) m_fTotalPercent = 100;

		// remain time
		clock_t finish				= clock();
		m_PassTime					= (finish - m_StartTime) / CLOCKS_PER_SEC;
		float fRemainTimeTotalSec	= ((m_TotalFileSize - fDownloadSize) / fDownloadSize) * m_PassTime;
		float fRemainHour			= fRemainTimeTotalSec / 3600;
		float fRemainMin			= (float)((int)(fRemainTimeTotalSec / 60) % 60);
		int iRemainSec				= (int)fRemainTimeTotalSec % 60;

		char szHour[64];
		memset(szHour, 0, sizeof(szHour));
		char szMin[64];
		memset(szMin, 0, sizeof(szMin));
		char szSec[64];
		memset(szSec, 0, sizeof(szSec));

		if (fRemainHour > 0)
		{
			sprintf_s(szHour, "%dHour ", (int)fRemainHour);
		}
		if (fRemainMin > 0)
		{
			sprintf_s(szMin, "%dMin ", (int)fRemainMin);
		}
		sprintf_s(szSec, "%dSec ", iRemainSec);

		if (fDownloadSize > m_TotalFileSize)
		{
			fDownloadSize = (float)m_TotalFileSize;
		}

		CalcCapacityText(szFileSize, (size_t)fDownloadSize);
		CalcCapacityText(szTotalSize, m_TotalFileSize);

		sprintf_s(szText, "%s%s%s- %s/%s", szHour, szMin, szSec, szFileSize, szTotalSize);

		SetRemainTimeText(szText);
	}

	Invalidate(FALSE);
}

void CPatcherDlg::CalcCapacityText(char *pkOutText, size_t FileSize)
{
	// 텍스트를 이쁘게. 바꾸자.
	bool bIsFileSizeKB	= false;
	bool bIsFileSizeMB	= false;
	int iFileSizeKB		= 0;
	int iFileSizeMB 	= 0;
	float fFileSize 	= (float)FileSize;
	
	if (FileSize >= 100000)
	{
		iFileSizeMB = (int)(FileSize / 1000000);
		fFileSize	= (float)((int)fFileSize % 1000000);
		fFileSize	/= 100000;

		bIsFileSizeMB = true;
	}
	else if (FileSize >= 100)
	{
		iFileSizeKB = (int)(FileSize / 1000);
		fFileSize	= (float)((int)fFileSize % 1000);
		fFileSize	/= 100;

		bIsFileSizeKB = true;
	}

	if (bIsFileSizeMB)
	{
		sprintf_s(pkOutText, 100, "%d.%dMB", iFileSizeMB, (int)fFileSize);
	}
	else if (bIsFileSizeKB)
	{
		sprintf_s(pkOutText, 100, "%d.%dKB", iFileSizeKB, (int)fFileSize);
	}
	else
	{
		sprintf_s(pkOutText, 100, "%dByte", FileSize);
	}
}

void CPatcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogSK::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CPatcherDlg::OnPaint()
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
		CDialogSK::OnPaint();
		// 더블 버퍼링-
		{
			int iX	= 0;
			int iY	= 0;
			int iSX = 515;
			int iSY = 395 - 40;

			CDC *WinDC = GetDC();
			CDC MemDC, kBufferDC;
			CBitmap bitmap;
			
			kBufferDC.CreateCompatibleDC(WinDC);
			MemDC.CreateCompatibleDC(WinDC);
			bitmap.CreateCompatibleBitmap(WinDC, iSX, iSY);
			kBufferDC.SelectObject(&bitmap);
			
			// 배경
			CBitmap bitmap2;
			if(g_Locale == LS_CHN)
			{
				bitmap2.LoadBitmap(IDB_BITMAP_BGCHN);
			}
			else
			{
				bitmap2.LoadBitmap(IDB_BITMAP_BG);
			}
			CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap2);
			kBufferDC.BitBlt(iX, iY, iSX, iSY, &MemDC, 0, 0, SRCCOPY);

			DrawProgressBar(0, m_fCurrentPercent, &kBufferDC, &MemDC);
			DrawProgressBar(1, m_fTotalPercent, &kBufferDC, &MemDC);

			// 텍스트
			RECT kDrawRect;

			SetBkMode(kBufferDC, TRANSPARENT);
			kBufferDC.SelectObject(&m_kFont);

			kDrawRect	= ControlText(IDC_PROGRESS_TEXT1);
			kBufferDC.DrawText(m_strProgressText1, &kDrawRect, DT_WORDBREAK);

			kDrawRect	= ControlText(IDC_PROGRESS_TEXT2);
			kBufferDC.DrawText(m_strProgressText2, &kDrawRect, DT_LEFT);

			kDrawRect	= ControlText(IDC_STATIC_PATCH_STATE);
			kBufferDC.DrawText(m_strStateText, &kDrawRect, DT_LEFT);

			kDrawRect	= ControlText(IDC_STATIC_PATCH_STATE_HEAD);
			kBufferDC.DrawText(m_strHeadState, &kDrawRect, DT_LEFT);

			kDrawRect	= ControlText(IDC_REMAIN_TIME);
			kBufferDC.DrawText(m_strRemainTime, &kDrawRect, DT_LEFT);

			WinDC->BitBlt(iX,iY,iSX,iSY,&kBufferDC,0,0,SRCCOPY);

			bitmap.DeleteObject();
			ReleaseDC(WinDC);
		}
	}
}

RECT CPatcherDlg::ControlText(DWORD DlgItemID)
{
	RECT kClientRect;
	RECT kWindowRect;
	RECT kDrawRect;
	RECT kWndRect;

	GetWindowRect(&kWndRect);

	GetDlgItem(DlgItemID)->GetWindowRect(&kWindowRect);
	GetDlgItem(DlgItemID)->GetClientRect(&kClientRect);

	kDrawRect.left		= kWindowRect.left - kWndRect.left;
	kDrawRect.top		= kWindowRect.top - kWndRect.top;
	kDrawRect.right		= kDrawRect.left + kClientRect.right;
	kDrawRect.bottom	= kDrawRect.top + kClientRect.bottom;

	return kDrawRect;
}
// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPatcherDlg::OnBnClickedBtnPatchProcess()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_eActionState != eActionState_Complete)
	{
		if (m_eActionState == eActionState_Prepare)
		{
			BM::PgDataPackManager::SetOnLoop(true);
			m_bIsRecovery = false;
			CString kTargetDir = m_wstrTargetDir.c_str();
			DoPatchProcess(kTargetDir, this);
		}
		else
		{
			MessageBox(L"Already running.");
		}
	}
	else
	{
		// 게임 실행
		CString kTargetDir;
		kTargetDir = m_wstrTargetDir.c_str();
		std::wstring wstrDirectory = kTargetDir;
		BM::AddFolderMark(wstrDirectory);
		std::wstring wstrStartProc;
		std::wstring wstrArgCmd;

		TCHAR szPath[MAX_PATH];
		HRESULT hModuleName = GetModuleFileName(GetModuleHandle(0), szPath, MAX_PATH);
		std::wstring strPath = szPath;
		strPath = strPath.substr(0,strPath.rfind(_T('\\')));
		std::wstring strFileName = strPath + _T("\\Release\\Dragonica.exe");

		HWND handle = 0;
		HINSTANCE kIns = 		
			ShellExecute(handle,
				_T("open"),
				//_T("Dragonica.exe"),
				strFileName .c_str(),
				_T("/NoGsm"),
				_T("Release\\"),
				SW_SHOWNORMAL);

		Sleep(100);
		DoExit();
	}
}

HBRUSH CPatcherDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogSK::OnCtlColor(pDC, pWnd, nCtlColor);

	hbr=CDialogSK::OnCtlColor(pDC,pWnd,nCtlColor); 
	     
	static HBRUSH hBrush_bmp=NULL;
	static HBRUSH hBrush_system=NULL;

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);

		break;
	}
	return hbr;
}

// IDLE Test
LRESULT CPatcherDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
	UpdateDialogControls(this, FALSE);

	return (LRESULT)0;
}

void CPatcherDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_eActionState == eActionState_Prepare ||
		m_eActionState == eActionState_Complete)
	{
		PostQuitMessage(0);
		//DoExit();
	}
	else if (m_eActionState == eActionState_Downloading ||
		m_eActionState == eActionState_Patching)
	{
		BM::PgDataPackManager::SetOnLoop(false);
		m_bIsProcessing = false;
		g_kPatchThread.IsStop(true);
		SetHeadStateText( "User called to cancel." );
		DeleteFile(L"Temp.ftp");
		DeleteFile(L"PATCH.TMP");
		PostQuitMessage(0);
	}
}

void CPatcherDlg::OnBnClickedBtnOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	COptionDlg dlgOption;
	dlgOption.DoModal();
}

void CPatcherDlg::OnBnClickedBtnRecovery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bIsRecovery)
	{
		DrawProgressBar(0, 0);
		DrawProgressBar(1, 0);
		BM::PgDataPackManager::SetOnLoop(true);
		m_bIsRecovery = true;
		CString kTargetDir;
		kTargetDir = m_wstrTargetDir.c_str();
		DoPatchProcess(kTargetDir, this);

		return;
	}

	// 메시지 처리
	if (m_eActionState != eActionState_Complete)
	{
		if (m_eActionState != eActionState_Prepare)
		{
			MessageBox(L"Already running.");
		}
	}
	else
	{
		MessageBox(L"Recovery complete.");
	}
}
