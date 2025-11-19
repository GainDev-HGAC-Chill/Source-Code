#include "stdafx.h"
#include <assert.h>
#include <process.h>

#include "resource.h"
#include "PatcherDlg.h"
#include "PgPatchThread.h"

#include "FTPMgr.h"

unsigned __stdcall UiThread( void* pArguments );

CPatcherDlg*	g_pDlg		= NULL;
CFTPMgr*		g_pkFtpMgr	= 0;
HANDLE			g_hThread	= INVALID_HANDLE_VALUE;
HANDLE			g_hUiThread = INVALID_HANDLE_VALUE;
volatile long	g_iCRCCount = 0;
int				g_iPort		= 0;
//int			g_iCRCCount = 0;
bool			g_bIsGuardOption = false;
bool			g_bIsGuardini = false;
bool			g_bIsGuarddes = false;

std::wstring	g_wstrTargetDir;
std::wstring	g_wstrIP;
std::wstring	g_wstrID;
std::wstring	g_wstrPW;
std::wstring	g_wstrCRC; // 패쳐 실행 파일의 CRC

const std::wstring	g_wstrGuardini = L"DRAGONICA.INI";
const std::wstring	g_wstrGuarddes = L"GAMEGUARD.DES";

int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{
	return EXCEPTION_EXECUTE_HANDLER;
}


//────────────────────────────────────────
//	파일리스트 받기
//────────────────────────────────────────
bool GetFileList(const std::wstring &wstrDatFileName, BM::FolderHash &rkFileHash)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일과 해시 비교 : %s"), _T(__FUNCTION__), __LINE__, wstrDatFileName.c_str());

	std::vector<char>	vTemp;
	std::wstring		wstrChildName = _T("");
	
	try
	{
		//xxx todo 캐싱 때문에 작업 -> ReadHeader 내부를 바꿔
		BM::PgDataPackManager::LoadFromPack(wstrDatFileName, wstrChildName, vTemp);
	}
	catch(...)
	{
		std::wstring wstrError = _T("Fail to downloading file list '") + wstrDatFileName + _T("'");
		g_pDlg->SetHeadStateText(MB(wstrError));
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일과 해시 비교 실패 : %s"), _T(__FUNCTION__), __LINE__, wstrDatFileName.c_str());
		return false;
	}
	
	const size_t header_size = BM::PgDataPackManager::ReadHeader(wstrDatFileName, rkFileHash);
	BM::PgDataPackManager::ClearBuffer(wstrDatFileName);

	if(header_size)
	{
		return true;	
	}

	INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 헤더 사이즈 오류 : %ld"), _T(__FUNCTION__), __LINE__, header_size);

	return false;
}

//────────────────────────────────────────
//	크기 비교 하기
//────────────────────────────────────────
bool SizeDiffList(const BM::FolderHash &rkSrcFolderHash, const BM::FolderHash &rkDstFolderHash,
				  BM::FolderHash &rkSameFolderHash, BM::FolderHash &rkDiffFolderHash)
{
	BM::FolderHash::const_iterator dst_folder_itor = rkDstFolderHash.begin();
	while(dst_folder_itor != rkDstFolderHash.end())
	{
		BM::FolderHash::const_iterator src_folder_itor = rkSrcFolderHash.find( (*dst_folder_itor).first );

		// Src에 폴더가 없다.
		if(src_folder_itor == rkSrcFolderHash.end())
		{
			rkDiffFolderHash.insert(std::make_pair((*dst_folder_itor).first, (*dst_folder_itor).second));
		}
		// Src에 폴더가 있다.
		else if(src_folder_itor != rkSrcFolderHash.end())
		{	
			const BM::FileHash &rkDstFileHash = (*dst_folder_itor).second.kFileHash;
			BM::FileHash::const_iterator dst_file_itor = rkDstFileHash.begin();
			while( rkDstFileHash.end() != dst_file_itor )
			{
				bool bIsNewFile = false;

				const std::wstring &rkDstFileName = (*dst_file_itor).first;
				const BM::PgFIleInfo &rkDstFileInfo = (*dst_file_itor).second;
				
				const BM::FileHash &rkSrcFileHash = (*src_folder_itor).second.kFileHash;
				BM::FileHash::const_iterator src_file_itor = rkSrcFileHash.find( (*dst_file_itor).first);

				// 파일을 찾았다.
				if( rkSrcFileHash.end() != src_file_itor)
				{
					const std::wstring &rkSrcFileName = (*src_file_itor).first;
					const BM::PgFIleInfo &rkSrcFileInfo = (*src_file_itor).second;

					// 사이즈 비교 해서 same, diff로 나누자.
					if(rkDstFileInfo.org_file_size != rkSrcFileInfo.org_file_size)
					{
						//
						BM::FolderHash::_Pairib Ret = rkDiffFolderHash.insert( std::make_pair((*dst_folder_itor).first, BM::PgFolderInfo()));
						(Ret.first)->second.Insert(rkDstFileName, rkDstFileInfo);
					}
					else
					{
						BM::FolderHash::_Pairib Ret = rkSameFolderHash.insert( std::make_pair((*dst_folder_itor).first, BM::PgFolderInfo()));
						(Ret.first)->second.Insert(rkSrcFileName, rkSrcFileInfo);
					}
				}
				else
				{//원본에서 찾을 수 없다.
					BM::FolderHash::_Pairib Ret = rkDiffFolderHash.insert( std::make_pair((*dst_folder_itor).first, BM::PgFolderInfo()));
					(Ret.first)->second.Insert(rkDstFileName, rkDstFileInfo);
				}

				++dst_file_itor;
			}
		}
		++dst_folder_itor;
	}

	if( rkSrcFolderHash.size() == 0 )
	{
		rkDiffFolderHash = rkDstFolderHash;
		return true;
	}

	return true;
}

//────────────────────────────────────────
//	팩 안하는 파일 받기
//────────────────────────────────────────
bool DownLoadData_NonePack(CFTPMgr &kFtpMgr, BM::FolderHash &rkDownloadList, const std::wstring &wstrOrgPackFileName)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] NonePack 다운 : %s"), _T(__FUNCTION__), __LINE__, wstrOrgPackFileName.c_str());

	g_pDlg->SetActionState(CPatcherDlg::eActionState_Downloading);
	g_pDlg->SetHeadStateText("Download : ");

	BM::FolderHash::iterator folder_itor = rkDownloadList.begin();
	BM::FolderHash::iterator dn_folder_itor = rkDownloadList.begin();
	while(dn_folder_itor != rkDownloadList.end() &&
		g_pDlg->GetIsProcess())
	{	
		const BM::FileHash &rkFileHash = (*dn_folder_itor).second.kFileHash;
	
		BM::FileHash::const_iterator file_itor = rkFileHash.begin();

		// 각각 파일을 받음.
		while(file_itor != rkFileHash.end() &&
			g_pDlg->GetIsProcess())
		{
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 다운 : %s"), _T(__FUNCTION__), __LINE__, (*file_itor).first.c_str());

			std::wstring wstrOrgPath = (*dn_folder_itor).first.c_str();

			const std::wstring::size_type pos = wstrOrgPath.find(_T(".\\")) + 2;
			std::wstring wstrTail = wstrOrgPath.substr(pos);
			std::wstring wstrRet = _T(".\\")+ wstrOrgPackFileName +_T("\\")+wstrTail;
			wstrRet += (*file_itor).first.c_str();

			g_pDlg->SetCurrentDownloadFile( (*file_itor).first.c_str(), file_itor->second.zipped_file_size );

			std::wstring wstrTarget = wstrRet;

			if(g_bIsGuardOption == true)
			{
				if((*file_itor).first.compare(g_wstrGuardini) != -1)
				{
					if(g_bIsGuardini == false)
					{
						++file_itor;
						continue;
					}
				}

				if((*file_itor).first.compare(g_wstrGuarddes) != -1)
				{
					if(g_bIsGuarddes == false)
					{
						++file_itor;
						continue;
					}
				}
			}

			wstrTarget = wstrRet + _T(".zip");

			//이부분에서 인터넷에 있는 파일을 가져온다.
			if(!kFtpMgr.GetFile( wstrTarget, _T(".\\Temp.ftp") ))
			{
				return	false;
			}

			// decry
			// uncompress
			std::vector<char> vecData;
			BM::FileToMem(_T(".\\Temp.ftp"), vecData);
			assert( vecData.size() );

			if ((*file_itor).second.bIsEncrypt)
			{
				std::vector< char > vecSrc;
				vecSrc.resize(vecData.size());
				memcpy(&vecSrc.at(0), &vecData.at(0), vecData.size());
				BM::DecLoadFromMem(vecSrc, vecData);
			}
			if ((*file_itor).second.bIsZipped )
			{
				std::vector<char> vecTemp;
				vecTemp.resize(file_itor->second.org_file_size); // size
				BM::UnCompress(vecTemp, vecData);
				vecData = vecTemp;
			}

			// Temp.ftp -> org file
			std::wstring wstrOrgFilename = wstrOrgPath + (*file_itor).first.c_str();
			BM::ReserveFolder(wstrOrgPath);
			bool bTemp = DeleteFile(wstrOrgFilename.c_str());
			BM::MemToFile(wstrOrgFilename, vecData);

			g_pDlg->SetCurrentDownloadFile( _T(""), 0 );
			g_pDlg->UiUpdate();

			++file_itor;
		}

		++dn_folder_itor;
	}
	DeleteFile(_T("Temp.ftp"));

	return true;
}

//────────────────────────────────────────
//	팩하는 파일 받기
//────────────────────────────────────────
bool DownLoadData(CFTPMgr &kFtpMgr, BM::FolderHash &rkDownloadList, const std::wstring &wstrOrgPackFileName)
{//Patch.TMP 를 만드는것
//5. 더미파일을 만들어 다운받고.(RetHash는 받아야할 파일의 목록이 들어있는 hash.)
	// 받을 사이즈로 파일 예약
	// 패치 데이터를 메모리에 씀(mapping 이라 파일에 바로 기록됨)
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] NonePack 다운 : %s"), _T(__FUNCTION__), __LINE__, wstrOrgPackFileName.c_str());

	g_pDlg->SetActionState(CPatcherDlg::eActionState_Downloading);
	g_pDlg->SetHeadStateText("Download : ");

	size_t data_size = 0;
	BM::FolderHash::iterator folder_itor = rkDownloadList.begin();

	while(folder_itor != rkDownloadList.end())
	{//데이터 사이즈 누적값 계산.
		BM::FileHash &rkFileHash = (*folder_itor).second.kFileHash;
		BM::FileHash::const_iterator file_itor = rkFileHash.begin();

		while(file_itor != rkFileHash.end())
		{	
			if((*file_itor).second.org_file_size)
			{
				if ((*file_itor).second.bIsZipped)
				{
					data_size += (*file_itor).second.zipped_file_size;
				}
				else
				{
					data_size += (*file_itor).second.org_file_size;
				}

				if(file_itor->second.bIsEncrypt)
				{
					data_size += BM::ENC_HEADER_SIZE;
				}
			}
			++file_itor;
		}
		++folder_itor;
	}

//6. ftp에서 다운받을 공간을 예약.
	PgFileMapping kPactchFile;

	// 앞의 폴더를 상대경로로 알맞게
	if (rkDownloadList.size() > 1)
	{
		// 이 함수 들어올때.. size 가 1로 해서 들어오기때문에 assert를 안타야 한다.
		assert(0);
	}

	BM::FolderHash kHeaderHash;
	kHeaderHash.insert(std::make_pair(_T(".\\"), rkDownloadList.begin()->second));
 	const size_t patch_header_size = BM::PgDataPackManager::MakeHeader(_T(".\\Patch.TMP"), kHeaderHash, kPactchFile);

	if(patch_header_size)
	{//받을게 있다.
		kPactchFile.Init(_T(".\\Patch.TMP"), patch_header_size + data_size);//Patch.TMP를 만듬. -> 여기다 다운 받는것임.

	//7. 패치 받을 데이터에 헤더 기록
		char *pPacthSrc = kPactchFile.Data();
		pPacthSrc += patch_header_size;//Seek (Header size)

	//8. ftp에서 파일을 주루룩 받아야함.
		BM::FolderHash::iterator dn_folder_itor = rkDownloadList.begin();
		while(dn_folder_itor != rkDownloadList.end() &&
			g_pDlg->GetIsProcess())
		{	
			const BM::FileHash &rkFileHash = (*dn_folder_itor).second.kFileHash;
		
			BM::FileHash::const_iterator file_itor = rkFileHash.begin();

			// 각각 파일을 받음.
			while(file_itor != rkFileHash.end() &&
				g_pDlg->GetIsProcess())
			{
				INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 다운 : %s"), _T(__FUNCTION__), __LINE__, (*file_itor).first.c_str());

				std::wstring wstrOrgPath = (*dn_folder_itor).first.c_str();

				const std::wstring::size_type pos = wstrOrgPath.find(_T(".\\")) + 2;
				std::wstring wstrTail = wstrOrgPath.substr(pos);
				std::wstring wstrRet = _T(".\\")+ wstrOrgPackFileName +_T("\\")+wstrTail;
				wstrRet += (*file_itor).first.c_str();

				std::wstring kDownFolder;
				std::wstring kDownFileName;
				BM::DivFolderAndFileName(((*file_itor).first.c_str()), kDownFolder, kDownFileName);
				g_pDlg->SetCurrentDownloadFile( kDownFileName, file_itor->second.zipped_file_size );

				// 파일 받기가 실패
				if(!kFtpMgr.GetFile( wstrRet + _T(".zip"), _T(".\\Temp.ftp") ))
				{
					return	false;
				}

				g_pDlg->SetCurrentDownloadFile( _T(""), 0 );
				g_pDlg->UiUpdate();

				std::vector<char> vecTemp;
				BM::FileToMem(_T(".\\Temp.ftp"), vecTemp);
				assert( vecTemp.size() );
				if( vecTemp.size())
				{
					::memcpy(pPacthSrc, &vecTemp.at(0), vecTemp.size());
					pPacthSrc+=vecTemp.size();
				}

				/*
				// 확인 되었음.
				// 직접 바이너리를 파일로 뽑아보면 원본으로 나온다. (아래는 직접 뽑는 코드)
				unsigned __int64 iFileSize = 0;
				if ((*file_itor).second.bIsZipped)
					iFileSize = (*file_itor).second.zipped_file_size;
				else
					iFileSize = (*file_itor).second.org_file_size;
				unsigned __int64 iRecSize = (iFileSize + (((*file_itor).second.bIsEncrypt)?BM::ENC_HEADER_SIZE:0));
				std::vector<char> vecData;
				if ((*file_itor).second.bIsEncrypt)
				{
					std::vector< char > vecSrc;
					vecSrc.resize(iRecSize);
					memcpy(&vecSrc.at(0), &vecTemp.at(0), iRecSize);
					BM::DecLoadFromMem(vecSrc, vecData);
				}
				else
				{
					vecData.resize(iRecSize);
					memcpy(&vecData.at(0), &vecTemp.at(0), iRecSize);
				}

				// 압축 되어 있다면 해제 하기 위해 압축을 푼 파일을 만든다.
				if ( (*file_itor).second.bIsZipped )
				{
					std::vector<char> vecTemp;
					vecTemp.resize((*file_itor).second.org_file_size); // size
					BM::UnCompress(vecTemp, vecData);
					vecData = vecTemp;
				}
				BM::MemToFile(_T("test0.txt"), vecData);
				*/

				++file_itor;
			}

			++dn_folder_itor;
		}
	}
	else
	{
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 다운 할 수 없다"), _T(__FUNCTION__), __LINE__);

		return false;		
	}

	DeleteFile(_T("Temp.ftp"));

	return true;
}

//────────────────────────────────────────
//	팩파일 합치기
//────────────────────────────────────────
bool MergeFile_Pack(CFTPMgr &kFtpMgr
				, const std::wstring &wstrOrgFileName
				, BM::FolderHash &kResultHash//패치된 결과물의 파일 목록
				)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 합치기 : %s"), _T(__FUNCTION__), __LINE__, wstrOrgFileName.c_str());
////////////////////////////////////////////////////////////////////////////////////////////////
//9. 실제 파일에 작업
	g_pDlg->SetActionState(CPatcherDlg::eActionState_Patching);
	g_pDlg->SetHeadStateText( "Processing to combine." );
//	BM::PgDataPackManager::ClearBuffer( _T(".\\") + wstrOrgFileName + _T(".DAT") ); //오리진 계속 사용
//	Ret의 offset 셋팅
	PgFileMapping kTempMapping;
	const unsigned __int64 iResultDataSize = BM::PgDataPackManager::BuildOffset(kResultHash);
	BM::PgDataPackManager::MakeHeader(_T(""), kResultHash, kTempMapping, false);
	kTempMapping.Clear();

	std::wstring wstrOrgDatPath = wstrOrgFileName + _T(".DAT");
	std::wstring wstrOrgDatFolder;
	std::wstring wstrOrgDatFile;
	BM::DivFolderAndFileName(wstrOrgDatPath, wstrOrgDatFolder, wstrOrgDatFile);
	BM::ReserveFolder(wstrOrgDatFolder);

//원래 있던 파일 -> 오리진이 캐쉬에 들어가있음.
	BM::FolderHash kOrgHash;
	const size_t org_header_size = BM::PgDataPackManager::ReadHeader(wstrOrgDatPath, kOrgHash);

	PgFileMapping kOrgFile;
	kOrgFile.Init(wstrOrgDatPath);

//다운받은 파일
	PgFileMapping kPacthFile;

	BM::FolderHash kPatchHash;

	const size_t patch_header_size = BM::PgDataPackManager::ReadHeader( _T(".\\Patch.TMP"), kPatchHash );
	BM::PgDataPackManager::ClearBuffer(_T(".\\Patch.TMP"));

	kPacthFile.Init(_T(".\\Patch.TMP"));

//만들어질 파일(패치후 사이즈)

	PgFileMapping kNewFile;
	const size_t result_header_size = BM::PgDataPackManager::MakeHeader(wstrOrgFileName + _T("_NEW.DAT"), kResultHash, kNewFile);//헤더 빌드

	kNewFile.Init(wstrOrgFileName+_T("_NEW.DAT"), result_header_size + iResultDataSize);//사이즈 예약

//이제 버퍼 돌자.
	char * pTarget = kNewFile.Data();
	pTarget += kNewFile.DataSize();//맨뒤로 Seek

	BM::FolderHash::reverse_iterator ret_folder_ritor = kResultHash.rbegin();
	while(ret_folder_ritor != kResultHash.rend() &&
		g_pDlg->GetIsProcess())//머지 루틴
	{//뒤에서 붙임. //이거하다 PC 꺼지거나 프로세스 종료 하면 으째되냐?
		const BM::FileHash &rkRetFileHash = (*ret_folder_ritor).second.kFileHash;

		BM::FileHash::const_reverse_iterator ret_file_itor = rkRetFileHash.rbegin();
		while(ret_file_itor != rkRetFileHash.rend() &&
			g_pDlg->GetIsProcess())
		{
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 합칠 파일 : %s"), _T(__FUNCTION__), __LINE__, (*ret_file_itor).first.c_str());
			std::wstring wstrFileName;
			std::wstring wstrFolderName;
			BM::DivFolderAndFileName(((*ret_file_itor).first.c_str()), wstrFolderName, wstrFileName);
			std::wstring wstrText = L"Processing to combine: " + wstrFileName;
			g_pDlg->SetHeadStateText(MB(wstrText));

			BM::FolderHash::const_iterator patch_folder_itor = kPatchHash.find((*ret_folder_ritor).first.c_str());//패치데이터 해쉬에서 찾고

			const BM::PgFIleInfo *pFileInfo = NULL;
			char* pSrc = NULL;

			bool bIsFindFromPatchDat = false;
			if(patch_folder_itor != kPatchHash.end())//패치데이터 해쉬에 있나?
			{
				if( (*patch_folder_itor).second.Find((*ret_file_itor).first.c_str(), pFileInfo) )
				{
					bIsFindFromPatchDat = true;
					pSrc = kPacthFile.Data() + patch_header_size + pFileInfo->offset;

					if (!pSrc)
					{
						INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 바이너리 오류 : %ld %ld"), _T(__FUNCTION__), __LINE__, patch_header_size, pFileInfo->offset);
						return false;
					}
				}				
			}
		
			bool bIsFindFromOrgDat = false;
			if(!bIsFindFromPatchDat)
			{
				//BM::FolderHash::const_iterator org_folder_itor = kOrgHash.find((*ret_folder_ritor).first.c_str());
				BM::FolderHash::const_iterator org_folder_itor = kOrgHash.begin();
				if(org_folder_itor != kOrgHash.end())
				{
					if( (*org_folder_itor).second.Find((*ret_file_itor).first.c_str(), pFileInfo) )
					{
						bIsFindFromOrgDat = true;
						pSrc = kOrgFile.Data() + org_header_size + pFileInfo->offset;
						
						if (!pSrc)
						{
							INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 바이너리 오류 : %ld %ld"), _T(__FUNCTION__), __LINE__, patch_header_size, pFileInfo->offset);
							return false;
						}
					}
				}

				if(!bIsFindFromOrgDat)
				{
					INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 패치 파일 손상"), _T(__FUNCTION__), __LINE__);
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
				pTarget -= iRecSize;//기록 사이즈 만큼 offset 이동

				::memcpy(pTarget, pSrc, iRecSize);

				/*
				// 확인 되었음.
				// 직접 바이너리를 파일로 뽑아보면 원본으로 나온다. (아래는 직접 뽑는 코드)
				std::vector<char> vecData;
				if (pFileInfo->bIsEncrypt)
				{
					std::vector< char > vecSrc;
					vecSrc.resize(iRecSize);
					memcpy(&vecSrc.at(0), pSrc, iRecSize);
					BM::DecLoadFromMem(vecSrc, vecData);
				}
				else
				{
					vecData.resize(iRecSize);
					memcpy(&vecData.at(0), pSrc, iRecSize);
				}

				// 압축 되어 있다면 해제 하기 위해 압축을 푼 파일을 만든다.
				if ( pFileInfo->bIsZipped )
				{
					std::vector<char> vecTemp;
					vecTemp.resize(pFileInfo->org_file_size); // size
					BM::UnCompress(vecTemp, vecData);
					vecData = vecTemp;
				}
				BM::MemToFile(_T("test0.txt"), vecData);
				*/

			}
			++ret_file_itor;
		}
		++ret_folder_ritor;
	}

{
	std::vector<char> kTemp;
	kTemp.resize(kNewFile.DataSize());
	memcpy(&kTemp.at(0), kNewFile.Data(), kNewFile.DataSize()); 
}
	BM::PgDataPackManager::ClearBuffer(_T(".\\Patch.TMP")); //캐쉬에서 빼는 함수 작성.

	kOrgFile.Clear();
	kPacthFile.Clear();
	kNewFile.Clear();

	DeleteFile(_T(".\\Patch.TMP"));
	DeleteFile((wstrOrgDatPath).c_str());
	const int ret = _wrename(
				(wstrOrgFileName+_T("_NEW.DAT")).c_str(),
				(wstrOrgDatPath).c_str());

	if(ret != 0)
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 이름 변경 오류 : %s"), _T(__FUNCTION__), __LINE__, (wstrOrgFileName+_T("_NEW.DAT")).c_str());
		assert(NULL);
		return false;
	}

	return true;
}

//────────────────────────────────────────
//	팩 필요 없는 파일 합치기?
//────────────────────────────────────────
bool MergeFile_NonePack(CFTPMgr &kFtpMgr, 
				const std::wstring &wstrTargetDir,
				const std::wstring &wstrOrgFileName,
				BM::FolderHash &kOrgHash,
				BM::FolderHash &kResultHash//패치된 결과물의 파일 목록
				)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 합치기 : %s"), _T(__FUNCTION__), __LINE__, wstrOrgFileName.c_str());

	////////////////////////////////////////////////////////////////////////////////////////////////
//9. 실제 파일에 작업
	g_pDlg->SetActionState(CPatcherDlg::eActionState_Patching);
	g_pDlg->SetHeadStateText( "Processing to combine." );

//	BM::PgDataPackManager::ClearBuffer( _T(".\\") + wstrOrgFileName + _T(".DAT") ); //오리진 계속 사용
//	Ret의 offset 셋팅
	PgFileMapping kTempMapping;
	const unsigned __int64 iResultDataSize = BM::PgDataPackManager::BuildOffset(kResultHash);
	const size_t result_header_size = BM::PgDataPackManager::MakeHeader(_T(""), kResultHash, kTempMapping, false);
	kTempMapping.Clear();

//다운받은 파일
	PgFileMapping kPacthFile;

	BM::FolderHash kPatchHash;

	const size_t patch_header_size = BM::PgDataPackManager::ReadHeader( _T(".\\Patch.TMP"), kPatchHash );
	BM::PgDataPackManager::ClearBuffer(_T(".\\Patch.TMP"));

	kPacthFile.Init(_T(".\\Patch.TMP"));

	//만들어질 파일(패치후 사이즈)
	BM::FolderHash::reverse_iterator ret_ritor = kResultHash.rbegin();
	while(ret_ritor != kResultHash.rend() &&
		g_pDlg->GetIsProcess())//머지 루틴
	{//뒤에서 붙임. //이거하다 PC 꺼지거나 프로세스 종료 하면 으째되냐?
		BM::FolderHash::const_iterator patch_folder_itor = kPatchHash.find((*ret_ritor).first.c_str());
		
		if(patch_folder_itor != kPatchHash.end())
		{
			const BM::PgFolderInfo &rkFolderInfo =  (*patch_folder_itor).second;

			const BM::FileHash &rkFileHash = rkFolderInfo.kFileHash;

			BM::FileHash::const_reverse_iterator file_itor = rkFileHash.rbegin();
			while(file_itor != rkFileHash.rend() &&
				g_pDlg->GetIsProcess())
			{	
				char* pSrc = kPacthFile.Data() + patch_header_size;
				const BM::PgFIleInfo *pFileInfo = &file_itor->second;

				pSrc += pFileInfo->offset;
				unsigned __int64 iFileSize = 0;
				if (pFileInfo->bIsZipped)
				{
					iFileSize = pFileInfo->zipped_file_size;
				}
				else
				{
					iFileSize = pFileInfo->org_file_size;
				}
				unsigned __int64 iRecSize = 0;
				if(iFileSize)
				{
					iRecSize = iFileSize + ((pFileInfo->bIsEncrypt)?(BM::ENC_HEADER_SIZE):0);
				}

				std::wstring wstrFolder = (*patch_folder_itor).first.c_str();

				std::wstring::size_type folder_mark_pos =  wstrFolder.find(_T("."));

				if(std::wstring::npos != folder_mark_pos)
				{
					std::wstring wstrFolderRet = wstrFolder.substr(folder_mark_pos+1);
					std::wstring wstrOutFolder = wstrTargetDir;
					BM::AddFolderMark(wstrOutFolder);
					std::wstring wstrOutFolderName = wstrOutFolder + wstrOrgFileName + wstrFolderRet;
					BM::ReserveFolder(wstrOutFolderName);
					
					std::wstring wstrFileName;
					std::wstring wstrFolderName;
					BM::DivFolderAndFileName(((*file_itor).first.c_str()), wstrFolderName,wstrFileName);
					std::wstring strSaveTargetFileName = wstrOutFolderName;
					//const std::wstring strSaveTargetFileName =  + wstrFolderName + wstrFileName;
					if (wstrFolderName.size() > 2)
						strSaveTargetFileName = strSaveTargetFileName + wstrFolderName.substr(2, wstrFolderName.size()-2);
					BM::ReserveFolder(strSaveTargetFileName);
					strSaveTargetFileName = strSaveTargetFileName + wstrFileName;

					// 복호화를 시도
					std::vector<char> vecData;
					if (file_itor->second.bIsEncrypt)
					{
						std::vector< char > vecSrc;
						vecSrc.resize(iRecSize);
						memcpy(&vecSrc.at(0), pSrc, iRecSize);
						BM::DecLoadFromMem(vecSrc, vecData);
					}
					else
					{
						vecData.resize(iRecSize);
						memcpy(&vecData.at(0), pSrc, iRecSize);
					}

					// 압축 되어 있다면 해제 하기 위해 압축을 푼 파일을 만든다.
					if ( pFileInfo->bIsZipped )
					{
						std::vector<char> vecTemp;
						vecTemp.resize((*file_itor).second.org_file_size); // size
						BM::UnCompress(vecTemp, vecData);
						vecData = vecTemp;
					}

					BM::MemToFile(strSaveTargetFileName, vecData);
				}

				++file_itor;
			}
		}
		++ret_ritor;
	}

	bool bRet =
		BM::PgDataPackManager::ClearBuffer(_T(".\\Patch.TMP")); //캐쉬에서 빼는 함수 작성.

	if (!bRet)
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 파일 손상 : %s"), _T(__FUNCTION__), __LINE__, L"Patch.TMP");
		assert(!"Patch.TMP 파일이 손상");

		return false;
	}

	kPacthFile.Clear();

	DeleteFile(_T(".\\Patch.TMP"));

	return true;
}

// 클라이언트쪽에 불필요한 파일 지우는 함수. (Pack용)
//────────────────────────────────────────
//	팩한 파일에 쓸모없어진 파일 지우기
//────────────────────────────────────────
bool PatchProcess_Pack_OrgErase(CFTPMgr &kFtpMgr, 
								  const std::wstring &wstrTargetDir, 
								  BM::FolderHash &rkOrgFileHash, 
								  BM::FolderHash &rkNewFileHash, 
								  const std::wstring &wstrOrgFileName)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 불필요 파일 삭제 : %s"), _T(__FUNCTION__), __LINE__, wstrOrgFileName.c_str());

	BM::FolderHash kResultHash = rkOrgFileHash;
	// org erase
	BM::FolderHash kEraseHash;
	BM::PgDataPackManager::MakeDiffList(
		kResultHash, 
		rkNewFileHash, 
		kEraseHash, 
		BM::DIFF_ONLY_LEFT );//Org에만 있음.
	if (!kEraseHash.size())
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 불필요 파일 삭제 오류 : %ld"), _T(__FUNCTION__), __LINE__, kEraseHash.size());
		return false;
	}

	// 지우기 루틴
	BM::FolderHash::iterator org_folder_itor = kResultHash.begin();
	while(org_folder_itor != kResultHash.end())
	{
		BM::FolderHash::const_iterator del_folder_itor = kEraseHash.find( (*org_folder_itor).first.c_str() );
		if(del_folder_itor != kEraseHash.end())
		{//헤드 폴더가 있다.
			const BM::FileHash &rkDelFileHash = (*del_folder_itor).second.kFileHash;
			BM::FileHash::const_iterator del_file_itor = rkDelFileHash.begin();
			while( rkDelFileHash.end() != del_file_itor )
			{
				BM::FileHash &_kResultHash = (*org_folder_itor).second.kFileHash;
				// org에서 삭제될 itor
				BM::FileHash::iterator todel_file_itor = _kResultHash.find( (*del_file_itor).first.c_str());
				_kResultHash.erase(todel_file_itor);

				++del_file_itor;
			}
		}
		++org_folder_itor;
	}

	if (!kResultHash.size())
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 불필요 파일 삭제 오류 : %ld"), _T(__FUNCTION__), __LINE__, kResultHash.size());

		return false;
	}

	PgFileMapping kTempMapping;
	const unsigned __int64 iResultDataSize = BM::PgDataPackManager::BuildOffset(kResultHash);
	BM::PgDataPackManager::MakeHeader(_T(""), kResultHash, kTempMapping, false);
	kTempMapping.Clear();

//원래 있던 파일 -> 오리진이 캐쉬에 들어가있음.
	BM::FolderHash kOrgHash;
	const size_t org_header_size =
		BM::PgDataPackManager::ReadHeader(_T(".\\") + wstrOrgFileName + _T(".DAT"), kOrgHash);
	PgFileMapping kOrgFile;
	kOrgFile.Init(_T(".\\") + wstrOrgFileName + _T(".DAT"));

//만들어질 파일(패치후 사이즈)
	PgFileMapping kNewFile;
	const size_t result_header_size =
		BM::PgDataPackManager::MakeHeader( _T(".\\") + wstrOrgFileName + _T("_NEW.DAT"), kResultHash, kNewFile);//헤더 빌드
	kNewFile.Init(_T(".\\") +wstrOrgFileName+_T("_NEW.DAT"), result_header_size + iResultDataSize);//사이즈 예약

//버퍼 돌자
	size_t data_size = result_header_size;
	char * pTarget = kNewFile.Data();

	//kOrgFile
	BM::FolderHash::iterator folder_itor = kResultHash.begin();
	while(folder_itor != kResultHash.end())
	{
		BM::FolderHash::iterator org_folder_itor = rkOrgFileHash.find( (*folder_itor).first.c_str() );

		if(org_folder_itor != rkOrgFileHash.end())
		{//헤드 폴더가 있다.
			BM::FileHash &rkRetFileHash = (*folder_itor).second.kFileHash;
			BM::FileHash::iterator file_itor = rkRetFileHash.begin();

			BM::FileHash &rkOrgFileHash = (*org_folder_itor).second.kFileHash;

			while(file_itor != rkRetFileHash.end())
			{
				// org 필요
				BM::FileHash::iterator org_file_itor = rkOrgFileHash.find( (*file_itor).first.c_str());

				// 저장해야 할 물체의 원본을 찾았다.
				if( rkOrgFileHash.end() != org_file_itor )
				{
					const BM::PgFIleInfo &kFileInfo = (*org_file_itor).second;
					
					// 저장.
					char *pSrc;
					pSrc = kOrgFile.Data() + org_header_size + kFileInfo.offset;
					
					unsigned __int64 iFileSize = 0;
					if (kFileInfo.bIsZipped)
						iFileSize = kFileInfo.zipped_file_size;
					else
						iFileSize = kFileInfo.org_file_size;

					// 저장 할수 있다면 (사이즈가 있다면)
					if(iFileSize)
					{
						unsigned __int64 iRecSize = (iFileSize + ((kFileInfo.bIsEncrypt)?BM::ENC_HEADER_SIZE:0));
						pTarget = kNewFile.Data() + result_header_size + (*file_itor).second.offset;

						::memcpy(pTarget, pSrc, iRecSize);
					}

				}
				++file_itor;
			}

		++org_folder_itor;
		}

		++folder_itor;
	}

	kOrgFile.Clear();
	kNewFile.Clear();

	// rename
	DeleteFile(_T(".\\Patch.TMP"));
	DeleteFile((_T(".\\") + wstrOrgFileName + _T(".DAT")).c_str());
	const int ret = _wrename(
				(_T(".\\") +wstrOrgFileName+_T("_NEW.DAT")).c_str(),
				(_T(".\\") + wstrOrgFileName + _T(".DAT")).c_str());

	if(ret != 0)
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 불필요 파일 삭제 오류 : %s"), _T(__FUNCTION__), __LINE__, (_T(".\\") +wstrOrgFileName+_T("_NEW.DAT")).c_str());
		assert(NULL);
		return false;
	}

	// end org erase

	return true;
}

//────────────────────────────────────────
//	팩하는 파일 패치 프로세스
//────────────────────────────────────────
bool PatchProcess_Pack(CFTPMgr &kFtpMgr, 
					  BM::FolderHash &rkOrgFolderHash, 
					  BM::FolderHash &rkNewFolderHash, 
					  BM::FolderHash &rkServerFolderHash, 
					  const std::wstring &wstrOrgFileName)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 팩 : %s"), _T(__FUNCTION__), __LINE__, wstrOrgFileName.c_str());

	BM::FolderHash::iterator folder_itr = rkNewFolderHash.begin();
	while(folder_itr != rkNewFolderHash.end())
	{
		BM::FileHash &rkRetFileHash = (*folder_itr).second.kFileHash;
		BM::FileHash::iterator file_itor = rkRetFileHash.begin();

		BM::FolderHash kDownHash;
		kDownHash.insert(std::make_pair(folder_itr->first, folder_itr->second));
		// 필요한 파일들 다운로드.
		if(!DownLoadData(kFtpMgr, kDownHash, wstrOrgFileName))
		{
			return false;
		}

		BM::FolderHash::iterator find_itr = rkServerFolderHash.find(folder_itr->first);
		if (find_itr == rkServerFolderHash.end())
		{
			// 이쪽으로 들어올일이 없다.
		}
		BM::FolderHash kResultHash;
		kResultHash.insert(std::make_pair(_T(".\\"), find_itr->second));
		//kResultHash.insert(std::make_pair(find_itr->first, find_itr->second));

		std::wstring kFileName = folder_itr->first;
		BM::DetachFolderMark(kFileName);
		MergeFile_Pack(kFtpMgr, kFileName, kResultHash);//파일 머징

		++folder_itr;
	}
	return true;
}

// 클라이언트쪽에 불필요한 파일 지우는 함수. (NonePack용)
//────────────────────────────────────────
//	쓸모없어진 클라 파일 지우기
//────────────────────────────────────────
bool PatchProcess_NonePack_OrgErase(CFTPMgr &kFtpMgr, 
								  const std::wstring &wstrTargetDir, 
								  BM::FolderHash &rkOrgFileHash, 
								  BM::FolderHash &rkNewFileHash, 
								  const std::wstring &wstrOrgFileName)
{
	BM::FolderHash kEraseHash;
	BM::PgDataPackManager::MakeDiffList(
		rkOrgFileHash, 
		rkNewFileHash, 
		kEraseHash, 
		BM::DIFF_ONLY_LEFT );//Org에만 있음.
	if (!kEraseHash.size())
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 불필요 파일 삭제 오류 : %ld"), _T(__FUNCTION__), __LINE__, kEraseHash.size());

		return false;
	}

	// 지우기 루틴
	BM::FolderHash::iterator erase_itor = kEraseHash.begin();
	while(erase_itor != kEraseHash.end())//머지 루틴
	{//지우기.
		const BM::PgFolderInfo &rkFolderInfo =  (*erase_itor).second;
		const BM::FileHash &rkFileHash = rkFolderInfo.kFileHash;

		BM::FileHash::const_iterator file_itor = rkFileHash.begin();

		while(rkFileHash.end() != file_itor)
		{
			const std::wstring strEraseTargetFileName =
				wstrTargetDir + wstrOrgFileName + _T("\\") + (*file_itor).first.c_str();

			if(!::DeleteFile( strEraseTargetFileName.c_str()))
			{
				const HRESULT hRet = GetLastError();
				INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 불필요 파일 삭제 오류 : %ld"), _T(__FUNCTION__), __LINE__, hRet);
				assert(NULL);
			}
			++file_itor;
		}
		++erase_itor;
	}

	return true;
}

//────────────────────────────────────────
//	팩안하는 패치 프로세스
//────────────────────────────────────────
bool PatchProcess_NonePack(CFTPMgr &kFtpMgr, 
						  BM::FolderHash &rkNewFolderHash, 
						  const std::wstring &wstrOrgFileName)
{
	BM::FolderHash kDownloadHash = rkNewFolderHash;
	
	if(kDownloadHash.size())
	{
		if(!DownLoadData_NonePack(kFtpMgr, kDownloadHash, wstrOrgFileName))
		{
			return	false;
		}
	}
	else
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 다운로드 해시 사이즈 오류 : %ld"), _T(__FUNCTION__), __LINE__, kDownloadHash.size());
		return	false;
	}

	return true;
}

//────────────────────────────────────────
//	시스템 로그
//────────────────────────────────────────
void initLogSystem(std::wstring wstrLogLevel)
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	TCHAR chDir[20];
	_stprintf_s(chDir, 20,_T("Log%d%d%d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	INIT_LOG2(chDir);

	INFO_LOG( BM::LOG_LV7, _T("------------------------------"));
	INFO_LOG( BM::LOG_LV7, _T("log_%04u_%02u_%02u_%02u_%02u_%02u"),
			sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	INFO_LOG( BM::LOG_LV7, _T("------------------------------"));
}

//────────────────────────────────────────
//	패쳐 설정 읽기
//────────────────────────────────────────
void ReadPatcherIni()
{
	TCHAR	szOption[MAX_PATH] = {0,};

	const TCHAR PACK_CONFIG_FILE_NAME[] =  _T(".\\PatcherConfig.ini");

	::GetPrivateProfileString( _T("LOCAL_INFO"), _T("ADDRESS"),	_T(""), szOption, sizeof(szOption), PACK_CONFIG_FILE_NAME);
	g_Addr = szOption;

	g_wPort = (WORD)::GetPrivateProfileInt( _T("LOCAL_INFO"), _T("PORT"),	6390, PACK_CONFIG_FILE_NAME);

	if(g_Locale != LS_CHN)
	{
		//::GetPrivateProfileString( _T("INFO"), _T("ID"),	_T(""), szOption, sizeof(szOption), PACK_CONFIG_FILE_NAME);
		//g_wstrID = szOption;
		g_ID = _T("ap");
		//::GetPrivateProfileString( _T("INFO"), _T("PW"),	_T(""), szOption, sizeof(szOption), PACK_CONFIG_FILE_NAME);
		//g_wstrPW = szOption;
		g_PW = _T("ap1234");
	}

	::GetPrivateProfileString( _T("LOG"), _T("LogLevel"),	_T(""), szOption, sizeof(szOption), PACK_CONFIG_FILE_NAME);
	const std::wstring wstrLogLevel = szOption;
	if (wstrLogLevel.size() > 0 &&
		wstrLogLevel.compare(L"1") != -1)
	{
		initLogSystem(wstrLogLevel);
	}

	char path[MAX_PATH];
	GetModuleFileNameA(GetModuleHandle(0), path, MAX_PATH);
	strrchr( path, '\\' )[1] = 0;
	const std::wstring	wstrDir = UNI(path);

	::GetPrivateProfileString(_T("LOCAL_INFO"), _T("NCGG"), _T(""), szOption, sizeof(szOption), PACK_CONFIG_FILE_NAME);
	const std::wstring wstrGuard = szOption;
	if((wstrGuard.size() > 0) && (wstrGuard.compare(L"1") != -1))
	{
		g_bIsGuardOption = true;

		const std::wstring	wstrGuardini = wstrDir + L"RELEASE\\" + g_wstrGuardini;
		const std::wstring	wstrGuarddes = wstrDir + L"RELEASE\\" + g_wstrGuarddes;

		if(_access(MB(wstrGuardini), 0) == -1)
		{
			g_bIsGuardini = true;
		}

		if(_access(MB(wstrGuarddes), 0) == -1)
		{
			g_bIsGuarddes = true;
		}
	}

	return;
}

//bool CalcCRC(std::wstring wstrDirectory, BM::FolderHash &rkOrgFolderHash, float fTotalPercent)
// FileTotal 이 있으면 파일 갯수로 Percent를 구하고 없지 아니 하면 지정한 TotalPercent로 구한다.
//────────────────────────────────────────
//	CRC 구하기
//────────────────────────────────────────
bool CalcCRC(std::wstring wstrDirectory, BM::FolderHash &rkOrgFolderHash, float fTotalPercent, DWORD &dwFileCount, DWORD dwFileTotal=0)
{
#ifdef PG_USE_ACE
	long lTotalFileCount = 0;

	DWORD time = 0;
	static DWORD threadTimeTotal = 0;
	static DWORD threadTimeCount = 0;
	time = ::GetTickCount();

	::InterlockedExchange(&g_iCRCCount, 0);

	BM::FolderHash::iterator org_itor = rkOrgFolderHash.begin();
	while(org_itor != rkOrgFolderHash.end() &&
		g_pDlg->GetIsProcess())
	{
		BM::FileHash &rkOrgFileHash = (*org_itor).second.kFileHash;
		BM::FileHash::iterator file_itor = rkOrgFileHash.begin();

		while( file_itor != rkOrgFileHash.end() &&
		g_pDlg->GetIsProcess())
		{
			BM::PgFIleInfo &rkFileInfo = (*file_itor).second;
			if (rkFileInfo.org_file_size <= 0)
			{
				continue;
			}

			std::wstring wstrFilename = file_itor->first;
			std::wstring wstrFilePath = wstrDirectory + org_itor->first + file_itor->first;

			int iSlash = -1;
			while( (iSlash = wstrFilePath.find(L".\\")) != -1 )
			{
				wstrFilePath.erase(wstrFilePath.find(L".\\"), 2);
			}
			while( (iSlash = wstrFilePath.find(L"..\\")) != -1 )
			{
				wstrFilePath.erase(wstrFilePath.find(L".\\"), 3);
			}

			::InterlockedIncrement(&g_iCRCCount);
			g_kPatchThread.DoCalcCRC(wstrFilename, wstrFilePath, &rkFileInfo);
			//receive_file_size += rkFileInfo.zipped_file_size;
			//bFind = true;
			lTotalFileCount += 1;

			++file_itor;
		}
		++org_itor;
	}

	if (lTotalFileCount <= 0)
	{
		g_pDlg->DrawProgressBar(0, fTotalPercent);
		return true;
	}

	g_kPatchThread.activate( THR_NEW_LWP| THR_JOINABLE | THR_INHERIT_SCHED, 3);
	g_kPatchThread.IsStop(false);
	float fPercent = 0.0f;

	DWORD dwDrawTime = 0;
	while(g_iCRCCount > 0)
	{
		if (!g_pDlg->GetIsProcess())
		{
			return false;
		}

		Sleep(1);
		dwDrawTime += 1;

		// 일정 시간이 되면 표시해준다.
		if (dwDrawTime > PG_DRAW_TIME)
		{
			dwDrawTime = 0;
			if (dwFileTotal > 0)
			{
				// 읽은 파일 갯수 / 총 파일 * 100
				fPercent = ((float)(dwFileCount + (lTotalFileCount - g_iCRCCount))) / (float)dwFileTotal * 100.0f;
			}
			else
			{
				fPercent = (((float)lTotalFileCount - (float)g_iCRCCount) / (float)lTotalFileCount) * fTotalPercent;
			}
			g_pDlg->DrawProgressBar(0, fPercent);
		}

	}
	g_kPatchThread.IsStop(true);

	threadTimeTotal += ::GetTickCount() - time;
	threadTimeCount++;
	{
		TCHAR temp[1024];
		_stprintf(temp, L"thread time : %d, %f\n", 
			threadTimeCount, (float)threadTimeTotal / (float)threadTimeCount);
		OutputDebugString(temp);
		INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Complete CRC : %s %d"), _T(__FUNCTION__), __LINE__, wstrDirectory.c_str(), threadTimeTotal);
	}

	dwFileCount += lTotalFileCount;
#endif
	return true;
}

//────────────────────────────────────────
//	파일 수 구하기
//────────────────────────────────────────
bool GetFileCount(const std::wstring &rkDirHeader, DWORD &dwFileCount)
{
	//폴더명 끝 컨버팅
	std::wstring kConvDirHeader = rkDirHeader;
	
	BM::ConvFolderMark(kConvDirHeader);

	if(kConvDirHeader.size())
	{
		const wchar_t tLast = kConvDirHeader.at(kConvDirHeader.size()-1);
		if( tLast != _T('\\') 
		&&	tLast != _T('/') )
		{
			kConvDirHeader += _T("\\");
		}
	}

	WIN32_FIND_DATA w32fd = {0,};
	std::wstring kFindDir = kConvDirHeader + _T("*.*");

	HANDLE hFindFile = FindFirstFile(kFindDir.c_str(), &w32fd);
	if(hFindFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	bool bRet = false;

	while(g_pDlg->GetIsProcess()) 
	{
		if(0 != ::_tcsupr_s(w32fd.cFileName) )
		{
			bRet = false;
			break;
		}
		const std::wstring kCurFileName = w32fd.cFileName;//디렉토리 이름일 수도 있다.

		if(w32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{// 디렉토리
			if( kCurFileName != _T(".") 
			&&	kCurFileName != _T("..") 	)
			{
				GetFileCount(kConvDirHeader+kCurFileName, dwFileCount);
			}
		}
		else
		{//일반 파일
			dwFileCount += 1;
		} 
		
		if(FindNextFile(hFindFile, &w32fd) == FALSE)
		{
			bRet = true;
			break;
		}
	}

	FindClose(hFindFile);
	
	return bRet;
}

#define PG_DIV_CALC
typedef stdext::hash_map<std::wstring, BM::FolderHash, BM::stringhasher> FoldersHash;
//────────────────────────────────────────
//	받을 파일 총크기 구하기
//────────────────────────────────────────
size_t GetReceiveTotalSize(BM::FolderHash &kHeadFolder, BM::FolderHash &kToDownloadHash, std::wstring wstrTargetDir)
{
	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 토탈 사이즈 GET : %s"), _T(__FUNCTION__), __LINE__, wstrTargetDir.c_str());

	int iHeadSize = (int)kHeadFolder.size();
	int iHeadCount = 0;
	float fPreparePercent = 0.0f;
	size_t receive_file_size = 0;

	//// 파일 갯수 가져오기
	DWORD dwFileTotal = 0;
	DWORD dwFileCount = 0;

	FoldersHash kOrgFolders;

#ifdef PG_DIV_CALC

	BM::FolderHash::iterator folder_itor = kHeadFolder.begin();
	while(folder_itor != kHeadFolder.end() &&
		g_pDlg->GetIsProcess())
	{
		BM::FolderHash kOrgFolderHash;

		const std::wstring wstrTargetFolder = (*folder_itor).first.c_str();
		const std::wstring wstrOrgFileName = BM::GetLastFolderName(wstrTargetFolder);//확장자 없는것임
		//BM::FolderHash kOrgFileList;

		std::wstring wstrText = L"Get file list in folder: " + wstrTargetFolder;
		g_pDlg->SetHeadStateText(MB(wstrText));

		BM::FolderHash kNewFileList;
		// Root 폴더일 경우. 하위 폴더를 타지 않는다.
		bool bIsRoot = false;
		BM::FolderHash::iterator sv_root_list;
		BM::FolderHash kRootFileList;
		if(folder_itor == kHeadFolder.find(_T(".\\")))
		{
			bIsRoot = true;

			BM::PgDataPackManager::GetFileListWithoutCRC(_T(".\\"), kOrgFolderHash, dwFileTotal, BM::GFL_ONLY_FILE);
		}
		else if((*folder_itor).second.bIsUsePack)
		{
			//GetFileList(_T(".\\")+wstrOrgFileName +_T(".DAT"),  kOrgFolderHash);
		}
		// NonePack 일 경우 그 폴더로 들어가 파일 리스트를 뽑는다.
		else

		{
			std::wstring wstrCurrFolder = wstrTargetFolder;
			BM::AddFolderMark(wstrCurrFolder);
			BM::ReserveFolder(wstrCurrFolder);
			::SetCurrentDirectory(wstrCurrFolder.c_str());

			//현재 내가 가진 파일의 정보를 추출.
			BM::PgDataPackManager::GetFileListWithoutCRC(_T(".\\"), kOrgFolderHash, dwFileTotal);

			::SetCurrentDirectory(_T("..\\"));
		}

		if (kOrgFolderHash.size() > 0)
		{
			kOrgFolders.insert(std::make_pair(wstrTargetFolder, kOrgFolderHash));
		}

		++folder_itor;
	}
#endif

#ifdef PG_DIV_CALC
	folder_itor = kHeadFolder.begin();
#else
	BM::FolderHash::iterator folder_itor = kHeadFolder.begin();
#endif
	while(folder_itor != kHeadFolder.end() &&
		g_pDlg->GetIsProcess())
	{
		iHeadCount += 1;
		fPreparePercent = (float)iHeadCount / (float)iHeadSize * 100.0f;

		BM::AddFolderMark(wstrTargetDir);
		BM::ReserveFolder(wstrTargetDir);
		::SetCurrentDirectory(wstrTargetDir.c_str());

		const std::wstring wstrTargetFolder = (*folder_itor).first.c_str();
		const std::wstring wstrOrgFileName = BM::GetLastFolderName(wstrTargetFolder);//확장자 없는것임
		const std::wstring wstrFileName = wstrOrgFileName + _T("_H_ZIP.DAT");

		std::wstring wstrText = L"Download File List : " + wstrFileName;
		g_pDlg->SetHeadStateText(MB(wstrText));
		if (!g_pkFtpMgr->GetFile( wstrFileName.c_str(), wstrFileName ))
		{
			assert(0);
		}
		// 폴더헤더 다운로드 완료
		BM::FolderHash kNewFileList;

		if (GetFileList(wstrFileName, kNewFileList))
		{
			DeleteFile(wstrFileName.c_str());

			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 리스트 GET : %s"), _T(__FUNCTION__), __LINE__, wstrFileName.c_str());

			// Get org File list
#ifdef PG_DIV_CALC
			BM::FolderHash kOrgFileList;

			FoldersHash::iterator folders_itor = kOrgFolders.begin();
			while(folders_itor != kOrgFolders.end() &&
				g_pDlg->GetIsProcess())
			{
				if ((*folders_itor).first.find(wstrTargetFolder) != -1)
				{
					BM::FolderHash::iterator prepare_itor = (*folders_itor).second.begin();
					while(prepare_itor != (*folders_itor).second.end() &&
						g_pDlg->GetIsProcess())
					{
						kOrgFileList.insert(*prepare_itor);
						++prepare_itor;
					}
					break;
				}
				++folders_itor;
			}
#else
			BM::FolderHash kOrgFileList;
#endif

			bool bIsRoot = false;
			BM::FolderHash::iterator sv_root_list;
			BM::FolderHash kRootFileList;
#ifdef PG_DIV_CALC
			if(folder_itor == kHeadFolder.find(_T(".\\")))
			{
				bIsRoot = true;
				sv_root_list = kNewFileList.find(_T(".\\"));
				kRootFileList.insert(std::make_pair((*sv_root_list).first.c_str(), (*sv_root_list).second));
			}
			else if((*folder_itor).second.bIsUsePack)
			{
				GetFileList(_T(".\\")+wstrOrgFileName +_T(".DAT"),  kOrgFileList);
			}
			else
			{
				// Get CRC and Thread
				if (!CalcCRC(wstrTargetDir + wstrOrgFileName + L"\\", kOrgFileList, fPreparePercent, dwFileCount, dwFileTotal))
				{
					g_pDlg->SetIsProcess(false);
					return false;
				}
			}
#else
	
			// Root 폴더일 경우. 하위 폴더를 타지 않는다.
			if(folder_itor == kHeadFolder.find(_T(".\\")))
			{
				bIsRoot = true;

				BM::PgDataPackManager::GetFileListWithoutCRC(_T(".\\"), kOrgFileList, dwFileTotal, BM::GFL_ONLY_FILE);
				sv_root_list = kNewFileList.find(_T(".\\"));
				kRootFileList.insert(std::make_pair((*sv_root_list).first.c_str(), (*sv_root_list).second));
			}
			else if((*folder_itor).second.bIsUsePack)
			{
				GetFileList(_T(".\\")+wstrOrgFileName +_T(".DAT"),  kOrgFileList);
			}
			// NonePack 일 경우 그 폴더로 들어가 파일 리스트를 뽑는다.
			else
			{
				std::wstring wstrCurrFolder = wstrTargetFolder;
				BM::AddFolderMark(wstrCurrFolder);
				BM::ReserveFolder(wstrCurrFolder);
				::SetCurrentDirectory(wstrCurrFolder.c_str());

				DWORD time = 0;
				static DWORD openTimeTotal = 0;
				static DWORD openTimeCount = 0;
				time = ::GetTickCount();

				//현재 내가 가진 파일의 정보를 추출.
				BM::PgDataPackManager::GetFileListWithoutCRC(_T(".\\"), kOrgFileList, dwFileTotal);
				
				openTimeTotal += ::GetTickCount() - time;
				openTimeCount++;
				{
					TCHAR temp[1024];
					_stprintf(temp, L"time : %d, %f\n", 
						openTimeCount, (float)openTimeTotal / (float)openTimeCount);
					OutputDebugString(temp);
				}

				::SetCurrentDirectory(_T("..\\"));

				// Get CRC and Thread
				if (!CalcCRC(wstrTargetDir + wstrOrgFileName + L"\\", kOrgFileList, fPreparePercent, dwFileCount))
				{
					g_pDlg->SetIsProcess(false);
					return false;
				}
			}
#endif

			BM::FolderHash kResultFileList;
			if (bIsRoot)
				BM::PgDataPackManager::MakeDiffList(
					kOrgFileList, 
					kRootFileList, 
					kResultFileList, 
					BM::DIFF_ONLY_RIGHT | BM::DIFF_ONLY_DIFF);
			else
				BM::PgDataPackManager::MakeDiffList(
					kOrgFileList, 
					kNewFileList, 
					kResultFileList, 
					BM::DIFF_ONLY_RIGHT | BM::DIFF_ONLY_DIFF);
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 파일 리스트 DIFF"), _T(__FUNCTION__), __LINE__);

			// Download에 추가 하기 위한 세팅. 안쓰는듯.
			//BM::FolderHash::iterator org_folder_itor =
			//	kHeadFolder.find(wstrTargetFolder);

			// 정욱 : Pack.exe에서 config.ini에 sub폴더를 use_pack 쓸수 있게 세팅해준다음.
			// 이 아래에서 FolderHash로 kDownFolders를 만들고...
			// 첫번째 while도는중... 서브폴더가 use_pack = true 가 걸려있다면..
			// 재귀적으로 kDownFolders 에 추가 해준다...
			// false가 걸려있으면 그냥...kDownFolder에 넣는다.
			// while을 모두 끝나면 kToDownloadHash에 kDownFolders와 kDownFolder 모두 넣는다.
			BM::PgFolderInfo kDownFolder;
			bool bFind = false;
			BM::FolderHash::iterator result_itor = kResultFileList.begin();
			while(result_itor != kResultFileList.end() &&
				g_pDlg->GetIsProcess())
			{
				BM::FileHash &rkResultFileHash = (*result_itor).second.kFileHash;
				BM::FileHash::iterator file_itor = rkResultFileHash.begin();

				while( file_itor != rkResultFileHash.end() &&
				g_pDlg->GetIsProcess())
				{
					BM::PgFIleInfo &rkFileInfo = (*file_itor).second;
					receive_file_size += rkFileInfo.zipped_file_size;
					bFind = true;
		
					// 파일을 일일이 추가.
					std::wstring wstrAddFilename = result_itor->first + file_itor->first;
					kDownFolder.Insert(wstrAddFilename, rkFileInfo);

					//// 헤더. 안쓰는듯.
					//if (result_itor->first.size() > 2)
					//	wstrAddFilename = result_itor->first + file_itor->first;
					//else
					//	wstrAddFilename = file_itor->first;
					//org_folder_itor->second.Insert(wstrAddFilename,file_itor->second);


					++file_itor;
				}

				kDownFolder.bIsUsePack = (*folder_itor).second.bIsUsePack;

				++result_itor;
			}

			if (bFind)
			{
				kToDownloadHash.insert(std::make_pair(wstrTargetFolder, kDownFolder));
			}

			if (!g_pDlg->GetIsProcess())
			{
				break;
			}
		}
		DeleteFile(wstrFileName.c_str());

		++folder_itor;
	}

	return receive_file_size;
}

// 새로운 패쳐의 CRC가 담긴 patcher.ID 를 받고.
// 현재 실행 프로그램 CRC를 구한것과 비교를 해본다.
// 다를 경우 새로운 패쳐를 받고 patcher.ID 는 지운다.
//────────────────────────────────────────
//	패쳐 패치하기
//────────────────────────────────────────
bool PatcherPatch()
{
	bool bGetNewPatcherId = g_pkFtpMgr->GetFile( _T("patcher.ID"), _T(".\\Patcher_New.ID") );//다운.

	if (!bGetNewPatcherId)
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 패쳐 ID GET Error"), _T(__FUNCTION__), __LINE__);

		return false;
	}

	if (bGetNewPatcherId)
	{
		std::wstring wstrNewCRC;
		wstrNewCRC.resize(PG_PATCHER_CRC_SIZE);

		std::vector<char> vecTemp;
		BM::FileToMem(_T(".\\Patcher_New.ID"), vecTemp);
		if (vecTemp.size())
		{
			char *pIdSrc = new char[vecTemp.size()];
			::memcpy(pIdSrc, &vecTemp.at(0), vecTemp.size());

			//복호화
			int iSize = BM::ENC_HEADER_SIZE + PG_PATCHER_CRC_SIZE;
			std::vector< char > vecDecrypt;
			std::vector< char > vecSrc;
			vecSrc.resize(iSize);
			memcpy(&vecSrc.at(0), pIdSrc, iSize);
			BM::DecLoadFromMem(vecSrc, vecDecrypt);

			::memcpy(&wstrNewCRC.at(0), &vecDecrypt.at(0), PG_PATCHER_CRC_SIZE);
		}
		else
		{
			g_pDlg->SetHeadStateText("Patcher_ID is invalid.");
			INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] Patcher_ID is invalid"), _T(__FUNCTION__), __LINE__);
			
			return false;
		}

		// 새버젼 실행파일을 다운 받자.
		if (wstrNewCRC.compare(g_wstrCRC) != 0)
		{
			g_pDlg->SetHeadStateText("Download new Patcher.");
			Sleep(800);
			//
			// 다운로드 UI 표시하기 위한 세팅
			g_pDlg->SetIsProcess(true);
			// UI 관련 쓰레드 생성
			g_hUiThread = (HANDLE)_beginthreadex( NULL, 0, &UiThread, g_pDlg, 0, 0 );
			g_pDlg->DrawProgressBar(0, 0);
			g_pDlg->SetTotalFileSize(g_pkFtpMgr->GetFileSize( _T("patcher.exe") ));
			g_pDlg->InitClock();
			g_pDlg->SetActionState(CPatcherDlg::eActionState_Downloading);
			g_pDlg->SetHeadStateText("Download : ");
			g_pDlg->SetCurrentDownloadFile( _T("patcher.exe"), g_pkFtpMgr->GetFileSize(L"patcher.exe") );
			//

			bool bGetNewPatcher = g_pkFtpMgr->GetFile( _T("patcher.exe"), _T(".\\patcher2.exe") );//다운.
			if (!bGetNewPatcher)
			{
				g_pDlg->SetHeadStateText("New Patcher get error.");
				INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] New Patcher get error."), _T(__FUNCTION__), __LINE__);
				
				return false;
			}

			// 다운 완료
			g_pDlg->DrawProgressBar(0, 100);
			g_pDlg->SetCurrentDownloadFile( _T(""), 0 );
			g_pDlg->UiUpdate();
			// 완료.

			// 다운 받은 Patcher CRC를 지운다.
			DeleteFile(_T(".\\Patcher_New.ID"));

			// 메시지 표시.
			g_pDlg->SetHeadStateText("Execute new Patcher.");
			Sleep(1500);

			// 실행 파일 이름을 구한다.
			//char path[512];
			//GetModuleFileNameA(GetModuleHandle(0), path, MAX_PATH);
			//if (strlen(path)==0)
			//{
			//	g_pDlg->SetHeadStateText("Execute Dirctory is invalid.");
			//	INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] Execute Dirctory is invalid."), _T(__FUNCTION__), __LINE__);

			//	return false;
			//}
			//std::wstring wstrFolder;
			//std::wstring wstrFile;
			//BM::DivFolderAndFileName(UNI(path),wstrFolder,wstrFile);
			//std::wstring wstrArgument(L"");

			TCHAR szPath[MAX_PATH];
			HRESULT hModuleName = GetModuleFileName(GetModuleHandle(0), szPath, MAX_PATH);
			std::wstring strPath = szPath;
			strPath = strPath.substr(0,strPath.rfind(_T('\\')));
			SetCurrentDirectory(strPath.c_str());

			std::wstring strFileName = strPath + _T("\\patcherpatch.exe");

			// Patcher Patch 실행
			HWND handle = 0;
			HINSTANCE kIns = 		
				ShellExecute(handle,
					_T("open"),
					//_T("patcherpatch.exe"),
					strFileName.c_str(),
					_T(""),
					_T(""),
					SW_SHOWNORMAL);

			g_pkFtpMgr->Close();
			delete g_pkFtpMgr;
			g_pkFtpMgr = 0;
			::CoUninitialize();
			g_hThread = INVALID_HANDLE_VALUE;
			_endthreadex( 0 );

			return true;
		}
	}

	// 다운 받은 Patcher CRC를 지운다.
	DeleteFile(_T(".\\Patcher_New.ID"));

	return true;
}

//────────────────────────────────────────
//	서버의 파일리스트 얻기
//────────────────────────────────────────
bool GetFileListFromServer(const std::wstring &rkLocation, BM::FolderHash &rkFolderHash)
{
	BM::FolderHash kFiles;
	BM::FolderHash kFolders;
	BM::FolderHash kZipFiles;
	g_pkFtpMgr->GetFolderData(rkLocation, kFiles, kFolders, kZipFiles);

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
		GetFileListFromServer(kSubDir, kSubFolders);

		//if (!kSubFolders.size())
		//{
		//	BM::PgFolderInfo kInfo;
		//	kInfo.bIsUsePack = false;
		//	kInfo.kFileHash.clear();
		//	kSubFolders.insert(std::make_pair(kSubDir, kInfo));
		//}

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
		//BM::FolderHash::iterator itr_sub = kSubFolders.begin();
		//while(itr_sub != kSubFolders.end())
		//{
		//	rkFolderHash.insert(std::make_pair(itr_sub->first, itr_sub->second));
		//	++itr_sub;
		//}
		++itr;
	}

	return true;
}

bool DownGuardFile(const BM::FolderHash& HeadList, const std::wstring& FolderName, const std::wstring& GuardFile)
{
	//	리스트검사
	BM::FolderHash::const_iterator	Folder_iter = HeadList.find(FolderName);
	if(Folder_iter == HeadList.end())
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] [가드]리스트에 없는 폴더."), _T(__FUNCTION__), __LINE__);
		return	false;
	}

	const BM::PgFIleInfo*	pFileInfo;
	(*Folder_iter).second.Find(GuardFile, pFileInfo);

	if(!g_pkFtpMgr->GetFile(FolderName + GuardFile + L".zip", L".\\Temp.ftp"))
	{
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] [가드]파일 받기 실패."), _T(__FUNCTION__), __LINE__);
		return	false;
	}

	std::vector<char>	vecData;
	BM::FileToMem(_T(".\\Temp.ftp"), vecData);
	assert(vecData.size());

	if(pFileInfo->bIsEncrypt)
	{
		std::vector< char > vecSrc;
		vecSrc.resize(vecData.size());
		memcpy(&vecSrc.at(0), &vecData.at(0), vecData.size());
		BM::DecLoadFromMem(vecSrc, vecData);		
	}

	if(pFileInfo->bIsZipped)
	{
		std::vector<char> vecTemp;
		vecTemp.resize(pFileInfo->org_file_size); // size
		BM::UnCompress(vecTemp, vecData);
		vecData = vecTemp;
	}

	const std::wstring	FileName = FolderName + GuardFile;
	DeleteFile(FileName.c_str());
	BM::MemToFile(FileName, vecData);
}

//#undef PG_PATCHER_PATCH
//────────────────────────────────────────
//	패치 쓰레드
//────────────────────────────────────────
unsigned __stdcall PatchThread( void* pArguments )
{//암호화를 안하고 패치데이터를 만들 수도 있고.
//확장자별로 암호화 여부를 결정 해야 하기도 하고
	DWORD time = 0;
	static DWORD patchTimeTotal = 0;
	static DWORD patchTimeCount = 0;
	time = ::GetTickCount();

	try
	{
#ifdef PG_USE_ACE
		ACE::init();
#endif
		g_pDlg->SetActionState(CPatcherDlg::eActionState_Downloading);

		BM::CPackInfo kPackInfo;//Init
		if(!kPackInfo.Init())
		{
			assert(NULL);
			return false;
		}
		BM::PgDataPackManager::Init(kPackInfo);

		ReadPatcherIni();

		CoInitialize(NULL);

		LPCWSTR pTargetDir = g_wstrTargetDir.c_str();
		std::wstring wstrTargetDir(pTargetDir);
		BM::ReserveFolder(wstrTargetDir);
		::SetCurrentDirectory(wstrTargetDir.c_str());


		bool bIdDownload	= false;
		bool bToDoRecovery	= true;
		bool bIsConnect		= false;

		if (!g_pkFtpMgr)
		{
			g_pkFtpMgr = new CFTPMgr;

			bIsConnect = g_pkFtpMgr->Connect(g_Addr.c_str(), g_wPort, g_ID.c_str(), g_PW.c_str());
			if(!bIsConnect)
			{
				g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
				
				delete g_pkFtpMgr;
				g_pkFtpMgr = 0;
				::CoUninitialize();
				g_hThread = INVALID_HANDLE_VALUE;
				_endthreadex( 0 );	
				return false;
			}
		}

		// patcher.id 다운, 패쳐 버젼 체크.
#ifdef PG_PATCHER_PATCH
		if (!PatcherPatch())
		{
			INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 패쳐 버젼 체크 실패."), _T(__FUNCTION__), __LINE__);
			g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
			
			delete g_pkFtpMgr;
			g_pkFtpMgr = 0;
			::CoUninitialize();
			g_hThread = INVALID_HANDLE_VALUE;
			_endthreadex( 0 );	
			return false;
		}
#endif
		// patch.id 다운, 복호화.
		bool bGetNewId = g_pkFtpMgr->GetFile( _T("Patch.ID"), _T(".\\Patch_New.ID") );//다운.
		std::vector<char> vecPatchNewID;
		BM::GUID kNewGuid;
		if (bGetNewId)
		{
			BM::FileToMem(_T(".\\Patch_New.ID"), vecPatchNewID);
			DeleteFile(_T(".\\Patch_New.ID"));

			if (vecPatchNewID.size())
			{
				char *pIdSrc = new char[vecPatchNewID.size()];
				::memcpy(pIdSrc, &vecPatchNewID.at(0), vecPatchNewID.size());

				//복호화
				int iSize = BM::ENC_HEADER_SIZE + sizeof(BM::GUID);
				std::vector< char > vecDecrypt;
				std::vector< char > vecSrc;
				vecSrc.resize(iSize);
				memcpy(&vecSrc.at(0), pIdSrc, iSize);
				BM::DecLoadFromMem(vecSrc, vecDecrypt);

				::memcpy(&kNewGuid, &vecDecrypt.at(0), sizeof(BM::GUID));

				bIdDownload = true;
			}
		}
		else
		{
			g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
			
			delete g_pkFtpMgr;
			g_pkFtpMgr = 0;
			::CoUninitialize();
			g_hThread = INVALID_HANDLE_VALUE;
			_endthreadex( 0 );	
			return false;
		}

		if (g_pDlg->GetIsRecovery() || g_fc || g_lc)
		{
			// 복구 할때는 가지고 있던 패치 정보 필요 없음 그냥 패치 하자..
		}
		else
		{
			// ID 다운로드해야만 서버 접속이 성공 되고, 버젼 비교 가능.
			if (bIdDownload)
			{
				std::vector<char> vecOrgId;
				BM::FileToMem(_T(".\\Patch.ID"), vecOrgId);

				if (vecOrgId.size())
				{
					char *pIdSrc = new char[vecOrgId.size()];
					::memcpy(pIdSrc, &vecOrgId.at(0), vecOrgId.size());

					//복호화
					int iSize = BM::ENC_HEADER_SIZE + sizeof(BM::GUID);
					std::vector< char > vecDecrypt;
					std::vector< char > vecSrc;
					vecSrc.resize(iSize);
					memcpy(&vecSrc.at(0), pIdSrc, iSize);
					BM::DecLoadFromMem(vecSrc, vecDecrypt);

					BM::GUID kOrgGuid;
					::memcpy(&kOrgGuid, &vecDecrypt.at(0), sizeof(BM::GUID));

					if ((kOrgGuid == kNewGuid))
					{
						bToDoRecovery = false;
						
						try
						{
							BM::FolderHash	FullHash;

							if((g_bIsGuardini == true) || (g_bIsGuarddes == true))
							{
								if(!g_pkFtpMgr->GetFile(L"HEADFOLDERS.DAT", L".\\HEADFOLDERS.DAT"))
								{
									throw	false;
								}
								BM::PgDataPackManager::ReadHeader(L".\\HEADFOLDERS.DAT", FullHash);

								if(g_bIsGuardini == true)
								{
									if(!DownGuardFile(FullHash, L".\\RELEASE\\", g_wstrGuardini))
									{
										throw	false;
									}
								}

								if(g_bIsGuarddes == true)
								{
									if(!DownGuardFile(FullHash, L".\\RELEASE\\", g_wstrGuarddes))
									{
										throw	false;
									}
								}

								DeleteFile(L"HEADFOLDERS.DAT");
							}
						}
						catch(bool err)
						{
							if(err == true)
							{
								//	넌 천재구나
							}

							g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
							
							delete g_pkFtpMgr;
							g_pkFtpMgr = 0;
							::CoUninitialize();
							g_hThread = INVALID_HANDLE_VALUE;
							_endthreadex( 0 );	
							return false;
						}
					}
				}
			}
		}

		size_t to_receive_totalsize = 0;
		// Dlg 프로세스 준비.
		g_pDlg->SetIsProcess(true);

		// 실제 패치 프로세스.
		// 복구 이거나, 복구가 아닐땐 버젼이 다를경우.
		if (bIdDownload &&
			(g_pDlg->GetIsRecovery() || (bToDoRecovery)) )
		{
			// ! 서버에서 모든 리스트를 가져온다.
			g_pDlg->SetHeadStateText( "Get file list from server." );
			BM::FolderHash kServerList;
			BM::FolderHash::iterator folder_itor;
			{
				std::wstring kHeaders = _T(".\\HEADFOLDERS.DAT");
				bool bGetNewId = g_pkFtpMgr->GetFile( kHeaders, kHeaders );//다운.
				if(!bGetNewId)
				{
					g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
					
					delete g_pkFtpMgr;
					g_pkFtpMgr = 0;
					::CoUninitialize();
					g_hThread = INVALID_HANDLE_VALUE;
					_endthreadex( 0 );	
					return false;
				}
				BM::PgDataPackManager::ReadHeader(kHeaders, kServerList);
				DeleteFile(kHeaders.c_str());
			}

			// ! 리스트에서 NonePack과 UsePack을 나누자.
			BM::FolderHash kServerPackList;
			BM::FolderHash kServerNonePackList;
			folder_itor = kServerList.begin();
			while(folder_itor != kServerList.end() && g_pDlg->GetIsProcess())
			{
				if (folder_itor->second.bIsUsePack)
				{
					kServerPackList.insert(std::make_pair(folder_itor->first, folder_itor->second));
				}
				else
				{
					kServerNonePackList.insert(std::make_pair(folder_itor->first, folder_itor->second));
				}
				++folder_itor;
			}

			// ! 내가 가지고 있는 리스트를 구하자. (NonePack, UsePack Hash를 이용)
			g_pDlg->SetHeadStateText( "Get file list from mine." );
			DWORD dwTotalFile = 0;
			BM::FolderHash kMyNonePackList;

			// NonePack의 리스트를 구한다.
			BM::PgDataPackManager::GetFileListWithoutCRC(_T(".\\"), kMyNonePackList, dwTotalFile);
	
			// Pack의 리스트를 구한다.
			BM::FolderHash kMyPackList;
			folder_itor = kServerPackList.begin();
			while(folder_itor != kServerPackList.end() && g_pDlg->GetIsProcess())
			{
				std::wstring kPackFolder = BM::GetLastFolderName(folder_itor->first);
				std::wstring kPackFileName = kPackFolder + _T(".DAT");
				std::wstring kParentFolder = folder_itor->first;
				BM::AddFolderMark(kParentFolder);
				kParentFolder.replace(kParentFolder.rfind(kPackFolder + _T("\\")), kPackFolder.size() + 1, _T(""));

				// 나의 리스트를 겟.
				BM::FolderHash kMySubPackList;
				if (_access(MB(kParentFolder + kPackFileName), 0) != -1)
				{
					GetFileList(kParentFolder + kPackFileName, kMySubPackList);
				}

				// 나의 리스트에서 first에 해당하는 이름을 Root으로 부터 상대경로로 고쳐주자.
				BM::FolderHash::iterator sub_itr = kMySubPackList.begin();
				while(sub_itr != kMySubPackList.end())
				{
					kMyPackList.insert(std::make_pair(folder_itor->first, sub_itr->second));

					++sub_itr;
				}
				++folder_itor;
			}

			// ! 서버 리스트, 내 리스트 Diff
			g_pDlg->SetHeadStateText( "Files diff mine and server" );
			// NonePack Diff
			// CRC비교 말고 사이즈 비교 부터 한다.
			BM::FolderHash kSameSizeList;	// 똑같은 사이즈: CRC  비교를 해보아야 한다.
			BM::FolderHash kDiffSizeList;	// 사이즈가 다른 파일들: CRC 비교 필요 없음 바로 Result에 대입.
			// CRC를 구한것을 다시 비교한다. MakeDiffList로.
			BM::FolderHash kResultNonePackList;
			SizeDiffList(
				kMyNonePackList,
				kServerNonePackList,
				kSameSizeList,
				kResultNonePackList
				);

			// 사이즈가 같은 파일들은 CRC를 구해보자. 쓰레드로.
			// TODO : Dlg의 Text를 변경해주자. 뭐라고? 음... 'State 구하는 중'
			DWORD dwFileCount;
			CalcCRC(_T(""), kSameSizeList, 100, dwFileCount, 0);

			BM::PgDataPackManager::MakeDiffList(
				kSameSizeList, 
				kServerNonePackList, 
				kResultNonePackList, 
				BM::DIFF_ONLY_RIGHT | BM::DIFF_ONLY_DIFF
				);
			// Pack Diff (얘는 CRC가 그냥 있다. 그래서 쓰레드 돌릴 필요 없음.)
			BM::FolderHash kResultPackList;
			BM::PgDataPackManager::MakeDiffList(
				kMyPackList, 
				kServerPackList, 
				kResultPackList, 
				BM::DIFF_ONLY_RIGHT | BM::DIFF_ONLY_DIFF
				);

			if(g_lc)
			{
				if(kResultPackList.size() || kResultNonePackList.size())
				{
					MessageBox(NULL, L"Client Discord.", L"Error", MB_OK);
					g_pDlg->SetHeadStateText( "Compare Result : Discord" );
					g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);

					delete g_pkFtpMgr;
					g_pkFtpMgr = 0;
					::CoUninitialize();
					g_hThread = INVALID_HANDLE_VALUE;
					_endthreadex( 0 );	
					exit(0);	
				}
			}

			// ! Total Size 계산.
			g_pDlg->SetHeadStateText( "Calculate file size to download" );
			size_t kTotalSize = 0;
			folder_itor = kResultNonePackList.begin();
			while(folder_itor != kResultNonePackList.end() && g_pDlg->GetIsProcess())
			{
				BM::FileHash &rkFileHash = (*folder_itor).second.kFileHash;
				BM::FileHash::iterator file_itor = rkFileHash.begin();
				while(file_itor != rkFileHash.end())
				{
					BM::PgFIleInfo &rkFileInfo = (*file_itor).second;
					kTotalSize += rkFileInfo.zipped_file_size;
					++file_itor;
				}
				++folder_itor;
			}
			folder_itor = kResultPackList.begin();
			while(folder_itor != kResultPackList.end() && g_pDlg->GetIsProcess())
			{
				BM::FileHash &rkFileHash = (*folder_itor).second.kFileHash;
				BM::FileHash::iterator file_itor = rkFileHash.begin();
				while(file_itor != rkFileHash.end())
				{
					BM::PgFIleInfo &rkFileInfo = (*file_itor).second;
					kTotalSize += rkFileInfo.zipped_file_size;
					++file_itor;
				}
				++folder_itor;
			}
			g_pDlg->SetTotalFileSize( kTotalSize );

			// UI 관련 쓰레드 생성
			g_hUiThread = (HANDLE)_beginthreadex( NULL, 0, &UiThread, (CPatcherDlg*)pArguments, 0, 0 );
			g_pDlg->DrawProgressBar(0, 0);
			g_pDlg->InitClock();

			// ! Case에 맞게 다운로드.
			g_pDlg->SetHeadStateText( "Download files." );
			if(!PatchProcess_NonePack(*g_pkFtpMgr, kResultNonePackList, _T("")))
			{
				g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
				
				delete g_pkFtpMgr;
				g_pkFtpMgr = 0;
				::CoUninitialize();
				g_hThread = INVALID_HANDLE_VALUE;
				_endthreadex( 0 );	
				return false;
			}

			if(!PatchProcess_Pack(*g_pkFtpMgr, kMyPackList, kResultPackList, kServerPackList, _T("")))
			{
				g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);

				delete g_pkFtpMgr;
				g_pkFtpMgr = 0;
				::CoUninitialize();
				g_hThread = INVALID_HANDLE_VALUE;
				_endthreadex( 0 );	
				return false;
			}

			::SetCurrentDirectory(pTargetDir);

			if (g_pDlg->GetIsProcess())
			{
				DeleteFile(_T(".\\Patch.ID"));
				BM::MemToFile(_T(".\\Patch.ID"), vecPatchNewID);
			}
		}

		DeleteFile(_T(".\\Patch_New.ID"));
		if (!g_pDlg->GetIsProcess())
		{
			g_pDlg->SetHeadStateText( "User called to stop." );
			g_pDlg->SetActionState(CPatcherDlg::eActionState_Prepare);
		}
		else
		{
			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 패치 완료"), _T(__FUNCTION__), __LINE__);
			if (to_receive_totalsize)
				g_pDlg->SetHeadStateText( "Patch was completed." );
			else
					g_pDlg->SetHeadStateText( "It's the latest version." );
			g_pDlg->DrawProgressBar(0, 100);
			g_pDlg->DrawProgressBar(1, 100);
			g_pDlg->SetRemainTimeText("Complete");
			g_pDlg->SetIsProcess(false);
			g_pDlg->SetActionState(CPatcherDlg::eActionState_Complete);
			g_pDlg->PatchComplete();

			INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 패치완료후 로케일 : %d"), _T(__FUNCTION__), __LINE__, g_Locale);

			if(g_Locale == LS_CHN)
			{
				//char path[MAX_PATH];

				//GetModuleFileNameA(GetModuleHandle(0), path, MAX_PATH);
				//if (strlen(path)==0)
				//{
				//	INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 모듈 핸들 가져오기 실패"), _T(__FUNCTION__), __LINE__);
				//	return false;
				//}
				//strrchr( path, '\\' )[1] = 0;
				//SetCurrentDirectoryA(path);

				TCHAR szPath[MAX_PATH];
				HRESULT hModuleName = GetModuleFileName(GetModuleHandle(0), szPath, MAX_PATH);
				std::wstring strPath = szPath;
				strPath = strPath.substr(0,strPath.rfind(_T('\\')));
				SetCurrentDirectory(strPath.c_str());

				INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 현재 디렉토리 지정: %s"), _T(__FUNCTION__), __LINE__, strPath.c_str());

				std::wstring strFileName = strPath + _T("\\Launcher.exe");

				HWND handle = 0;
				HINSTANCE kIns = 		
					ShellExecute(handle,
						_T("open"),
						//_T("Launcher.exe"),
						strFileName.c_str(),
						_T(""),
						//UNI(path),
						strPath.c_str(),
						SW_SHOWNORMAL);

				const HRESULT hRet = GetLastError();

				INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 런처 실행 : %d"), _T(__FUNCTION__), __LINE__, hRet);
				TCHAR szCurdir[300]={0,};
				::GetCurrentDirectory(300, szCurdir);
				INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 현재 디렉토리 : %s"), _T(__FUNCTION__), __LINE__, szCurdir);


				Sleep(100);
				exit(0);
			}
		}

#ifdef PG_USE_ACE
		g_kPatchThread.IsStop(true);
		ACE::fini();
#endif

		g_pkFtpMgr->Close();
		delete g_pkFtpMgr;
		g_pkFtpMgr = 0;
		::CoUninitialize();
		g_hThread = INVALID_HANDLE_VALUE;

		patchTimeTotal += ::GetTickCount() - time;
		patchTimeCount++;
		{
			TCHAR temp[1024];
			_stprintf(temp, L"patch_time : %d, %f\n", 
				patchTimeCount, (float)patchTimeTotal / (float)patchTimeCount);
			OutputDebugString(temp);
		}

		_endthreadex( 0 );
	} // end of try
	catch (CSystemException* e)
	{
		DeleteFile(_T("Temp.ftp"));
		DeleteFile(_T("Patch.TMP"));
		SETDIR_ERROR_REPORT(TEXT("./Log"));
		TCHAR wcause[256];
		e->GetErrorMessage(wcause, 256);
		//FORMAT_ERROR_REPORT(e->mExceptInfo->ExceptionRecord->ExceptionCode, wcause, TEXT(""), 0);
		e->WriteAdditionalInfo();
		INFO_LOG( BM::LOG_LV5, _T("[%s]-[%d] 패쳐 실패 : %s"), _T(__FUNCTION__), __LINE__, wcause);
		delete e;
	}

	return true;
}

//────────────────────────────────────────
//	유아이 쓰레드
//────────────────────────────────────────
unsigned __stdcall UiThread( void* pArguments )
{
	while(g_pDlg->GetIsProcess())
	{
		Sleep(1);
		
		if (g_pkFtpMgr)
		{
			if ( g_pDlg->GetReceiveCurrentFileSize() !=
				g_pkFtpMgr->GetReceiveFileSize() )
			{
				g_pDlg->SetReceiveCurrentFileSize( g_pkFtpMgr->GetReceiveFileSize() );
				g_pDlg->UiUpdate();
			}
		}
	}
	
	if (g_pkFtpMgr)
		g_pkFtpMgr->ConnectionState(false);

	_endthreadex( 0 );	
	return true;
}

//────────────────────────────────────────
//	패치 프로세스 시작
//────────────────────────────────────────
void DoPatchProcess(LPCWSTR pTargetDir, void *pDlg)
{
	static Loki::Mutex local_mutex;
	BM::CAutoMutex lock(local_mutex);
    
	if( g_hThread == INVALID_HANDLE_VALUE)
	{
		unsigned threadID;
		g_pDlg = (CPatcherDlg*)pDlg;

		g_wstrTargetDir = pTargetDir;

		g_hThread = (HANDLE)_beginthreadex( NULL, 0, &PatchThread, pDlg, 0, &threadID );
	}
	else
	{
		MessageBox(NULL, _T("Already running patch process."),_T(""),0);
	}
}

//────────────────────────────────────────
//	종료
//────────────────────────────────────────
void DoExit()
{
	if( g_hThread == INVALID_HANDLE_VALUE)
	{
		exit(0);
	}
}