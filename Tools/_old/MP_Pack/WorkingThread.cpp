#include	"defines.h"
#include	"WorkingThread.h"
#include	"PFile.h"
#include	"SimpEnc/SimpEnc.h"
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿詭檣 蝶溯萄
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
unsigned __stdcall DiffToPack(void* pArgument)
{
	//InitLogSystem();

	try
	{
		//	蛤Щ蒂 ж濠
		if(!DiffCore(g_PackProcess.GetOrgFolder(), g_PackProcess.GetCrtFolder(), 
					 g_PackProcess.GetOutFolder() + L"\\DiffResult"))
		{
			throw	false;
		}

		//	ね擊 ж濠
		if(!PackCore(g_PackProcess.GetOrgFolder(), g_PackProcess.GetOutFolder()))
		{
			throw	false;
		}

		//	葬蝶お蒂 虜菟濠
		if(!ListCore(g_PackProcess.GetOrgFolder(), g_PackProcess.GetCrtFolder(), 
					 g_PackProcess.GetOutFolder()))
		{
			return	false;
		}

		//	贗塭ね 虜菟濠
		if(g_PackProcess.GetWork() == CPackProcess::eWork_BindPack)
		{
			if(!BindCore(g_PackProcess.GetOrgFolder(), g_PackProcess.GetOutFolder()))
			{
				return	false;
			}
		}

		//	衛葬鍔煎 ぬ纂蒂 虜菟濠
		if(g_PackProcess.GetWork() == CPackProcess::eWork_SeriesPatch)
		{
			if(!SeriesPatch(g_PackProcess.GetOrgFolder() + L"\\", g_PackProcess.GetCrtFolder(), 
							g_PackProcess.GetOutFolder() + L"\\"))
			{
				return	false;
			}
		}
	}
	catch(bool Failed)
	{
		if(Failed != false)
		{
			g_PackProcess.SetStateText(L"U HEAD. GOD HEAD!.");
		}

		g_PackProcess.ThreadClear();
		g_PackProcess.SetProcState(CPackProcess::eProcess_Prepare);
		if(g_PackProcess.GetIsAuto())
		{
			exit(0);
		}
		return	false;
	}

	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Щ煎撮蝶 謙猿"), _T(__FUNCTION__), __LINE__);
	g_PackProcess.SetStateText(L"Complete.");
	g_PackProcess.SetProcState(CPackProcess::eProcess_Prepare);
	if(g_PackProcess.GetIsAuto())
	{
		exit(0);
	}
	g_PackProcess.ThreadClear();
	return	true;
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	衛蝶蠱 煎斜
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
void InitLogSystem()
{
//	SYSTEMTIME sysTime;
//	GetLocalTime(&sysTime);
//	TCHAR chDir[20];
//	_stprintf_s(chDir, 20,_T("Log%d%d%d%d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour);
//	INIT_LOG2(chDir);

//	INFO_LOG( BM::LOG_LV7, _T("------------------------------"));
//	INFO_LOG( BM::LOG_LV7, _T("log_%04u_%02u_%02u_%02u_%02u_%02u"),
//			sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
//	INFO_LOG( BM::LOG_LV7, _T("------------------------------"));
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿Diff 婦溼 л熱
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	蛤Щ 婦葬
bool DiffCore(const std::wstring& DestFolder, const std::wstring& SourFolder,
			  const std::wstring& OutputFolder)
{
	//	Diff ж濠.
	if(g_PackProcess.GetWork() & CPackProcess::eWork_Diff)
	{
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Diff Щ煎撮蝶"), _T(__FUNCTION__), __LINE__);
		//	鼠歙擊 綠掖 ж釭?
		if(!g_PackProcess.GetIsPackToDir())
		{
			//	ィ渦 渠 ィ渦
			//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] ィ渦 渠 ィ渦"), _T(__FUNCTION__), __LINE__);
			if(!FolderToFolderDiff(DestFolder, SourFolder, OutputFolder))
			{
				return	false;
			}
		}
		else
		{
			//	ね 渠 ィ渦
			//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] ね 渠 ィ渦"), _T(__FUNCTION__), __LINE__);
			if(!PackToFolderDiff(DestFolder, SourFolder, OutputFolder))
			{
				return	false;
			}
		}
	}

	return	true;
}

//	ィ渦諦 ィ渦
bool FolderToFolderDiff(const std::wstring& DestFolder, const std::wstring& SourFolder, 
						const std::wstring& OutFolder, const std::wstring& SubFolder)
{
	g_PackProcess.SetStateText(L"Folder Seek");

	//	熱薑ィ渦曖 等檜顫
	std::wstring	wstrDestDir	= DestFolder + SubFolder;
	BM::FolderHash	kDestFolderHash;
	BM::FolderHash	kDestFileHash;

	BM::AddFolderMark(wstrDestDir);
	if(!FolderSeek(wstrDestDir, SubFolder, kDestFileHash, kDestFolderHash))
	{
		return	false;
	}

	//	錳獄ィ渦曖 等檜顫
	std::wstring	wstrSourDir	= SourFolder + SubFolder;
	BM::FolderHash	kSourFolderHash;
	BM::FolderHash	kSourFileHash;

	BM::AddFolderMark(wstrSourDir);
	if(!FolderSeek(wstrSourDir, SubFolder, kSourFileHash, kSourFolderHash))
	{
		return	false;
	}

	//	唸婁 轎溘ィ渦
	std::wstring	wstrOutFolder = OutFolder + SubFolder;
	BM::AddFolderMark(wstrOutFolder);

	//	匐餌瞪縑 CRC
	g_PackProcess.SetStateText(L"File Info Update");
	if(kDestFileHash.size())
	{
		if(kSourFileHash.size())
		{
			//	だ橾 匐餌
			DiffFile(wstrDestDir, wstrOutFolder, 
					 kDestFileHash.begin()->second->kFileHash,
					 kSourFileHash.begin()->second->kFileHash);
		}
		else
		{
			//	だ橾 犒餌
			CopyFiles(wstrDestDir, wstrOutFolder, kDestFileHash.begin()->second->kFileHash);
		}
	}

	//	ж嬪 ィ渦 匐餌
	if(kDestFolderHash.size())
	{
		BM::FolderHash::iterator	Dest_iter = kDestFolderHash.begin();
		while(Dest_iter != kDestFolderHash.end())
		{
			g_PackProcess.SetStateText(L"Folder : " + (*Dest_iter).first);

			BM::FolderHash::iterator	Sour_iter = kSourFolderHash.find((*Dest_iter).first);
			std::wstring	wstrSubFolder = SubFolder + (*Dest_iter).first;
			wstrSubFolder.erase(wstrSubFolder.find(_T(".\\")), 2);

			if(Sour_iter == kSourFolderHash.end())
			{
				CopyNewFolder(DestFolder, OutFolder, wstrSubFolder);
			}
			else
			{
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Folder : %s"), _T(__FUNCTION__), __LINE__, wstrSubFolder.c_str());
				const bool bResult = FolderToFolderDiff(DestFolder, SourFolder, OutFolder, wstrSubFolder);
				if(bResult == false)
				{
					return	false;
				}
			}

			++Dest_iter;
		}
	}

	return	true;
}

//	ね婁 ィ渦 綠掖
bool PackToFolderDiff(const std::wstring& DestFolder, const std::wstring& SourFolder, 
					  const std::wstring& OutputFolder, const std::wstring& SubFolder)
{
	//	葬蝶お 儅撩
	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 葬蝶お 儅撩"), _T(__FUNCTION__), __LINE__);
	if(!CreateList(DestFolder))
	{
		return	false;
	}

	//	葬蝶お 煽м
	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 葬蝶お 煽м"), _T(__FUNCTION__), __LINE__);
	if(!ListMerge(DestFolder + SubFolder, L"HEADFOLDERS.DAT"))
	{
		return	false;
	}

	//	葬蝶お 綠掖
	if(!DiffList(DestFolder + SubFolder, SourFolder + SubFolder, OutputFolder + SubFolder))
	{
		return	false;
	}

	return	true;
}

//	葬蝶お 綠掖
bool DiffList(const std::wstring& DestFolder, const std::wstring& SourFolder,
			  const std::wstring& OutputFolder)
{
	//	п蓮
	BM::FolderHash		HeadDestList;
	BM::FolderHash		HeadSourList;

	//	煎萄
	ReadList(DestFolder, HeadDestList, L"HEADFOLDERS.DAT");
	ReadList(SourFolder, HeadSourList, L"HEADFOLDERS.DAT");

	//	譆鼻 唳煎
	const std::wstring	DestDir	= CutDir(HeadDestList);
	const std::wstring	SourDir	= CutDir(HeadSourList);

	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Header Diff"), _T(__FUNCTION__), __LINE__);

	//	檗橫菟檣啪 氈朝陛
	if(HeadDestList.size() && HeadSourList.size())
	{
		BM::FolderHash::iterator	Dest_iter = HeadDestList.begin();
		while(Dest_iter != HeadDestList.end())
		{
			//	模蝶 酈高戲煎 滲唳
			//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Key Setting"), _T(__FUNCTION__), __LINE__);
			std::wstring	KeyFolder = (*Dest_iter).first;
			KeyFolder.erase(KeyFolder.find(DestDir), DestDir.size());
			KeyFolder = SourDir + KeyFolder;

			//	ィ渦 瓊晦
			BM::FolderHash::iterator	Sour_iter = HeadSourList.find(KeyFolder);

			//	鼻渠 唳煎煎 滲唳
			KeyFolder.erase(KeyFolder.find(SourDir), SourDir.size());

			if(Sour_iter == HeadSourList.end())
			{
				//	蹺陛脹 ィ渦棻
				CopyNewFolder(DestFolder + KeyFolder, OutputFolder + KeyFolder, L"");
			}
			else
			{
				//	だ橾擊 綠掖
				DiffFile(DestFolder + KeyFolder, OutputFolder + KeyFolder,
						 (*Dest_iter).second->kFileHash,
						 (*Sour_iter).second->kFileHash);
			}

			++Dest_iter;
		}
	}
	else
	{
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Not File"), _T(__FUNCTION__), __LINE__);
		return	false;
	}

	return	true;
}

//	譆鼻 瑞お 憲嬴頂晦
std::wstring CutDir(const BM::FolderHash& TargetHash)
{
	BM::FolderHash		FolderHash;
	std::wstring		FolderName = TargetHash.begin()->first;
	BM::FolderHash::const_iterator	iter = TargetHash.begin();
	for(;iter != TargetHash.end(); ++iter)
	{
		if(FolderName.size() > (*iter).first.size())
		{
			FolderName = (*iter).first;
		}
	}

	return	FolderName;
}

//	だ橾擊 綠掖
void DiffFile(const std::wstring& DestFolder, const std::wstring& OutFolder, 
			  const BM::FileHash& DestHash, const BM::FileHash& SourHash)
{
	if(DestHash.size())
	{
		//	綠掖 衛濛
		BM::FileHash::const_iterator	Dest_iter = DestHash.begin();
		while(Dest_iter != DestHash.end())
		{
			//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Compare : %s"), _T(__FUNCTION__), __LINE__, (*Dest_iter).first.c_str());

			if(SourHash.size())
			{
				//	匐儀
				BM::FileHash::const_iterator	Sour_iter = SourHash.find((*Dest_iter).first);

				if(Sour_iter == SourHash.end())
				{
					//	だ橾檜 橈朝等 蹺陛腎歷釭.
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] New Add File"), _T(__FUNCTION__), __LINE__);
					OutputFile(DestFolder, OutFolder, (*Dest_iter).first);
				}
				else
				{
					g_PackProcess.SetStateText(L"File Compare > " + (*Dest_iter).first);

					//	だ橾檜 氈朝等 觼晦陛 棻腦啻.
					if((*Dest_iter).second != (*Sour_iter).second)
					{
						OutputFile(DestFolder, OutFolder, (*Dest_iter).first);
					}
				}
			}
			else
			{
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] New Add File"), _T(__FUNCTION__), __LINE__);
				OutputFile(DestFolder, OutFolder, (*Dest_iter).first);
			}

			++Dest_iter;
		}
	}
	else
	{
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Not File"), _T(__FUNCTION__), __LINE__);
	}
}

//	億煎遴 ィ渦 犒餌
bool CopyNewFolder(const std::wstring& TargetFolder, const std::wstring& OutFolder, const std::wstring& SubFolder)
{
	g_PackProcess.SetStateText(L"Folder Copy");

	//	顫啃 ィ渦
	std::wstring	wstrTargetDir	= TargetFolder + SubFolder;
	BM::FolderHash	kTargetFolderHash;
	BM::FolderHash	kTargetFileHash;

	BM::AddFolderMark(wstrTargetDir);
	if(!FolderSeek(wstrTargetDir, SubFolder, kTargetFileHash, kTargetFolderHash))
	{
		return	false;
	}

	//	轎溘 ィ渦 儅撩
	std::wstring	wstrOutFolder = OutFolder + SubFolder;
	BM::AddFolderMark(wstrOutFolder);
	BM::ReserveFolder(wstrOutFolder);

	//	だ橾檜 氈戲賊 犒餌
	if(kTargetFileHash.size())
	{
		CopyFiles(wstrTargetDir, wstrOutFolder, kTargetFileHash.begin()->second->kFileHash);
	}


	//	ж嬪 ィ渦陛 氈戲賊 犒餌
	if(kTargetFolderHash.size())
	{
		BM::FolderHash::iterator	Target_iter = kTargetFolderHash.begin();
		while(Target_iter != kTargetFolderHash.end())
		{
			std::wstring	wstrSubFolder	= SubFolder + (*Target_iter).first;
			wstrSubFolder.erase(wstrSubFolder.find(_T(".\\")), 2);
			CopyNewFolder(TargetFolder, OutFolder, wstrSubFolder);
			++Target_iter;
		}
	}

	return	true;
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿Pack 婦溼 л熱
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
bool PackCore(const std::wstring& TargetFolder, const std::wstring& OutputFolder)
{
	//	Pack 瑞ず
	if(g_PackProcess.GetWork() & CPackProcess::eWork_Pack)
	{
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Pack Щ煎撮蝶"), _T(__FUNCTION__), __LINE__);
		//	ね曖 謙盟縑 評塭憮
		std::wstring	wstrPackFolder	= TargetFolder;

		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] ねィ渦 撲薑"), _T(__FUNCTION__), __LINE__);
		if(g_PackProcess.GetWork() == CPackProcess::eWork_AllProcess)
		{
			if(!g_PackProcess.GetIsFullPack())
			{
				//	翕衛霞ч檣等 睡碟ね檜賊
				wstrPackFolder = OutputFolder + L"\\DiffResult";
			}
		}

		//	ね擊 褒ч
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] ね"), _T(__FUNCTION__), __LINE__);
		if(!PackProcess(wstrPackFolder, OutputFolder+ L"\\PackResult"))
		{
			return	false;
		}
	}

	return	true;
}

//	ね擊 儅撩
bool PackProcess(const std::wstring& TargetFolder, const std::wstring& OutputFolder, 
				 const std::wstring& SubFolder, const bool bIsPack)
{
	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Diff Щ煎撮蝶"), _T(__FUNCTION__), __LINE__);

	g_PackProcess.SetStateText(L"Folder Seek");

	//	顫啃ィ渦曖 等檜顫
	std::wstring	wstrTargetDir	= TargetFolder + SubFolder;
	wstrTargetDir.erase(wstrTargetDir.find(_T(".\\")), 1);
	BM::FolderHash	kTargetFolderHash;
	BM::FolderHash	kTargetFileHash;

	BM::AddFolderMark(wstrTargetDir);
	if(!FolderSeek(wstrTargetDir, SubFolder, kTargetFileHash, kTargetFolderHash))
	{
		return	false;
	}

	//	唸婁 轎溘ィ渦
	std::wstring	wstrOutFolder = OutputFolder + SubFolder;
	wstrOutFolder.erase(wstrOutFolder.find(_T(".\\")), 1);
	BM::AddFolderMark(wstrOutFolder);
	BM::ReserveFolder(wstrOutFolder);

	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Pack From %s"), _T(__FUNCTION__), __LINE__, wstrTargetDir.c_str());
	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Pack To   %s"), _T(__FUNCTION__), __LINE__, wstrOutFolder.c_str());

	//	匐餌瞪縑 寰瞪匐餌
	if(kTargetFileHash.size())
	{
		//	だ橾 ね
		const bool bResult = PackFile(wstrTargetDir, wstrOutFolder, kTargetFileHash.begin()->second->kFileHash);
		if(bResult == false)
		{
			g_PackProcess.SetStateText(L"Pack : File Packing Failed");
			return	false;
		}

		//	ィ渦 撲薑
		kTargetFileHash.begin()->second->bIsUsePack = bIsPack;

		//	だ橾薑爾 盪濰
		if(!CreateHashFile(wstrOutFolder + _T("_FILES.PGH"), kTargetFileHash))
		{
			return	false;
		}
	}

	//	ж嬪 ィ渦 匐餌
	if(kTargetFolderHash.size())
	{
		BM::FolderHash::iterator	Dest_iter = kTargetFolderHash.begin();
		while(Dest_iter != kTargetFolderHash.end())
		{
			std::wstring	wstrSubFolder = SubFolder + BM::GetLastFolderName((*Dest_iter).first);
			BM::AddFolderMark(wstrSubFolder);
			g_PackProcess.SetStateText(L"Recursive Folder > " + wstrSubFolder);

			const bool bResult = PackProcess(TargetFolder, OutputFolder, wstrSubFolder, 
											 (*Dest_iter).second->bIsUsePack);
			if(bResult == false)
			{
				return	false;
			}
			++Dest_iter;
		}

		//	ィ渦薑爾 盪濰
		if(!CreateHashFile(wstrOutFolder + _T("_FOLDERS.PGH"), kTargetFolderHash))
		{
			return	false;
		}
	}

	return	true;
}

//	だ橾擊 ねж濠
bool PackFile(const std::wstring& DestFolder, const std::wstring& OutFolder, BM::FileHash& FileHash)
{
	if(FileHash.size())
	{
		BM::FileHash::iterator	File_iter = FileHash.begin();
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Pack Dest %s"), _T(__FUNCTION__), __LINE__, DestFolder.c_str());
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Pack Out  %s"), _T(__FUNCTION__), __LINE__, OutFolder.c_str());

		//	だ橾 ね
		while(File_iter != FileHash.end())
		{
			g_PackProcess.SetStateText(L"Pack : File Packing > " + (*File_iter).first);

			std::vector<char>	kFileData;
			std::vector<char>	kZippedData;

			//	だ橾 煎萄
			//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File : %s"), _T(__FUNCTION__), __LINE__, (*File_iter).first.c_str());
			if(BM::FileToMem((*File_iter).first, kFileData))
			{
				/*
				//	憶蹴
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File To Mem Success"), _T(__FUNCTION__), __LINE__);
				if(BM::Compress(kFileData, kZippedData))
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Zipped File"), _T(__FUNCTION__), __LINE__);
					(*File_iter).second.bIsZipped = true;
					(*File_iter).second.zipped_file_size = kZippedData.size();	
				}
				else
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Normal File"), _T(__FUNCTION__), __LINE__);
					(*File_iter).second.bIsZipped = false;
					(*File_iter).second.zipped_file_size = (*File_iter).second.org_file_size;
					kZippedData = kFileData;
				}

				//	懍���� 盪濰
				if((*File_iter).second.bIsEncrypt)
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Encrypt : %s"), _T(__FUNCTION__), __LINE__, (*File_iter).first.c_str());
					BM::EncSave(OutFolder + (*File_iter).first + _T(".zip"), kZippedData);
				}
				else
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Normal : %s"), _T(__FUNCTION__), __LINE__, (*File_iter).first.c_str());
					BM::MemToFile(OutFolder + (*File_iter).first + _T(".zip"), kZippedData);
				}
				*/
				//	憶蹴
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File To Mem Success"), _T(__FUNCTION__), __LINE__);
				if(BM::Compress(kFileData, kZippedData))
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Zipped File"), _T(__FUNCTION__), __LINE__);
					(*File_iter).second.bIsZipped = true;
					(*File_iter).second.zipped_file_size = kZippedData.size();	
				}
				else
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Normal File"), _T(__FUNCTION__), __LINE__);
					(*File_iter).second.bIsZipped = false;
					(*File_iter).second.zipped_file_size = (*File_iter).second.org_file_size;
					kZippedData = kFileData;
				}

				//	懍���� 盪濰
				if((*File_iter).second.bIsEncrypt)
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Encrypt : %s"), _T(__FUNCTION__), __LINE__, (*File_iter).first.c_str());
					//BM::EncSave(OutFolder + (*File_iter).first + _T(".zip"), kZippedData);
					std::fstream ffile;
					std::wstring const& strFileName = OutFolder + (*File_iter).first + _T(".zip");
					ffile.open( strFileName.c_str(), std::ios_base::out | std::ios_base::trunc | std::ios_base::ate | std::ios_base::binary );//in 賅萄歜.
					if(!ffile.is_open())
					{
						return false;
					}
					else
					{
						std::vector< char > vecEncryptInfo;

						/*
						CEL::CPacket kCompressInfo;

						kCompressInfo.Push((*File_iter).second.org_file_size);//憶蹴瞪 餌檜鍔.
						kCompressInfo.Push((*File_iter).second.zipped_file_size);//憶蹴�� 餌檜鍔.
						kCompressInfo.Push((*File_iter).second.bIsZipped);//憶蹴罹睡 盪濰.

						BM::EncStream(kCompressInfo.Data(), vecEncryptInfo);
						size_t write_offset = 0;

						ffile.seekp(write_offset);
						ffile.write(&vecEncryptInfo.at(0), vecEncryptInfo.size());
						write_offset += vecEncryptInfo.size();

						ffile.seekp(write_offset);
						ffile.write(&kCompressInfo.Data().at(0), kCompressInfo.Data().size());
						write_offset += kCompressInfo.Data().size();
						*/
						BM::EncStream(kZippedData, vecEncryptInfo);
						
						size_t write_offset = 0;
						ffile.seekp(write_offset);
						ffile.write(&vecEncryptInfo.at(0), vecEncryptInfo.size());
						write_offset += vecEncryptInfo.size();

						ffile.seekp(write_offset);
						ffile.write(&kZippedData.at(0), kZippedData.size());
						write_offset += kZippedData.size();

						ffile.close();
					}
				}
				else
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Normal : %s"), _T(__FUNCTION__), __LINE__, (*File_iter).first.c_str());
					BM::MemToFile(OutFolder + (*File_iter).first + _T(".zip"), kZippedData);
				}
			}
			else
			{
				//	褒ぬ
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File To Mem Failed"), _T(__FUNCTION__), __LINE__);
				g_PackProcess.SetStateText(L"Find Not File");
				return	false;
			}

			++File_iter;
		}
	}

	return	true;
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿List 婦溼 л熱
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
bool ListCore(const std::wstring& OriFolder, const std::wstring& CrtFolder, const std::wstring& OutputFolder)
{
	//	List 瑞ず
	if(g_PackProcess.GetWork() & CPackProcess::eWork_Pack)
	{
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] List Щ煎撮蝶"), _T(__FUNCTION__), __LINE__);
		//	葬蝶お 儅撩
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 葬蝶お 煽м"), _T(__FUNCTION__), __LINE__);
		ListMerge(OutputFolder + L"\\PackResult\\", L"HEADFOLDERS.DAT");

		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] List 煽м ィ渦 撲薑"), _T(__FUNCTION__), __LINE__);
		if(g_PackProcess.GetWork() == CPackProcess::eWork_AllProcess)
		{
			if(g_PackProcess.GetIsPackToDir())
			{
				//	翕衛霞ч : ね婁 だ橾 綠掖橾陽
				PartListMerge(CrtFolder + L"\\", OutputFolder + L"\\PackResult\\");
			}
		}

		//	ぬ纂 嬴檜蛤 儅撩
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] ぬ纂 嬴檜蛤 儅撩"), _T(__FUNCTION__), __LINE__);
		//CreateGUID(OutputFolder + L"\\PackResult\\");
	}

	if(g_PackProcess.GetWork() == CPackProcess::eWork_CreateHeader)
	{
		CreateList(OriFolder);
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] 葬蝶お 煽м"), _T(__FUNCTION__), __LINE__);
		ListMerge(OriFolder + L"\\", L"HEADFOLDERS.DAT");		
	}

	if(g_PackProcess.GetWork() == (CPackProcess::eWork_HeaderMerge))
	{
		PartListMerge(CrtFolder + L"\\", OriFolder + L"\\");
	}

	return	true;
}

//	葬蝶お 儅撩
bool CreateList(const std::wstring& TargetFolder, const std::wstring& SubFolder, const bool bIsPack)
{
	g_PackProcess.SetStateText(L"Folder Seek");

	//	顫啃ィ渦曖 等檜顫
	std::wstring	wstrTargetDir	= TargetFolder + SubFolder;
	wstrTargetDir.erase(wstrTargetDir.find(_T(".\\")), 1);
	BM::FolderHash	kTargetFolderHash;
	BM::FolderHash	kTargetFileHash;

	if(!FolderSeek(wstrTargetDir, SubFolder, kTargetFileHash, kTargetFolderHash))
	{
		return	false;
	}
	BM::AddFolderMark(wstrTargetDir);

	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Create Folder List : %s"), _T(__FUNCTION__), __LINE__, wstrTargetDir.c_str());

	//	匐餌瞪縑 寰瞪匐餌
	if(kTargetFileHash.size())
	{
		//	だ橾 ね
		const bool bIsResult = UpdateFileState(wstrTargetDir, kTargetFileHash.begin()->second->kFileHash);
		if(bIsResult == false)
		{
			g_PackProcess.SetStateText(L"Pack : File Packing Failed");
			return	false;
		}

		//	ィ渦 樓撩
		kTargetFileHash.begin()->second->bIsUsePack = bIsPack;
		
		//	だ橾薑爾 盪濰
		if(!CreateHashFile(wstrTargetDir + _T("_FILES.PGH"), kTargetFileHash))
		{
			return	false;
		}
	}

	//	ж嬪 ィ渦 匐餌
	if(kTargetFolderHash.size())
	{
		BM::FolderHash::iterator	Dest_iter = kTargetFolderHash.begin();
		while(Dest_iter != kTargetFolderHash.end())
		{
			std::wstring	wstrSubFolder = SubFolder + BM::GetLastFolderName((*Dest_iter).first);
			BM::AddFolderMark(wstrSubFolder);
			g_PackProcess.SetStateText(L"Recursive Folder > " + wstrSubFolder);

			const bool bResult = CreateList(TargetFolder, wstrSubFolder, (*Dest_iter).second->bIsUsePack);
			if(bResult == false)
			{
				return	false;
			}
			++Dest_iter;
		}

		//	ィ渦薑爾 盪濰
		if(!CreateHashFile(wstrTargetDir + _T("_FOLDERS.PGH"), kTargetFolderHash))
		{
			return	false;
		}
	}
	
	return	true;
}

//	葬蝶お 煽м
bool ListMerge(const std::wstring& TargetFolder, const std::wstring& FileName)
{
	//	顫啃 ィ渦
	::SetCurrentDirectory(TargetFolder.c_str());
	g_PackProcess.SetStateText(L"ListMerge");
	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Merge Target Folder : %s"), _T(__FUNCTION__), __LINE__, TargetFolder.c_str());

	//	譆謙 葬蝶お蒂 橢朝棻
	BM::FolderHash	TotalHash;
	GetList(L".\\", TotalHash);

	BM::PgDataPackManager::RecursiveProcessPackState(TotalHash);

	size_t iCount = TotalHash.size();

	g_PackProcess.SetStateText(L"HeaderMerge : Create Header File");
	if(!CreateHashFile(FileName.c_str(), TotalHash))
	{
		return	false;
	}

	return	true;
}

//	睡碟ね ④渦 煽м
bool PartListMerge(const std::wstring& FullFolder, const std::wstring& PartFolder)
{
	BM::FolderHash		HeadFull;
	BM::FolderHash		HeadPart;

	ReadList(FullFolder, HeadFull, L"HEADFOLDERS.DAT");
	ReadList(PartFolder, HeadPart, L"HEADFOLDERS.DAT");

	//	檗橫菟檣啪 氈朝陛
	if(HeadFull.size() && HeadPart.size())
	{
		//	ィ渦蒂 瓊嬴爾濠
		BM::FolderHash::iterator	Part_iter = HeadPart.begin();
		while(Part_iter != HeadPart.end())
		{
			//	模蝶 酈高戲煎 滲唳
			BM::FolderHash::iterator	Full_iter = HeadFull.find((*Part_iter).first);

			if(Full_iter != HeadFull.end())
			{
				//	だ橾擊 陛雖堅 氈替傍
				if(Part_iter->second->kFileHash.size())
				{
					BM::FileHash::iterator	Part_File_iter = Part_iter->second->kFileHash.begin();
					while(Part_File_iter != Part_iter->second->kFileHash.end())
					{
						//	だ橾擊 瓊嬴塭
						BM::FileHash::iterator	Full_File_iter = Full_iter->second->kFileHash.find((*Part_File_iter).first);

						//	氈戲賊 雖辦堅 蹺陛
						if(Full_File_iter != Full_iter->second->kFileHash.end())
						{
							(*Full_File_iter).second.org_file_size = (*Part_File_iter).second.org_file_size;
							(*Full_File_iter).second.zipped_file_size = (*Part_File_iter).second.zipped_file_size;
							(*Full_File_iter).second.bIsEncrypt = (*Part_File_iter).second.bIsEncrypt;
							(*Full_File_iter).second.bIsZipped = (*Part_File_iter).second.bIsZipped;
							(*Full_File_iter).second.iOrgCRC = (*Part_File_iter).second.iOrgCRC;
						}
						else
						{
							//	橈戲賊 蹺陛
							Full_iter->second->kFileHash.insert(std::make_pair((*Part_File_iter).first, (*Part_File_iter).second));					
						}

						++Part_File_iter;
					}
				}
			}
			else
			{
				//	ィ渦陛 橈戲賊 蹺陛
				HeadFull.insert(std::make_pair((*Part_iter).first, (*Part_iter).second));	
			}

			Part_iter++;
		}
	}

	std::wstring	DelFileName = PartFolder + L"HEADFOLDERS.DAT";
	DeleteFile(DelFileName.c_str());

	//	盪濰
	if(!CreateHashFile(PartFolder + L"HEADFOLDERS.DAT", HeadFull))
	{
		return	false;
	}

	return	true;
}

//	葬蝶お蒂 橢朝棻.
bool GetList(const std::wstring& wstrFolderName, BM::FolderHash& rkFolderHash)
{
	BM::FolderHash		FileHash;
	BM::FolderHash		FolderHash;

	//	④渦蒂 檗朝棻.
	ReadList(wstrFolderName, FileHash, L"_FILES.PGH");
	ReadList(wstrFolderName, FolderHash, L"_FOLDERS.PGH");

	//	⑷薯 ィ渦曖 だ橾薑爾蒂 厥朝棻.
	BM::FolderHash::iterator	iter = FileHash.begin();
	while(iter != FileHash.end())
	{
		g_PackProcess.SetStateText(L"HeaderMerge : Insert File Data");
		rkFolderHash.insert(std::make_pair(wstrFolderName, iter->second));
		iter++;
	}

	//	ж嬪 ィ渦煎 除棻
	iter = FolderHash.begin();
	while(iter != FolderHash.end())
	{
		//	ж嬪 ィ渦曖 薑爾紫 橢朝棻.
		std::wstring	wstrSubFolder	= wstrFolderName;
		wstrSubFolder	+= BM::GetLastFolderName((*iter).first);
		BM::AddFolderMark(wstrSubFolder);

		BM::FolderHash	SubFolderHash;
		GetList(wstrSubFolder, SubFolderHash);

		//	橢橫螞 薑爾蒂 盪濰
		g_PackProcess.SetStateText(L"HeaderMerge : Insert List Data");
		rkFolderHash.insert(SubFolderHash.begin(), SubFolderHash.end());
		rkFolderHash.insert(std::make_pair(wstrSubFolder, (*iter).second));

		++iter;
	}

	//	だ橾 餉薯
	const std::wstring	FileList = wstrFolderName + L"_FILES.PGH";
	const std::wstring	FolderList = wstrFolderName + L"_FOLDERS.PGH";
	DeleteFile(FileList.c_str());
	DeleteFile(FolderList.c_str());

	return	true;
}


//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿Bind 婦溼 л熱
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
bool BindCore(const std::wstring& OriFolder, const std::wstring& OutputFolder)
{
	g_PackProcess.SetStateText(L"Binding Patch File");
	std::wstring	ResultFileName = L"";
	ResultFileName = BM::GetLastFolderName(OriFolder);
	ResultFileName += L".DAT";
	std::wstring	Result = OriFolder + L".DAT";
	
	if( ::PathFileExists(Result.c_str()) )
	{
		DeleteFile(Result.c_str());
	}

	if(!BM::PgDataPackManager::PackTargetFolder(OriFolder.c_str(), ResultFileName))
	{
		g_PackProcess.SetStateText(L"Binding Failed");
		return	false;
	}

	// 等檜顫 ね縑 幗瞪 厥朝 睡碟
	std::wstring wstrPathfile(OriFolder);
	BM::DetachFolderMark(wstrPathfile);
	wstrPathfile += L".DAT";
	if(!g_PackProcess.SetPackVersion(wstrPathfile))
	{
		g_PackProcess.SetStateText(L"Binding Failed - Can not set version");
		return false;
	}

	return	true;
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿Series 婦溼 л熱
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	衛葬鍔煎 ぬ纂 儅撩
bool SeriesPatch(const std::wstring& OriFolder, const std::wstring& LimitAFinal, const std::wstring& OutputFolder)
{
	typedef	std::list<std::wstring>	CUT_STRING;
	CUT_STRING	List;

	int	nLimit = 0;
	int	nFinal = 0;
	LimitRange(LimitAFinal, nLimit, nFinal);

	TCHAR	szTemp[MAX_PATH] = {0,};

	std::wstring	wstrLimit	= _itow(nLimit, szTemp, 10);
	std::wstring	wstrFinal	= _itow(nFinal, szTemp, 10);
	std::wstring	wstrTemp	= _itow(nFinal - 1, szTemp, 10);
	std::wstring	wstrDestFile	= (wstrTemp + L"TO") + wstrFinal + L".DAT";
	wstrTemp	= wstrFinal + L".DAT";
	CopyFile((OriFolder + wstrTemp).c_str(), (OutputFolder + wstrDestFile).c_str(), false); 

	for(int i = nFinal - 1; i >= nLimit; --i)
	{
		std::wstring	wstrSourFile;
		std::wstring	wstrOutFile;

		CreateFileName(i, nFinal, wstrSourFile, wstrOutFile);

		if(_waccess((OutputFolder + wstrSourFile).c_str(), 0) == -1) 
		{ 
			return	false; 
		}

		g_PackProcess.SetStateText(L"Series Patch Merging : " + ((wstrDestFile + L" >> ") + (wstrSourFile + L" = ") + wstrOutFile));
		MergePatchFile(wstrDestFile, wstrSourFile, wstrOutFile, OriFolder, OutputFolder);

		wstrDestFile = wstrOutFile;
	}

	CreatePatchID(wstrLimit, wstrFinal);

	return	true;
}

void CreateFileName(const int Limit, const int Final, std::wstring& Sour, std::wstring& Output)
{
	TCHAR	szTemp[MAX_PATH] = {0, };

	std::wstring	wstrLimit = _itow(Limit, szTemp, 10);
	std::wstring	wstrFinal = _itow(Final, szTemp, 10);
	std::wstring	wstrFirst = _itow(Limit - 1, szTemp, 10);
	
	Sour	= wstrLimit + L".DAT";
	Output	= (wstrFirst + L"TO") + wstrFinal + L".DAT";
}

//	ぬ纂 掘除擊 橢濠
bool LimitRange(const std::wstring& LimitAFinal, int& Limit, int& Final)
{
	typedef	std::list<std::wstring>	CUT_STRING;
	CUT_STRING	List;
	BM::vstring::CutTextByKey(LimitAFinal,std::wstring(L"|"), List);

	if(List.size() > 1)
	{
		CUT_STRING::iterator	iter = List.begin();
		while(iter != List.end())
		{
			CUT_STRING	SubList;
			BM::vstring::CutTextByKey((*iter), std::wstring(L":"), SubList);

			if(SubList.size())
			{
				CUT_STRING::iterator	Sub_iter = SubList.begin();
				if((*Sub_iter).compare(L"L") == 0)
				{
					++Sub_iter;
					Limit = _wtoi((*Sub_iter).c_str());
				}
				else if((*Sub_iter).compare(L"F") == 0)
				{
					++Sub_iter;
					Final = _wtoi((*Sub_iter).c_str());
				}
			}
			else
			{
				return	false;
			}

			++iter;
		}
	}
	else
	{
		return	false;
	}

	return	true;
}

//	僮濠
bool	MergePatchFile(const std::wstring& TargetDestName, const std::wstring& TargetSourName, const std::wstring& OutPutName, 
					   const std::wstring& TargetDir, const std::wstring& OutPutDir)
{
	CPFile		kDestFile;
	kDestFile.Load(OutPutDir + TargetDestName);
	CPFile		kSourFile;
	kSourFile.Load(TargetDir + TargetSourName);

	BM::FolderHash	kNewHash;	
	//	葬蝶お 儅撩 塽 熱薑
	MergeList(kDestFile.GetHash(), kSourFile.GetHash(), kNewHash);

	CPFile		kNewFile;
	kNewFile.Init(OutPutDir + OutPutName, kNewHash);

	typedef	BM::FolderHash::const_iterator		FOLDER_CITER;
	typedef BM::FileHash::const_iterator		FILE_CITER;

	if(kNewFile.GetHash().size())
	{
		FOLDER_CITER		Folder_iter = kNewFile.GetHash().begin();
		while(Folder_iter != kNewFile.GetHash().end())
		{
			kNewFile.FindFolder((*Folder_iter).first);
			bool	bIsDest = kDestFile.FindFolder((*Folder_iter).first);
			bool	bIsSour = kSourFile.FindFolder((*Folder_iter).first);

			if((*Folder_iter).second->kFileHash.size())
			{
				FILE_CITER	File_iter = (*Folder_iter).second->kFileHash.begin();
				while(File_iter != (*Folder_iter).second->kFileHash.end())
				{
					kNewFile.FindFile((*File_iter).first);

					bool				bIsDestCopy = false;
					std::vector<char>	vecData;
					char*				pData = NULL;
					int					nSize = 0;

					if(bIsDest)
					{
						if(kDestFile.FindFile((*File_iter).first))
						{
							kDestFile.GetData(vecData);
							bIsDestCopy = true;
						}
					}

					if(!bIsDestCopy && bIsSour)
					{
						if(kSourFile.FindFile((*File_iter).first))
						{
							kSourFile.GetData(vecData);
						}
						else
						{
							//凱 橫替滌縑憮 諮棲.
						}
					}
					else
					{
						//凱 橫替滌縑憮 諮棲.
					}
					
					kNewFile.SaveData(vecData);
					
					++File_iter;
				}
			}

			++Folder_iter;
		}
	}

	kNewFile.Clear();
	kSourFile.Clear();
	kDestFile.Clear();

	return	true;
}

bool MergeList(const BM::FolderHash& PatchList, const BM::FolderHash& OrgList, BM::FolderHash& kResultList)
{
	//	萃醞ж釭塭紫 綠賊 йв蹂陛 氈釭?
	if(PatchList.size() || OrgList.size())
	{
		//	錳獄擊 葬撲お縑 厥堅
		kResultList.insert(OrgList.begin(), OrgList.end());

		//	ィ渦蒂 給濠
		BM::FolderHash::const_iterator	Patch_iter = PatchList.begin();
		while(Patch_iter != PatchList.end())
		{
			//	ィ渦蒂 瓊嬴塭
			BM::FolderHash::iterator	Result_iter = kResultList.find((*Patch_iter).first);

			//	瓊懊傍?
			if(Result_iter != kResultList.end())
			{
				//	だ橾擊 匐餌ж濠.
				BM::FileHash::const_iterator	Patch_file_iter = (*Patch_iter).second->kFileHash.begin();
				while(Patch_file_iter != (*Patch_iter).second->kFileHash.end())
				{
					//	だ橾擊 瓊嬴塭
					BM::FileHash::iterator	Result_file_iter = (*Result_iter).second->kFileHash.find((*Patch_file_iter).first);
					//	瓊懊傍?
					if(Result_file_iter != (*Result_iter).second->kFileHash.end())
					{
						//	偵褐 塽 餉薯
						(*Result_file_iter).second = (*Patch_file_iter).second;

					}
					else
					{
						//	蹺陛
						(*Result_iter).second->kFileHash.insert(std::make_pair((*Patch_file_iter).first, (*Patch_file_iter).second));
					}

					++Patch_file_iter;
				}
			}
			else
			{
				//	蹺陛
				kResultList.insert(std::make_pair((*Patch_iter).first, (*Patch_iter).second));
			}

			++Patch_iter;
		}

		return	true;
	}

	return	false;
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	⊿晦顫 л熱
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//	ぬ纂 嬴檜蛤 儅撩
void CreateGUID(const std::wstring& OutFolder)
{
	g_PackProcess.SetStateText(L"Pactch.ID Create");
	BM::GUID	Guid;
	std::vector<char>	vecGuid;

	Guid.Generate();
	vecGuid.resize(sizeof(BM::GUID));
	memcpy(&vecGuid.at(0), &Guid, sizeof(BM::GUID));

	BM::EncSave(OutFolder + _T("Patch.ID"), vecGuid);
}

bool CreatePatchID(const std::wstring& Final, const std::wstring& Limit, const std::wstring& OutFolder)
{
	//	PatchID	儅撩
	TCHAR		szTemp[MAX_PATH];
	BM::VersionInfo kVersionInfo;
	
	std::string	strClient = "";
	std::string	strCount = "";
	std::string	strLimit = "";
	std::string	strPatchID = "";
	
	//	檗橫螃堅
	if(Final.size())
	{
		kVersionInfo.Version.i16Minor = _wtoi64(Final.c_str());
		strCount	= MB(Final);
	}
	else
	{
		GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_COUNT), szTemp, MAX_PATH);
		kVersionInfo.Version.i16Minor = _wtoi64(szTemp);
		strCount	= MB(szTemp);
	}

	if(Limit.size())
	{
		kVersionInfo.Version.i32Tiny = _wtoi64(Limit.c_str());
		strLimit	= MB(Limit);
	}
	else
	{
		GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_LIMIT), szTemp, MAX_PATH);
		kVersionInfo.Version.i32Tiny = _wtoi64(szTemp);
		strLimit	= MB(szTemp);
	}

	GetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_CLIENT_INFO), szTemp, MAX_PATH);
	kVersionInfo.Version.i16Major = _wtoi64(szTemp);
	strClient	= MB(szTemp);

	//	ぬ纂 嬴檜蛤
	strPatchID = strClient + "." + strCount + "." + strLimit;

	std::vector<char>	vecPatchID;
	vecPatchID.resize(strPatchID.size());
	//vecPatchID.resize(sizeof(kVersionInfo.iVersion));
	::memcpy(&vecPatchID.at(0), strPatchID.c_str(), strPatchID.size());
	//::memcpy(&vecPatchID.at(0), &kVersionInfo.iVersion, sizeof(kVersionInfo.iVersion));

	//	盪濰
	if(OutFolder.size())
	{
		BM::SimpleEncrypt(vecPatchID, vecPatchID);
		BM::MemToFile(OutFolder + L"./PATCH.ID", vecPatchID);
//		BM::EncSave(OutFolder + L"PATCH.ID", vecPatchID);
	}
	else
	{
	
		BM::SimpleEncrypt(vecPatchID, vecPatchID);
		BM::MemToFile(L"./PATCH.ID", vecPatchID);
//		BM::EncSave(L"PATCH.ID", vecPatchID);

	}

	//	罹晦睡欐 偵褐
	const TCHAR	CONFIG[] = L".\\PackConfig.ini";


	::WritePrivateProfileString(L"PATCH", L"CLIENT", UNI(strClient), CONFIG);
	::WritePrivateProfileString(L"PATCH", L"COUNT", UNI(strCount), CONFIG);
	::WritePrivateProfileString(L"PATCH", L"LIMIT",  UNI(strLimit), CONFIG);

	int	nCount = atoi(strLimit.c_str());
	_itot_s(++nCount, szTemp, MAX_PATH, 10);
	SetWindowText(GetDlgItem(g_hDlgWnd, IDC_TXT_PATCH_LIMIT), szTemp);

	return	true;
}

//	だ橾薑爾蒂 偵褐
bool UpdateFileState(const std::wstring& TargetFolder, BM::FileHash& TargetHash)
{
	//	剩橫螞 だ橾 п蓮縑 だ橾檜 氈擊 唳辦縑虜.
	if(TargetHash.size())
	{
		BM::FileHash::iterator	File_iter = TargetHash.begin();

		//	だ橾 ね
		while(File_iter != TargetHash.end())
		{
			//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File State Update > %s"), _T(__FUNCTION__), __LINE__, (*File_iter).first.c_str());
			g_PackProcess.SetStateText(L"File State Update > " + (*File_iter).first);

			std::vector<char>	kFileData;
			std::vector<char>	kZippedData;

			//	だ橾 煎萄
			if(BM::FileToMem((*File_iter).first, kFileData))
			{
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File To Mem Success"), _T(__FUNCTION__), __LINE__);
				//	憶蹴
				if(BM::Compress(kFileData, kZippedData))
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Zipped File"), _T(__FUNCTION__), __LINE__);
					(*File_iter).second.bIsZipped = true;
					(*File_iter).second.zipped_file_size = kZippedData.size();
				}
				else
				{
					//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Normal File"), _T(__FUNCTION__), __LINE__);
					(*File_iter).second.bIsZipped = false;
					(*File_iter).second.zipped_file_size = (*File_iter).second.org_file_size;
				}
			}
			else
			{
				//	褒ぬ
				//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] File To Mem Failed"), _T(__FUNCTION__), __LINE__);
				g_PackProcess.SetStateText(L"File State Update : Find Not File");
				return	false;
			}

			++File_iter;
		}
	}
	else
	{
		g_PackProcess.SetStateText(L"File State Update : Not File");
	}

	return	true;
}

//	だ橾菟 犒餌
void CopyFiles(const std::wstring& DestFolder, const std::wstring& OutFolder,
			   const BM::FileHash& DestHash)
{
	//	犒餌 衛濛
	BM::FileHash::const_iterator	Dest_iter = DestHash.begin();
	while(Dest_iter != DestHash.end())
	{
		//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Diff NewFile %s"), _T(__FUNCTION__), __LINE__, (*Dest_iter).first.c_str());
		//	だ橾擊 犒餌ж濠
		OutputFile(DestFolder, OutFolder, (*Dest_iter).first);
		++Dest_iter;
	}
}

//	だ橾 犒餌
void OutputFile(const std::wstring& TargetFolder, const std::wstring& OutFolder, 
			    const std::wstring& FileName)
{
	//INFO_LOG( BM::LOG_LV7, _T("[%s]-[%d] Copy File : %s"), _T(__FUNCTION__), __LINE__, FileName.c_str());
	g_PackProcess.SetStateText(L"Copy File > " + FileName);
	std::wstring	TargetFile = TargetFolder + FileName;
	std::wstring	OutFile	 = OutFolder + FileName;
	BM::ReserveFolder(OutFile);
	CopyFile(TargetFile.c_str(), OutFile.c_str(), false);
}

//	ィ渦 鬚儀
bool FolderSeek(const std::wstring FolderName, const std::wstring SubFolder, 
				BM::FolderHash& FileList, BM::FolderHash& FolderList)
{
	if(::SetCurrentDirectory(FolderName.c_str()) == FALSE)
	{
		g_PackProcess.SetStateText(L"Diff : Find Not Folder");
		return	false;
	}

	BM::PgDataPackManager::GetFileList(_T(".\\"), FolderList, BM::GFL_ONLY_FOLDER, SubFolder);
	BM::PgDataPackManager::GetFileList(_T(".\\"), FileList, BM::GFL_ONLY_FILE, SubFolder);

	if(FileList.size())
	{
		//	だ橾 薑爾 偵褐
		if(!UpdateFileState(FolderName, FileList.begin()->second->kFileHash))
		{
			return	false;
		}
	}
	
	return	true;
}

//	④渦 だ橾擊 儅撩
bool CreateHashFile(const std::wstring& OutFolderFile, BM::FolderHash& ListHash)
{
	//	④渦 盪濰
	std::fstream ffile_ret;
	ffile_ret.open(OutFolderFile.c_str(), std::ios_base::in | std::ios_base::app | std::ios_base::ate | std::ios_base::binary);

	//	だ橾薑爾 盪濰
	if(!BM::PgDataPackManager::MakeHeader(ListHash, ffile_ret))
	{
		ffile_ret.close();
		g_PackProcess.SetStateText(L"List Data Save Failed");
		return	false;
	}
	
	ffile_ret.close();
	return	true;
}

//	④渦 だ橾 煎萄
void ReadList(const std::wstring& FolderName, BM::FolderHash& Hash, const std::wstring& FileName)
{
	g_PackProcess.SetStateText(L"HeaderMerge : List Load");

	BM::PgDataPackManager::PackFileCache_new kCache;
	if(kCache.Open(FolderName + FileName))
	{
		BM::PgDataPackManager::ReadHeader(kCache);
		Hash.insert(kCache.mFolderHash.begin(),kCache.mFolderHash.end());
//		BM::PgDataPackManager::ClearBuffer(FolderName + FileName);
	}
}