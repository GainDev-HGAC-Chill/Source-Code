#pragma once

class CLoginDlg;
class CChattingDlg;

extern UINT g_nRegMsg;

class CPetitionDlg : public CDialog
{
	typedef std::map<BM::GUID, CChattingDlg*> CONT_CHAT;
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPopupPossession();
	afx_msg void OnBnClickedChatBtn();
	afx_msg void OnPopupAssingMe();
	afx_msg void OnLvnItemchangingMyPetitonList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuExit();
	afx_msg LRESULT OnRegMsg(WPARAM wParam, LPARAM lParam);

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CONT_CHAT				m_kChatDlg;
//	CChattingDlg *			m_kChatDlg;
	bool					bReady;
	CListCtrl				m_ListAll;
	CListCtrl				m_ListMine;
	CComboBox				m_KindCombo;
	CButton					m_kChatBtn;
	CButton					m_kMessageBtn;
	CButton					m_kExitBtn;

	CStatic					m_kDateTime;
	CStatic					m_kAllNumber;
	CStatic					m_kCompleteNum;
	CStatic					m_kAssignNum;
	CStatic					m_kRemainderNum;

	CStatic					m_kNameLabel;
	CStatic					m_kTitle;
	CEdit					m_kNote;

	void InitDlg();
	void ReflashLabels();
	void ReflashListControl(CListCtrl* pListControl);
	bool InsertSel(CListCtrl* List, SPetitionData &Data);
	void CreateChatDlg(CONT_PETITION_DATA::value_type * const pkData);
public:
	int						m_MyListSelectItem;

	void StartPetitionDlg();
	bool IsReady(){return bReady;};	
	void ReflashAll();
	void ReflashDetailInfo();
	void ClearGmChatDlg();
	void SendChatMessage(BM::GUID const &kPetitionGuid, std::wstring &kMsg);
	void DestroyChatDlg(BM::GUID const &kPetitionGuid);
// 대화 상자 데이터입니다.
	enum { IDD = IDD_PETITION_FRM };
	afx_msg void OnBnClickedExitBtn();

	CPetitionDlg(CWnd* pParent = NULL);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnClose();
};
