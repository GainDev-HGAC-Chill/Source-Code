// GeneralDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "GMToolDlg.h"
#include "GMServer.h"

#include "GeneralDlg.h"


// CGeneralDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGeneralDlg, CDialog)

CGeneralDlg::CGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralDlg::IDD, pParent),
	m_kMainSheet(IDS_MAINSHEET_TITLE)
{
#ifdef USE_OLD_GMSERVER
	// Start Server
	m_pkServer = new CGMServer;
	m_pkServer->Initialize();
	m_pkServer->SetDialog(this);
#endif
}

CGeneralDlg::~CGeneralDlg()
{
#ifdef USE_OLD_GMSERVER
	m_pkServer->Terminate();
	delete m_pkServer;
	m_pkServer = 0;
#endif
}

void CGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGeneralDlg, CDialog)
END_MESSAGE_MAP()


// CGeneralDlg 메시지 처리기입니다.
BOOL CGeneralDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(L"Main (Disconnected)");

	// Property Sheet
	//m_kMainSheet(IDS_MAINSHEET_TITLE);
	if(!m_kMainSheet.Create(this, WS_CHILD | WS_VISIBLE, 0))
	{
		return false;
	}

	// 다음 탭을 제대로 찾게.
	// 무한루프를 하지 않게.
	m_kMainSheet.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	m_kMainSheet.ModifyStyleEx(0, WS_TABSTOP);

	// MainSheet 사이즈.
	RECT rtRect;
	GetWindowRect(&rtRect);
	m_kMainSheet.SetSize(0, 150, rtRect.right, rtRect.bottom);

	CComboBox* pkCombo = ((CComboBox*)GetDlgItem(IDC_GENERAL_SELECT_SERVER));
	if (pkCombo)
	{
		pkCombo->Clear();
		pkCombo->InsertString(0, L"Not Connected");
		pkCombo->SetCurSel(0);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
