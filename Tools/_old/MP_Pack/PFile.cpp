#include "PFile.h"

CPFile::CPFile(void)
{

}

CPFile::~CPFile(void)
{
	Clear();
}

//	이건 읽어오는거고
bool CPFile::Load(const std::wstring& wstrFileName)
{
	if(!wstrFileName.size())	{ return	false; }
	if(_waccess(wstrFileName.c_str(), 0) == -1)
	{
		return	false;
	}

	BM::PgDataPackManager::PackFileCache_new kCache;
	if(kCache.Open(wstrFileName))
	{
		m_kHashSize	= BM::PgDataPackManager::ReadHeader(kCache);
		m_kHash.insert(kCache.mFolderHash.begin(), kCache.mFolderHash.end());
//		m_kFile.Init(wstrFileName);
	}
	return	true;
}

//	이건 만드는 거고
bool CPFile::Init(const std::wstring& wstrFileName, const BM::FolderHash& Hash)
{
	if(!wstrFileName.size())	{ return	false; }
	if(!Hash.size())			{ return	false; }
	m_kHash.insert(Hash.begin(), Hash.end());
	const unsigned __int64	DataSize = BM::PgDataPackManager::BuildOffset(m_kHash);
	
	m_ffile.open(wstrFileName.c_str(), std::ios_base::in | std::ios_base::app | std::ios_base::ate | std::ios_base::binary);

	m_kHashSize	= BM::PgDataPackManager::MakeHeader(m_kHash, m_ffile);

	return	true;
}

//	이건 자원 해제하는 거고
void CPFile::Clear()
{
	if(m_ffile.is_open())
	{
		m_ffile.close();
	}
}

//	이건 폴더 찾는거고
bool CPFile::FindFolder(const std::wstring& wstrFolderName)
{
	if(m_kHash.size())
	{
		m_Folder_iter	= m_kHash.find(wstrFolderName);

		if(m_Folder_iter == m_kHash.end())	{ return	false; }
	}
	else
	{
		return	false;
	}

	return	true;
}

//	이건 파일 찾는거고
bool CPFile::FindFile(const std::wstring& wstrFileName)
{
	if(m_Folder_iter == m_kHash.end())	{ return	false; }

	if((*m_Folder_iter).second->kFileHash.size())
	{	
		m_File_iter		= (*m_Folder_iter).second->kFileHash.find(wstrFileName);

		if(m_File_iter == (*m_Folder_iter).second->kFileHash.end())	{ return	false; }
	}
	else
	{
		return	false;
	}

	return	true;
}

//	이건 데이타 받아오는 거고
bool CPFile::GetData(std::vector<char>& vecData)
{
	if(m_File_iter == (*m_Folder_iter).second->kFileHash.end()) { return	false; }

	size_t offset = m_kHashSize + (*m_File_iter).second.offset;
	size_t	pDataSize	= 0;

	//	사이즈 알아보자 - 압축?
	if((*m_File_iter).second.bIsZipped)
	{
		pDataSize = (*m_File_iter).second.zipped_file_size;
	}
	else
	{
		pDataSize = (*m_File_iter).second.org_file_size;
	}

	//	사이즈 알아보자 - 암호화?
	if((*m_File_iter).second.bIsEncrypt)
	{
		pDataSize += BM::ENC_HEADER_SIZE;
	}

	//	복사하자
	vecData.resize(pDataSize);
	m_ffile.seekg(static_cast<std::streamoff>(offset));
	m_ffile.read(&vecData.at(0), static_cast<std::streamsize>(pDataSize));

	return	true;
}

//	이건 데이타 쓰는 거고
bool CPFile::SaveData(const std::vector<char>& vecData)
{
	if(!vecData.size())	{ return	false; }
	if(m_File_iter == (*m_Folder_iter).second->kFileHash.end()) { return	false; }

	size_t offset = m_kHashSize + (*m_File_iter).second.offset;
	m_ffile.seekg(static_cast<std::streamoff>(offset));
	m_ffile.write(&vecData.at(0), static_cast<std::streamsize>(vecData.size()));

	return	true;
}