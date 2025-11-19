#pragma once


class CChattingDlg : public CDialog
{
//	DECLARE_DYNAMIC(CChattingDlg)
protected:
	afx_msg void OnPaint();

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
private:
	CEdit			m_kChattingWindow;
	CEdit			m_kSendEdit;
	bool			m_bChatNow;
	SPetitionData	m_kData;

	afx_msg void OnBnClickedCompleteBtn();
	afx_msg void OnBnClickedSendBtn();
public:
	enum { IDD = IDD_CHATTING_FRM };

	void AddMsg(std::wstring &kMsg, bool bReturn = true);
	void ExecuteDlg(CWnd* pParent, SPetitionData &Data);

	afx_msg void OnClose();
	CChattingDlg(CWnd* pParent = NULL);
	virtual ~CChattingDlg();
	afx_msg void OnNcDestroy();
};
//#define g_kChattingDlg Loki::SingletonHolder <CChattingDlg>::Instance()
