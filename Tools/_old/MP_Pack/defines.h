#pragma	once
#define WIN32_LEAN_AND_MEAN
#include	<winsock2.h>
#include	<windows.h>
#include	<commdlg.h>
#include	<process.h>
#include	<shlobj.h>
#include	<string>
#include	<io.h>
#include	"BM/HSEL.h"
#include	"BM/BM.h"
#include	"BM/Guid.h"
#include	"BM/common.h"
#include	"BM/FileSupport.h"
#include	"BM/PgFileMapping.h"
#include	"SimpEnc/Common.h"
#include	"DataPack/Common.h"
#include	"DataPack/packInfo.h"
#include	"DataPack/PgDataPackManager.h"
#include	"lohengrin/lohengrin.h"
#include	"lohengrin/loggroup.h"
#include	"resource.h"

extern	HWND				g_hDlgWnd;
extern class CPackProcess	g_PackProcess;

#include	"PackProcess.h"
#include	"WorkingThread.h"
#include	"DataPack/packInfo.h"
