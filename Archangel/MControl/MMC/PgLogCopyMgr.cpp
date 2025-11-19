#include "stdafx.h"
#include "DataPack/PackInfo.h"
#include "DataPack/PgDataPackManager.h"
#include "Variant/Global.h"
#include "PgLogCopyMgr.h"
#include "PgMMCManager.h"

// -----------------------------------------------------
// CopyMgr
// -----------------------------------------------------
PgLogCopyMgr::PgLogCopyMgr(void)
:	m_dwHackLogIntervalTime(3600000)
,	m_dwLastUpdateTime(0)
,	m_dwUpdateTickTime(0)
{
}

PgLogCopyMgr::~PgLogCopyMgr(void)
{

}

void PgLogCopyMgr::Locked_ReadFromConfig( LPCWSTR lpFileName )
{
	BM::CAutoMutex kLock( m_kMutex );

	wchar_t chValue[MAX_PATH] = {0,};
	::GetPrivateProfileStringW( L"COPY_LOG", L"PATH", L"..\\LogFiles\\Recv\\", chValue, MAX_PATH, lpFileName );
	m_wstrPath = chValue;

	BM::ConvFolderMark(m_wstrPath);
	if ( m_wstrPath.size() )
	{
		wchar_t const tLast = m_wstrPath.at(m_wstrPath.size()-1);
		if( tLast != _T('\\') 
			&&	tLast != _T('/') )
		{
			m_wstrPath += _T("\\");
		}
	}

	BM::ReserveFolder( m_wstrPath );

	DWORD const dwValue = static_cast<DWORD>( ::GetPrivateProfileIntW( L"COPY_LOG", L"HACKLOG_COPY_INTERVAL_MIN ", 3600000, lpFileName ) ) * 60 * 1000;
	if ( 0 == dwValue )
	{
		m_dwHackLogIntervalTime = 0;
	}
	else if ( m_dwHackLogIntervalTime < dwValue )
	{
		m_dwHackLogIntervalTime = dwValue;
	}

}

void PgLogCopyMgr::Locked_Init( ContServerSiteID const &kServerList )
{
	BM::CAutoMutex kLock( m_kMutex );

	if ( 0 == m_dwHackLogIntervalTime )
	{
		m_dwUpdateTickTime = 0xFFFFFFFF;
		return;
	}

	m_dwLastUpdateTime = BM::GetTime32();

	if ( kServerList.size() )
	{
		m_dwUpdateTickTime = m_dwHackLogIntervalTime / static_cast<DWORD>(kServerList.size());
		if ( (1000 * 30) > m_dwUpdateTickTime )
		{
			m_dwUpdateTickTime = 1000 * 30;
		}
	}
	else
	{
		m_dwUpdateTickTime = m_dwHackLogIntervalTime;
	}
}

void PgLogCopyMgr::Locked_Tick()
{
	if ( true == g_kMMCMgr.Locked_IsLoadPatchFileList() )
	{
		return;
	}

	BM::CAutoMutex kLock( m_kMutex );

	if ( 0 == m_dwHackLogIntervalTime )
	{
		return;
	}

	DWORD const dwCurTime = BM::GetTime32();

	if ( m_kContCopyer.size() && ::DifftimeGetTime( m_dwLastUpdateTime, dwCurTime ) >= m_dwUpdateTickTime )
	{
		CONT_SMC_DOWNLOAD::const_iterator itr = m_kContCopyer.find( m_kTickCheckID );
		if ( itr != m_kContCopyer.end() )
		{
			BM::CPacket kPacket( PT_MMC_SMC_GET_LOG_FILE_INFO, static_cast<size_t>(2) );
			kPacket.Push( std::wstring( L"HackLog\\") );
			kPacket.Push( std::wstring( L"CautionLog\\") );
			g_kCoreCenter.Send( itr->first, kPacket );

			m_dwLastUpdateTime = dwCurTime;
			++itr;
		}

		if ( itr == m_kContCopyer.end() )
		{
			m_kTickCheckID = m_kContCopyer.begin()->first;
		}
		else
		{
			m_kTickCheckID = itr->first;
		}
	}
}

void PgLogCopyMgr::Locked_Connect( CEL::SESSION_KEY const &kSessionKey )
{
	BM::CAutoMutex kLock( m_kMutex );
	m_kContCopyer.insert( std::make_pair( kSessionKey, CONT_SMC_DOWNLOAD::mapped_type() ) );
}

void PgLogCopyMgr::Locked_Disconnect( CEL::SESSION_KEY const &kSessionKey )
{
	BM::CAutoMutex kLock( m_kMutex );
	
	if ( m_kTickCheckID == kSessionKey )
	{
		CONT_SMC_DOWNLOAD::iterator itr = m_kContCopyer.find( m_kTickCheckID );
		if ( itr != m_kContCopyer.end() )
		{
			itr = m_kContCopyer.erase( itr );
		}

		if ( itr != m_kContCopyer.end() )
		{
			m_kTickCheckID = itr->first;
		}
	}
	else
	{
		m_kContCopyer.erase( kSessionKey );
	}
}

void PgLogCopyMgr::Locked_Recv_PT_SMC_MMC_ANS_LOG_FILE_INFO( CEL::SESSION_KEY const &kSessionkey, BM::CPacket * pkPacket )
{
	std::wstring wstrFolder;
	std::wstring wstrLocalFolder;
	pkPacket->Pop( wstrFolder );
	GetPath( wstrFolder, wstrLocalFolder );

	SLogCopyer::CONT_LOG_FILE_INFO kFileList;
	PU::TLoadTable_AA(*pkPacket, kFileList);//받은걸로 내꺼와 비교

	BM::CAutoMutex kLock( m_kMutex );

	WIN32_FIND_DATA w32fd = {0,};
	wstrLocalFolder += L"*.txt";

	HANDLE hFindFile = ::FindFirstFileW( wstrLocalFolder.c_str(), &w32fd );
	if ( INVALID_HANDLE_VALUE != hFindFile )
	{
		do 
		{
			SLogCopyer::CONT_LOG_FILE_INFO::iterator itr = kFileList.find( std::wstring(w32fd.cFileName) );
			if ( itr != kFileList.end() )
			{
				__int64 i64Temp = static_cast<__int64>(w32fd.nFileSizeHigh);
				i64Temp <<= 32;
				i64Temp += static_cast<__int64>(w32fd.nFileSizeLow);
				if ( i64Temp == itr->second )
				{
					kFileList.erase( itr );
				}
			}

		} while ( TRUE == ::FindNextFileW( hFindFile, &w32fd ) );

		::FindClose( hFindFile );
		hFindFile = NULL;
	}

	//받을 목록 뽑기.
	CONT_SMC_DOWNLOAD::iterator itr = m_kContCopyer.find( kSessionkey );
	if ( itr != m_kContCopyer.end() )
	{
		SLogCopyer::CONT_DOWNLOAD &kElement = itr->second.m_kContDownLoad;
		SLogCopyer::CONT_DOWNLOAD::_Pairib kPair = kElement.insert( std::make_pair( wstrFolder, kFileList ) );
		if ( !kPair.second )
		{
			kPair.first->second.swap( kFileList );
		}

		ProcessDownLoad( itr );
	}
}

void PgLogCopyMgr::Locked_Recv_PT_MMC_SMC_ANS_GET_FILE( CEL::SESSION_KEY const &kSessionkey, BM::CPacket * pkPacket )
{
	BM::CAutoMutex kLock( m_kMutex );

	std::wstring strFileName;
	std::vector<char> kFileData;
	pkPacket->Pop(strFileName);
	pkPacket->Pop(kFileData);

	INFO_LOG( BM::LOG_LV2, _T("Recv File [") << strFileName.c_str() << _T("]") );

	std::wstring wstrFile;
	GetPath( strFileName, wstrFile );

	if( !BM::MemToFile( wstrFile, kFileData ))
	{
		if ( kFileData.empty() )
		{
			CAUTION_LOG( BM::LOG_LV5, _T("Recv File Failed [") << strFileName.c_str() << _T("] size empty") );
		}
		else
		{
			CAUTION_LOG( BM::LOG_LV5, _T("Recv File Failed [") << strFileName.c_str() << _T("]") );
		}

		strFileName.clear();// 실패했으니까 지우지 않게
	}

	CONT_SMC_DOWNLOAD::iterator itr = m_kContCopyer.find( kSessionkey );
	if ( itr != m_kContCopyer.end() )
	{
		ProcessDownLoad( itr, strFileName );
	}
}

void PgLogCopyMgr::ProcessDownLoad( CONT_SMC_DOWNLOAD::iterator itr, std::wstring const &wstrOldfile )
{
	SLogCopyer::CONT_DOWNLOAD &kElement = itr->second.m_kContDownLoad;

	SLogCopyer::CONT_DOWNLOAD::iterator head_itor = kElement.begin();
	while(head_itor != kElement.end())
	{
		SLogCopyer::CONT_LOG_FILE_INFO &kFileList = head_itor->second;
		SLogCopyer::CONT_LOG_FILE_INFO::iterator file_itr = kFileList.begin();

		if( file_itr != kFileList.end() )
		{
			//폴더와 파일 컨터이너 비면 지워야함.
			std::wstring wstrFileName = head_itor->first + file_itr->first;

			BM::CPacket kPacket( PT_SMC_MMC_REQ_GET_FILE, wstrFileName );
			kPacket.Push( wstrOldfile );
			g_kCoreCenter.Send( itr->first, kPacket );

			kFileList.erase( file_itr );
			return;
		}

		kElement.erase(head_itor++);
	}

	if ( wstrOldfile.size() )
	{
		BM::CPacket kPacket( PT_SMC_MMC_ANS_DATA_SYNC_END, wstrOldfile );//싱크 끝.
		g_kCoreCenter.Send( itr->first, kPacket );
	}
}
