#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


class CNoticeDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoticeDlg)

protected:
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
private:
	std::vector<std ::wstring>	m_kNoticText;
	bool						m_bCheck;
	CEdit						m_kCountEdit;
	CEdit						m_kNoticDelyTimeEdit;
	CEdit						m_kNoticEdit;
	CEdit						m_kTextDelyEdit;
	CDateTimeCtrl				m_kStartTime;
	CStatic						m_kNowTimeLabel;
	CButton						m_kSetBtn;
	CComboBox					m_kCombo_Server;
	CComboBox					m_kCombo_Channel;

	bool MakeSendString();
	void StartSendNotic();
	void SetServerInfo();
	void SetDateTime();
	void SetChannelInfo(unsigned short usRealmNo);
public:
	CNoticeDlg(CWnd* pParent = NULL);
	virtual ~CNoticeDlg();

	void StartNoticeDlg();

	enum { IDD = IDD_NOTIC_FRM };
	afx_msg void OnClose();
	afx_msg void OnBnClickedSetBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedNoticClose();
	afx_msg void OnCbnSelchangeComboNoticeServernum();
	afx_msg void OnCbnSelchangeComboNoticeChannelnum();
};

