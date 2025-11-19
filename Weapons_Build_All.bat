@ECHO OFF

SETLOCAL
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET LOGFILE=.\Archangel\BuildLog\
SET ARCHANGEL=.\Archangel\
SET BUILDMODE=/Rebuild

REM Debug 빌드.
SET BUILD=Debug
SET W_BUILD="LIB MDd"
@echo ====================================================
@echo = Weapons %BUILD% %BUILDMODE% : Begin
@echo ====================================================
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Weapons\Weapons.sln" /Out %LOGFILE%Weapons_%BUILD%.log /Log 
%MSDEV% %BUILDMODE% %W_BUILD% "%ARCHANGEL%Weapons\Weapons.sln" >> %LOGFILE%Weapons_%BUILD%.log
IF ERRORLEVEL 1 GOTO :BUILDFAILED
@echo = Weapons %BUILD% %BUILDMODE% : End
@echo ====================================================

REM Release 빌드.
SET BUILD=Release
SET W_BUILD="LIB MD"
@echo ====================================================
@echo = Weapons %BUILD% %BUILDMODE% : Begin
@echo ====================================================
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Weapons\Weapons.sln" /Out %LOGFILE%Weapons_%BUILD%.log /Log 
%MSDEV% %BUILDMODE% %W_BUILD% "%ARCHANGEL%Weapons\Weapons.sln" >> %LOGFILE%Weapons_%BUILD%.log
IF ERRORLEVEL 1 GOTO :BUILDFAILED
@echo = Weapons %BUILD% %BUILDMODE% : End
@echo ====================================================

REM External 빌드.
SET BUILD=ExternalRelease
SET W_BUILD="LIB MDo"
@echo ====================================================
@echo = Weapons %BUILD% %BUILDMODE% : Begin
@echo ====================================================
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Weapons\Weapons.sln" /Out %LOGFILE%Weapons_%BUILD%.log /Log 
%MSDEV% %BUILDMODE% %W_BUILD% "%ARCHANGEL%Weapons\Weapons.sln" >> %LOGFILE%Weapons_%BUILD%.log 
IF ERRORLEVEL 1 GOTO :BUILDFAILED
@echo = Weapons %BUILD% %BUILDMODE% : End
@echo ====================================================


REM 빌드 성공.
@echo ====================================================
@echo = Complete Build : 성공
@echo = Log는 "%LOGFILE%" 에 남습니다.
@echo ====================================================

ENDLOCAL

:BUILDFAILED
@echo ***************************************************
@echo * Build Failed
@echo * Log는 "%LOGFILE%" 에 남습니다.
@echo ***************************************************
