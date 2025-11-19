@ECHO OFF
REM - 滲熱 撲薑
REM -------------------------------------------------------------------------------------
SET SUCCESS_BEEP=.\Beep.exe Success.txt
SET FAILED_BEEP=.\Beep.exe Failed.txt
SET ONESTEP_BEEP=.\Beep.exe Success_OneStep.txt
SETLOCAL
REM - 闡だ橾楝 嬪纂陛 棻腦棻賊 嬴楚 高擊 夥紱撮蹂!
SET BATCHNAME="FreedomBuild"
SET SVN="C:\Program Files\Subversion\bin\svn.exe"
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET LOGFILE="FreedomBuild.log"
SET SOURCE_R_EXE=".\SFreedom_Dev\Release\Dragonica_Internal.exe"
SET SOURCE_R_MAP=".\SFreedom_Dev\Release\Dragonica_Internal.map"
SET SOURCE_R_PDB=".\SFreedom_Dev\Release\Dragonica_Internal.pdb"
SET SOURCE_R_ZIP=".\SFreedom_Dev\Release\Dragonica_Internal.zip"
SET SOURCE_EXE=".\SFreedom_Dev\Release\Dragonica.exe"
SET SOURCE_MAP=".\SFreedom_Dev\Release\Dragonica.map"
SET SOURCE_PDB=".\SFreedom_Dev\Release\Dragonica.pdb"
SET SOURCE_ZIP=".\SFreedom_Dev\Release\Dragonica.zip"
SET TARGET_EXE=".\SFreedom_Rel\Release\Dragonica.exe"
SET TARGET_MAP=".\SFreedom_Rel\Release\Dragonica.map"
SET TARGET_PDB=".\SFreedom_Rel\Release\Dragonica.pdb"
SET TARGET_ZIP=".\SFreedom_Rel\Release\Dragonica.zip"
SET BUILD_NUMBER=".\Freedom\MobileSuit\BuildNumber.h"
SET DEVDIR=".\SFreedom_Dev\"
SET RELDIR=".\SFreedom_Rel\"
SET XML_PATH=E:\ProjectD_Release\SFreedom_Dev\XML
SET SCRIPT_PATH=E:\ProjectD_Release\SFreedom_Dev\Script
SET XML_DATA=".\SFreedom_Dev\XML.dat"
SET SCRIPT_DATA=".\SFreedom_Dev\SCRIPT.dat"
SET PACK_EXE=".\ToolBin\Pack\Pack.exe"

ECHO [Building... %LOGFILE% だ橾縑 煎斜陛 陴蝗棲棻.]

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ
ECHO Ⅰ DELETE OLD LOG FILE
ECHO Ⅰ
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
DEL %LOGFILE%
REM Conflict陛 釭朝 匙擊 虞晦 嬪п
DEL %SOURCE_EXE% /F
DEL %SOURCE_PDB% /F
DEL %SOURCE_MAP% /F
DEL %SOURCE_ZIP% /F
DEL %SOURCE_R_EXE% /F
DEL %SOURCE_R_PDB% /F
DEL %SOURCE_R_MAP% /F
DEL %SOURCE_R_ZIP% /F
DEL %XML_DATA% /F
DEL %SCRIPT_DATA% /F
%ONESTEP_BEEP%

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ
ECHO Ⅰ SVN UPDATE
ECHO Ⅰ
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO [Start Svn Update]
ECHO [Start Svn Update] %DATE:~2,10% %TIME:~0,5% >> %LOGFILE%
%SVN% update .\* >> %LOGFILE%
%ONESTEP_BEEP%

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ
ECHO Ⅰ freedom/MobileSuit Release Build
ECHO Ⅰ
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO [Start Release Build]
ECHO [Start Release Build] %DATE:~2,10% %TIME:~0,5% >> %LOGFILE%
call Weapons_Build_All.bat
REM - 瞪羹 樂瑞暮擊 瓊嬴憮 闡だ橾 и棻.
%MSDEV% /rebuild Release .\Freedom\MobileSuit\Freedom.sln >> %LOGFILE%
%MSDEV% /rebuild ExternalRelease .\Freedom\MobileSuit\Freedom.sln >> %LOGFILE%
REM - 縑楝 羹觼
IF ERRORLEVEL 1 GOTO :FAILEDBATCH
%ONESTEP_BEEP%
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ SUCCESS %BATCHNAME% Release Build
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - 闡だ橾 撩奢 >> %LOGFILE%
ECHO %DATE% %TIME% - 闡だ橾 撩奢
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

REM .\ToolBin\BuildNumberIncrease .\Freedom\MobileSuit\BuildNumber.h
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ COPY SFreedom_Dev/Release/Dragonica.exe To SFreedom_Rel/Release/Dragonica.exe
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
REM 橾欽 虞嬴場擠. Daily Build縑憮朝 Relィ渦縑 Commitй в蹂陛 橈棻.
REM COPY %SOURCE% %TARGET%
REM IF ERRORLEVEL 1 GOTO :FAILEDCOPY
REM %ONESTEP_BEEP%
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ COMMIT SFreedom_Dev\Release\Dragonica.exe
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
%PACK_EXE% -automake_onepack %XML_PATH%
%PACK_EXE% -automake_onepack %SCRIPT_PATH%
DEL %SOURCE_ZIP% /F
.\ToolBin\zip -m -9 %SOURCE_ZIP% %SOURCE_MAP% %SOURCE_PDB%
.\ToolBin\zip -m -9 %SOURCE_R_ZIP% %SOURCE_R_MAP% %SOURCE_R_PDB%

REM IF ERRORLEVEL 1 GOTO :FAILEDCOMMIT
%ONESTEP_BEEP%
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收


REM ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
REM ECHO Ⅰ DIFF
REM ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

REM IF ERRORLEVEL 1 GOTO :FAILEDCOPY
REM ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
%SUCCESS_BEEP%
ENDLOCAL
PAUSE
EXIT

REM - :褒ぬ
REM -------------------------------------------------------------------------------------
:FAILEDBATCH
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ FAILED %BATCHNAME% Release Build
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - 闡だ橾 褒ぬ >> %LOGFILE%
%FAILED_BEEP%
ENDLOCAL
PAUSE
EXIT

:FAILEDCOPY
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ FAILED COPY SFreedom_Dev/Release/Dragonica.exe To SFreedom_Rel/Release/Dragonica.exe
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - 犒餌 褒ぬ >> %LOGFILE%
ECHO %DATE% %TIME% - 犒餌 褒ぬ
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
%FAILED_BEEP%
ENDLOCAL
PAUSE
EXIT

:FAILEDCOMMIT
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ FAILED COMMIT SFreedom_Dev\Release\Dragonica.exe
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - COMMIT 褒ぬ >> %LOGFILE%
ECHO %DATE% %TIME% - COMMIT 褒ぬ
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
%FAILED_BEEP%
ENDLOCAL
PAUSE
EXIT