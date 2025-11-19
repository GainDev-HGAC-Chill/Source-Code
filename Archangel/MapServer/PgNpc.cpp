#include "stdafx.h"
#include "PgNpc.h"


PgNpc::PgNpc(void)
{
	SetID(BM::GUID());
	m_iID = 0;
}

PgNpc::~PgNpc(void)
{
}

int PgNpc::Tick(float fElapsedTime)
{
	return 0;
}


int PgNpc::CallAction(WORD wActCode, SActArg *pActArg)
{
	return 0;
}

void PgNpc::Create(BM::GUID& rkGuid, const std::wstring& rstrkName, const std::wstring& rstrkActor, const std::wstring& rstrkScript, POINT3& rkPosition, int iID)
{
	SetID(rkGuid);
	_tcscpy_s(m_kName, MAX_NPC_NAME_LEN, rstrkName.c_str());
	_tcscpy_s(m_kActor, MAX_NPC_ACTOR_LEN, rstrkActor.c_str());
	_tcscpy_s(m_kScript, MAX_SCRIPT_NAME_LEN, rstrkScript.c_str());
	m_iID = iID;

	m_kPosition = rkPosition;
}


void PgNpc::WriteToPacket(CEL::CPacket &rkPacket)
{
	SNpcInfo info;
	info.guid = GetID();
	strcpy_s(info.chName, MAX_NPC_NAME_LEN, MB(m_kName));
	strcpy_s(info.chActor, MAX_NPC_ACTOR_LEN, MB(m_kActor));
	strcpy_s(info.chScript, MAX_SCRIPT_NAME_LEN, MB(m_kScript));
	//_tcscpy_s(info.chName, MAX_NPC_NAME_LEN, m_kName);
	//_tcscpy_s(info.chActor, MAX_NPC_ACTOR_LEN, m_kActor);
	//_tcscpy_s(info.chScript, MAX_SCRIPT_NAME_LEN, m_kScript);
	info.ptPosition = m_kPosition;

	rkPacket.Push(info);
}

void PgNpc::AddBeginQuest(int iQuestID)
{
	m_kBeginQuest.push_back(iQuestID);
	std::sort(m_kBeginQuest.begin(), m_kBeginQuest.end());
}

void PgNpc::AddIngQuest(int iQuestID)
{
	m_kIngQuest.push_back(iQuestID);
	std::sort(m_kIngQuest.begin(), m_kIngQuest.end());
}
