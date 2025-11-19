#include "stdafx.h"
#include "resource.h"
#include "PackDlg.h"

extern CPackDlg* g_pDlg;

bool MakeVersionForUser_NonePackFolder(const std::wstring &wstrSrcDir, const std::wstring &wstrTgtDir, const std::wstring &wstrPackedName)
{
/*	//Config 읽어야 됨
	BM::FolderHash kInHash;
	::SetCurrentDirectory(wstrSrcDir.c_str());

	PgFileMapping kFileMapping;

	if(!BM::PgDataPackManager::GetFileList(_T(".\\"), kInHash))
	{
		return false;
	}

	if(!BM::PgDataPackManager::MakeHeader(wstrTgtDir+ _T("\\")+wstrPackedName +_T("_H.dat"), kInHash, kFileMapping))
	{
		return false;
	}//h는 헤더만 뽑는다는 의미

	//각각의 실제 파일들 암호화 해서 카피

	ImproveData(kInHash, wstrTgtDir+wstrPackedName);//파일을 다른데로 이동 복사.

*/	return true;
}

bool MakeForUser(std::wstring &wstrTargetDir, std::wstring &wstrOutputForUser)
{
/*	::SetCurrentDirectory(wstrTargetDir.c_str());//Setcurrent 안해주면 절대경로가 들어간다.

	BM::FolderHash kHeadFolder;

//전체 목록을 얻어와라//얻어온 다음 가르자.
	if(!BM::PgDataPackManager::GetFileList(_T(".\\"), kHeadFolder, BM::GFL_ONLY_FOLDER))// BM::GFL_RECURSIVE_ALL))
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Error: Get HeadFolder List"));
		return false;
	}
		 
	BM::FolderHash::iterator folder_itor = kHeadFolder.begin();
	while(folder_itor != kHeadFolder.end())
	{
		const std::wstring wstrTargetFolder = (*folder_itor).first;
		const std::wstring wstrCreateFileName = BM::GetLastFolderName(wstrTargetFolder);

		::SetCurrentDirectory(wstrTargetDir.c_str());//Setcurrent 안해주면 MakeVersionDetail에서 위쪽 경로를 찾을 수 없기때문에.

		if((*folder_itor).second.bIsUsePack)
		{//팩 하는건 XML. SCRIPT 나머지는 카피.
//			g_pDlg->m_stcPackState.SetWindowText((_T("MakeVersion: Pack Folder ")+wstrCreateFileName).c_str());
//			MakeVersion_PackFolder(wstrTargetFolder, wstrOutputForFTP, wstrCreateFileName);
		}
		else
		{
			g_pDlg->m_stcPackState.SetWindowText( (_T("MakeVersion: None Pack Folder ")+wstrCreateFileName).c_str() );
			MakeVersion_NonePackFolder(wstrTargetFolder, wstrOutputForFTP, wstrCreateFileName);
		}
		++folder_itor;
	}
{
	//	kHeadFolder -> 헤드 폴더를. header로 만들어줄 필요가 있음.
	const std::wstring wstrParentFileName = BM::GetLastFolderName(wstrTargetDir);//최상위로 되는 폴더명

	PgFileMapping kFileMapping;
	if(!BM::PgDataPackManager::MakeHeader(wstrOutputForFTP+_T("\\HeadFolders.dat"), kHeadFolder, kFileMapping))
	{
		g_pDlg->m_stcPackState.SetWindowText(_T("Error Parent Head Folder Make Failed"));
		return false;
	}//h는 헤더만 뽑는다는 의미
}
*/	return true;
}
