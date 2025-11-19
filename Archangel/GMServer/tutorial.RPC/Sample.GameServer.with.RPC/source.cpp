/*
	This is a sample server which added RPC support
	note the rpc function is executer in RPC worker threads which are created and maintained by system
	this function must be thread safe and make no thread binding assumption
*/

#include "header.h"

////// rpc modification begin
#include "informer_h.h"

#pragma comment(lib, "rpcrt4")

BOOL StartRPC()
{
	return(
		RPC_S_OK==RpcServerUseAllProtseqsIf(RPC_C_PROTSEQ_MAX_REQS_DEFAULT, informer_v1_0_s_ifspec, NULL) &&
		RPC_S_OK==RpcServerRegisterIfEx(informer_v1_0_s_ifspec, NULL, NULL, RPC_IF_AUTOLISTEN, RPC_C_LISTEN_MAX_CALLS_DEFAULT, NULL)
		);
}

VOID StopRPC()
{
	RpcServerUnregisterIf(informer_v1_0_s_ifspec, NULL, TRUE);
}

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}
////// rpc modification end

using namespace std;

CRITICAL_SECTION lock;
list<DWORD> g_usrs;

void threadAdd(void *)
{
	while(TRUE) {
		EnterCriticalSection(&lock);
		g_usrs.push_back(rand());
		LeaveCriticalSection(&lock);
		Sleep(100);
	}
}

void threadDel(void *)
{
	while(TRUE) {
		EnterCriticalSection(&lock);
		if(g_usrs.size()>1000) {
			g_usrs.clear();
		} else if(!g_usrs.empty()) {
			g_usrs.pop_front();
		}
		LeaveCriticalSection(&lock);
		Sleep(400);
	}
}

int _tmain(int argc, TCHAR *argv[], TCHAR *envp[])
{
	srand((unsigned int)time(NULL));
	InitializeCriticalSection(&lock);
	_beginthread(threadAdd, 0, NULL);
	_beginthread(threadDel, 0, NULL);
////// rpc modification begin
	if(!StartRPC()) abort();
////// rpc modification end
	while(TRUE) {
		_tprintf(_T("%d users in list\n"), g_usrs.size());
		Sleep(1000);
	}
////// rpc modification begin
	StopRPC();
////// rpc modification end
	return(0);
}

////// rpc modification begin
boolean KickUser(handle_t hBinding, const wchar_t *szUserName)
{
	boolean result = false;
	_tprintf(_T("Kicking user %s\n"), szUserName);
	DWORD id = _ttoi(szUserName);
	EnterCriticalSection(&lock);
	for(list<DWORD>::iterator iter=g_usrs.begin(); iter!=g_usrs.end(); ++iter) {
		if(id==*iter) {
			g_usrs.erase(iter);
			result = true;
			break;
		}
	}
	_tprintf(result ? _T("found and kicked\n") : _T("not found\n"));
	LeaveCriticalSection(&lock);
	for(int i=0; i<10; ++i) {
		CBKickUser(i);
	}
	return(result);
}
////// rpc modification end
