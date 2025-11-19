#pragma once

#ifdef USE_OLD_GMSERVER

//#include "GMToolDev/GMPacketInfo.h"
#include "GMToolDev/GMPacketInfo_CS.h"
#include "GMToolDev/GMPacketInfo_SC.h"
#include "Winsock2.h"

class CGeneralDlg;

class CGMServer :
	public CSingleton<CGMServer>
{
	//api
public:
	WSADATA wsaData;
	SOCKET ServerSocket;
	SOCKADDR_IN ServerAddress;

	SOCKADDR_IN ClientAddress;
	SOCKET ClientSocket;
	int AddressSize;
	HANDLE m_hThread;

public:
	bool m_bRunning;
	bool m_bConnect;
	CGeneralDlg *m_pkStateDlg;		// 상태표시를 위한 다이얼로그

public:
	CGMServer(void);
	virtual ~CGMServer(void);

public:
	bool Initialize();
	void SetDialog(CGeneralDlg *pkDlg);
	bool Terminate();
	void Connect();
	void MakeThread();
	void TermThread();
	void SendMessageConnect();
	void SendMessageDisConnect();
	void DisConnect();
	int Send(int iLen, char *pkString);

public:
	__inline bool GetConnected() const;

public:
	//send
	void Send_NetReqMapMove(DWORD dwMapNo, float fX, float fY, float fZ);
	void Send_Chat(wchar_t *pwString);
	void Send_Notice(wchar_t *pwString);
	void Send_NoticeWithColor(wchar_t *pwString, DWORD dwColor);
	void Send_ChangeClass(SCPacket_ChangeClass::ESCPacket_ChangeClass eClassType, DWORD dwLevel);
	//void Send_Notice(std::wstring wstrString);

	//recv
	void PacketProcess(char *pkData);

};

#define g_pkGMServer	CGMServer::GetSingleton()

__inline bool CGMServer::GetConnected() const
{
	return m_bConnect;
}

#endif