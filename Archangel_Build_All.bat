
@echo off

REM 비쥬얼 스튜디오의 위치를 셋팅해주세요.
SETLOCAL
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET ARCHANGEL=.\Archangel\
SET ALLSIN=.\
SET LOGFILE=.\Archangel\BuildLog\
SET TOOLS=.\Tools\

SET SUCCESS_BEEP=.\Beep.exe Success.txt
SET FAILED_BEEP=.\Beep.exe Failed.txt
SET ONESTEP_BEEP=.\Beep.exe Success_OneStep.txt

DEL /Q %LOGFILE%*.*
@echo [Auto Build Archangel]
@echo .
:BUILDMODE
@echo ====================================================
@echo 1. Debug
@echo 2. Release
@echo 3. External
@echo ====================================================
CHOICE /C:123 /M:"빌드모드를 선택하세요"

if ERRORLEVEL 3 GOTO :BUILD_EXTERNAL
if ERRORLEVEL 2 GOTO :BUILD_RELEASE
if ERRORLEVEL 1 GOTO :BUILD_DEBUG

:BUILD_DEBUG
SET BUILD=Debug
SET W_BUILD="LIB MDd"
GOTO BUILDMODE2

:BUILD_RELEASE
SET BUILD=Release
SET W_BUILD="LIB MD"
GOTO BUILDMODE2

:BUILD_EXTERNAL
SET BUILD=ExternalRelease
SET W_BUILD="LIB MDo"

:BUILDMODE2
@echo .
@echo ====================================================
@echo 1. Build
@echo 2. ReBuild (10초후 자동 선택)
@echo ====================================================
CHOICE /C:12 /T 10 /D 2 /M:"빌드방법을 선택하세요"

if ERRORLEVEL 2 GOTO :BUILDMODE_REBUILD
if ERRORLEVEL 1 GOTO :BUILDMODE_BUILD

:BUILDMODE_BUILD:
SET BUILDMODE=/Build
GOTO NEXT_MENU:

:BUILDMODE_REBUILD:
SET BUILDMODE=/Rebuild
GOTO NEXT_MENU:

:NEXT_MENU2
@echo .
@echo * 현재 빌드모드는 %BUILD% 입니다.
@echo * 현재 빌드방법은 %BUILDMODE% 입니다.
@echo * 빌드 하실 서버를 선택하세요.
@echo ====================================================
@echo 0. 이전메뉴
@echo 1. 빌드모드 다시 선택
@echo 2. 빌드방법 다시 선택
@echo 3. 종료
@echo ====================================================
CHOICE /C 0123 /M:"* 선택하세요"
if ERRORLEVEL 4 goto QUIT
if ERRORLEVEL 3 goto BUILDMODE2
if ERRORLEVEL 2 goto BUILDMODE
if ERRORLEVEL 1 goto NEXT_MENU

:NEXT_MENU
@echo .
@echo * 현재 빌드모드는 %BUILD% 입니다.
@echo * 현재 빌드방법은 %BUILDMODE% 입니다.
@echo * 빌드 하실 서버를 선택하세요.
@echo ====================================================
@echo 0. Weapons
@echo 1. Immigration
@echo 2. Switch
@echo 3. Login Server
@echo 4. Contents Server
@echo 5. Center Server
@echo 6. Map Server
@echo 7. All Servers(Support제외)
@echo 8. Support Server (Log,, GM, MCtrl)
@echo 9. 다음메뉴
@echo ====================================================
CHOICE /C 0123456789 /T 20 /D 8 /M:"* 선택하세요"
if ERRORLEVEL 10 goto NEXT_MENU2
if ERRORLEVEL 9 goto BUILD_SUPPORT
if ERRORLEVEL 8 goto BUILD_ALL
if ERRORLEVEL 7 goto BUILD_MAP
if ERRORLEVEL 6 goto BUILD_CENTER
if ERRORLEVEL 5 goto BUILD_CONTENTS
if ERRORLEVEL 4 goto BUILD_LOGIN
if ERRORLEVEL 3 goto BUILD_SWITCH
if ERRORLEVEL 2 goto BUILD_IMM
if ERRORLEVEL 1 goto BUILD_WEAPON

:BUILD_WEAPON
@echo ====================================================
@echo = Weapons %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %W_BUILD% "%ARCHANGEL%Weapons\Weapons.sln" /Out %LOGFILE%Weapons_%BUILD%.log /Log 
IF ERRORLEVEL 1 GOTO :BUILDFAILED

@echo = Weapons %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_IMM
@echo ====================================================
@echo =Immigration %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Immigration\ImmigrationServer.sln" /Out %LOGFILE%Immigration_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = Immigration %BUILD% %BUILDMODE% : End
@echo ==================================================== 
goto PRINT_RESULT

:BUILD_SWITCH
@echo ====================================================
@echo = Switch %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Switch\SwitchServer.sln" /Out %LOGFILE%Switch_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = Switch %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_LOGIN
@echo ====================================================
@echo = LoginServer %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%LoginServer\LoginServer.sln" /Out %LOGFILE%LoginServer_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = LoginServer %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_CONTENTS
@echo ====================================================
@echo = ContentsServer %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%ContentsServer\ContentsServer.sln" /Out %LOGFILE%ContentsServer_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = ContentsServer %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_CENTER
@echo ====================================================
@echo = CenterServer %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Center\CenterServer.sln" /Out %LOGFILE%CenterServer_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = CenterServer %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_MAP
@echo ====================================================
@echo = MapServer %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%MapServer\MapServer.sln" /Out %LOGFILE%MapServer_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = MapServer %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_SUPPORT
:BUILD_LOG
@echo ====================================================
@echo = LogServer %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%LogServer\LogServer.sln" /Out %LOGFILE%LogServer_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = LogServer %BUILD% %BUILDMODE% : End

@echo ====================================================
:BUILD_GM Server
@echo ====================================================
@echo = GM Server %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%GMServer\GMServer.sln" /Out %LOGFILE%GmServer_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = GM Server %BUILD% %BUILDMODE% : End
@echo ====================================================

@echo ====================================================
:BUILD_MMC
@echo ====================================================
@echo = MMC Server %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%MControl\MMC\MMC.sln" /Out %LOGFILE%MMC_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

@echo ====================================================
:BUILD_SMC
@echo ====================================================
@echo = SMC Server %BUILD% %BUILDMODE% : Begin

%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%MControl\SMC\SMC.sln" /Out %LOGFILE%SMC_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED

REM %MSDEV% %BUILDMODE% %BUILD% "%TOOLS%ServerControl\MonTool\ServerControl.sln" / Out %LOGFILE%ServerControlTool_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED

%ONESTEP_BEEP%
@echo = MCtrl Server %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:BUILD_ALL
@echo ====================================================
@echo = All Server Build %BUILD% %BUILDMODE% : Begin

REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Weapons\Weapons.sln" /Out %LOGFILE%Weapons_%BUILD%.log /Log 
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Immigration\ImmigrationServer.sln" /Out %LOGFILE%Immigration_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%LoginServer\LoginServer.sln" /Out %LOGFILE%LoginServer_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%CenterServer\CenterServer.sln" /Out %LOGFILE%CenterServer_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Switch\SwitchServer.sln" /Out %LOGFILE%Switch_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%ContentsServer\ContentsServer.sln" /Out %LOGFILE%ContentsServer_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%MapServer\MapServer.sln" /Out %LOGFILE%MapServer_%BUILD%.log /Log
REM IF ERRORLEVEL 1 GOTO :BUILDFAILED
%MSDEV% %BUILDMODE% %W_BUILD% "%ALLSIN%ArchangelAll.sln" /Out %LOGFILE%AllSin_%BUILD%.log /Log
IF ERRORLEVEL 1 GOTO :BUILDFAILED


%ONESTEP_BEEP%
@echo = All Server %BUILD% %BUILDMODE% : End
@echo ====================================================
goto PRINT_RESULT

:PRINT_RESULT
@echo ====================================================
@echo = Complete Build : 성공
@echo = Log는 "%LOGFILE%" 에 남습니다.
@echo ====================================================
%SUCCESS_BEEP%
pause
goto NEXT_MENU

:BUILDFAILED
@echo ***************************************************
@echo * Build Failed                                    *
@echo * Log는 ".\Archangel\BuildLog" 에 남습니다.       *
@echo ***************************************************
%FAILED_BEEP%
pause

:QUIT
END_LOCAL

