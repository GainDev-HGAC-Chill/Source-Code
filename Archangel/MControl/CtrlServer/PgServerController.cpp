#include "StdAfx.h"
#include "Global.h"
#include "PgServerController.h"
#include "Lohengrin/PacketStruct.h"
#include "PgClientMng.h"


PgServerController::PgServerController(void)
: m_kServerPool(1, 1), m_kCenterPool(1, 1)
{
}

PgServerController::~PgServerController(void)
{
}

void PgServerController::AddAccount(LPCTSTR lpszID, LPCTSTR lpszPassword)
{
	if (lpszID == NULL || lpszPassword == NULL)
	{
		return;
	}
	SIMPLE_ACCOUNT kAccount;
	_tcscpy_s(kAccount.chID, 21, lpszID);
	_tcscpy_s(kAccount.chPW, 21, lpszPassword);
	
	m_kAccountInfo.push_back(kAccount);
}

void PgServerController::AddServerFile(CEL::E_SESSION_TYPE eType, LPCTSTR lpszPath, LPCTSTR lpszParam)
{
	if (lpszPath == NULL)
	{
		return;
	}
	SERVER_FILE kInfo;
	kInfo.eType = eType;
	_tcscpy_s(kInfo.chPath, MAX_PATH, lpszPath);
	if (lpszParam == NULL)
	{
		kInfo.chParam[0] = _T('\0');
	}
	else
	{
		_tcscpy_s(kInfo.chParam, MAX_PATH, lpszParam);
	}

	m_kServerFile.insert(std::make_pair(eType, kInfo));
}

void PgServerController::Login(const BM::GUID& rkSession, SClientTryLogin* pkLogin)
{
	if (pkLogin == NULL)
	{
		return;
	}
	STryLoginResult kLogR(*pkLogin);
	kLogR.eResult = E_TLR_SUCCESS;
	kLogR.iExtValue = 0;
	kLogR.guidParent = BM::GUID();
	kLogR.guidChild = BM::GUID();
	
	SIMPLE_ACCOUNT kAccount;
	if (!GetAccount(pkLogin->szID, &kAccount))
	{
		kLogR.eResult = E_TLR_WRONG_ID;
	}
	else
	{
		if (_tcsicmp(kAccount.chPW, pkLogin->szPW) != 0)
		{
			kLogR.eResult = E_TLR_WRONG_PASS;
		}
		else
		{
			// Success
			ObjectLock<PgCtrlClient*> kClient;
			g_kClientMng.GetClient(rkSession, &kClient);
			if (kClient.m_pkObject != NULL)
			{
				kClient.m_pkObject->Logined();
			}
		}
	}
	CEL::CPacket kRPacket(PT_CS_CC_RES_LOGIN, kLogR);
	g_kClientMng.Send(rkSession, kRPacket);
	/*
	This Client will be deleted in Timer
	if (kLogR.eResult != E_TLR_SUCCESS)
	{
		g_kClientMng.Disconnect(rkSession);
	}
	*/
}

bool PgServerController::GetAccount(LPCTSTR lpszID, SIMPLE_ACCOUNT* pkOut)
{
	if (lpszID == NULL || pkOut == NULL)
	{
		return false;
	}
	int iSize = m_kAccountInfo.size();
	for (int i=0; i<iSize; i++)
	{
		SIMPLE_ACCOUNT& rkInfo = m_kAccountInfo.at(i);
		if (_tcsicmp(rkInfo.chID, lpszID) == 0)
		{
			*pkOut = rkInfo;
			return true;
		}
	}
	return false;
}

// PT_CC_CS_REQ_STARTSERVER
// [PARAMETER]
//	pkSInfo : Server information to start
//	pkCenterAddr : Center server addresss
void PgServerController::StartServer(const BM::GUID& rkSession, TBL_SERVERLIST* pkSInfo, SAddrInfo* pkCenterAddr)
{
	if (pkSInfo == NULL || pkCenterAddr == NULL)
	{
		INFO_LOG( BM::LOG_LV4, _T("[%S] Paramter is NULL.....pkSInfo[%08X], pkCenterAddr[%08X]"), _T(__FUNCTION__), pkSInfo, pkCenterAddr);
		return;
	}
	INFO_LOG(BM::LOG_LV5, _T("[%s][%d] ChannelID[%d], ServerNo[%d], ServerType[%d]....CenterIP[%s:%d]"), _T(__FUNCTION__), __LINE__, pkSInfo->nChannel, pkSInfo->iServerNo, pkSInfo->nServerType,
		pkCenterAddr->StrIP().c_str(), pkCenterAddr->wPort);

	AddServer(pkSInfo);
	
	SERVER_FILE* pkFileInfo = GetServerFileInfo((CEL::E_SESSION_TYPE)pkSInfo->nServerType);
	if (pkFileInfo == NULL)
	{
		INFO_LOG(BM::LOG_LV4, _T("[%s] Cannot find Server File information ChannelID[%d], ServerNo[%d], ServerType[%d]"), _T(__FUNCTION__),
			pkSInfo->nChannel, pkSInfo->iServerNo, pkSInfo->nServerType);
		return;
	}
	TCHAR chPath[MAX_PATH];
	TCHAR chParam[MAX_PATH];
	TCHAR chCommandLine[MAX_PATH*2];
	MakeExeParameter(pkSInfo, pkCenterAddr, pkFileInfo->chParam, chParam);
	_stprintf_s(chCommandLine, MAX_PATH*2, _T("\"%s\" %s"), pkFileInfo->chPath, chParam);
	_tcscpy_s(chPath, MAX_PATH, pkFileInfo->chPath);
	GetPathWithoutFilename(pkFileInfo->chPath, chPath, MAX_PATH);
	STARTUPINFO stInfo;
	PROCESS_INFORMATION prInfo;
	ZeroMemory(&stInfo, sizeof(STARTUPINFO));
	ZeroMemory(&prInfo, sizeof(PROCESS_INFORMATION));
	stInfo.cb = sizeof(STARTUPINFO);
	int iError = ERROR_SUCCESS;
	if (!CreateProcess(NULL, chCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, chPath,&stInfo, &prInfo))
	{
		iError = GetLastError();
		INFO_LOG(BM::LOG_LV4, _T("[%s] CreateProcess failure ErroCode[%d], CommandLine[%s]"), _T(__FUNCTION__), iError, chCommandLine);
	}

	CEL::CPacket kCPacket(PT_CS_CC_RES_STARTSERVER, *pkSInfo);
	kCPacket.Push(iError);
	g_kClientMng.Send(rkSession, kCPacket);	
}

bool PgServerController::AddServer(SERVER_IDENTITY* pkServer)
{
	if (pkServer == NULL)
	{
		return false;
	}
	{
		ObjectLock<PgCtrlServer*> kFind;
		GetServer(pkServer->nChannel, pkServer->iServerNo, kFind);
		if (kFind.m_pkObject != NULL)
		{
			return false;
		}
	}

	{
		PgCtrlServer* pkNew = m_kServerPool.New();
		pkNew->Set(pkServer);
		BM::CAutoMutex kLock(m_kServerLock.kObjectLock);
		m_kServer.push_back(pkNew);
	}

	return true;
}

void PgServerController::GetServer(int iChannel, int iServerNo, ObjectLock<PgCtrlServer*>& kFind)
{
	m_kServerLock.IncRefCount();

	CTRLSERVER_LIST::iterator itor = m_kServer.begin();
	while (m_kServer.end() != itor)
	{
		if (((*itor)->GetChannelID() == iChannel) && ((*itor)->GetServerNo() == iServerNo))
		{
			kFind.SetValue(&m_kServerLock, *itor);
			break;
		}
		itor++;
	}

	m_kServerLock.DecRefCount();
}

SERVER_FILE* PgServerController::GetServerFileInfo(CEL::E_SESSION_TYPE eType)
{
	SERVERFILE_MAP::iterator itor = m_kServerFile.find((int)eType);
	if (m_kServerFile.end() == itor)
	{
		return NULL;
	}
	return &(itor->second);	// SERVER_FILE 정보는 초기에만 Setting되고, 이후 추가/삭제 등이 이루어 지지 않는다고 가정해야 한다.
}

bool PgServerController::MakeExeParameter(TBL_SERVERLIST* pkSInfo, SAddrInfo* pkCenterAddr, LPCTSTR lpszSource, LPTSTR lpszParam)
{
	if (lpszSource == NULL || lpszParam == NULL)
	{
		return false;
	}
	
	LPCTSTR lpszFind[] = { _T("%CHANNELID%"), _T("%SERVERID%"), _T("%CENTERIP%"), _T("%CENTERPORT%"), NULL };
	_tcscpy_s(lpszParam, MAX_PATH, lpszSource);
	int iIndex = 0;
	LPTSTR lpszFound = NULL;
	while (lpszFind[iIndex] != NULL)
	{
		while ((lpszFound = _tcsstr(lpszParam, lpszFind[iIndex])) != NULL)
		{
			*lpszFound = _T('\0');
			TCHAR chTemp[MAX_PATH];
			LPCTSTR lpszSecond = (lpszFound+_tcslen(lpszFind[iIndex]) == NULL) ? _T("") : lpszFound+_tcslen(lpszFind[iIndex]);
			switch (iIndex)
			{
			case 0:
				_stprintf_s(chTemp, MAX_PATH, _T("%s%d%s"), lpszParam, pkSInfo->nChannel, lpszSecond);
				break;
			case 1:
				_stprintf_s(chTemp, MAX_PATH, _T("%s%d%s"), lpszParam, pkSInfo->iServerNo, lpszSecond);
				break;
			case 2:
				_stprintf_s(chTemp, MAX_PATH, _T("%s%s%s"), lpszParam, pkCenterAddr->StrIP().c_str(), lpszSecond);
				break;
			case 3:
				_stprintf_s(chTemp, MAX_PATH, _T("%s%hd%s"), lpszParam, pkCenterAddr->wPort, lpszSecond);
				break;
			}
			_tcscpy_s(lpszParam, MAX_PATH, chTemp);
		}
		iIndex++;
	}

	return true;
}

void PgServerController::ReqServerStatus(const BM::GUID& rkSession, TBL_SERVERLIST* pkSInfo, SAddrInfo* pkCenterAddr)
{
	if (pkSInfo == NULL || pkCenterAddr == NULL)
	{
		INFO_LOG( BM::LOG_LV4, _T("[%S] Paramter is NULL.....pkSInfo[%08X], pkCenterAddr[%08X]"), _T(__FUNCTION__), pkSInfo, pkCenterAddr);
		return;
	}
	INFO_LOG(BM::LOG_LV5, _T("[%s][%d] ChannelID[%d], ServerNo[%d], ServerType[%d]....CenterIP[%s:%d]"), _T(__FUNCTION__), __LINE__, pkSInfo->nChannel, pkSInfo->iServerNo, pkSInfo->nServerType,
		pkCenterAddr->StrIP().c_str(), pkCenterAddr->wPort);

	AddServer(pkSInfo);
	AddCenter(pkSInfo->nChannel, pkCenterAddr);
	AddCenterListener(pkSInfo->nChannel, rkSession);

	ObjectLock<SIMPLE_CENTER_INFO*> kFind;
	GetCenter(pkCenterAddr, kFind);
	if (kFind.m_pkObject == NULL)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer bConnected[%d], ConnectorGuid[%s], SessionGuid[%s], Addr[%s:%hd]"), _T(__FUNCTION__), 
			pkCenterAddr->StrIP().c_str(), pkCenterAddr->wPort);
		return;
	}

	ObjectLock<PgCtrlServer*> kServer;
	GetServer(pkSInfo->nChannel, pkSInfo->iServerNo, kServer);
	if (kServer.m_pkObject == NULL)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot fine Server inforamtion Channel[%d], ServerNo[%d]"), _T(__FUNCTION__), pkSInfo->nChannel, pkSInfo->iServerNo);
		return;
	}

	if (!kFind.m_pkObject->bConnected)
	{
		BM::GUID kGuid = BM::GUID();
		CEL::ADDR_INFO kCAddr(pkCenterAddr->StrIP(), pkCenterAddr->wPort);
		g_kCoreCenter.Connect(m_kConnectorObjGuid, kCAddr, kGuid);
		return;
	}
	else if (kServer.m_pkObject->GetStatus() == SSTATUS_UNKNOWN)
	{
		QueryServerStatus(pkSInfo->nChannel);
	}
	else
	{
		SendChannelInfo(rkSession, pkSInfo->nChannel);
	}
}

void PgServerController::AddCenter(int iChannelID, SAddrInfo* pkAddr)
{
	if (pkAddr == NULL)
	{
		return;
	}
	{
		ObjectLock<SIMPLE_CENTER_INFO*> kFind;
		GetCenter(iChannelID, kFind);
		if (kFind.m_pkObject != NULL)
		{
			return;
		}
	}

	{
		SIMPLE_CENTER_INFO* pkNew = m_kCenterPool.New();
		pkNew->bConnected = false;
		pkNew->nChannel = iChannelID;
		pkNew->kAddr = *pkAddr;

		BM::CAutoMutex kLock(m_kServerLock.kObjectLock);
		m_kCenter.push_back(pkNew);
	}
}

void PgServerController::GetCenter(int iChannel, ObjectLock<SIMPLE_CENTER_INFO*>& kFind)
{
	m_kCenterLock.IncRefCount();

	SIMPLE_CENTER_LIST::iterator itor = m_kCenter.begin();
	while (m_kCenter.end() != itor)
	{
		if ((*itor)->nChannel == iChannel)
		{
			kFind.SetValue(&m_kCenterLock, *itor);
			break;
		}
		itor++;
	}

	m_kCenterLock.DecRefCount();
}

void PgServerController::ConnectedCenter(bool bConnected, const BM::GUID& rkConnector, const BM::GUID& rkSession, SAddrInfo* pkAddr)
{
	ObjectLock<SIMPLE_CENTER_INFO*> kFind;
	GetCenter(pkAddr, kFind);
	if (kFind.m_pkObject == NULL)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer bConnected[%d], ConnectorGuid[%s], SessionGuid[%s], Addr[%s:%hd]"), _T(__FUNCTION__), bConnected,
			rkConnector.str().c_str(), rkSession.str().c_str(), pkAddr->StrIP().c_str(), pkAddr->wPort);
		return;
	}
	INFO_LOG(BM::LOG_LV5, _T("[%s] Connected to Center....bConnected[%d], ConnectorGuid[%s], SessionGuid[%s], Addr[%s:%hd]"), _T(__FUNCTION__), bConnected,
		rkConnector.str().c_str(), rkSession.str().c_str(), pkAddr->StrIP().c_str(), pkAddr->wPort);

	if (bConnected)
	{
		kFind.m_pkObject->bConnected = true;
		kFind.m_pkObject->kConnectGuid = rkConnector;
		kFind.m_pkObject->kSessionGuid = rkSession;
		//QueryServerStatus(kFind.m_pkObject->nChannel);
	}
	else
	{
		kFind.m_pkObject->bConnected = false;
		kFind.m_pkObject->kConnectGuid = BM::GUID();
		kFind.m_pkObject->kSessionGuid = BM::GUID();
	}

}

void PgServerController::GetCenter(SAddrInfo* pkAddr, ObjectLock<SIMPLE_CENTER_INFO*>& kFind)
{
	m_kCenterLock.IncRefCount();

	SIMPLE_CENTER_LIST::iterator itor = m_kCenter.begin();
	while (m_kCenter.end() != itor)
	{
		if ((*itor)->kAddr == *pkAddr)
		{
			kFind.SetValue(&m_kCenterLock, *itor);
			break;
		}
		itor++;
	}

	m_kCenterLock.DecRefCount();
}

void PgServerController::AddCenterListener(int iChannelID, const BM::GUID& rkClientSession)
{
	ObjectLock<SIMPLE_CENTER_INFO*> kFind;
	GetCenter(iChannelID, kFind);
	if (kFind.m_pkObject == NULL)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer iChannelID"), _T(__FUNCTION__), iChannelID);
		return;
	}

	std::list<BM::GUID>::iterator itor = kFind.m_pkObject->kListenClient.begin();
	while (itor != kFind.m_pkObject->kListenClient.end())
	{
		if ((*itor) == rkClientSession)
		{
			return;
		}
		itor++;
	}
	kFind.m_pkObject->kListenClient.push_back(rkClientSession);
}

void PgServerController::DeleteJob(const BM::GUID& rkClientSession)
{
	{
		BM::CAutoMutex kLock(m_kCenterLock.kObjectLock);
		SIMPLE_CENTER_LIST::iterator itor = m_kCenter.begin();
		while (itor != m_kCenter.end())
		{
			(*itor)->kListenClient.remove(rkClientSession);

			itor++;
		}
	}
	{
		BM::CAutoMutex kLock(m_kServerLock.kObjectLock);
		CTRLSERVER_LIST::iterator itor = m_kServer.begin();
		while (itor != m_kServer.end())
		{
			(*itor)->DeleteJob(rkClientSession);

			itor++;
		}
	}
	
}

void PgServerController::QueryServerStatus(int iChannelID)
{
	CEL::CPacket kSPacket(PT_CS_T_REQ_SERVERSTATUS);
	SendCenter(iChannelID, kSPacket);
}

void PgServerController::SendCenter(int iChannelID, CEL::CPacket& rkPacket)
{
	ObjectLock<SIMPLE_CENTER_INFO*> kFind;
	GetCenter(iChannelID, kFind);
	if (kFind.m_pkObject == NULL)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer iChannelID"), _T(__FUNCTION__), iChannelID);
		return;
	}
	g_kCoreCenter.Send(kFind.m_pkObject->kConnectGuid, kFind.m_pkObject->kSessionGuid, rkPacket);
}

void PgServerController::SendChannelInfo(const BM::GUID& rkClientSession, int iChannelID)
{
	short int sNum = 0;
	CEL::CPacket kCPacket(PT_CS_CC_RES_SERVERSTATUS);
	int iPacketPos = kCPacket.GetWritePos();
	kCPacket.Push(sNum);
	ObjectListIterLoc<PgCtrlServer*> kServer;
	GetFirstServer(kServer);
	while (GetNextServer(iChannelID, kServer))
	{
		TBL_SERVERLIST kInfo;
		kInfo.nChannel = (*(kServer.m_kItor))->GetChannelID();
		kInfo.iServerNo = (*(kServer.m_kItor))->GetServerNo();
		kInfo.nServerType = (int) (*(kServer.m_kItor))->GetType();
		kCPacket.Push(kInfo);
		kCPacket.Push((*(kServer.m_kItor))->GetStatus());

		sNum++;
	}

	if (sNum != 0)
	{
		kCPacket.ModifyData(iPacketPos, &sNum, sizeof(short int));
	}
	g_kClientMng.Send(rkClientSession, kCPacket);

}

void PgServerController::GetFirstServer(ObjectListIterLoc<PgCtrlServer*>& kFind)
{
	m_kServerLock.IncRefCount();

	kFind.m_kItor = m_kServer.end();
	kFind.SetLock(&m_kServerLock);

	m_kServerLock.DecRefCount();
}

bool PgServerController::GetNextServer(int iChannelID, ObjectListIterLoc<PgCtrlServer*>& kItor)
{
	if (m_kServer.end() == kItor.m_kItor)
	{
		kItor.m_kItor = m_kServer.begin();
	}
	else
	{
		kItor.m_kItor++;
	}

	while (m_kServer.end() != kItor.m_kItor)
	{
		if ((*(kItor.m_kItor))->GetChannelID() == iChannelID)
		{
			return true;
		}
		kItor.m_kItor++;
	}
	return false;
}

void PgServerController::ResServerStatus(int iChannelID, CEL::CPacket * const pkPacket)
{
	short int sServerNum = 0;
	pkPacket->Pop(sServerNum);
	CEL::CPacket kOPacket(PT_CS_CC_RES_SERVERSTATUS, sServerNum);

	for (short int i=0; i<sServerNum; i++)
	{
		SERVER_IDENTITY kInfo;
		EServerStatus eStatus;
		short int sUserNum = 0;
		pkPacket->Pop(kInfo);
		pkPacket->Pop(eStatus);
		pkPacket->Pop(sUserNum);

		AddServer(&kInfo);
		{
			ObjectLock<PgCtrlServer*> kFind;
			GetServer(kInfo.nChannel, kInfo.iServerNo, kFind);
			if (kFind.m_pkObject != NULL)
			{
				kFind.m_pkObject->SetStatus(eStatus);
				kFind.m_pkObject->SetUserCount(sUserNum);
			}
		}

		kOPacket.Push(kInfo);
		kOPacket.Push(eStatus);
		kOPacket.Push(sUserNum);
	}

	{
		// Sending Server Status
		ObjectLock<SIMPLE_CENTER_INFO*> kCenter;
		GetCenter(iChannelID, kCenter);
		if (kCenter.m_pkObject == NULL)
		{
			INFO_LOG(BM::LOG_LV5, _T("[%s] [ERROR].....Cannot find CenterServer iChannelID"), _T(__FUNCTION__), iChannelID);
		}
		std::list<BM::GUID>::iterator itor = kCenter.m_pkObject->kListenClient.begin();
		while (itor != kCenter.m_pkObject->kListenClient.end())
		{
			g_kClientMng.Send(*itor, kOPacket);
			itor++;
		}
	}

}
