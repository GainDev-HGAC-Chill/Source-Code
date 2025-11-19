#pragma once

#include <string>
#include <map>
#include "afxwin.h"
#include "afxcmn.h"
#include "PgGameServerMgr.h"

class CGeneralDlg : public CDialog
{
	DECLARE_DYNAMIC(CGeneralDlg)

public:
	CGeneralDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGeneralDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERALDLG };

protected:
	CImageList m_kImageList;
	enum SORT_BY {
		SERVER_NAME=1,
		SERVER_TYPE,
		MACHINIP,
		SERVER_NO,
		CHANNEL,
		CONNECT,
		PROCESS,
		IP,
		PORT
	};
	SORT_BY m_sortedBy;

public:
	bool ServerRefresh(const ContServerInfo& kServerList);
//	bool ServerRefresh();
	void SetTreeView();
	bool AddMsg(int nID, std::wstring wstrContent, bool bReturn);

protected:
	CTreeCtrl m_kTree;
	ContServerID m_kSelectServerList;
	HTREEITEM m_hSelectTreeItem;

	void GetCheckedList(ContServerID& rkOutServerID, std::wstring& rkOutText)const;
	void AddSelectServerList(const int Idx, const ContServerInfo& rkAllServerInfo, ContServerInfo& rkOutput);
	bool FindRealmMember(const int iRealmNo, ContServerInfo & rkOut) const;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	void LogWork(const ContServerID& rkServerVec, TCHAR* szWorkType);

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void    OnColumnclickServerList  (NMHDR* pNMHDR, LRESULT* pResult);
	static LPCTSTR      GetToken        (LPCTSTR psz, int n);
	static int CALLBACK CompareServerList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	CListCtrl m_listServer;
	afx_msg void OnBnClickedBtnRefresh();
	CMenu m_menu;
	afx_msg void OnNMCustomdrawListServer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnOff();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnProcesskill();
	afx_msg void OnBnClickedCheckUsebeep();
	afx_msg void OnBnClickedBtnLogClear();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedConfirmKill();
	CButton m_bKillConfirm;
	CButton m_KillButton;
	afx_msg void OnFileExit();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTvnSelchangedTreeview(NMHDR *pNMHDR, LRESULT *pResult);
};

//#define g_kGeneralDlg Loki::SingletonHolder<CGeneralDlg>::Instance()

extern CGeneralDlg* g_pkGeneralDlg;