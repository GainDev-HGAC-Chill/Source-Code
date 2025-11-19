#pragma once
#include "afxwin.h"


// CLoginDlg 대화 상자입니다.
class CAccountDlg;

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

protected:
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_kCbSelectServer;

	afx_msg void OnOkBtnClicked();
	afx_msg void OnNewAccountBtnClicked();
public:
	CAccountDlg		*m_pkAccountDlg;

	enum { IDD = IDD_LOGIN_FRM };

	void InitDlg();
	void SetServerList();

	CLoginDlg(CWnd* pParent = NULL);
	virtual ~CLoginDlg();
	afx_msg void OnNcDestroy();
	afx_msg void OnCancelBtnClicked();
	afx_msg void OnClose();
};

//#define g_kLoginDlg Loki::SingletonHolder <CLoginDlg>::Instance()
