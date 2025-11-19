#pragma once
#include "mfcgrid.h"
#include "afxcmn.h"
#include "GMServer.h"

#include "MainSheet.h"
#include "afxwin.h"


// CGeneralDlg 대화 상자입니다.

class CGeneralDlg : public CDialog
{
	DECLARE_DYNAMIC(CGeneralDlg)

public:
	CGeneralDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGeneralDlg();
	CMainSheet* GetMainSheet() { return &m_kMainSheet; }

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERALDLG };

protected:
	BOOL OnInitDialog();

protected:
	CMainSheet m_kMainSheet;
#ifdef USE_OLD_GMSERVER
#ifdef USE_OLD_GMSERVER
	CGMServer *m_pkServer;
#endif
#endif

public:
	__inline CMainSheet* GetMainSheet() const;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//CColorButton m_btnTest;
};
#define g_kGeneralDlg Loki::SingletonHolder<CGeneralDlg>::Instance()

__inline CMainSheet* CGeneralDlg::GetMainSheet() const
{
	return (CMainSheet*)&m_kMainSheet;
}
