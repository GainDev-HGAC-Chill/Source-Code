#include "stdafx.h"
#include "resource.h"
#include "PackDlg.h"

extern CPackDlg* g_pDlg;

bool ImproveData(BM::FolderHash &kInHash, const std::wstring &strOutputDir)//데이터 가공
{//파일 엔코딩만 해서. 올리는게 어떻겠소.
//	::SetCurrentDirectory(pOutputDir);
	BM::FolderHash::iterator folder_itor = kInHash.begin();
	while(folder_itor != kInHash.end())
	{
//SetTargetDir 해줘야함.
		const std::wstring& wstrSrcFolder =  (*folder_itor).first;
		BM::PgFolderInfo& rFolderInfo =  (*folder_itor).second;

		//BM::FileHash::const_iterator file_itor = rFolderInfo.kFileHash.begin();
		BM::FileHash::iterator file_itor = rFolderInfo.kFileHash.begin();
		while(file_itor != rFolderInfo.kFileHash.end())
		{
			const std::wstring& wstrSrcFile = wstrSrcFolder + (*file_itor).first;
//			const std::wstring::size_type dividepos = wstrSrcFile.find(_T("."));

			std::wstring wstrMsg = L"ImproveData : " + (*file_itor).first;
			g_pDlg->m_stcPackState.SetWindowText(wstrMsg.c_str());

			std::wstring wstrOutputFolder = strOutputDir;
			BM::AddFolderMark(wstrOutputFolder);
			
			if(wstrSrcFolder.size() >2)
			{
				const std::wstring::size_type pos = wstrSrcFolder.find(_T(".\\"));
				if(pos != std::wstring::npos)
				{
					wstrOutputFolder += wstrSrcFolder.substr(pos+2);
					BM::AddFolderMark(wstrOutputFolder);
				}
			}

			const std::wstring wstrTgtFileName = wstrOutputFolder + (*file_itor).first;

			BM::ReserveFolder(wstrTgtFileName);

			std::vector<char> kFileData;
			std::vector<char> kZippedData;
			if(BM::FileToMem(wstrSrcFile.c_str(), kFileData))
			{
				if(BM::Compress(kFileData, kZippedData))
				{//압축
					(*file_itor).second.bIsZipped = true;
					(*file_itor).second.zipped_file_size = kZippedData.size();
					if((*file_itor).second.bIsEncrypt)
					{
						BM::EncSave(wstrTgtFileName + _T(".zip"), kZippedData);
					}
					else
					{
						BM::MemToFile(wstrTgtFileName + _T(".zip"), kZippedData);
					}
				}
				else
				{//압축 안됨. (오히려 커짐)
					(*file_itor).second.bIsZipped = false;
					(*file_itor).second.zipped_file_size = kFileData.size();
					if((*file_itor).second.bIsEncrypt)
					{
						BM::EncSave(wstrTgtFileName + _T(".zip"), kFileData);
					}
					else
					{
						BM::MemToFile(wstrTgtFileName + _T(".zip"), kFileData);
					}
				}
				++file_itor;
			}
			else
			{
				assert(NULL);
				return false;
			}
		}
		++folder_itor;
	}
	return true;
}

bool MakeVersionForFTP(const std::wstring &wstrSrcDir, const std::wstring &wstrTgtDir, const std::wstring &wstrPackedName, bool bIsPackFolder)
{
	std::wstring wstrDestFolder = wstrTgtDir + wstrPackedName;

	BM::FolderHash kInHash;
	{
		//내부 파일 목록을 뽑아옴.
		DWORD dwFlag = (wstrSrcDir == L".\\") ? dwFlag = BM::GFL_ONLY_FILE : BM::GFL_RECURSIVE_ALL_FILE;
		if(!BM::PgDataPackManager::GetFileList(wstrSrcDir, kInHash, dwFlag))
		{
			return false;
		}
		
		// 현재 Target폴더가 Pack이면 Pack속성을 준다.
		BM::FolderHash::iterator find_itr = kInHash.find(wstrSrcDir);
		if (find_itr != kInHash.end())
		{
			(*find_itr).second.bIsUsePack = bIsPackFolder;
		}
		BM::PgDataPackManager::RecursiveProcessPackState(kInHash);

		//h는 헤더만 뽑는다는 의미
		//PgFileMapping kFileMapping;
		std::fstream ffile;
		if(!BM::PgDataPackManager::MakeHeader(wstrDestFolder + _T("_H.dat"), kInHash, ffile))
		{
			return false;
		}
	}
	
	//각각의 실제 파일들 암호화 해서 카피
	if( ImproveData(kInHash, wstrTgtDir) )//파일을 다른데로 이동 복사.
	{
		BM::FolderHash kZipHash;
		//PgFileMapping kFileMapping;
		std::fstream ffile;

		if(!BM::PgDataPackManager::MakeHeader(wstrDestFolder +_T("_H_ZIP.dat"), kInHash, ffile))
		{
			return false;
		}
	}
	return true;
}

/*
bool MakeVersionForFTP_PackFolder(const std::wstring &wstrSrcDir, const std::wstring &wstrTgtDir, const std::wstring &wstrPackedName)
{
	std::wstring wstrDestFolder = wstrTgtDir + wstrPackedName;

	BM::FolderHash kInHash;
	{
		//내부 파일 목록을 뽑아옴.
		DWORD dwFlag = (wstrSrcDir == L".\\") ? dwFlag = BM::GFL_ONLY_FILE : BM::GFL_RECURSIVE_ALL_FILE;
		if(!BM::PgDataPackManager::GetFileList(wstrSrcDir, kInHash, dwFlag))
		{
			return false;
		}
		RecursiveProcessPackState(kInHash);

		//h는 헤더만 뽑는다는 의미
		PgFileMapping kFileMapping;
		if(!BM::PgDataPackManager::MakeHeader(wstrDestFolder + _T("_H.dat"), kInHash, kFileMapping))
		{
			return false;
		}
	}
	
	//각각의 실제 파일들 암호화 해서 카피
	if( ImproveData(kInHash, wstrDestFolder) )//파일을 다른데로 이동 복사.
	{
		BM::FolderHash kZipHash;
		PgFileMapping kFileMapping;

		if(!BM::PgDataPackManager::MakeHeader(wstrDestFolder +_T("_H_ZIP.dat"), kInHash, kFileMapping))
		{
			return false;
		}
	}
	return true;
}

bool MakeVersionForFTP_NonePackFolder(const std::wstring &wstrSrcDir, const std::wstring &wstrTgtDir, const std::wstring &wstrPackedName)
{
	return false;
	std::wstring wstrDestFolder = wstrTgtDir + wstrPackedName;
	//::SetCurrentDirectory(wstrSrcDir.c_str());//타겟폴더 안으로 디렉토리 들어왔음.

	//Config 읽어야 됨
	BM::FolderHash kInHash;

	DWORD dwFlag = BM::GFL_RECURSIVE_ALL_FILE;
	if (wstrSrcDir == L".\\")
	{
		dwFlag = BM::GFL_ONLY_FILE;
	}

	{
		if(!BM::PgDataPackManager::GetFileList(wstrSrcDir, kInHash, dwFlag))//내부 파일 목록을 뽑아옴.
		{
			return false;
		}
		RecursiveProcessPackState(kInHash);

		PgFileMapping kFileMapping;
		if(!BM::PgDataPackManager::MakeHeader(wstrTgtDir+ _T("\\")+wstrPackedName +_T("_H.dat"), kInHash, kFileMapping))
		{
			return false;
		}
	}

	//각각의 실제 파일들 암호화 해서 카피

	if( ImproveData(kInHash, wstrTgtDir+wstrPackedName) )//파일을 다른데로 이동 복사.
	{
		BM::FolderHash kZipHash;
		PgFileMapping kFileMapping;
		
		::SetCurrentDirectory((wstrTgtDir+wstrPackedName).c_str() );
		//if(!BM::PgDataPackManager::GetFileList(_T(".\\"), kZipHash))
		//{
		//	return false;
		//}

		if(!BM::PgDataPackManager::MakeHeader(wstrTgtDir+ _T("\\")+wstrPackedName +_T("_H_ZIP.dat"), kInHash, kFileMapping))
		{
			return false;
		}
	}
	return true;
}
*/

bool MakeForFTP(const std::wstring &wstrTargetDir,const  std::wstring &wstrOutputForFTP)
{
	::SetCurrentDirectory(wstrTargetDir.c_str());//Setcurrent 안해주면 절대경로가 들어간다.

	BM::FolderHash kHeadFolderHash;

//전체 목록을 얻어와라//얻어온 다음 가르자.
	if(!BM::PgDataPackManager::GetFileList(_T(".\\"), kHeadFolderHash, BM::GFL_ONLY_FOLDER | BM::GFL_ONLY_FILE))// BM::GFL_RECURSIVE_ALL))
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Error: Get HeadFolder List"));
		return false;
	}
		 
	BM::FolderHash::iterator folder_itor = kHeadFolderHash.begin();
	while(folder_itor != kHeadFolderHash.end())//헤드 폴더를 다 돈다.
	{
		const std::wstring &wstrTargetFolder = (*folder_itor).first;
		const std::wstring wstrCreateFileName = BM::GetLastFolderName(wstrTargetFolder);//생성 될 파일이름

		::SetCurrentDirectory(wstrTargetDir.c_str());//Setcurrent 안해주면 MakeVersionDetail에서 위쪽 경로를 찾을 수 없기때문에.

		if((*folder_itor).second.bIsUsePack)
		{
			g_pDlg->m_stcPackState.SetWindowText((_T("MakeVersion: Pack Folder ")+wstrCreateFileName).c_str());
			//MakeVersionForFTP_PackFolder(wstrTargetFolder, wstrOutputForFTP, wstrCreateFileName);
		}
		else
		{
			g_pDlg->m_stcPackState.SetWindowText( (_T("MakeVersion: None Pack Folder ")+wstrCreateFileName).c_str() );
			//MakeVersionForFTP_NonePackFolder(wstrTargetFolder, wstrOutputForFTP, wstrCreateFileName);
		}
		MakeVersionForFTP(wstrTargetFolder, wstrOutputForFTP, wstrCreateFileName, (*folder_itor).second.bIsUsePack);
		++folder_itor;
	}
{
	//	kHeadFolderHash -> 헤드 폴더를. header로 만들어줄 필요가 있음.
	const std::wstring wstrParentFileName = BM::GetLastFolderName(wstrTargetDir);//최상위로 되는 폴더명

	//PgFileMapping kFileMapping;
	std::fstream ffile;
	if(!BM::PgDataPackManager::MakeHeader(wstrOutputForFTP+_T("\\HeadFolders.dat"), kHeadFolderHash, ffile))
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Error Parent Head Folder Make Failed"));
		return false;
	}//h는 헤더만 뽑는다는 의미
}
	return true;
}

bool RecursiveMakeData()
{
	return true;
}

bool MakeData(const std::wstring &wstrOutputForFTP, const std::wstring &wstrTargetRoot, const std::wstring &wstrTargetDir, bool bIsPackFolder)
{
	// 파일들이 있는 폴더. (Input)
	std::wstring kTargetDir = wstrTargetRoot + wstrTargetDir;
	kTargetDir.erase(kTargetDir.find(_T(".\\")), 2);
	BM::AddFolderMark(kTargetDir);

	// Header 파일이 만드어질 폴더 (Output)
	std::wstring kHeaderFileDir = wstrOutputForFTP + wstrTargetDir;
	kHeaderFileDir.erase(kHeaderFileDir.find(_T(".\\")), 2);
	BM::ReserveFolder(kHeaderFileDir);

	// 폴더리스트, 파일리스트를 얻는다. (재귀적은 아님)
	::SetCurrentDirectory(kTargetDir.c_str());
	BM::FolderHash kFolderHash;
	BM::PgDataPackManager::GetFileList(_T(".\\"), kFolderHash, BM::GFL_ONLY_FOLDER, wstrTargetDir);
	BM::FolderHash kFileHash;
	BM::PgDataPackManager::GetFileList(_T(".\\"), kFileHash, BM::GFL_ONLY_FILE, wstrTargetDir);

	//폴더를 다 돈다.
	BM::FolderHash::iterator folder_itor = kFolderHash.begin();
	while(folder_itor != kFolderHash.end())
	{
		std::wstring kSubFolder = wstrTargetDir;
		kSubFolder += BM::GetLastFolderName((*folder_itor).first);
		BM::AddFolderMark(kSubFolder);

		//생성 될 파일이름
		const std::wstring wstrCreateFileName = BM::GetLastFolderName((*folder_itor).first);

		// 만약 지금 폴더가 Pack폴더 하위 라면. 그 하위들은 전부 UsePack이 false 속성으로 되어야 한다.
		bool bIsPack = bIsPackFolder;
		if (bIsPack)
		{
			(*folder_itor).second.bIsUsePack = false;
		}

		// UsePack이면 그다음 재귀는 .bIsUsePack 이 false가 되어야 한다.
		if((*folder_itor).second.bIsUsePack)
		{
			g_pDlg->m_stcPackState.SetWindowText((_T("MakeVersion: Pack Folder ")+wstrCreateFileName).c_str());
			bIsPack = true;
			// 여기도 아래와 같다.
		}
		else 
		{
			g_pDlg->m_stcPackState.SetWindowText( (_T("MakeVersion: None Pack Folder ")+wstrCreateFileName).c_str() );
		}

		// 재귀적으로 만들자.
		MakeData(wstrOutputForFTP, wstrTargetRoot, kSubFolder, bIsPackFolder);
		++folder_itor;
	}

	// 폴더 저장
	//PgFileMapping kFileMapping;
	std::fstream ffile;
	if(!BM::PgDataPackManager::MakeHeader(kHeaderFileDir + _T("_FOLDERS.PGH"), kFolderHash, ffile))
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Error Parent Head Folder Make Failed"));
		return false;
	}

	// 파일 저장
	if(!BM::PgDataPackManager::MakeHeader(kHeaderFileDir + _T("_FILES.PGH"), kFileHash, ffile))
	{
		return false;
	}
	
	//각각의 실제 파일들 암호화 해서 카피
	::SetCurrentDirectory(kTargetDir.c_str());
	if( ImproveData(kFileHash, kHeaderFileDir) )//파일을 다른데로 이동 복사.
	{
		BM::FolderHash kZipHash;
		//PgFileMapping kFileMapping;
		std::fstream ffile;

		if(!BM::PgDataPackManager::MakeHeader(kHeaderFileDir +_T("_ZIPFILES.PGH"), kFileHash, ffile))
		{
			return false;
		}
	}

	return true;
}
