#pragma	once

//──────────────────────────────────────────────────
//	메인 스레드
//──────────────────────────────────────────────────
extern	unsigned __stdcall DiffToPack(void* pArgument);

//──────────────────────────────────────────────────
//	시스템 로그
//──────────────────────────────────────────────────
void InitLogSystem();

//──────────────────────────────────────────────────
//	↓Diff 관련 함수
//──────────────────────────────────────────────────
bool	DiffCore(const std::wstring& DestFolder, const std::wstring& SourFolder,
				 const std::wstring& OutputFolder);
//	↓폴더 대 폴더 비교
bool	FolderToFolderDiff(const std::wstring& DestFolder, const std::wstring& SourFolder, 
						   const std::wstring& OutFolder, const std::wstring& SubFolder = L"\\");
void	DiffFile(const std::wstring& DestFolder, const std::wstring& OutFolder,
				 const BM::FileHash& DestHash, const BM::FileHash& SourHash);
bool	CopyNewFolder(const std::wstring& TargetFolder, const std::wstring& OutFolder, 
					  const std::wstring& SubFolder);
//	↓팩 대 폴더 비교
bool	PackToFolderDiff(const std::wstring& DestFolder, const std::wstring& SourFolder, 
						 const std::wstring& OutFolder, const std::wstring& SubFolder = L"\\");
bool	DiffList(const std::wstring& DestFolder, const std::wstring& SourFolder,
				 const std::wstring& OutputFolder);
//──────────────────────────────────────────────────
//	↓Pack 관련 함수
//──────────────────────────────────────────────────
bool	PackCore(const std::wstring& TargetFolder, const std::wstring& OutputFolder);
bool	PackProcess(const std::wstring& TargetFolder, const std::wstring& OutputFolder, 
					const std::wstring& SubFolder = L".\\", const bool bIsPack = false);
bool	PackFile(const std::wstring& DestFolder, const std::wstring& OutFolder, BM::FileHash& FileHash);

//──────────────────────────────────────────────────
//	↓List 관련 함수
//──────────────────────────────────────────────────
bool	ListCore(const std::wstring& OriFolder, const std::wstring& CrtFolder, const std::wstring& OutputFolder);
bool	CreateList(const std::wstring& TargetFolder, const std::wstring& SubFolder = L".\\",
				   const bool bIsPack = false);
bool	ListMerge(const std::wstring& TargetFolder, const std::wstring& FileName);
bool	GetList(const std::wstring& wstrFolderName, BM::FolderHash& rkFolderHash);
//	↓부분팩 리스트 병합
bool	PartListMerge(const std::wstring& FullFolder, const std::wstring& PartFolder);

//──────────────────────────────────────────────────
//	↓Bind 관련 함수
//──────────────────────────────────────────────────
bool	BindCore(const std::wstring& OriFolder, const std::wstring& OutputFolder);

//──────────────────────────────────────────────────
//	↓Series 관련 함수
//──────────────────────────────────────────────────
bool	SeriesPatch(const std::wstring& OriFolder, const std::wstring& LimitAFinal, const std::wstring& OutputFolder);
bool	LimitRange(const std::wstring& LimitAFinal, int& Limit, int& Final);
bool	MergePatchFile(const std::wstring& TargetDestName, const std::wstring& TargetSourName, const std::wstring& OutPutName, 
					   const std::wstring& TargetDir, const std::wstring& OutPutDir);
bool	MergeList(const BM::FolderHash& PatchList, const BM::FolderHash& OrgList, BM::FolderHash& kResultList);
void	CreateFileName(const int Limit, const int Final, std::wstring& Sour, std::wstring& Output);

//──────────────────────────────────────────────────
//	↓기타 함수
//──────────────────────────────────────────────────
void	CreateGUID(const std::wstring& OutFolder);
bool	CreatePatchID(const std::wstring& Final = L"", const std::wstring& Limit = L"", const std::wstring& OutFolder = L"");
bool	UpdateFileState(const std::wstring& TargetFolder, BM::FileHash& TargetHash);
void	CopyFiles(const std::wstring& DestFolder, const std::wstring& OutFolder,
				  const BM::FileHash& DestHash);
void	OutputFile(const std::wstring& TargetFolder, const std::wstring& OutFolder, 
				   const std::wstring& FileName);
bool	FolderSeek(const std::wstring FolderName, const std::wstring SubFolder, 
				   BM::FolderHash& FileList, BM::FolderHash& FolderList);
bool	CreateHashFile(const std::wstring& OutFolderFile, BM::FolderHash& ListHash);
void	ReadList(const std::wstring& FolderName, BM::FolderHash& Hash, const std::wstring& FileName);
std::wstring	CutDir(const BM::FolderHash& TargetHash);
