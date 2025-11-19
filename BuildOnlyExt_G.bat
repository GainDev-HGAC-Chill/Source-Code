@ECHO OFF
REM - 변수 설정
REM -------------------------------------------------------------------------------------
SETLOCAL
REM - 컴파일러 위치가 다르다면 아래 값을 바꾸세요!
SET BATCHNAME="BuildOnlyExt"
SET SVN="C:\Program Files\Subversion\bin\svn.exe"
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET LOGFILE="BuildOnlyExt_G.log"
SET SOURCE_EXE="..\Dragonica_Exe\SFreedom_Dev\Release\Dragonica_ExternalRelease_G.exe"
SET SOURCE_MAP="..\Dragonica_Exe\SFreedom_Dev\Release\Dragonica_ExternalRelease_G.map"
SET SOURCE_PDB="..\Dragonica_Exe\SFreedom_Dev\Release\Dragonica_ExternalRelease_G.pdb"
SET SOURCE_ZIP="..\Dragonica_Exe\SFreedom_Dev\Release\Dragonica_ExternalRelease_G.zip"
SET SOURCE_DEBUG_EXE="..\Dragonica_Exe\SFreedom_Dev\Debug\Dragonica_ExternalRelease_G.exe"
SET BUILD_NUMBER=".\Freedom\MobileSuit\BuildNumber.h"
SET DEVDIR="..\Dragonica_Exe\SFreedom_Dev\"

ECHO [Building... %LOGFILE% 파일에 로그가 남습니다.]
DEL %LOGFILE% /F

ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷
ECHO ▷ freedom/MobileSuit Release Build
ECHO ▷
ECHO ──────────────────────────────────────
ECHO [Start Release Build]
ECHO [Start Release Build] %DATE:~2,10% %TIME:~0,5% >> %LOGFILE%

REM - 전체 솔루션을 찾아서 컴파일 한다.
%MSDEV% /rebuild ExternalRelease_G .\Freedom\MobileSuit\Freedom.sln >> %LOGFILE%

REM - 에러 체크
IF ERRORLEVEL 1 GOTO :FAILEDBATCH
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷ SUCCESS %BATCHNAME% Release Build
ECHO ──────────────────────────────────────
ECHO %DATE% %TIME% - 컴파일 성공 >> %LOGFILE%
ECHO %DATE% %TIME% - 컴파일 성공
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷ COMMIT SFreedom_Dev\Release\Dragonica_ExternalRelease_G.exe
ECHO ──────────────────────────────────────
DEL %SOURCE_ZIP% /F
.\..\Dragonica_Exe2\ToolBin\zip -m -9 %SOURCE_ZIP% %SOURCE_MAP% %SOURCE_PDB%
REM IF ERRORLEVEL 1 GOTO :FAILEDCOMMIT
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

ENDLOCAL
PAUSE
EXIT

REM - :실패
REM -------------------------------------------------------------------------------------
:FAILEDBATCH
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷ FAILED %BATCHNAME% Release Build
ECHO ──────────────────────────────────────
ECHO %DATE% %TIME% - 컴파일 실패 >> %LOGFILE%
ENDLOCAL
PAUSE
EXIT