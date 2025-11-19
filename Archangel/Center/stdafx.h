//!  stdafx.h : 자주 사용하지만 자주 변경되지는 않는
//!  표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
//!  들어 있는 포함 파일입니다.
//! 

#ifndef CENTER_CENTERSERVER_MAINFRAME_STDAFX_H
#define CENTER_CENTERSERVER_MAINFRAME_STDAFX_H

#define WIN32_LEAN_AND_MEAN		//!  거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include <fstream>
#include <iostream>
#include <ostream>

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "BM/BM.h"
#include "BM/Guid.h"
#include "BM/Objectpool.h"
#include "BM/ExceptionFilter.h"
#include "BM/vstring.h"
#include "BM/FileSupport.h"
#include "BM/Stream.h"
#include "BM/LocalMgr.h"
#include "BM/PgFilterString.h"

#include "CEL/CEL.h"
#include "CEL/CoreCenter.h"
#include "CEL/ConsoleCommander.h"

#include "Lohengrin/Lohengrin.h"
//#define _MEMORY_TRACKING
#include "Lohengrin/MemoryTrack.h"

#include "FCS/FCS.h"

#include "Collins/Collins.h"

#include "Variant/Variant.h"
#include "Variant/gm_const.h"
#include "Variant/PgDBCache.h"
#include "variant/PgTotalObjectMgr.h"

//!  TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "PgServerSetMgr.h"
#include "PgSwitchAssignMgr.h"
#include "PgSendWrapper.h"
#include "PgUserWrapper.h"

#include "Contents/PgTask_Contents.h"
/*
#include "NC/IBGameDefine.h"
#include "NC/IBGameInterface.h"

#pragma comment(lib, "NC/IBGameInterface.lib")
*/
//LOCAL_MGR::CLocal g_kLocal;

//#define _DEBUGGING

#endif // CENTER_CENTERSERVER_MAINFRAME_STDAFX_H