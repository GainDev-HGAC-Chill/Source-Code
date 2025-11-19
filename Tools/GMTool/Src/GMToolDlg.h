// GMToolDlg.h : 헤더 파일
//

#pragma once

#include "GeneralDlg.h"

// CGMToolDlg 대화 상자
class CGMToolDlg : public CDialog
{
// 생성입니다.
public:
	CGMToolDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GMTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	CGeneralDlg *m_pkGeneralDlg;
	HICON m_hIcon;

public:
	void ExcuteGM();

protected:
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnCanceldCancel();	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
#define g_kGMTooldlg Loki::SingletonHolder<CGMToolDlg>::Instance()
