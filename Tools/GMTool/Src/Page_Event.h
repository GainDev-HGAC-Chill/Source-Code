#pragma once


// CPage_Event 대화 상자입니다.

class CPage_Event : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Event)

public:
	CPage_Event();
	virtual ~CPage_Event();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAGE_EVENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
