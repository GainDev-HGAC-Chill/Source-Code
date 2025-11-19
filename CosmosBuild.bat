@ECHO OFF
REM - 滲熱 撲薑
REM -------------------------------------------------------------------------------------
SETLOCAL
REM - 闡だ橾楝 嬪纂陛 棻腦棻賊 嬴楚 高擊 夥紱撮蹂!
SET BATCHNAME="CosmosBuild"
SET SVN="C:\Program Files\Subversion\bin\svn.exe"
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET LOGFILE="CosmosBuild.log"
SET SOURCE=".\SFreedom_Dev\Release\MobileSuit.exe"
SET TARGET=".\SFreedom_Rel\Release\MobileSuit.exe"
SET DEVDIR=".\SFreedom_Dev\"
SET RELDIR=".\SFreedom_Rel\"

ECHO [Building... %LOGFILE% だ橾縑 煎斜陛 陴蝗棲棻.]

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ
ECHO Ⅰ DELETE OLD LOG FILE
ECHO Ⅰ
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
DEL %LOGFILE%

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ
ECHO Ⅰ SVN UPDATE
ECHO Ⅰ
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO [Start Svn Update]
ECHO [Start Svn Update] %DATE:~2,10% %TIME:~0,5% >> %LOGFILE%
%SVN% update Cosmos Cosmos_src >> %LOGFILE%

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ
ECHO Ⅰ %BATCHNAME% Release Build
ECHO Ⅰ
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO [Start Release Build]
ECHO [Start Release Build] %DATE:~2,10% %TIME:~0,5% >> %LOGFILE%
REM - 瞪羹 樂瑞暮擊 瓊嬴憮 闡だ橾 и棻.
%MSDEV% /rebuild Debug .\Cosmos_src\Cosmos_src.sln >> %LOGFILE%
%MSDEV% /rebuild Release .\Cosmos_src\Cosmos_src.sln >> %LOGFILE%
REM - 縑楝 羹觼
IF ERRORLEVEL 1 GOTO :FAILEDBATCH
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ SUCCESS %BATCHNAME% Release Build
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - 闡だ橾 撩奢 >> %LOGFILE%
ECHO %DATE% %TIME% - 闡だ橾 撩奢
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ Cosmos Sync
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
"cosmos sync.bat" >> %LOGFILE%
IF ERRORLEVEL 1 GOTO :FAILEDCOPY
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ COMMIT SFreedom_Rel/Release/MobileSuit.exe
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
svn commit -m "%DATE%" %TARGET%
IF ERRORLEVEL 1 GOTO :FAILEDCOMMIT
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收


REM ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
REM ECHO Ⅰ DIFF
REM ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

REM IF ERRORLEVEL 1 GOTO :FAILEDCOPY
REM ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

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
ENDLOCAL
PAUSE
EXIT

:FAILEDCOPY
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ FAILED Cosmos Sync
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - 犒餌 褒ぬ >> %LOGFILE%
ECHO %DATE% %TIME% - 犒餌 褒ぬ
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ENDLOCAL
PAUSE
EXIT

:FAILEDCOMMIT
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ECHO Ⅰ FAILED COMMIT SFreedom_Rel/Release/MobileSuit.exe
ECHO 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ECHO %DATE% %TIME% - COMMIT 褒ぬ >> %LOGFILE%
ECHO %DATE% %TIME% - COMMIT 褒ぬ
ECHO 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
ENDLOCAL
PAUSE
EXIT