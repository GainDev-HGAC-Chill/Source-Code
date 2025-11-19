#include "stdafx.h"
#include "LoginDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define STRING_TABLE_LOGINDLG		20000

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	m_pkAccountDlg = NULL;
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT_SERVER, m_kCbSelectServer);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(ID_OK, &CLoginDlg::OnOkBtnClicked)
	ON_BN_CLICKED(ID_CANCEL, &CLoginDlg::OnCancelBtnClicked)
	ON_BN_CLICKED(ID_NEW_ACCOUNT, &CLoginDlg::OnNewAccountBtnClicked)
	ON_WM_NCDESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDlg();

	return TRUE; 
}

void CLoginDlg::OnClose()
{
	if(theApp.m_pkPetitionDlg)
		theApp.m_pkPetitionDlg->DestroyWindow();

	if(theApp.m_pkNoticDlg)
		theApp.m_pkNoticDlg->DestroyWindow();	
	DestroyWindow();
	g_kNetwork.Terminate();
}

void CLoginDlg::OnCancelBtnClicked()
{
	OnClose();
}

void CLoginDlg::PostNcDestroy()
{
	delete this;

	CDialog::PostNcDestroy();
}

void CLoginDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();
}


void CLoginDlg::InitDlg()
{
	CWnd *pkWnd;
	CString kString;
	STRING_TABLE::iterator Itr;

	for(int i = 1; i <= 6; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_LOGINDLG + i);
		kString = UNI(Itr->second.c_str());
		pkWnd = GetDlgItem(IDD_LOGIN_FRM + i);
		pkWnd->SetWindowText(kString);
	}

	m_pkAccountDlg = NULL;
}

void CLoginDlg::OnOkBtnClicked()
{
	wchar_t wId[20];
	wchar_t wPw[20];

	GetDlgItemTextW(IDC_ID_EDIT, wId, 20);
	GetDlgItemTextW(IDC_PW_EDIT, wPw, 20);

	g_kProcessInfoMgr.m_kMyInfo.SetID(wId);
	g_kProcessInfoMgr.m_kMyInfo.SetPW(wPw);
	g_kProcessInfoMgr.m_kMyInfo.SetVersion(PACKET_VERSION);
	if(g_kNetwork.ConnectServer())
	{
		INFO_LOG(BM::LOG_LV6, _T("LoginServer Connection Seccess"));	
	}
}

void CLoginDlg::OnNewAccountBtnClicked()
{
	if(m_pkAccountDlg == NULL)
	{
		m_pkAccountDlg = new CAccountDlg;
		m_pkAccountDlg->Create(IDD_ADD_ACCOUNT_FRM);
	} 
	m_pkAccountDlg->ShowWindow(SW_SHOW);
	m_pkAccountDlg->SetFocus();
}


/*
void CLoginDlg::CreatePetitonDlg()
{
	m_pkPetitionDlg = new CPetitionDlg;
	m_pkPetitionDlg->Create(IDD_PETITION_FRM);
	theApp.m_pMainWnd = m_pkPetitionDlg;
	m_pkPetitionDlg->ShowWindow(SW_SHOW);
	m_pkPetitionDlg->SetFocus();
}

void CLoginDlg::CreateNoticDlg()
{
	m_pkNoticDlg = new CNoticeDlg;
	m_pkNoticDlg->Create(IDD_NOTIC_FRM);
	theApp.m_pMainWnd = m_pkNoticDlg;
	m_pkNoticDlg->ShowWindow(SW_SHOW);
}
*/