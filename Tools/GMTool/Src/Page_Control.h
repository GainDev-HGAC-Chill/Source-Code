#pragma once
#include "mfcgrid.h"
#include "afxwin.h"
#include "afxcmn.h"


// CPage_Control 대화 상자입니다.

class CPage_Control : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Control)

public:
	CPage_Control();
	virtual ~CPage_Control();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAGE_CONTROL };

protected:
	BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//CMFCGrid m_kGridCharList;
	//CMFCGrid m_kGridSelectList;
	CComboBox m_cbMapNo;
	afx_msg void OnBnClickedPageControlMapmoveMove();
	afx_msg void OnCbnSelchangePageControlMapmoveMapno();
	CListCtrl m_listChar1;
};
