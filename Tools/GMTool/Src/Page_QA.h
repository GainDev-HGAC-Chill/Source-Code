#pragma once

class CPage_QA : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_QA)

public:
	CPage_QA();   // 표준 생성자입니다.
	virtual ~CPage_QA();
	void AddMsg(std::wstring wstrContent, bool bReturn = true);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAGE_QA };

public:
	BM::GUID m_guidRefresh;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnQaRefresh();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_listUserList;	
	afx_msg void OnBnClickedBtnQaConnect();
};
