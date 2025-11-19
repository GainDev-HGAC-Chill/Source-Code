#include "StdAfx.h"

PgPetitionDataMgr::PgPetitionDataMgr(void):
m_bReflash(false)
{
}

PgPetitionDataMgr::~PgPetitionDataMgr(void)
{
	m_kAllData.clear();
	m_kMyAssignData.clear();
}

void PgPetitionDataMgr::ReqPetitionData()
{
	BM::CAutoMutex kLock(m_kMutex);

	CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_GET_PETITIONDATA);
	kPacket.Push(g_kProcessInfoMgr.m_kMyInfo.kMemberGuid);
	kPacket.Push(g_kProcessInfoMgr.m_kMyInfo.RealmNo());
	g_kNetwork.SendToLoginServer(kPacket);
	INFO_LOG(BM::LOG_LV6, _T("Request PetitionData"));
}

void PgPetitionDataMgr::RecvPetitionData(CEL::CPacket *pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);

	m_kAllData.clear();
	m_kMyAssignData.clear();

	if(pkPacket == NULL)
	{
		INFO_LOG(BM::LOG_LV4,_T("Packet is NULL"));
		return ;
	}

	int iSize = 0;

	pkPacket->Pop(iSize);

	while(iSize > 0)
	{
		CONT_PETITION_DATA::value_type kTemp;
		kTemp.ReadFromPacket(*pkPacket);

		if( (kTemp.m_State == EPSTATE_ASSIGN) && (kTemp.m_GmId == g_kProcessInfoMgr.m_kMyInfo.kMemberGuid) )
		{
			m_kMyAssignData.push_back(kTemp);
		} else
			if( (kTemp.m_State == EPSTATE_NONE) && (kTemp.m_GmId == BM::GUID::NullData()) )
		{
			m_kAllData.push_back(kTemp);
		}
		--iSize;
	}
	m_bReflash = true;
}

void PgPetitionDataMgr::UpdatePetitionData(SPetitionData const &UpDateData)
{
	BM::CAutoMutex kLock(m_kMutex);

	CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_MODIFY_PETITIONDATA);
	kPacket.Push(g_kProcessInfoMgr.m_kMyInfo.kMemberGuid);
	UpDateData.WriteToPacket(kPacket);
	g_kNetwork.SendToLoginServer(kPacket);
}

void PgPetitionDataMgr::RecvUpdatePetitionData(CEL::CPacket * const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);

	int iSize = 0;
	pkPacket->Pop(iSize);
	while(iSize > 0)
	{
		SPetitionData kUpdateData;
		kUpdateData.ReadFromPacket(*pkPacket);

		//전체 진정검색
		CONT_PETITION_DATA::iterator All_Itr = m_kAllData.begin();
		while(All_Itr != m_kAllData.end())
		{
			if(All_Itr->m_PetitionId == kUpdateData.m_PetitionId)
			{
				All_Itr->m_State		= kUpdateData.m_State;
				All_Itr->m_Kind			= kUpdateData.m_Kind;
				All_Itr->m_GmId			= kUpdateData.m_GmId;
				All_Itr->m_Answerkind	= kUpdateData.m_Answerkind;
				All_Itr->m_dtStartTime	= kUpdateData.m_dtStartTime;
				All_Itr->m_dtEndTime	= kUpdateData.m_dtEndTime;

				CONT_PETITION_DATA::value_type const &kElement = (*All_Itr);
				//내용이 수정되는 경우는 자신 아니면 다른 GM에게 할당될때다.
				if(kUpdateData.m_GmId == g_kProcessInfoMgr.m_kMyInfo.kMemberGuid
					&& kUpdateData.m_State == EPSTATE_ASSIGN)
				{
					m_kMyAssignData.push_back(kElement);
				}
				m_kAllData.erase(All_Itr);
				return ;
			}
			++All_Itr;
		}

		//내 진정검색
		CONT_PETITION_DATA::iterator My_Itr = m_kMyAssignData.begin();
		while(My_Itr != m_kMyAssignData.end())
		{
			if(My_Itr->m_PetitionId == kUpdateData.m_PetitionId)
			{
				My_Itr->m_State		= kUpdateData.m_State;
				My_Itr->m_Kind			= kUpdateData.m_Kind;
				My_Itr->m_GmId			= kUpdateData.m_GmId;
				My_Itr->m_Answerkind	= kUpdateData.m_Answerkind;
				My_Itr->m_dtStartTime	= kUpdateData.m_dtStartTime;
				My_Itr->m_dtEndTime		= kUpdateData.m_dtEndTime;

				CONT_PETITION_DATA::value_type const &kElement = (*My_Itr);
				//내쪽에서 수정되는 경우는 완료되거나 타 GM에게 가거나 다시 모든 진정으로 돌아가는거다.
				if(BM::GUID::IsNull(kUpdateData.m_GmId)
					&& kUpdateData.m_State == EPSTATE_NONE)
				{
					m_kAllData.push_back(kElement);
				}
				m_kMyAssignData.erase(My_Itr);
				return ;
			}
			++My_Itr;
		}
		--iSize;
	}
}