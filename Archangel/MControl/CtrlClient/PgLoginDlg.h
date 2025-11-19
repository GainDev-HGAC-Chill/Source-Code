#pragma once

#include "resource.h"

// PgLoginDlg 대화 상자입니다.

class PgLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(PgLoginDlg)

public:
	PgLoginDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~PgLoginDlg();


// 대화 상자 데이터입니다.
	enum { IDD = IDD_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strID;
	CString m_strPassword;
};
