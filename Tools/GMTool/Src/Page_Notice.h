#pragma once
#include "afxwin.h"

// CPage_Notice 대화 상자입니다.

class CPage_Notice : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Notice)

public:
	CPage_Notice();
	virtual ~CPage_Notice();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAGE_NOTICE };

public:
	size_t m_timeRemain;
	DWORD m_dwTime;
	COLORREF m_clrNotice;

public:
	virtual BOOL OnInitDialog();
	void SendNotice();
	void SendNotice(std::wstring wstrContent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPageNoticeSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPageNoticeStop();
	afx_msg void OnBnClickedPageNoticeColor();
	afx_msg void OnPaint();
};
