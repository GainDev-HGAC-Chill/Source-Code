#pragma once

class CAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccountDlg)
protected:
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
private:
	void InitDlg();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
	afx_msg void OnAddBtnClicked();
public:
	enum { IDD = IDD_ADD_ACCOUNT_FRM };

	CAccountDlg(CWnd* pParent = NULL);
	virtual ~CAccountDlg();
};
