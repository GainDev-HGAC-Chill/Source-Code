#pragma once


// CPage_Extra 대화 상자입니다.

class CPage_Extra : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Extra)

public:
	CPage_Extra();
	virtual ~CPage_Extra();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAGE_EXTRA };

public:
	CComboBox* m_pkComboClassChange;

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPageExtraBtnClasschage();
};
