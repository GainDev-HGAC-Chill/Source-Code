#pragma once

#include "variant/idobject.h"


class PgNpc :
	public IDObject
{
public:
	PgNpc(void);
	virtual ~PgNpc(void);

	virtual const TCHAR* GetName() { return NULL; }
	virtual int Tick(float fElapsedTime);
	virtual int CallAction(WORD wActCode, SActArg *pActArg);
	virtual int Register() { return 0; }

	/* -------------------------------- */
public:
	void Create(BM::GUID& rkGuid, const std::wstring& rstrkName, const std::wstring& rstrkActor, const std::wstring& rstrkScript, POINT3& rkPosition, int iID);
	void WriteToPacket(CEL::CPacket &rPacket);
	void AddBeginQuest(int iQuestID);
	void AddIngQuest(int iQuestID);
	int GetNpcID() { return m_iID; }
	POINT3 GetPos() { return m_kPosition; }

public:
	std::vector<int> m_kBeginQuest;	// Quest 시작 NPC가 자신인 것
	std::vector<int> m_kIngQuest;	// Quest 시작 후 자신과 관련된 것

private:
	TCHAR m_kName[MAX_NPC_NAME_LEN];
	TCHAR m_kActor[MAX_NPC_ACTOR_LEN];
	TCHAR m_kScript[MAX_SCRIPT_NAME_LEN];
	POINT3 m_kPosition;
	int m_iID;
};


