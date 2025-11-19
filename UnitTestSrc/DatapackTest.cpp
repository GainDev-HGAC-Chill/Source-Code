
// Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include "PgTestModule.h"
#include "BM/FileSupport.h"
#include "BM/Common.h"

class PgFileLoadTask
	: public PgTask< std::string >
{
public:
	void Init()
	{
		m_kQueuedCount= 0;
		m_kLoadCount = 0;
		m_kFolders.push_back(".\\bgm");
		m_kFolders.push_back(".\\xml");
		m_kFolders.push_back(".\\script");
		m_kFolders.push_back(".\\data\\1_cha");
		m_kFolders.push_back(".\\data\\2_Mon");
		m_kFolders.push_back(".\\data\\3_World");
		m_kFolders.push_back(".\\data\\4_Item");
		m_kFolders.push_back(".\\data\\5_Effect");
		m_kFolders.push_back(".\\data\\6_UI");
	}

	virtual void HandleMessage(std::string *pkMsg)
	{
		HandleMessage_PackCheck(pkMsg);
//		HandleMessage_SaveCheck(pkMsg);
//		HandleMessage_fstream(pkMsg);
	}

	virtual void HandleMessage_PackCheck(std::string *pkMsg)
	{
		::InterlockedDecrement(&m_kQueuedCount);
		std::string const &kStrName = *pkMsg;

		CONT_FOLDERS::const_iterator folder_itor = m_kFolders.begin();

		while(folder_itor != m_kFolders.end())
		{
			if(0 == strnicmp(kStrName.c_str(), (*folder_itor).c_str(), (kStrName.size() < (*folder_itor).size())?kStrName.size():(*folder_itor).size() ) )
			{
				::InterlockedIncrement(&m_kLoadCount);

				std::string kHead = kStrName.substr(0, (*folder_itor).size());
				std::string kTail = kStrName.substr((*folder_itor).size());
				std::vector<char>	kData;

				std::wstring kPack = UNI(*folder_itor + ".dat");
				std::wstring kChild = UNI(std::string(".") + kTail);
				if(!BM::PgDataPackManager::LoadFromPack(kPack, kChild, kData))
				{
					BM::CAutoMutex kLock(m_kMutex);
					CONT_CANT_LOAD_INFO::_Pairib ret = m_kContCantLoad.insert(std::make_pair(kStrName, 0));
					++((*ret.first).second);
				}
				else
				{//로드 성공.
					std::vector<char>	kOrgData;
					BM::FileToMem(UNI(kStrName), kOrgData);
					
					if(kOrgData.size() == kData.size())
					{
						if(0 == memcmp(&kOrgData.at(0), &kData.at(0), kOrgData.size()))
						{
						
						}
						else
						{
							__asm int 3;
						}
					}
					else
					{
						__asm int 3;
					}
				}
			}
			++folder_itor;
		}
	}

	virtual void HandleMessage_SaveCheck(std::string *pkMsg)
	{
		std::string const &kStrName = *pkMsg;

		CONT_FOLDERS::const_iterator folder_itor = m_kFolders.begin();
		std::vector<char>	kOrgData;
		std::vector<char>	kMemData;
		std::vector<char>	kDecData;
		
		BM::FileToMem(UNI(kStrName), kOrgData);

		if(kOrgData.size())
		{
			BM::MemToFile(UNI(kStrName+"Mem"), kOrgData);
			BM::FileToMem(UNI(kStrName+"Mem"), kMemData);
			
			if(kOrgData.size() == kMemData.size())
			{
				if(0 == memcmp(&kOrgData.at(0), &kMemData.at(0), kOrgData.size()))
				{
				}
				else
				{
					__asm int 3;
				}
			}
			else
			{
				__asm int 3;
			}

			BM::EncSave(UNI(kStrName+"Enc"), kOrgData);
			BM::DecLoad(UNI(kStrName+"Enc"), kDecData);

			if(kOrgData.size() == kDecData.size())
			{
				if(0 == memcmp(&kOrgData.at(0), &kDecData.at(0), kOrgData.size()))
				{
				}
				else
				{
					__asm int 3;
				}
			}
			else
			{
				__asm int 3;
			}

		}
		::InterlockedDecrement(&m_kQueuedCount);
	}

	virtual void HandleMessage_fstream(std::string *pkMsg)
	{
		std::string const &strFileName = *pkMsg;

		std::vector<char> vecOut;

		size_t const file_size = BM::GetFileSize(UNI(strFileName));

		std::fstream ffile;
		ffile.open( strFileName.c_str(), std::ios_base::in | std::ios_base::app | std::ios_base::ate | std::ios_base::binary );//in 모드임.

		if(ffile.is_open())
		{
			Sleep(1000);
			::InterlockedIncrement(&m_kLoadCount);
			
			if(file_size)
			{
				vecOut.reserve(file_size);
				vecOut.resize(file_size);

				ffile.seekg(0);
				ffile.read(&vecOut.at(0), static_cast<std::streamsize>(vecOut.size()));
			}

			::InterlockedDecrement(&m_kLoadCount);
			ffile.close();
		}
		else
		{
			__asm int 3;
		}

		::InterlockedDecrement(&m_kQueuedCount);
	}

	virtual bool PutMsg(std::string &rkMsg, unsigned long ulPriority = 0)
	{
		::InterlockedIncrement(&m_kQueuedCount);
		return PgTask< std::string >::PutMsg(rkMsg);
	}

	typedef std::vector< std::string > CONT_FOLDERS;
	CONT_FOLDERS m_kFolders;
	volatile long m_kLoadCount;
	
	volatile long m_kQueuedCount;
	
	typedef std::map<std::string, int> CONT_CANT_LOAD_INFO;
	CONT_CANT_LOAD_INFO m_kContCantLoad;
	Loki::Mutex m_kMutex;
};
PgFileLoadTask g_kTask;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "kor");
	ACE::init();
	std::vector<char> kContFile;
	BM::FileToMem(L"./FileList.txt", kContFile);

	if(!kContFile.size())
	{
		return 0;
	}

	std::string kFileList(&kContFile.at(0));

	std::vector< std::string > kContElement;
	std::string::size_type prev_offset = 0;
	std::string::size_type offset = kFileList.find('\n', prev_offset);
	while(offset != std::string::npos )
	{
		kContElement.push_back(std::string(&kFileList.at(prev_offset), offset-prev_offset-1));
		prev_offset = offset+1;
		offset = kFileList.find('\n', prev_offset);
	}

	g_kTask.Init();
	g_kTask.StartSvc(8);

	printf("start");
	int i = kContElement.size();
	std::random_shuffle(kContElement.begin(), kContElement.end());

	while(i--)
	{
//		std::string & kKey = kContElement.at(BM::Rand_Index(kContElement.size()));
		std::string & kKey = kContElement.at(i);

//		std::string kKey = ".\\script\\world\\02_chaosarea\\020107_fd.lua";
//		std::string kKey = ".\\bgm\\BattleBlues.mp3";
//		std::string kKey = ".\\Data\\1_Cha\\1_PC\\1_Male\\00_Common\\01_Shoulder\\Common_Com_intro_idle_01.kf";
//							.\\data\\1_cha\\1_pc\\1_male\\00_common\\06_wing\\common_com_ladder_01.kf
		g_kTask.PutMsg(kKey);
//		g_kTask.HandleMessage(&kKey);
		
		if((i%1000) == 0 )
		{
			printf("%d\n", i);
		}
//		if( 0 == (rand()%100) )
		{
//			Sleep(2);
		}
	}

	while(g_kTask.m_kQueuedCount)
	{
		printf("%d\n", g_kTask.m_kQueuedCount);
		Sleep(1000);
	}

	printf("close");

	
	ACE::fini();
	return 0;
}



