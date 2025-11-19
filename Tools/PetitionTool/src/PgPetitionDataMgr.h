#pragma once

#define MAX_LOAD_PEITION		1000		//최대 1000개 까지 읽어옴

class PgPetitionDataMgr
{
private:
	CONT_PETITION_DATA m_kAllData;	
	CONT_PETITION_DATA m_kMyAssignData;

	bool	m_bReflash;
//	int		m_iAllCount;			//Petition Count	
//	int		m_iComplete;			//Complete Count

	mutable Loki::Mutex m_kMutex;
public:

	void ReqPetitionData();
	void RecvPetitionData(CEL::CPacket *pkPacket);
	void RecvUpdatePetitionData(CEL::CPacket * const pkPacket);
	void GetAllPetitionData(CONT_PETITION_DATA & rkOut) {rkOut = m_kAllData;};
	void GetMyAssignData(CONT_PETITION_DATA & rkOut) {rkOut = m_kMyAssignData;};
	void UpdatePetitionData(SPetitionData const &UpDateData);
	bool IsReflash() {return m_bReflash;};

	PgPetitionDataMgr(void);
	~PgPetitionDataMgr(void);
};

#define g_kPetitionDataMgr SINGLETON_STATIC(PgPetitionDataMgr)