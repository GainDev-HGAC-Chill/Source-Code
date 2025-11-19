// PgLoginDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PgLoginDlg.h"


// PgLoginDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(PgLoginDlg, CDialog)

PgLoginDlg::PgLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PgLoginDlg::IDD, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
{

}

PgLoginDlg::~PgLoginDlg()
{
}

void PgLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDID, m_strID);
	DDX_Text(pDX, IDC_EDPASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(PgLoginDlg, CDialog)
END_MESSAGE_MAP()


// PgLoginDlg 메시지 처리기입니다.

void PgLoginDlg::OnOK()
{
	UpdateData(TRUE);

	if (m_strID.GetLength() == 0 || m_strPassword.GetLength() == 0)
	{
		return;
	}

	CDialog::OnOK();
}