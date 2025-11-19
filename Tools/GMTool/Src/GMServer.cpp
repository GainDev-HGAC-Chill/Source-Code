#include "StdAfx.h"

#ifdef USE_OLD_GMSERVER
#include "resource.h"
#include "GeneralDlg.h"
#include "GMServer.h"

unsigned long __stdcall GMThread( void *arg )
{
	// 소켓 생성
	g_pkGMServer->ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( g_pkGMServer->ServerSocket == INVALID_SOCKET )
	{
		ASSERT( !"소켓을 생성할수 없습니다." );
		WSACleanup();
		return 1;
	}

	// 포트 바인딩
	g_pkGMServer->ServerAddress.sin_family = AF_INET;
	g_pkGMServer->ServerAddress.sin_addr.s_addr = INADDR_ANY;
	g_pkGMServer->ServerAddress.sin_port = htons( GM_CONNECT_PORT );
	if( bind(g_pkGMServer->ServerSocket,(SOCKADDR*)&g_pkGMServer->ServerAddress,sizeof(g_pkGMServer->ServerAddress)) == SOCKET_ERROR )
	{
		ASSERT( !"bind() failed with error %d \n" );
		closesocket(g_pkGMServer->ServerSocket);
		return 2;
	}

	// 포트 열기
	if( listen(g_pkGMServer->ServerSocket,SOMAXCONN) == SOCKET_ERROR )
	{
		ASSERT( !"listen함수 설정을 실패했습니다." );
		closesocket(g_pkGMServer->ServerSocket);
		return 3;
	}

	// 여기서 부터 프로세싱
    while( g_pkGMServer->m_bRunning )
    {
		bool bDisconnected = false;

		// 접속 대기
		g_pkGMServer->ClientSocket =
			accept(g_pkGMServer->ServerSocket, 
				(struct sockaddr*)&g_pkGMServer->ClientAddress, 
				&g_pkGMServer->AddressSize); //접속을 받아들임.
		if(!g_pkGMServer ||
			g_pkGMServer->ClientSocket == INVALID_SOCKET)
		{
			break;
		}
		// Connect
		g_pkGMServer->SendMessageConnect();

		// 여기서 부터 프로세싱
		while(!bDisconnected)
		{
			////
			// 총 데이터 길이를 받음
			int iRecvsize=0;
			int iLen=0;
			
			char *pkLen = new char[4];
			memset(pkLen, 0, 4);
			char *pkLenTemp = new char[4];
			memset(pkLenTemp, 0, 4);

			while(iRecvsize < 4 &&
				g_pkGMServer->m_bRunning)
			{
				//(char *)&iLen
				int rettmp = recv(g_pkGMServer->ClientSocket, pkLenTemp, 4-iRecvsize, 0 ); //데이터를 읽어들임.
				
				if (rettmp > 0)
				{
					memcpy(&(pkLen[iRecvsize]), pkLenTemp, rettmp);
					memset(pkLenTemp, 0, 4);
					iRecvsize += rettmp;
				}
				else if(rettmp <= 0)
				{
					bDisconnected = true;
					break;
				}
			}
			if(bDisconnected || !g_pkGMServer->m_bRunning)
			{
				g_pkGMServer->SendMessageDisConnect();
				break;
			}

			int *piLen = (int *)pkLen;
			iLen = *piLen;
			delete[] pkLen;
			delete[] pkLenTemp;

			////
			// 진짜 데이터를 받음
			int iGetSize = 0;
			char *pcBuffer = new char[iLen];	
			char *pcBufferTemp = new char[iLen];
			while(iGetSize < iLen &&
				g_pkGMServer->m_bRunning)
			{
				int rettmp = recv(g_pkGMServer->ClientSocket, pcBufferTemp, iLen-iGetSize, 0);

				if (rettmp > 0)
				{
					memcpy(&(pcBuffer[iGetSize]), pcBufferTemp, rettmp);
					memset(pcBufferTemp, 0, iLen);
					iGetSize += rettmp;
				}
				else if(rettmp <= 0)
				{
					bDisconnected = true;
				}
			}
			if (bDisconnected || !g_pkGMServer->m_bRunning)
			{
				break;
			}

			// 데이터 처리
			g_pkGMServer->PacketProcess(pcBuffer);

			delete[] pcBufferTemp;
			delete[] pcBuffer;
		}

		closesocket(g_pkGMServer->ClientSocket);
	}
	
	// 끝
	g_pkGMServer->m_bRunning = false;
	closesocket( g_pkGMServer->ClientSocket ); //해당 소켓이 닫혔음.
	g_pkGMServer->DisConnect();

    return 1;
}

CGMServer::CGMServer(void)
{
	m_pkStateDlg = 0;
	m_bConnect = false;
}

CGMServer::~CGMServer(void)
{
}

bool CGMServer::Initialize()
{
	m_bRunning = true;
	m_bConnect = false;
	Connect();
	MakeThread();

	return true;
}

void CGMServer::SetDialog(CGeneralDlg *pkDlg)
{
	m_pkStateDlg = pkDlg;
}

bool CGMServer::Terminate()
{
	return true;
}

void CGMServer::Connect()
{
	ClientSocket = 0;
	//ServerPort = GM_CONNECT_PORT;
	
	// WinSock 모듈 장착
	if (WSAStartup(MAKEWORD( 2, 2 ),&wsaData) == SOCKET_ERROR)
	{
		ASSERT(!"WSAStartup설정에서 문제 발생");
	}

	AddressSize = sizeof( ClientAddress ); //주소 크기를 저장하는

}

void CGMServer::MakeThread()
{
    unsigned long TempValL;
	m_hThread = CreateThread( NULL, 0, GMThread, 0, 0, &TempValL );
}

void CGMServer::TermThread()
{
}

void CGMServer::SendMessageConnect()
{
	m_bConnect = true;

	if (m_pkStateDlg)
	{
		m_pkStateDlg->SetWindowText(L"Main (Connected)");
	}
}

void CGMServer::SendMessageDisConnect()
{
	m_bConnect = false;

	if (m_pkStateDlg)
	{
		m_pkStateDlg->SetWindowText(L"Main (Disconnected)");
	}
}

void CGMServer::DisConnect()
{
	if (!this)
		return;

	closesocket( ServerSocket ); //소켓을 닫습니다.
	WSACleanup();

	TermThread();
}

int CGMServer::Send(int iLen, char *pkString)
{
	if (!m_bRunning)
	{
		return 0;
	}
	if (!m_bConnect)
	{
		return 0;
	}

	char *pkLen;
	pkLen = (char *)&iLen;

	int iSendsize=0;
	while(iSendsize < 4)
	{
		int ActualSendSize = send( ClientSocket,
			pkLen+iSendsize,
			4-iSendsize,
			0);

		if (ActualSendSize > 0)
			iSendsize += ActualSendSize;

		if (ActualSendSize < 0)
			return 0;
	}

	iSendsize=0;
	while(iSendsize < iLen)
	{
		int ActualSendSize =
			send( ClientSocket,
			pkString+iSendsize,
			iLen-iSendsize,
			0);

		if (ActualSendSize > 0)
			iSendsize += ActualSendSize;

		if (ActualSendSize < 0)
			return 0;
	}

	return iSendsize;
}

#endif