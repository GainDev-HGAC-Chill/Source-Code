#include "StdAfx.h"
#include "PgChannelMgr.h"
#include "Global.h"
#include "Lohengrin/PacketStruct.h"
#include "PgLoginDlg.h"
#include "PgControlServerMgr.h"
#include "SuperVw.h"

PgChannelMgr::PgChannelMgr(void)
{
}

PgChannelMgr::~PgChannelMgr(void)
{
	Clear();
}

void PgChannelMgr::Clear()
{
	CHANNEL_MAP::iterator itor = m_kChannelMap.begin();
	while (m_kChannelMap.end() != itor)
	{
		PgChannel* pkChannel = itor->second;
		if (pkChannel != NULL)
		{
			delete pkChannel;
		}
		itor++;
	}
	m_kChannelMap.clear();
}

bool PgChannelMgr::ReadChannel()
{
	TCHAR chFile[MAX_PATH];
	GetMainDirectory(chFile, MAX_PATH);
	_tcscat_s(chFile, MAX_PATH, _T("DR2_ServerList.ini"));
	const BM::vstring SECTION_NAME = _T("SERVER");

	int i = 1;
	TCHAR chValue[100];

	while (GetPrivateProfileString(SECTION_NAME+i,NULL, NULL, chValue, 100, chFile) > 0)
	{
		TBL_SERVERLIST kServer;
		std::wstring kSIP = _T("");
		std::wstring kSNatIP = _T("");
		std::wstring kUIP = _T("");
		std::wstring kUNatIP = _T("");
		WORD wSPort, wSNatPort, wUPort, wUNatPort;
		wSPort = wSNatPort = wUPort = wUNatPort = 0;
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERNO"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%d"), &(kServer.iServerNo));
			kServer.iServerNo = _ttoi(chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("CHANNEL"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%d"), &(kServer.nChannel));
			kServer.nChannel = _ttoi(chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("NAME"), NULL, chValue, 100, chFile) > 0)
		{
			_tcscpy_s(kServer.szName, 21, chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("TYPE"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%d"), &(kServer.nServerType));
			kServer.nServerType = _ttoi(chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERBINDIP"), NULL, chValue, 100, chFile) > 0)
		{
			kSIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERBiNDPORT"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%hd"), &wSPort);
			wSPort = _ttoi(chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERNATIP"), NULL, chValue, 100, chFile) > 0)
		{
			kSNatIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("SERVERNATPORT"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%hd"), &wSNatPort);
			wSNatPort = _ttoi(chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERBINDIP"), NULL, chValue, 100, chFile) > 0)
		{
			kUIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERBINDPORT"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%hd"), &wUPort);
			wUPort = _ttoi(chValue);
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERNATIP"), NULL, chValue, 100, chFile) > 0)
		{
			kUNatIP = chValue;
		}
		if (GetPrivateProfileString(SECTION_NAME+i, _T("USERNATPORT"), NULL, chValue, 100, chFile) > 0)
		{
			//_stscanf_s(chValue, _T("%hd"), &wUNatPort);
			wUNatPort = _ttoi(chValue);
		}
		kServer.addrServerBind.Set(kSIP, wSPort);
		kServer.addrServerNat.Set(kSNatIP, wSNatPort);
		kServer.addrUserBind.Set(kUIP, wUPort);
		kServer.addrUserNat.Set(kUNatIP, wUNatPort);
		kServer.Build();

		AddServer(&kServer);
		if (kServer.nServerType == CEL::ST_MACHINE_CONTROL)
		{
			g_kServerMgr.AddServer(&kServer);
		}

		i++;
	}

	return true;	
}

bool PgChannelMgr::Init()
{
	if (!ReadChannel())
	{
		return false;
	}

	return false;
}

bool PgChannelMgr::AddServer(TBL_SERVERLIST* pkInfo)
{
	if (pkInfo == NULL)
	{
		return false;
	}

	PgChannel* pkFind = NULL;
	CHANNEL_MAP::iterator itor = m_kChannelMap.find(pkInfo->nChannel);
	if (m_kChannelMap.end() == itor)
	{
		BM::CAutoMutex kLock(m_kChannelLock.kObjectLock);
		pkFind = new PgChannel(pkInfo->nChannel);
		m_kChannelMap.insert(std::make_pair(pkInfo->nChannel, pkFind));
	}
	else
	{
		pkFind = itor->second;
	}
	ERIC_SERVERINFO kSInfo = *pkInfo;
	return pkFind->AddServer(&kSInfo);

}

void PgChannelMgr::GetFirstChannel(ObjectMapIterLoc<int, PgChannel*>& itor)
{
	itor.m_kItor = m_kChannelMap.end();
	itor.SetLock(&m_kChannelLock);
}

bool PgChannelMgr::GetNextChannel(ObjectMapIterLoc<int, PgChannel*>& itor)
{
	if (m_kChannelMap.end() == itor.m_kItor)
	{
		itor.m_kItor = m_kChannelMap.begin();
	}
	else
	{
		itor.m_kItor++;
	}

	if (m_kChannelMap.end() == itor.m_kItor)
	{
		return false;
	}

	return true;	
}

void PgChannelMgr::StartChannel(int iID)
{
	CC_SHOW_LOG(7, _T("Starting Channel ID[%d]"), iID);
	if (m_wstrID.length() == 0)
	{
		PgLoginDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			m_wstrID = (LPCTSTR) dlg.m_strID;
			m_wstrPassword = (LPCTSTR) dlg.m_strPassword;
		}
		else
		{
			MessageBox(NULL, _T("Aborted"), _T("Notice"), MB_OK);
			return;
		}
	}

	CHANNEL_MAP::iterator itor = m_kChannelMap.find(iID);
	if (m_kChannelMap.end() != itor)
	{
		itor->second->StartAllServer();
	}
}

LPCTSTR PgChannelMgr::GetLoginID()
{
	return m_wstrID.c_str();
}

LPCTSTR PgChannelMgr::GetLoginPassword()
{
	return m_wstrPassword.c_str();
}

void PgChannelMgr::Login(CEL::CSession_Base* pkSession, STryLoginResult* pkResult)
{
	if (pkResult->eResult != E_TLR_SUCCESS)
	{
		CC_SHOW_LOG(5, _T("Login failed.....Error[%d]"), pkResult->eResult);
		m_wstrID = _T("");
		m_wstrPassword = _T("");
		return;
	}
	SAddrInfo kAddr(pkSession->Addr().wstrIP, pkSession->Addr().wPort);
	
	g_kServerMgr.DoJob(&kAddr);
}

void PgChannelMgr::GetChannel(int iChannel, ObjectLock<PgChannel*>& kFind)
{
	CHANNEL_MAP::iterator itor = m_kChannelMap.find(iChannel);
	if (m_kChannelMap.end() == itor)
	{
		return;
	}
	kFind.SetValue(&m_kChannelLock, itor->second);
}

void PgChannelMgr::ResServerStatus(CEL::CPacket* const pkPacket)//서버 상태 업데이트
{
	short int sServerNum = 0;
	pkPacket->Pop(sServerNum);

	for (short int i=0; i<sServerNum; i++)
	{
		SERVER_IDENTITY kInfo;
		EServerStatus eStatus;
		short int sUserCount;
		pkPacket->Pop(kInfo);
		pkPacket->Pop(eStatus);
		pkPacket->Pop(sUserCount);

		ObjectLock<PgChannel*> kChannel;
		GetChannel(kInfo.nChannel, kChannel);
		if (kChannel.m_pkObject == NULL)
		{
			CC_SHOW_LOG(5, _T("[%s].....Cannot find Channel information Channel[%d], ServerNo[%d]"), __FUNCTIONW__, kInfo.nChannel, kInfo.iServerNo);
			continue;
		}

		//여기서 ini파일로 부터 만든 서버 목록에
		//Center로 부터 받은 서버 목록 상태를 업데이트 시킨다.
		ObjectLock<ERIC_SERVERINFO*> kServer;
		kChannel.m_pkObject->GetServer(kInfo.iServerNo, kServer);//TODO: 정확한 ini설정방법은?
		if (kServer.m_pkObject == NULL)
		{
			CC_SHOW_LOG(5, _T("[%s].....Cannot find Server information Channel[%d], ServerNo[%d], ServerType[%d]"), __FUNCTIONW__, kInfo.nChannel, kInfo.iServerNo, kInfo.nServerType);
			continue;
		}

		kServer.m_pkObject->eStatus = eStatus;
		kServer.m_pkObject->sUserCount = sUserCount;
	}

	//UI상의 서버 상태 업데이트
	((CSuperVw*)g_pkView)->UpdateServerList();
}
