#include "stdafx.h"
#include "Lohengrin/PacketStructLog.h"
#include "../PgLog.h"

template< typename T >
void PushLogParam(size_t count, PgLogWrapper &kLogData, CEL::DB_QUERY &kQuery)
{
	while(count--)
	{
		T kData;
		kLogData.Pop(kData);
		kQuery.PushParam(kData);
	}
}

template< typename T >
void PushToFileLog(size_t count, BM::vstring &kString)
{
	while(count--)
	{
		T kData;
		kLogData.Pop(kData);
		
		kString += _T(", ");
		kString += kData;
	}
}

PgLogManager::PgLogManager()
{
	BM::CAutoMutex kLock(m_kMutex);
}

PgLogManager::~PgLogManager()
{
}

void PgLogManager::Init(CONT_LOG_TYPE const &kContLogType)
{
	BM::CAutoMutex kLock(m_kMutex);

	m_kContLogType = kContLogType;
}

void PgLogManager::WriteChat(CEL::CPacket* const pkPacket )
{
	BM::CAutoMutex kLock(m_kMutex);

	BYTE ucType = 0;
	pkPacket->Pop( ucType );

	PgLogWrapper kFormat( LOG_USER3_CHAT );
	kFormat.Push((int)ucType);

	BM::GUID kCharacterGuid;
	BM::GUID kMemberGuid;

	std::wstring strName;
	int usChannelNo = 0;
	std::wstring strChat, strTargetName;

	BM::GUID kTargetMemberGuid;
	BM::GUID kTargetCharacterGuid;
	DWORD dwColor = 0;

	switch( ucType )
	{
	case CT_Whisper_ByGuid:
		{
			pkPacket->Pop( kCharacterGuid );
			pkPacket->Pop( strName );	// 보내는 케릭터명
			pkPacket->Pop( usChannelNo); //채널
			pkPacket->Pop( strChat);	// 내용
			pkPacket->Pop( dwColor);
//			pkPacket->Pop( kContItem);
			pkPacket->Pop( kMemberGuid );
			pkPacket->Pop( kTargetMemberGuid );	// 받는 MemGuid
			pkPacket->Pop( kTargetCharacterGuid );	// 받는 CharGuid
			pkPacket->Pop( strTargetName );	// 받는 케릭터명
		}break;
	case CT_TEAM:
		{
			pkPacket->Pop( kCharacterGuid );
			pkPacket->Pop( strName );
			pkPacket->Pop( usChannelNo); //채널
			pkPacket->Pop( strChat );
			pkPacket->Pop( dwColor);
//			pkPacket->Pop( kContItem);
			pkPacket->Pop( kTargetMemberGuid );
		}
	default:
		{
			return;
		}break;
	}

	kFormat.MemberKey(kMemberGuid);
	kFormat.CharacterKey(kCharacterGuid);
	kFormat.Name(strName);
	kFormat.ChannelNo(usChannelNo);

	kFormat.Push(strChat);
	kFormat.Push(strTargetName);
	kFormat.Push(kTargetMemberGuid);
	kFormat.Push(kTargetCharacterGuid);

	WriteLog( kFormat );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PgLogManager::CanWrite(ELogType const &eLogType, ELogWriteType const &eWriteType)const
{
	BM::CAutoMutex kLock(m_kMutex);

	CONT_LOG_TYPE::const_iterator itor_find = m_kContLogType.find(eLogType);
	if (itor_find != m_kContLogType.end())
	{
		if(itor_find->second & eWriteType)
		{
			return true;
		}
	}
	return false;
}

void WriteLog(PgLogWrapper &kLogData)
{
	if(g_kLog.CanWrite(kLogData.LogType(), ELogWrite_Database))
	{
		CEL::DB_QUERY kQuery( DT_LOG, DQT_WRITE_LOG, _T("EXEC [dbo].[UP_Log_Write] ?,?,?,?,?, ?,?,?,?,  ?,?,?,?,?,  ?,?,?,?,?,  ?,?,?,?,?"));

		kQuery.PushParam(kLogData.LogType());
		kQuery.PushParam(kLogData.MemberKey());
		kQuery.PushParam(kLogData.CharacterKey());
		kQuery.PushParam(kLogData.Name());
		kQuery.PushParam(kLogData.ChannelNo());

		PushLogParam< std::wstring >(PgLogWrapper::MAX_ARRAY_STRING, kLogData, kQuery);
		PushLogParam< int >(PgLogWrapper::MAX_ARRAY_INT, kLogData, kQuery);
		PushLogParam< __int64 >(PgLogWrapper::MAX_ARRAY_INT64, kLogData, kQuery);
		PushLogParam< BM::GUID >(PgLogWrapper::MAX_ARRAY_GUID, kLogData, kQuery);

		g_kCoreCenter.PushQuery(kQuery);
	}
//	else //테스트코드
//	{
//		CEL::DB_QUERY kQuery( DT_LOG, DQT_WRITE_LOG, _T("EXEC [dbo].[up_Logtest2] ?"));
//		
//		kQuery.PushParam((int)1000);
//		g_kCoreCenter.PushQuery(kQuery);
//	}

	if(g_kLog.CanWrite(kLogData.LogType(), ELogWrite_File))
	{
/*		CEL::DB_QUERY kQuery( DT_LOG, DQT_WRITE_LOG, _T("EXEC [dbo].[UP_Log_Write] ?,?,?,?,?, ?,?,?,?,  ?,?,?,?,?,  ?,?,?,?,?,  ?,?,?,?,?"));

		kQuery.PushParam(kLogData.LogType());
		kQuery.PushParam(kLogData.MemberKey());
		kQuery.PushParam(kLogData.CharacterKey());
		kQuery.PushParam(kLogData.Name());
		kQuery.PushParam(kLogData.ChannelNo());

		PushLogParam<std::wstring> (PgLogWrapper::MAX_ARRAY_STRING, kLogData, kQuery);
		PushLogParam<int> (PgLogWrapper::MAX_ARRAY_INT, kLogData, kQuery);
		PushLogParam<__int64> (PgLogWrapper::MAX_ARRAY_INT64, kLogData, kQuery);
		PushLogParam<BM::GUID> (PgLogWrapper::MAX_ARRAY_GUID, kLogData, kQuery);

		g_kCoreCenter.PushQuery(kQuery);
*/	}

//	if(	(WriteType() & ELogWrite_File)
//	||	(	!bWriteDB 
//		&&	(WriteType() & ELogWrite_FileNextDB)))
	{//
		//std::wstring const wstrLogHead = _T("EXEC [dbo].[UP_Log_Write_FromFile]");
		//
		//// PARAMETER
		////	@procMethod, @LogType @MemberKey @CharacterKey, @Name,
		////	@Channel, @Message1, @Message2, @Message3, @Message4,
		////	@iValue1, @iValue2, @iValue3, @iValue4, @iValue5,
		////	@i64Value1, @i64Value2, @i64Value3, @i64Value4, @i64Value5,
		////	@guidValue1, @guidValue2, @guidValue3, @guidValue4, @guidValue5,
		////	@CurrentTime
		//size_t const iMessageMaxLen = 500;
		//static TCHAR chLogMessage[6][iMessageMaxLen];

		//_stprintf_s(chLogMessage[0], iMessageMaxLen, _T(" '%s', %d, '%s', '%s', '%s',"),
		//	m_akCategory[kLogData.Category()].c_str(), kLogData.LogType(), kLogData.MemberKey().str().c_str(), kLogData.CharacterKey().str().c_str(), kLogData.Name().c_str());
		//
		//_stprintf_s(chLogMessage[1], iMessageMaxLen, _T(" %d, '%s', '%s', '%s', '%s',"),
		//	kLogData.ChannelNo(), kLogData.strMessage[0].c_str(), kLogData.strMessage[1].c_str(), kLogData.strMessage[2].c_str(), kLogData.strMessage[3].c_str());
		//
		//_stprintf_s(chLogMessage[2], iMessageMaxLen, _T(" %d, %d, %d, %d, %d,"),
		//	kLogData.iValue[0], kLogData.iValue[1], kLogData.iValue[2], kLogData.iValue[3], kLogData.iValue[4]);
		//
		//_stprintf_s(chLogMessage[3], iMessageMaxLen, _T(" %I64d, %I64d, %I64d, %I64d, %I64d,"),
		//	kLogData.i64Value[0], kLogData.i64Value[1], kLogData.i64Value[2], kLogData.i64Value[3], kLogData.i64Value[4]);
		//
		//_stprintf_s(chLogMessage[4], iMessageMaxLen, _T(" '%s', '%s', '%s', '%s', '%s',"),
		//
		//kLogData.guidValue[0].str().c_str(), kLogData.guidValue[1].str().c_str(), kLogData.guidValue[2].str().c_str(), kLogData.guidValue[3].str().c_str(), kLogData.guidValue[4].str().c_str());
		//SYSTEMTIME kSystemTime;
		//GetLocalTime(&kSystemTime);
		//_stprintf_s(chLogMessage[5], iMessageMaxLen, _T("'%04hd-%02hd-%02hd %02hd:%02hd:%02hd.%03hd'"),kSystemTime.wYear, kSystemTime.wMonth, kSystemTime.wDay,
		//	kSystemTime.wHour, kSystemTime.wMinute, kSystemTime.wSecond, kSystemTime.wMilliseconds);

		//m_kLog.Log(BM::LOG_LV0, _T("%s %s%s%s%s%s%s"), wstrLogHead.c_str(),
		//	chLogMessage[0], chLogMessage[1], chLogMessage[2], chLogMessage[3], chLogMessage[4], chLogMessage[5]);

	}
}

