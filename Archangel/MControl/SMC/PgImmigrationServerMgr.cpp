#include "StdAfx.h"
#include "PgSMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "PgSendWrapper.h"


#ifdef _DEBUG
	#define EXE_TAIL	_T("d")
#elif EXTERNAL_RELEASE
	#define EXE_TAIL	_T("")
#else
	#define EXE_TAIL	_T("_Release")
#endif

#define _PathDefW(PathName, ExeName, ExeTail)				\
	const wchar_t* szPath##PathName = L#PathName;		\
	const wchar_t* szExe##PathName = L"\\" L#ExeName ExeTail L".exe";

_PathDefW(Center, CenterServer, EXE_TAIL)
_PathDefW(Map, MapServer, EXE_TAIL)
_PathDefW(Login, LoginServer, EXE_TAIL)
_PathDefW(Contents, ContentsServer, EXE_TAIL)
_PathDefW(Switch, Switch, EXE_TAIL)
_PathDefW(Item, ItemServer, EXE_TAIL)
_PathDefW(GM, GMServer, EXE_TAIL)
_PathDefW(Log, LogServer, EXE_TAIL)
_PathDefW(Immigration, Immigration, EXE_TAIL)

//>>
void SendServerCommand(SERVER_IDENTITY const& rkServerID, const EMCtrlCommand eCommand)
{
//	CEL::CPacket kPacket(PT_MCTRL_MMS_A_NFY_SERVER_COMMAND);
//	kPacket.Push((BYTE)eCommand);
//	rkServerID.WriteToPacket(kPacket);
	//등록된 머신 컨트롤러의 목록 중 해당 서버가 접속하는 머신 컨트롤러가 있으면 해당 머신 컨트롤러로 전송 아니면 내꺼다!!
//	std::wstring wstrServerIP;
//	if(g_kGameServerMgr.IsSMSConnection(rkServerID, wstrServerIP))
//	{
//		g_kSMCMgr.SendToSMS(wstrServerIP, kPacket);
//		return ;
//	}
//	else
//	{
//		if(g_kGameServerMgr.IsImmConnection(rkServerID))
//			SendToImmigration(kPacket);
//		else
//			g_kCoreCenter.Send(g_kCenterMgr.m_kSessionKey, kPacket);
//	}
}

bool CompareOnCommand(ContServerID::value_type& rkLeft, ContServerID::value_type& rkRight)
{
	//1.       MCtrl (서버 컨트롤을 위해서 가장 먼저 떠야할 서버)
	//2.	   IMM
	//3.       Center (서버군에서 가장 먼저 떠야 할 서버)
	//4.       Log (로그를 남기기 위해서 다른 모든 서버들 보다 먼저)
	//5.       Item
	//6.       Switch
	//7.       모든 Map
	//8.       Login
	//9.       GM
	//10.   맵서버가 전부 뜬 상태가 접속 가능 상태이고 MCtrl 툴의 Login Open 기능으로 서버를 연다
	static const SServerSortInfo kSortInfo[] =//아래 순서 바꾸지 말것
	{
		SServerSortInfo(CEL::ST_NONE, 999),
		SServerSortInfo(CEL::ST_CENTER, 3),
		SServerSortInfo(CEL::ST_MAP, 7),
		SServerSortInfo(CEL::ST_LOGIN, 8),
		SServerSortInfo(CEL::ST_SWITCH, 6),
		SServerSortInfo(CEL::ST_MACHINE_CONTROL, 999),
		SServerSortInfo(0, 999),//		SServerSortInfo(CEL::ST_RELAY, 999),
		SServerSortInfo(0, 999),//		SServerSortInfo(CEL::ST_USER, 999),
		SServerSortInfo(CEL::ST_ITEM, 5),
//		SServerSortInfo(CEL::ST_CONTENTS, 999),
		SServerSortInfo(CEL::ST_LOG, 4),
		SServerSortInfo(0, 8),//		SServerSortInfo(CEL::ST_MMAP, 8),
		SServerSortInfo(CEL::ST_GMSERVER, 9),
		SServerSortInfo(CEL::ST_GHOST_LOGIN, 999),
		SServerSortInfo(CEL::ST_IMMIGRATION, 2),
	};

	if( CEL::ST_NONE >= rkLeft.nServerType
	||	CEL::ST_MAX < rkLeft.nServerType
	||	CEL::ST_NONE >= rkRight.nServerType
	||	CEL::ST_MAX < rkRight.nServerType )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Can't identify server type %d or %d"), __FUNCTIONW__, __LINE__, rkLeft.nServerType, rkRight.nServerType);
		return false;
	}

	const SServerSortInfo& rkLeftScore = kSortInfo[rkLeft.nServerType];
	const SServerSortInfo& rkRightScore = kSortInfo[rkRight.nServerType];

	return rkLeftScore.iSortScore < rkRightScore.iSortScore;
}

bool CompareOffCommand(ContServerID::value_type& rkLeft, ContServerID::value_type& rkRight)
{
	//1.       MCtrl 툴의 Login Close 기능으로 새로운 유저 접속을 맊는다.
	//2.       모든 사용자 연결 Disconnect
	//3.       Login
	//4.       Map 자신에 속한 캐릭터 정보가 정상 저장하도록 하고서
	//5.       Switch
	//6.       Item
	//7.	   Center 자신이 가지고 있는 저장되지 않은 사용자 정보가 모두 저장 될 때 까지 기다리고 나서 Off
	//8.       Log
	//9.	   GM
	//10.	   IMM
	static const SServerSortInfo kSortInfo[] =//아래 순서 바꾸지 말것
	{
		SServerSortInfo(CEL::ST_NONE, 999),
		SServerSortInfo(CEL::ST_CENTER, 7),
		SServerSortInfo(CEL::ST_MAP, 4),
		SServerSortInfo(CEL::ST_LOGIN, 3),
		SServerSortInfo(CEL::ST_SWITCH, 5),
		SServerSortInfo(CEL::ST_MACHINE_CONTROL, 999),
		SServerSortInfo(0, 999),//		SServerSortInfo(CEL::ST_RELAY, 999),
		SServerSortInfo(0, 999),//		SServerSortInfo(CEL::ST_USER, 999),
		SServerSortInfo(CEL::ST_ITEM, 6),
//		SServerSortInfo(CEL::ST_CONTENTS, 999),
		SServerSortInfo(CEL::ST_LOG, 999),	//	off커맨드로 못죽이도록 수정
		SServerSortInfo(0, 8),//		SServerSortInfo(CEL::ST_MMAP, 8),
		SServerSortInfo(CEL::ST_GMSERVER, 8),
		SServerSortInfo(CEL::ST_GHOST_LOGIN, 999),
		SServerSortInfo(CEL::ST_IMMIGRATION, 9),
	};

	if( CEL::ST_NONE >= rkLeft.nServerType
	||	CEL::ST_MAX < rkLeft.nServerType
	||	CEL::ST_NONE >= rkRight.nServerType
	||	CEL::ST_MAX < rkRight.nServerType )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Can't identify server type %d or %d"), __FUNCTIONW__, __LINE__, rkLeft.nServerType, rkRight.nServerType);
		return false;
	}

	const SServerSortInfo& rkLeftScore = kSortInfo[rkLeft.nServerType];
	const SServerSortInfo& rkRightScore = kSortInfo[rkRight.nServerType];

	return rkLeftScore.iSortScore < rkRightScore.iSortScore;
}
//<<

//
PgCommandStack::PgCommandStack()
{
}

PgCommandStack::~PgCommandStack()
{
}

bool PgCommandStack::AddCommandOn(const ContServerID& rkCommandVec)
{
	BM::CAutoMutex kLock(m_kStackMutex);

	if( !m_kServerOffStack.empty()
	||	!m_kServerOnStack.empty()
	||	rkCommandVec.empty() )
	{
		return false;
	}

	m_kServerOnStack.insert(m_kServerOnStack.end(), rkCommandVec.begin(), rkCommandVec.end());
	return true;
}

bool PgCommandStack::AddCommandOff(const ContServerID& rkCommandVec)
{
	BM::CAutoMutex kLock(m_kStackMutex);

	if( !m_kServerOnStack.empty()
	||	!m_kServerOffStack.empty()
	||	rkCommandVec.empty() )
	{
		return false;
	}

	m_kServerOffStack.insert(m_kServerOffStack.end(), rkCommandVec.begin(), rkCommandVec.end());
	return true;
}

void PgCommandStack::DelOnCommand(SERVER_IDENTITY const &rkServerID)
{
	ContServerIDList::iterator iter = std::find(m_kServerOnStack.begin(), m_kServerOnStack.end(), rkServerID);
	if( m_kServerOnStack.end() != iter )
	{
		m_kServerOnStack.erase(iter);
		m_kCurCommand.Clear();
	}
}

bool PgCommandStack::NextCommand(SServerControlCommand& rkNext)
{
	BM::CAutoMutex kLock(m_kStackMutex);

	SServerControlCommand kTempCmd;//임시
	if( m_kServerOffStack.empty()
	&&	m_kServerOnStack.empty() )
	{
		//m_kPrevCommand.Clear();
		m_kCurCommand.Clear();
		return false;
	}
	if( m_kServerOffStack.empty()
	&&	!m_kServerOnStack.empty() )
	{
		kTempCmd.eType = CCT_On;
		kTempCmd.kServerID = *m_kServerOnStack.begin();
		m_kServerOnStack.pop_front();
	}
	if( !m_kServerOffStack.empty()
	&&	m_kServerOnStack.empty() )
	{
		kTempCmd.eType = CCT_Off;
		kTempCmd.kServerID = *m_kServerOffStack.begin();
		m_kServerOffStack.pop_front();
	}

	if( CCT_None != kTempCmd.eType )
	{
		//m_kPrevCommand = m_kCurCommand;//이전거 백업
		rkNext = m_kCurCommand = kTempCmd;//새로운거
		return true;
	}
	return false;
}

void PgCommandStack::StackWriteToPacket(CEL::CPacket& rkPacket) const
{
	TWriteArray(rkPacket, m_kServerOnStack);
	TWriteArray(rkPacket, m_kServerOffStack);
}

void PgCommandStack::ClearCommand()
{
	BM::CAutoMutex kLock(m_kStackMutex);
	m_kServerOffStack.clear();
	m_kServerOnStack.clear();
	m_kCurCommand.Clear();
}

void PgCommandStack::FailPrevCommand(const ContServerID& rkFailVec)
{
	BM::CAutoMutex kLock(m_kStackMutex);
	ContServerID::const_iterator fail_iter = rkFailVec.begin();
	while(rkFailVec.end() != fail_iter)
	{
		const ContServerID::value_type& rkElement = (*fail_iter);
		if( rkElement == m_kCurCommand.kServerID )
		{
			m_kCurCommand.Clear();
		}

		ContServerIDList::iterator find_iter;
		find_iter = std::remove(m_kServerOnStack.begin(), m_kServerOnStack.end(), rkElement);
		m_kServerOnStack.erase(find_iter, m_kServerOnStack.end());

		find_iter = std::remove(m_kServerOffStack.begin(), m_kServerOffStack.end(), rkElement);
		m_kServerOffStack.erase(find_iter, m_kServerOffStack.end());

		++fail_iter;
	}
}