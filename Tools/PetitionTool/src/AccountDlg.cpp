#include "stdafx.h"
#include "AccountDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define STRING_TABLE_ACCOUNTDLG		30000
#define MAX_SYSTEM_TEXT				5

IMPLEMENT_DYNAMIC(CAccountDlg, CDialog)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{

}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
ON_BN_CLICKED(ID_ADD, &CAccountDlg::OnAddBtnClicked)
ON_BN_CLICKED(ID_ACANCEL, &CAccountDlg::OnBnClickedCancel)
ON_WM_NCDESTROY()
ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL CAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDlg();

	return TRUE;
}

void CAccountDlg::OnClose()
{
	DestroyWindow();
}

void CAccountDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();
	theApp.m_pMainWnd = theApp.m_pkLoginDlg;
	theApp.m_pkLoginDlg->m_pkAccountDlg = NULL;
}

void CAccountDlg::PostNcDestroy()
{
	delete this;
}

void CAccountDlg::InitDlg()
{
	CWnd *pkWnd;
	CString kString;
	STRING_TABLE::iterator Itr;

	for(int i = 1; i <= MAX_SYSTEM_TEXT; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_ACCOUNTDLG + i);
		kString = UNI(Itr->second.c_str());
		pkWnd = GetDlgItem(IDD_ADD_ACCOUNT_FRM + i);
		pkWnd->SetWindowText(kString);
	}
}

void CAccountDlg::OnAddBtnClicked()
{
	wchar_t wId[20];
	wchar_t wPw[20];
	wchar_t wGmName[20];

	GetDlgItemTextW(IDC_ID, wId, 20);
	GetDlgItemTextW(IDC_PW, wPw, 20);
	GetDlgItemTextW(IDC_NAME, wGmName, 20);

	if( (wcscmp(wId, L"") == 0) || (wcscmp(wPw, L"") == 0) )
	{
		ShowMessageBox(m_hWnd, 10002, 10001);
		return ;
	}else if( wcscmp(wGmName, L"") == 0)
	{
		ShowMessageBox(m_hWnd, 10003, 10001);
		return ;
	}

	CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_CREATE_GM_ACCOUNT);
	kPacket.Push(wId);
	kPacket.Push(wPw);
	kPacket.Push(wGmName);
	if(g_kNetwork.SendToLoginServer(kPacket))
		INFO_LOG(BM::LOG_LV6, _T("Create New Account Id is [%s]"), wId);
	else
	{
		ShowMessageBox(m_hWnd, 10010, 10001);
	}
}
void CAccountDlg::OnBnClickedCancel()
{
	OnClose();
}
