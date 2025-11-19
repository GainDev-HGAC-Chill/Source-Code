// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

// 아래 지정된 플랫폼에 우선하는 플랫폼을 대상으로 하는 경우 다음 정의를 수정하십시오.
// 다른 플랫폼에 사용되는 해당 값의 최신 정보는 MSDN을 참조하십시오.
#ifndef WINVER				// Windows XP 이상에서만 기능을 사용할 수 있습니다.
#define WINVER 0x0501		// 다른 버전의 Windows에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_WINNT		// Windows XP 이상에서만 기능을 사용할 수 있습니다.                   
#define _WIN32_WINNT 0x0501	// 다른 버전의 Windows에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_WINDOWS		// Windows 98 이상에서만 기능을 사용할 수 있습니다.
#define _WIN32_WINDOWS 0x0410 // Windows Me 이상에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_IE			// IE 6.0 이상에서만 기능을 사용할 수 있습니다.
#define _WIN32_IE 0x0600	// 다른 버전의 IE에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


//BM
#include "DataPack/PgDataPackManager.h"
#include "BM/BM.h"
#ifdef _DEBUG
	#pragma comment (lib, "DataPackd.lib")
#else
	#pragma comment (lib, "DataPack.lib")
#endif
#include "BM/HSEL.h"
#include "BM/BM.h"
#include "BM/Guid.h"
#include "BM/FileSupport.h"
#include "BM/PgFileMapping.h"
#include "BM/ThreadObject.h"
#include "BM/vstring.h"

//LOG
#include "./Lohengrin/Lohengrin.h"
#include "ErrorReportFile.h"
#include "ExceptionHandler.h"

//// XML Parser
//
#ifdef _DEBUG
#pragma comment(lib, "tinyxmld.lib")
#else
#pragma comment(lib, "tinyxml.lib")
#endif
#include "tinyxml/tinyxml.h"
#include "ConfigDef.h"

// Patcher CRC
#define PG_PATCHER_CRC_SIZE		(100)
#define PG_DRAW_TIME			(100)


//!Definition

// 패쳐 패치를 할것인가.
#define PG_PATCHER_PATCH

// 접속을 어느 것으로 할 것인가? FTP / HTTP
//#define FTP_CONNECT

// ACE Thread를 쓸 것인가?
#define PG_USE_ACE
#ifdef PG_USE_ACE
#ifdef _DEBUG
	#pragma comment(lib, "ACEsd.lib")
#else
	#pragma comment(lib, "ACEs.lib")
#endif
#endif


#define PG_USE_PARTPACK
//#define PG_USE_PERFORM_CHECK

enum	LOCALE_STATE	{ LS_NULL, LS_KOR, LS_CHN, LS_SGP, LS_END };
extern	LOCALE_STATE	g_Locale;
extern	std::wstring	g_Addr;
extern	std::wstring	g_ID;
extern	std::wstring	g_PW;
extern	WORD			g_wPort;
extern	bool			g_fc;
extern	bool			g_lc;
