#pragma once

class CPackProcess
{
//-----------------------------------------------------------------------------
//  변수
//-----------------------------------------------------------------------------
public:
	typedef	enum	eWorkSet	
	{
		eWork_Diff			= 0x00000001,
		eWork_Pack			= 0x00000002,
		eWork_CreateHeader	= 0x00000004,
		eWork_HeaderMerge	= 0x00000008,
		eWork_BindPack		= 0x00000010,
		eWork_SeriesPatch	= 0x00000020,
		eWork_AllProcess	= eWork_Diff | eWork_Pack | eWork_CreateHeader,
	}EWorkSet;
	
	typedef	enum	eProcess_State
	{
		eProcess_Prepare,
		eProcess_Diff,
		eProcess_Pack,
		eProcess_CreateHeader,
		eProcess_HeadMerge,
		eProcess_BindPack,
		eProcess_Complete,
	}EProcess_State;

private:
	//	프로세스 설정
	eWorkSet		m_eWork;
	eProcess_State	m_eProcess;
	
	//	옵션
	bool			m_bIsAuto;
	bool			m_bIsFullPack;
	bool			m_bIsPackToDir;
	bool			m_bIsHeaderList;
	int				m_nPatchCount;

	//	폴더명
	std::wstring	m_wstrOrgDir;
	std::wstring	m_wstrCrtDir;
	std::wstring	m_wstrOutDir;

	//	리스트
	BM::FolderHash	m_OrgList;
	BM::FolderHash	m_CrtList;
	BM::FolderHash	m_OutList;

	HANDLE			m_PackThread;
//-----------------------------------------------------------------------------
//   
//-----------------------------------------------------------------------------
public:
	EWorkSet		GetWork() const				{ return m_eWork; }
	EProcess_State	GetProcess() const			{ return m_eProcess; }
	bool			GetIsFullPack() const		{ return m_bIsFullPack; }
	bool			GetIsPackToDir() const		{ return m_bIsPackToDir; }
	bool			GetIsAuto() const			{ return m_bIsAuto; }
	const std::wstring&	GetOrgFolder() const	{ return m_wstrOrgDir; }
	const std::wstring&	GetCrtFolder() const	{ return m_wstrCrtDir; }
	const std::wstring&	GetOutFolder() const	{ return m_wstrOutDir; }
	void	SetProcState(EProcess_State State)	{ m_eProcess = State; }
	void	SetIsFullPack(bool IsVal) 		{ m_bIsFullPack = IsVal; }
	void	SetIsPackToFolder(bool IsVal) 	{ m_bIsPackToDir = IsVal; }
	void	ThreadClear()	
	{ 
		_endthreadex(0);	
		m_PackThread = INVALID_HANDLE_VALUE; 
	}
private:
	//	버튼체크
	inline void	SetCheckBox(const HWND& hDlg, const DWORD ItemID, bool& Button) const
	{
		if(Button == false)
		{
			Button = true;
			SendMessage(GetDlgItem(hDlg, ItemID), BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			Button = false;
			SendMessage(GetDlgItem(hDlg, ItemID), BM_SETCHECK, BST_UNCHECKED, 0);
		}				
	}

	//	디렉토리 입력
	inline void FolderInput(const HWND& hWnd, const DWORD ItemID)
	{
		TCHAR	szFolderName[MAX_PATH];

		if(FolderSelect(hWnd, szFolderName))
		{
			SetWindowText(GetDlgItem(hWnd, ItemID), szFolderName);
		}
	}

	//	파일 입력
	inline void FileInput(const HWND& hWnd, const DWORD ItemID, bool const IsMulti = false)
	{
		TCHAR	szFileName[MAX_PATH];

		if(FileSelect(hWnd, szFileName, IsMulti))
		{
			SetWindowText(GetDlgItem(hWnd, ItemID), szFileName);
		}
	}
//-----------------------------------------------------------------------------
//    
//-----------------------------------------------------------------------------
public:
	CPackProcess(void);
	virtual ~CPackProcess(void);

	void	Init(const std::wstring& CmdLine);
	bool	CommandAction(WPARAM wParam, LPARAM lParam);
	void	SetStateText(const std::wstring& wstrState);
	bool	StartProcess();
	bool	SetPackVersion(std::wstring const& wstrFileName);

private:
	bool	FolderSelect(const HWND& hWnd, TCHAR* wstrFolderName, const int& Length = MAX_PATH);
	bool	FileSelect(const HWND& hWnd, TCHAR* szFolderName, bool const IsMulti = false, const int& Length = MAX_PATH);
	void	PackInit();
	void	DialogState();
	bool	CmdParse(const std::wstring& CmdLine);
	bool	_ParseFolder(const std::wstring&	CmdLine);
	bool	UpdateDATVersion(std::wstring const& FolderDir, BM::VersionInfo const& Version);

public:
	void	LogFileCreate(std::wstring& FileName);
};
