#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <direct.h>

#include "mmsystem.h"
#pragma comment (lib, "winmm.lib")

#include "PackWork.h"
#include <process.h>
#include "resource.h"
#include "PackDlg.h"

CPackDlg* g_pDlg = NULL;
HANDLE g_hThread = INVALID_HANDLE_VALUE;
extern bool g_bIsAutoRecovery;
extern bool g_bIsAutoOnePack;
bool g_bIsComplete = false;

extern bool MakeForFTP(const std::wstring &wstrTargetDir, const std::wstring &wstrOutputForFTP);
extern bool MakeForUser(std::wstring &wstrTargetDir, std::wstring &wstrOutputForFTP);
extern bool MakeData(const std::wstring &wstrOutputForFTP, const std::wstring &wstrTargetRoot, const std::wstring &wstrTargetDir, bool bIsPackFolder);


void InitPack()
{
	//ReadConfig를 해야함.
	BM::CPackInfo kPackInfo;
	if(!kPackInfo.Init())
	{
		assert(NULL);
	}

	BM::PgDataPackManager::Init(kPackInfo);
}

void RecursivePackWork(LPCWSTR pTargetDir)
{
	//SRAND();
	BM::PgDataPackManager::PackFolders(pTargetDir);
}

void OneFilePackWork(LPCWSTR pTargetDir, LPCWSTR pResultFileName, LPCWSTR pPatchVer)
{
	//SRAND();
	BM::PgDataPackManager::PackTargetFolder(pTargetDir, pResultFileName);
	std::wstring strPathName(pTargetDir);
	strPathName = strPathName + _T(".DAT");

	setLocalDirectory();

	SetPatchVer(strPathName, pPatchVer);

	if (g_bIsAutoOnePack)
	{
		if (g_pDlg && g_pDlg->m_hWnd)
		{
			::PostMessage(g_pDlg->m_hWnd, WM_CLOSE, 0, 0);
		}
	}
}

bool GetHeaderData(const std::wstring &wstrLocation, BM::FolderHash &rkFiles, BM::FolderHash &rkFolders, BM::FolderHash &rkZipFiles)
{
	const std::wstring wstrFiles = _T("_FILES.PGH");
	const std::wstring wstrFolders = _T("_FOLDERS.PGH");
	const std::wstring wstrZipFiles = _T("_ZIPFILES.PGH");

	// Get Header
	BM::PgDataPackManager::PackFileCache_new kCachefiles;
	if(kCachefiles.Open(wstrLocation + wstrFiles))
	{
		BM::PgDataPackManager::ReadHeader(kCachefiles);
		rkFiles = kCachefiles.mFolderHash;
	}
	BM::PgDataPackManager::PackFileCache_new kCachefolders;
	if(kCachefolders.Open(wstrLocation + wstrFolders))
	{
		BM::PgDataPackManager::ReadHeader(kCachefolders);
		rkFolders = kCachefolders.mFolderHash;
	}
	BM::PgDataPackManager::PackFileCache_new kCachezipfiles;
	if(kCachezipfiles.Open(wstrLocation + wstrZipFiles))
	{
		BM::PgDataPackManager::ReadHeader(kCachezipfiles);
		rkZipFiles = kCachezipfiles.mFolderHash;
	}

	//BM::PgDataPackManager::ReadHeader(wstrLocation + wstrFiles, rkFiles);
	//BM::PgDataPackManager::ClearBuffer(wstrLocation + wstrFiles);
	//BM::PgDataPackManager::ReadHeader(wstrLocation + wstrFolders, rkFolders);
	//BM::PgDataPackManager::ClearBuffer(wstrLocation + wstrFolders);
	//BM::PgDataPackManager::ReadHeader(wstrLocation + wstrZipFiles, rkZipFiles);
	//BM::PgDataPackManager::ClearBuffer(wstrLocation + wstrZipFiles);

	return true;
}

bool GetList(const std::wstring &rkLocation, BM::FolderHash &rkFolderHash)
{
	BM::FolderHash kFiles;
	BM::FolderHash kFolders;
	BM::FolderHash kZipFiles;
	GetHeaderData(rkLocation, kFiles, kFolders, kZipFiles);

	// Insert File
	BM::FolderHash::iterator itr;
	itr = kZipFiles.begin();
	while(itr != kZipFiles.end())
	{
		rkFolderHash.insert(std::make_pair(rkLocation, itr->second));
		++itr;
	}

	// Recursive Folder
	itr = kFolders.begin();
	while(itr != kFolders.end())
	{
		std::wstring kSubDir = rkLocation;
		BM::AddFolderMark(kSubDir);
		kSubDir += BM::GetLastFolderName(itr->first);
		BM::AddFolderMark(kSubDir);

		BM::FolderHash kSubFolders;
		GetList(kSubDir, kSubFolders);

		if (itr->second.bIsUsePack)
		{
			BM::FolderHash::iterator itr_find = kSubFolders.find(kSubDir);
			if (itr_find != kSubFolders.end())
			{
				itr_find->second.bIsUsePack = true;
			}
		}

		rkFolderHash.insert(kSubFolders.begin(), kSubFolders.end());
		rkFolderHash.insert(std::make_pair(kSubDir, itr->second));
		++itr;
	}

	return true;
}

bool HeaderMerge(LPCWSTR pTargetDir, LPCWSTR pResultFileName)
{
	// _FOLDERS.PGH _FILES.PGH _ZIPFILES.PGH
	std::wstring wstrDir(pTargetDir);
	std::wstring wstrFile(pResultFileName);

	BM::AddFolderMark(wstrDir);
	::SetCurrentDirectory(wstrDir.c_str());

	BM::FolderHash kListHash;
	GetList(_T(".\\"), kListHash);

	BM::PgDataPackManager::RecursiveProcessPackState(kListHash);

	//PgFileMapping kFileMapping;
	std::fstream ffile;
	if(!BM::PgDataPackManager::MakeHeader(pResultFileName, kListHash, ffile))
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Error Parent Head Folder Make Failed"));
		return false;
	}

	if (g_pDlg)
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Complete"));
	}

	return true;
}

void PrepareTargetDir(LPCWSTR pOutputDir, std::wstring &wstrOutputForUser, std::wstring &wstrOutputForFTP)
{
	std::wstring wstrOutputDir(pOutputDir);
	BM::AddFolderMark(wstrOutputDir);

	wstrOutputForUser = wstrOutputDir + _T("USER");
	wstrOutputForFTP = wstrOutputDir + _T("FTP");

	BM::AddFolderMark(wstrOutputForUser);
	BM::AddFolderMark(wstrOutputForFTP);
	
	//나갈 폴더 생성
	BM::ReserveFolder(wstrOutputForUser);
	BM::ReserveFolder(wstrOutputForFTP);
}

unsigned __stdcall MakeVersion( void* pArguments )//ftp 올릴 데이터 만들기
{//Output에 쉴드용. ftp용 두개다 만들어 주자.
	CString kTargetDir;
	g_pDlg->m_edtTargetDir.GetWindowText(kTargetDir);
	LPCWSTR pTargetDir = kTargetDir;

	CString kOutputDir;
	g_pDlg->m_edtOutputDir.GetWindowText(kOutputDir);
	LPCWSTR pOutputDir = kOutputDir;

	bool bIsPartPack = g_pDlg->m_checkPartPack.GetCheck() == BST_CHECKED;

	std::wstring wstrTargetDir(pTargetDir);
	BM::AddFolderMark(wstrTargetDir);

	std::wstring wstrOutputForUser;
	std::wstring wstrOutputForFTP;

	PrepareTargetDir(pOutputDir, wstrOutputForUser, wstrOutputForFTP);

	BM::GUID guid;
	std::vector<char> vecGuid;

	//ReadConfig를 해야함.
	BM::CPackInfo kPackInfo;
	if(!kPackInfo.Init())
	{//옵션을 못읽었다.
		assert(NULL);
		goto __FAILED;
	}

	if(!BM::PgDataPackManager::Init(kPackInfo))
	{//옵션은 읽없는데 값이 이상타.
		assert(NULL);
		goto __FAILED;
	}

//1. GUID 생성 (이 GUID가 패치 고유번호)
//GUID 제작.
//GUID 데이터 세이브.
	guid.Generate();
	vecGuid.resize(sizeof(BM::GUID));
	memcpy(&vecGuid.at(0), &guid, sizeof(BM::GUID));
	//패치 ID 만들어 내리기
	BM::EncSave( wstrOutputForFTP + _T("\\Patch.ID"), vecGuid);
	BM::EncSave( wstrOutputForUser + _T("\\Patch.ID"), vecGuid);

	//Test Code
	BM::PgFIleInfo kInfo1;
	BM::PgFIleInfo kInfo2;
	kInfo1.org_file_size = 1;
	kInfo2.org_file_size = 2;
	if (kInfo1.org_file_size != kInfo2.org_file_size)
	{
		int asdf = 0;
	}
	int asdf = 0;

#ifdef PG_USE_SUPPORT_PART
	if(!g_kPackProcess.MakeForFTP(wstrTargetDir, wstrOutputForFTP))
#else
	//if(!MakeForFTP(wstrTargetDir, wstrOutputForFTP))
	if(!MakeData(wstrOutputForFTP, wstrTargetDir, _T(".\\"), false))
#endif
	{
		goto __FAILED;
	}
	// FTP Merge Header용.
	{
		std::wstring wstrDir = wstrOutputForFTP;
		BM::AddFolderMark(wstrDir);
		std::wstring wstrFileName = wstrDir + _T("HEADFOLDERS.DAT");

		std::wstring wstrOutputText = _T("Merge Header : ");
		wstrOutputText += wstrFileName;
		g_pDlg->m_stcPackState.SetWindowText(wstrOutputText.c_str());
		
		HeaderMerge(wstrOutputForFTP.c_str(), wstrFileName.c_str());
	}

	if(!MakeForUser(wstrTargetDir, wstrOutputForUser))
	{
		goto __FAILED;
	}

	g_pDlg->m_stcPackState.SetWindowText(_T("Complete"));

	{	
		// AutoPack 일때는 자동종료.
		if (g_bIsAutoRecovery)
		{
			::PostMessage(g_pDlg->m_hWnd, WM_CLOSE, 0, 0);
		}

		_endthreadex( 0 );
		g_hThread = INVALID_HANDLE_VALUE;
		g_bIsComplete = true;

		return true;
	}
__FAILED:
	{	
		_endthreadex( 0 );
		g_hThread = INVALID_HANDLE_VALUE;
		return true;
	}
}

void DoMakeVersion(void *pDlg)
{
	if (g_hThread == INVALID_HANDLE_VALUE)
	{
		unsigned threadID;
		g_pDlg = (CPackDlg*)pDlg;

		g_hThread = (HANDLE)_beginthreadex( NULL, 0, &MakeVersion, pDlg, 0, &threadID );
	}
//HANDLE g_hThread = INVALID_HANDLE_VALUE;
}

bool ImproveData(BM::FolderHash &kInHash, const std::wstring &strOutputDir);
void DeletePath(CString strPath)
{
    CFileFind finder;
    BOOL bContinue = TRUE;

    if(strPath.Right(1) != _T("\\"))
        strPath += _T("\\");

    strPath += _T("*.*");
    bContinue = finder.FindFile(strPath);
    while(bContinue)
    {
        bContinue = finder.FindNextFile();

        if(finder.IsDots()) // Ignore this item.
        {
            continue;
        }
        else if(finder.IsDirectory()) // Delete all sub item.
        {
            DeletePath(finder.GetFilePath());
            ::RemoveDirectory((LPCTSTR)finder.GetFilePath());
        }
        else // Delete file.
        {
            ::DeleteFile((LPCTSTR)finder.GetFilePath());
        }
    }

    finder.Close();

    strPath = strPath.Left(strPath.ReverseFind('\\')); // "c:\\a\\" -> "c:\\a"
    ::RemoveDirectory((LPCTSTR)strPath);
}

unsigned __stdcall MergeFile( void* pArguments )
{
	bool bIsPackAndDir = true;
	if (g_pDlg->m_cmbPackMerge_Option.GetCurSel() == 1)
		bIsPackAndDir = false;

	CString strOrgFile;
	g_pDlg->m_edtPackMerge_OrgFile.GetWindowText(strOrgFile);
	CString strMergePath;
	g_pDlg->m_edtPackMerge_Dir.GetWindowText(strMergePath);
	CString strOutFile;
	g_pDlg->m_edtPackMerge_OutFile.GetWindowText(strOutFile);
	

	std::wstring wstrOrgFileName(strOrgFile);
	std::wstring wstrDestPath(strMergePath);
	if (bIsPackAndDir)
		BM::AddFolderMark(wstrDestPath);
	std::wstring wstrOutFileName(strOutFile);

	// 파일을 읽어서 hash를 만든다.
	BM::FolderHash kOrgHash;
	BM::PgDataPackManager::PackFileCache_new kOrgCache;
	kOrgCache.Open(wstrOrgFileName);
	const size_t org_header_size = BM::PgDataPackManager::ReadHeader(kOrgCache);
	kOrgHash = kOrgCache.mFolderHash;
	//const size_t org_header_size =
	//	BM::PgDataPackManager::ReadHeader(wstrOrgFileName, kOrgHash);
	//PgFileMapping kOrgFile;
	//kOrgFile.Init(wstrOrgFileName);

	// 현재 폴더를 저장해둔다.
	// 이름 뒤에 빈공간들을 지우기 위한 처리.
	std::wstring wstrDefaultDir;
	wstrDefaultDir.resize(512);
	::GetCurrentDirectory(512, &wstrDefaultDir.at(0));
	int iEndOfNull = 0;
	for (int i=512-1; i>=0 ; i--)
	{
		if (wstrDefaultDir.at(i) != 0)
		{
			iEndOfNull = i;
			break;
		}
	}
	wstrDefaultDir.resize(iEndOfNull+1);

	BM::FolderHash kDestHash;
	size_t dest_header_size;
	//PgFileMapping kDestFile;
	BM::PgDataPackManager::PackFileCache_new kDestCache;
	if (bIsPackAndDir)
	{
		// 폴더를 읽어서 hash 만듬.
		::SetCurrentDirectory(wstrDestPath.c_str());
		BM::PgDataPackManager::GetFileList(_T(".\\"), kDestHash, BM::GFL_RECURSIVE_ALL_FILE);
	}
	else
	{
		// 파일을 읽어서 hash를 만든다.
		if(kDestCache.Open(wstrDestPath))
		{
			dest_header_size = BM::PgDataPackManager::ReadHeader(kDestCache);
			kDestHash = kDestCache.mFolderHash;
		}

		//dest_header_size =
		//	BM::PgDataPackManager::ReadHeader(wstrDestPath, kDestHash);
		//kDestFile.Init(wstrDestPath);
	}

	// 두 hash를 비교해서 추가나 수정된것을 찾기
	BM::FolderHash kNewHash;
	BM::PgDataPackManager::MakeDiffList(
		kOrgHash, 
		kDestHash, 
		kNewHash, 
		BM::DIFF_ONLY_RIGHT | BM::DIFF_ONLY_DIFF);//다르거나 새로운것.

	if (kNewHash.size())
	{
		std::wstring wstrTempDir;
		if (bIsPackAndDir)
		{
			// NewHash를 압축, 암호화
			BM::AddFolderMark(wstrDefaultDir);
			wstrTempDir = wstrDefaultDir + L"Temp";
			BM::AddFolderMark(wstrTempDir);
			ImproveData(kNewHash, wstrTempDir);
		}

		// Reseult = New + Org 한다.
		BM::FolderHash kResultHash;
		kResultHash.insert(kNewHash.begin(), kNewHash.end());
		kResultHash.insert(kOrgHash.begin(), kOrgHash.end());
		for (BM::FolderHash::iterator itor = kOrgHash.begin() ;
			itor != kOrgHash.end() ;
			++itor)
		{
			BM::FolderHash::iterator itorS = kResultHash.find(itor->first);

			if (itorS != kResultHash.end())
			{
				itorS->second.kFileHash.insert(
					itor->second.kFileHash.begin(), itor->second.kFileHash.end());
			}
		}

		// BuildOffset을 하고
		const unsigned __int64 iResultDataSize = BM::PgDataPackManager::BuildOffset(kResultHash);
		//PgFileMapping kResultFile;
		std::fstream fResultfile;
		fResultfile.open(wstrOutFileName.c_str(), std::ios_base::in | std::ios_base::app | std::ios_base::ate | std::ios_base::binary);
		const size_t result_header_size = BM::PgDataPackManager::MakeHeader(wstrOutFileName, kResultHash, fResultfile);
		fResultfile.seekg(result_header_size);
		//const size_t result_header_size =
		//	BM::PgDataPackManager::MakeHeader( wstrOutFileName, kResultHash, kResultFile);
		//kResultFile.Init( wstrOutFileName, result_header_size + iResultDataSize);

		// 데이터를 직접 쓴다
		//char * pTarget = kResultFile.Data();
		//pTarget += kResultFile.DataSize();//맨뒤로 Seek

		BM::FolderHash::iterator ret_folder_ritor = kResultHash.begin();
		while(ret_folder_ritor != kResultHash.end())//머지 루틴
		{
			const BM::FileHash &rkRetFileHash = (*ret_folder_ritor).second.kFileHash;

			BM::FileHash::const_iterator ret_file_itor = rkRetFileHash.begin();
			while(ret_file_itor != rkRetFileHash.end())
			{
				BM::FolderHash::const_iterator new_folder_itor = kNewHash.find((*ret_folder_ritor).first);

				const BM::PgFIleInfo *pFileInfo = NULL;
				char* pSrc = NULL;
				std::vector<char> vecTemp;
				std::vector<char> vecTemp2;


				// New에 파일이 있다면 그 파일은 수정 혹은 추가된 파일이다.
				bool bIsFindFromNewDat = false;
				if(new_folder_itor != kNewHash.end())
				{
					if( (*new_folder_itor).second.Find((*ret_file_itor).first, pFileInfo) )
					{
						bIsFindFromNewDat = true;

						if (bIsPackAndDir)
						{
							std::wstring wstrRelFolder;
							if (((*ret_folder_ritor).first).size() > 1)
								wstrRelFolder = ((*ret_folder_ritor).first);

							if (pFileInfo->bIsZipped)
								BM::FileToMem(wstrTempDir + wstrRelFolder + (*ret_file_itor).first + _T(".zip"), vecTemp);
							else
								BM::FileToMem(wstrTempDir + wstrRelFolder + (*ret_file_itor).first, vecTemp);
							pSrc = &vecTemp.at(0);
						}
						else
						{
							unsigned __int64 iFileSize = 0;
							if (pFileInfo->bIsZipped)
								iFileSize = pFileInfo->zipped_file_size;
							else
								iFileSize = pFileInfo->org_file_size;
							vecTemp2.resize(iFileSize);
							kDestCache.ReadData(dest_header_size + pFileInfo->offset, &vecTemp2.at(0), iFileSize);
							pSrc = &vecTemp2.at(0);
						}
					}				
				}
			
				// New에서 찾지 못했다면 Org에서 찾는다.
				bool bIsFindFromOrgDat = false;
				if(!bIsFindFromNewDat)
				{
					BM::FolderHash::const_iterator org_folder_itor = kOrgHash.find((*ret_folder_ritor).first);
					if(org_folder_itor != kOrgHash.end())
					{
						if( (*org_folder_itor).second.Find((*ret_file_itor).first, pFileInfo) )
						{
							bIsFindFromOrgDat = true;

							unsigned __int64 iFileSize = 0;
							if (pFileInfo->bIsZipped)
								iFileSize = pFileInfo->zipped_file_size;
							else
								iFileSize = pFileInfo->org_file_size;
							vecTemp2.resize(iFileSize);
							kOrgCache.ReadData(org_header_size + pFileInfo->offset, &vecTemp2.at(0), iFileSize);
							pSrc = &vecTemp2.at(0);

							//pSrc = kOrgFile.Data() + org_header_size + pFileInfo->offset;
						}
					}

					if(!bIsFindFromOrgDat)
					{
						assert(NULL); // 어디에도 파일이 없다. 이건 뭐...
					}
				}

				unsigned __int64 iFileSize = 0;
				if (pFileInfo->bIsZipped)
					iFileSize = pFileInfo->zipped_file_size;
				else
					iFileSize = pFileInfo->org_file_size;

				if(iFileSize)
				{
					unsigned __int64 iRecSize = (iFileSize + ((pFileInfo->bIsEncrypt)?BM::ENC_HEADER_SIZE:0));
					fResultfile.write(pSrc,  std::ios_base::in | std::ios_base::app | std::ios_base::ate | std::ios_base::binary);
					//pTarget -= iRecSize;
					//::memcpy(pTarget, pSrc, iRecSize);
				}

				++ret_file_itor;
			}
			++ret_folder_ritor;
		}

		// 끝나고 뒤처리, 원본 지우고 이름 바꾼다.
		fResultfile.close();
		//kOrgFile.Clear();
		//kResultFile.Clear();
		//DeleteFile((wstrOrgFileName + _T("_OLD")).c_str());6
		//int ret = _wrename(
		//		(wstrOrgFileName).c_str(),
		//		(wstrOrgFileName + _T("_OLD")).c_str());
		//ret = _wrename(
		//		(wstrOrgFileName + _T("_NEW")).c_str(),
		//		(wstrOrgFileName).c_str());

		if (bIsPackAndDir)
		{
			DeletePath(wstrTempDir.c_str());
		}

		g_pDlg->m_stcPackState.SetWindowText(_T("Complete"));
	}
	else
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Version is same"));
	}

	_endthreadex( 0 );
	g_hThread = INVALID_HANDLE_VALUE;
	return true;
}

void DoMergeFile(void *pDlg)
{
	if (g_hThread == INVALID_HANDLE_VALUE)
	{
		unsigned threadID;
		g_pDlg = (CPackDlg*)pDlg;
		g_hThread = (HANDLE)_beginthreadex( NULL, 0, &MergeFile, pDlg, 0, &threadID );
	}
}

unsigned __stdcall MakeOnePack( void* pArguments )
{
	g_pDlg->m_stcPackState.SetWindowText(_T("Making Version."));

	// 어떤 버젼으로 만들고 있는 중 인가?
	// 0=Normal 1=Assem 2=Full
	int iVer = g_pDlg->m_cmbMakeOnePack_Option.GetCurSel();
	char cVer = '?';
	if (iVer == 0) cVer = 'N';
	else if (iVer == 1) cVer = 'A';
	else if (iVer == 2) cVer = 'F';
	CString strVer;
	strVer.Insert(0, cVer);
	std::wstring wstrVer(strVer);

	// 경로, 이름등 받아서 wide string으로 바꾼다.
	CString strOrgFileDir;
	g_pDlg->m_edtMakeOnePack_OrgDir.GetWindowText(strOrgFileDir);
	CString strNewFileDir;
	g_pDlg->m_edtMakeOnePack_NewDir.GetWindowText(strNewFileDir);
	CString strOutFileDir;
	g_pDlg->m_edtMakeOnePack_OutDir.GetWindowText(strOutFileDir);
	CString strVersion;
	g_pDlg->m_edtMakeOnePack_Version.GetWindowText(strVersion);

	if( iVer != 2 &&
		!strOrgFileDir.IsEmpty() &&
		GetFileAttributes(strOrgFileDir) == INVALID_FILE_ATTRIBUTES )
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Origin folder isn't exist"));
		_endthreadex( 0 );
		g_hThread = INVALID_HANDLE_VALUE;
		return false;
	}
	if( GetFileAttributes(strNewFileDir) == INVALID_FILE_ATTRIBUTES )
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("New folder isn't exist"));
		_endthreadex( 0 );
		g_hThread = INVALID_HANDLE_VALUE;
		return false;
	}

	std::wstring wstrOrgPath(strOrgFileDir);
	BM::AddFolderMark(wstrOrgPath);
	std::wstring wstrNewPath(strNewFileDir);
	BM::AddFolderMark(wstrNewPath);
	std::wstring wstrOutPath(strOutFileDir);
	BM::AddFolderMark(wstrOutPath);
	std::wstring wstrOutFileName;
	std::wstring wstrOutVersion(strVersion);
	for (int i=0 ; i<wstrOutVersion.size() ; i++)
		if (wstrOutVersion.at(i) == '.')
			wstrOutVersion.at(i) = '_';
	wstrOutFileName = (_T("P") + wstrOutVersion + _T("_") + wstrVer + _T(".DAT")).c_str();
	if( GetFileAttributes((wstrOutPath + wstrOutFileName).c_str()) == FILE_ATTRIBUTE_ARCHIVE )
	{
		g_pDlg->m_stcPackState.SetWindowText((wstrOutFileName + _T(" is exist")).c_str());
		_endthreadex( 0 );
		g_hThread = INVALID_HANDLE_VALUE;
		return false;
	}

	// 폴더를 읽어서 hash 만듬.
	g_pDlg->m_stcPackState.SetWindowText(_T("Making hash"));
	BM::FolderHash kOrgHash;
	if (!wstrOrgPath.empty() &&
		iVer != 2)
	{
		::SetCurrentDirectory(wstrOrgPath.c_str());
		BM::PgDataPackManager::GetFileList(_T(".\\"), kOrgHash, BM::GFL_RECURSIVE_ALL_FILE);
	}
	BM::FolderHash kNewHash;
	::SetCurrentDirectory(wstrNewPath.c_str());
	BM::PgDataPackManager::GetFileList(_T(".\\"), kNewHash, BM::GFL_RECURSIVE_ALL_FILE);

	// 두 hash를 비교해서 추가나 수정된것을 찾기
	g_pDlg->m_stcPackState.SetWindowText(_T("Diffing hash"));
	BM::FolderHash kResultHash;
	BM::PgDataPackManager::MakeDiffList(
		kOrgHash, 
		kNewHash, 
		kResultHash, 
		BM::DIFF_ONLY_RIGHT | BM::DIFF_ONLY_DIFF);//다르거나 새로운것.

	if (kResultHash.size())
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Improve Data"));
		// NewHash를 압축, 암호화
		BM::AddFolderMark(wstrOutPath);
		std::wstring wstrTempDir = wstrOutPath + L"Temp";
		BM::AddFolderMark(wstrTempDir);
		ImproveData(kResultHash, wstrTempDir);

		// BuildOffset을 하고
		const unsigned __int64 iResultDataSize = BM::PgDataPackManager::BuildOffset(kResultHash);
		//PgFileMapping kResultFile;
		std::fstream fResultfile;
		std::wstring wstrPathName(wstrOutPath + wstrOutFileName);
		fResultfile.open(wstrPathName.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::ate | std::ios_base::binary );
		const size_t result_header_size =
			BM::PgDataPackManager::MakeHeader( wstrOutPath + wstrOutFileName, kResultHash, fResultfile);
		//kResultFile.Init( wstrOutPath + wstrOutFileName, result_header_size + iResultDataSize);

	//	// 데이터를 직접 쓴다
	//	char * pTarget = kResultFile.Data();
	//	pTarget += kResultFile.DataSize();//맨뒤로 Seek

	//	BM::FolderHash::reverse_iterator ret_folder_ritor = kResultHash.rbegin();
	//	while(ret_folder_ritor != kResultHash.rend())//머지 루틴
	//	{
	//		const BM::FileHash &rkRetFileHash = (*ret_folder_ritor).second.kFileHash;

	//		BM::FileHash::const_reverse_iterator ret_file_itor = rkRetFileHash.rbegin();
	//		while(ret_file_itor != rkRetFileHash.rend())
	//		{
	//			const BM::PgFIleInfo *pFileInfo = NULL;
	//			char* pSrc = NULL;
	//			std::vector<char> vecTemp;

	//			// 새로운 파일을 바이너리로 바꾸자.
	//			pFileInfo = &((*ret_file_itor).second);
	//			std::wstring wstrRelFolder;
	//			if (((*ret_folder_ritor).first).size() > 1)
	//				wstrRelFolder = ((*ret_folder_ritor).first);

	//			if (pFileInfo->bIsZipped)
	//				BM::FileToMem(wstrTempDir + wstrRelFolder + (*ret_file_itor).first + _T(".zip"), vecTemp);
	//			else
	//				BM::FileToMem(wstrTempDir + wstrRelFolder + (*ret_file_itor).first, vecTemp);
	//			assert(vecTemp.size());
	//			pSrc = &vecTemp.at(0);
	//			
	//			unsigned __int64 iFileSize = 0;
	//			if (pFileInfo->bIsZipped)
	//				iFileSize = pFileInfo->zipped_file_size;
	//			else
	//				iFileSize = pFileInfo->org_file_size;

	//			if(iFileSize)
	//			{
	//				unsigned __int64 iRecSize = (iFileSize + ((pFileInfo->bIsEncrypt)?BM::ENC_HEADER_SIZE:0));
	//				pTarget -= iRecSize;
	//				::memcpy(pTarget, pSrc, iRecSize);
	//			}

	//			g_pDlg->m_stcPackState.SetWindowText(((*ret_file_itor).first + _T(" was made")).c_str());

	//			++ret_file_itor;
	//		}
	//		++ret_folder_ritor;
	//	} // end of 데이터 직접 쓰기

	//	// 끝나고 Temp를 지운다..
	//	kResultFile.Clear();
	//	g_pDlg->m_stcPackState.SetWindowText(_T("Deleting Temp"));
	//	DeletePath(wstrTempDir.c_str());

	//	// 최신 버젼 Patch.VER파일 만들기
	//	DeleteFile((wstrOutPath + _T("Patch.VER")).c_str());
	//	std::wstring wstrVersion(strVersion);
	//	size_t con;
	//	std::vector<char> vecVersion;
	//	vecVersion.resize(wstrVersion.size()+1);
	//	wcstombs_s(&con,
	//		&vecVersion.at(0),
	//		wstrVersion.size()+1,
	//		wstrVersion.c_str(),
	//		wstrVersion.size()+1);
	//	vecVersion.resize(vecVersion.size()-1);
	//	// 저장되는 형식 '1.0.0.5'
	//	BM::EncSave( wstrOutPath + _T("Patch.VER"), vecVersion);

	//	// Version List를 만든다.
	//	g_pDlg->m_stcPackState.SetWindowText(_T("Making Version List"));
	//	CString strVerListFile;
	//	g_pDlg->m_edtMakeOnePack_VerList.GetWindowText(strVerListFile);
	//	std::wstring wstrVerListFile(strVerListFile);
	//	if (!strVerListFile.IsEmpty())
	//	{
	//		bool bIsExist = true;
	//		if(GetFileAttributes(strVerListFile) == INVALID_FILE_ATTRIBUTES )
	//		{
	//			// 존재 하지 않으면 파일 새로 만든다.
	//			PgFileMapping kMapTemp;
	//			kMapTemp.Init(wstrVerListFile, 0);
	//			kMapTemp.Clear();
	//			bIsExist = false;
	//		}

	//		char *pSrc = NULL;
	//		std::vector<char> vecVerList;
	//		BM::FileToMem(wstrVerListFile, vecVerList);
	//		if (bIsExist &&
	//			vecVerList.at(vecVerList.size()-1) != 13)
	//		{
	//			vecVerList.insert(vecVerList.end(), 13);
	//		}
	//		vecVerList.insert(vecVerList.end(), cVer);
	//		vecVerList.insert(vecVerList.end(), ' ');
	//		size_t end = vecVerList.size();
	//		vecVerList.resize(vecVerList.size() + wstrOutVersion.size());
	//		pSrc = &vecVerList.at(end);
	//		memcpy(pSrc, &vecVersion.at(0), vecVersion.size());
	//		vecVerList.insert(vecVerList.end(), 13);
	//		BM::MemToFile(wstrVerListFile, vecVerList);
	//	}

		// 완료
		g_pDlg->m_stcPackState.SetWindowText((_T("Complete : ") + wstrOutFileName + _T(" was created.")).c_str());
	}
	else
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Version is same"));
	}

	_endthreadex( 0 );
	g_hThread = INVALID_HANDLE_VALUE;
	return true;
}

void DoMakeOnePack(void *pDlg)
{
	if (g_hThread == INVALID_HANDLE_VALUE)
	{
		unsigned threadID;
		g_pDlg = (CPackDlg*)pDlg;
		g_hThread = (HANDLE)_beginthreadex( NULL, 0, &MakeOnePack, pDlg, 0, &threadID );
	}
}

bool SetPatchVer(std::wstring strName, std::wstring strVersionNum)
{
	std::wstring wstrKey = strVersionNum;

	if(!wstrKey.size()){ return false; }

	typedef	std::list<std::wstring>	CUT_STRING;

	CUT_STRING	kNumberList;
	BM::vstring::CutTextByKey(wstrKey, std::wstring(L"."), kNumberList);

	if(kNumberList.size() != 3){ return false; }

	CUT_STRING::iterator	iter = kNumberList.begin();

	BM::VersionInfo	Info;
	Info.Version.i16Major = (WORD)_wtoi(iter->c_str());	++iter;
	Info.Version.i16Minor = (WORD)_wtoi(iter->c_str()); ++iter;
	Info.Version.i32Tiny = _wtoi(iter->c_str());

	if(!BM::PgDataPackManager::UpdatePackVersion(strName, Info))
	{
		return false;
	}

	return true;
}