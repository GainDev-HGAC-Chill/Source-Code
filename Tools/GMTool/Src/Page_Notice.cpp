// Page_Notice.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "GMServer.h"
#include "PgNetwork.h"
#include "Page_Notice.h"

//#define GM_USE_NOTICE_COLOR
#define STATIC_REMAIN_TIME	L"Remain time: "

// CPage_Notice 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_Notice, CPropertyPage)

CPage_Notice::CPage_Notice()
	: CPropertyPage(CPage_Notice::IDD)
{
	m_timeRemain = 0;
}

CPage_Notice::~CPage_Notice()
{
}

void CPage_Notice::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_Notice, CPropertyPage)
	ON_BN_CLICKED(IDC_PAGE_NOTICE_SEND, &CPage_Notice::OnBnClickedPageNoticeSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PAGE_NOTICE_STOP, &CPage_Notice::OnBnClickedPageNoticeStop)
	ON_BN_CLICKED(IDC_PAGE_NOTICE_COLOR, &CPage_Notice::OnBnClickedPageNoticeColor)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPage_Notice 메시지 처리기입니다.
BOOL CPage_Notice::OnInitDialog() 
{
	SetWindowTextW(L"Notice");
	SetDlgItemText(IDC_PAGE_NOTICE_TIMERNUM, L"0");

	std::wstring wstrStatic = STATIC_REMAIN_TIME;
	wstrStatic += L"0";
	SetDlgItemText(IDC_PAGE_NOTICE_REMAINTIME, wstrStatic.c_str());

	// 버튼 초기화.
	m_clrNotice = RGB(0,0,0);
	SetTimer(2, 1, 0);


	return true;
}

void CPage_Notice::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		DWORD dwTime = ::GetTickCount() - m_dwTime;

		// 지정된 시간 까지...
		if (dwTime < m_timeRemain)
		{
			wchar_t wTime[32];
			int iTime = (int)((float)(m_timeRemain-dwTime) / 1000.0f) + 1;
			_itow(iTime, wTime, 10);

			std::wstring wstrStatic = STATIC_REMAIN_TIME;
			wstrStatic += wTime;
			SetDlgItemText(IDC_PAGE_NOTICE_REMAINTIME, wstrStatic.c_str());
		}
		else
		{
			// 시간이 다 되었으면 전송.
			m_timeRemain = 0;
			m_dwTime = 0;

			std::wstring wstrStatic = STATIC_REMAIN_TIME;
			wstrStatic += L"0";
			SetDlgItemText(IDC_PAGE_NOTICE_REMAINTIME, wstrStatic.c_str());

			SendNotice();

			KillTimer(0);
		}
	}
	// 버튼 초기화
	else if (nIDEvent == 2)
	{
		int iR = GetRValue(m_clrNotice);
		int iG = GetGValue(m_clrNotice);
		int iB = GetBValue(m_clrNotice);

		CButton* pkBtn = ((CButton*)GetDlgItem(IDC_PAGE_NOTICE_COLOR));
		if (pkBtn)
		{
			CDC* pDC = pkBtn->GetDC();
			CRect rect;
			pkBtn->GetClientRect(&rect);
			pDC->FillSolidRect(&rect, RGB(iR,iG,iB));
		}
		KillTimer(2);
	}
}

void CPage_Notice::OnBnClickedPageNoticeSend()
{
	wchar_t wTime[32];
	GetDlgItemText(IDC_PAGE_NOTICE_TIMERNUM, wTime, 32);
	long lTime = _wtol(wTime);

	CButton* pkBtn = ((CButton*)GetDlgItem(IDC_PAGE_NOTICE_TIMERSEND));
	if (pkBtn->GetCheck() == BST_CHECKED)
	{
		m_dwTime = ::GetTickCount();
		m_timeRemain = lTime * 1000;
		SetTimer(0, 1, 0);
	}
	else
	{
		SendNotice();
	}
}

void CPage_Notice::OnBnClickedPageNoticeStop()
{
	KillTimer(0);
}

void CPage_Notice::OnBnClickedPageNoticeColor()
{
	CColorDialog kColorDlg;

	if (kColorDlg.DoModal() == IDOK)
	{
		m_clrNotice = kColorDlg.GetColor();
		int iR = GetRValue(m_clrNotice);
		int iG = GetGValue(m_clrNotice);
		int iB = GetBValue(m_clrNotice);
		
		CButton* pkBtn = ((CButton*)GetDlgItem(IDC_PAGE_NOTICE_COLOR));

		CDC* pDC = pkBtn->GetDC();
		CRect rect;
		pkBtn->GetClientRect(&rect);
		pDC->FillSolidRect(&rect, RGB(iR,iG,iB));
	}
}

void CPage_Notice::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.
	SetTimer(2, 1, 0);
}

void CPage_Notice::SendNotice()
{
	std::wstring wstrContent;
	wstrContent.resize(1024);
	GetDlgItemText(IDC_PAGE_NOTICE_CONTENTS, &wstrContent.at(0), 1024);
	wstrContent.resize(wstrContent.find(L'\0'));
	SendNotice(wstrContent);
}

void CPage_Notice::SendNotice(std::wstring wstrContent)
{
	CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_NOTICE);
	kPacket.Push(g_kNetwork.m_usChannel);
	kPacket.Push(wstrContent);
	g_kNetwork.SendToChannel(kPacket);
}
