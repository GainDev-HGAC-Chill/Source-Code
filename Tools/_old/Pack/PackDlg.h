// PackDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CPackDlg 대화 상자
class CPackDlg : public CDialog
{
// 생성입니다.
public:
	CPackDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PACK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtOutputDir;
	CEdit m_edtTargetDir;
	CEdit m_edtResultFileName;
	CEdit m_edtVersionNum;
	CEdit m_edtPackMerge_OrgFile;
	CEdit m_edtPackMerge_Dir;
	CEdit m_edtPackMerge_OutFile;
	CEdit m_edtMakeOnePack_OrgDir;
	CEdit m_edtMakeOnePack_NewDir;
	CEdit m_edtMakeOnePack_OutDir;
	CEdit m_edtMakeOnePack_Version;
	CEdit m_edtMakeOnePack_VerList;
	CComboBox m_cmbMakeOnePack_Option;
	CComboBox m_cmbPackMerge_Option;
	CEdit m_edtHeaderMerge_Dir;
	CEdit m_edtHeaderMerge_File;
	CEdit m_edtDatFileDir;
	CEdit m_edtDatNewVersion;


public:
	afx_msg void OnBnClickedBtnSetTargetDir();
	afx_msg void OnBnClickedBtnOnlyTargetPack();
	afx_msg void OnBnClickedBtnRecursivePack();
	afx_msg void OnEnChangeEdtDir();
	afx_msg void OnBnClickedBtnMakeVer();
	afx_msg void OnBnClickedBtnPackMerge_OrgFile();
	afx_msg void OnBnClickedBtnPackMerge_Dir();
	afx_msg void OnBnClickedBtnPackMerge_Merge();
	afx_msg void OnBnClickedBtnMakeOnePack_Make();
	afx_msg void OnBnClickedBtnMakeOnePack_Org();
	afx_msg void OnBnClickedBtnMakeOnePack_New();
	afx_msg void OnBnClickedBtnMakeOnePack_Out();
	afx_msg void OnBnClickedBtnMakeOnePack_VerList();
	afx_msg void OnBnClickedBtnSetOutputDir();
	CStatic m_stcPackState;
	afx_msg void OnCbnSelchangeComboMakeonepackOption();
	afx_msg void OnBnClickedBtnPackmergeSetOutfile();
	afx_msg void OnCbnSelchangeComboPackmergeOption();
	CButton m_checkPartPack;
	afx_msg void OnBnClickedBtnHeaderMerge_Make();
	afx_msg void OnEnChangeEdtHeaderMergeDir();
	afx_msg void OnBnClickedBtnHeaderMerge_Dir();
	afx_msg void OnBnClickedBtnHeaderMerge_File();
	afx_msg void OnBnClickedBtnOpenFile();
	afx_msg void OnBnClickedBtnUpdateFileVer();
};

extern void setLocalDirectory();