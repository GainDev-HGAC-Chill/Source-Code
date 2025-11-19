// Page_Extra.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "GMServer.h"
#include "Page_Extra.h"


// CPage_Extra 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_Extra, CPropertyPage)

CPage_Extra::CPage_Extra()
	: CPropertyPage(CPage_Extra::IDD)
{
	m_pkComboClassChange = 0;
}

CPage_Extra::~CPage_Extra()
{
}

void CPage_Extra::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_Extra, CPropertyPage)
	ON_BN_CLICKED(IDC_PAGE_EXTRA_BTN_CLASSCHAGE, &CPage_Extra::OnBnClickedPageExtraBtnClasschage)
END_MESSAGE_MAP()


// CPage_Extra 메시지 처리기입니다.
BOOL CPage_Extra::OnInitDialog() 
{
	m_pkComboClassChange = ((CComboBox*)GetDlgItem(IDC_PAGE_EXTRA_COMBO_CLASSCHAGE));
	if (m_pkComboClassChange)
	{
		m_pkComboClassChange->InsertString(0,L"Gladiator");
		m_pkComboClassChange->InsertString(1,L"Mage");
		m_pkComboClassChange->InsertString(2,L"Trapper");
		m_pkComboClassChange->InsertString(3,L"Thief");
		m_pkComboClassChange->SetCurSel(0);
	}
	SetDlgItemText(IDC_PAGE_EXTRA_EDT_CLASSCHAGE_LEVEL, L"1"); 

	return true;
}

void CPage_Extra::OnBnClickedPageExtraBtnClasschage()
{
	if (m_pkComboClassChange)
	{
		int iCur = m_pkComboClassChange->GetCurSel();
		wchar_t wLevel[256];
		GetDlgItemText(IDC_PAGE_EXTRA_EDT_CLASSCHAGE_LEVEL, wLevel, 256);
		DWORD dwLevel = _wtol(wLevel);
#ifdef USE_OLD_GMSERVER
		g_pkGMServer->Send_ChangeClass((SCPacket_ChangeClass::ESCPacket_ChangeClass)(iCur+1), dwLevel);
#endif
	}
}
