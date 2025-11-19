#pragma once


// CPage_Chat 대화 상자입니다.

class CPage_Chat : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Chat)

public:
	CPage_Chat();
	virtual ~CPage_Chat();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAGE_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPageChatChatSend();
};
