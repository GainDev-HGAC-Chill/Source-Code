/*
	This sample game server creates two worker thread to manipulate a user list simultaneously
	threadAdd adds random numbers to the list
	threadDel removes first number from the list or clear the list if it's too long
	a critical section is used to synchronize two thread
	the main thread print out the list size periodically
	note that the main thread do not use the critical section because it performs non-critical read only operation
*/

#include "header.h"

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
	while(TRUE) {
		_tprintf(_T("%d users in list\n"), g_usrs.size());
		Sleep(1000);
	}
	return(0);
}
