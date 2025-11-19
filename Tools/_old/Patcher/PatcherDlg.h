// PatcherDlg.h : 헤더 파일
//

#pragma once
#include <string>
#include "afxwin.h"
#include "CDialogSK.h"
#include "BtnST.h"
#include "Browser.h"

// CPatcherDlg 대화 상자
class CPatcherDlg : public CDialogSK
{
// 생성입니다.
public:
	CPatcherDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PATCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
public:
	typedef enum eActionState
	{
		eActionState_Prepare,		// 준비중,
		eActionState_Downloading,	// 다운로드
		eActionState_Patching,		// 패치중
		eActionState_Complete,		// 완료
	}EActionState;

protected:
	EActionState m_eActionState;

	HICON m_hIcon;
	
	CClientDC *m_pdc;
	CBitmap *m_pOB;
	CDC *m_MemDC, *m_BufferDC;
	CBitmap m_bmpBuffer;
	bool m_bIsRecovery;
	bool m_bIsProcessing;
	CFont m_kFont;

	HWND m_hOptionDlg;

	// remain time
	float m_fPassTime;	// 지나간 시간.
	clock_t m_StartTime;
	clock_t m_PassTime;

	// UI manage
	// current
	size_t m_CurrentFileTotalSize;
	size_t m_ReceiveCurrentFileSize;
	std::wstring m_wstrCurrentFileName;
	float m_fCurrentPercent;
	bool m_bChangeCurrentPercent;
	// total
	size_t m_TotalFileSize;			// 받아야 할 전체 총 용량
	size_t m_ReceiveTotalFileSize;  // 한 파일이 다 받아지면 새로 갱신한다. (한마디로 최후까지 받은 파일이 총합)
	float m_fTotalPercent;

	// Btn
	CButtonST m_btnCancelAction;	
	CButtonST m_btnPatch;
	CButtonST m_btnOption;
	CButtonST m_btnRecovery;
	CString m_strPatch;
	CString m_strExecute;
	CString m_strCancel;
	CString m_strExit;
	CString m_strOption;
	CString m_strRecovery;
	std::wstring m_wstrTargetDir;

	CBrowser m_WB;

public:
	void SetActionState(EActionState eState);
	void PatchComplete();
	void SetCurrentDownloadFile(const std::wstring wstrFilename, size_t file_size);
	size_t GetReceiveCurrentFileSize();
	void SetReceiveCurrentFileSize(size_t receive_file_size);
	std::wstring GetCurrentFileName() { return m_wstrCurrentFileName; }

	void SetTotalFileSize(size_t total_size);

	void SetProgressBar(int iidx, float fPercent);
	void DrawProgressBar(int iIdx, float fPercent);
	void DrawProgressBar(int iIdx, float fPercent, CDC *pkBufferDC, CDC *pkMemDC);
	void SetHeadStateText(const char *szText, bool bDoInvalidate = true);
	void SetHeadStateText(char *szText, bool bDoInvalidate = true);
	void SetStateText(char *szText);
	void SetRemainTimeText(char *szText);

	void InitClock();
	void UiUpdate();
	void SetIsProcess(bool bIsProcess) { m_bIsProcessing = bIsProcess; }
	bool GetIsProcess() { return m_bIsProcessing; }
	bool GetIsRecovery() { return m_bIsRecovery; }

	void SetUIText(char *pkPatch, char *pkCancel, char *pkExit, char *pkExcute, char *pkRecovery, char *pkOption);

protected:
	// 그리기
	void SetProgressText1(char *szText1);
	void SetProgressText2(char *szText2);
	
	void CalcCapacityText(char *pkOutText, size_t FileSize);
	void ReadIni_UiText();

	
	// 생성된 메시지 맵 함수
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPatchProcess();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_strProgressText1;
	CString m_strProgressText2;
	CString m_strStateText;
	CString m_strHeadState;
	afx_msg void OnBnClickedBtnAction();
	CString m_strRemainTime;
	afx_msg void OnBnClickedBtnOption();
	afx_msg void OnBnClickedBtnRecovery();

private:
	void ImgButtonSetup(CButtonST& Btn, CString text, int x, int y, int width, int height);
	RECT ControlText(DWORD DlgItemID);
public:
};
