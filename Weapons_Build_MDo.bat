REM @ECHO OFF

SETLOCAL
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET LOGFILE=.\Archangel\BuildLog\
SET ARCHANGEL=.\Archangel\
SET BUILDMODE=/Rebuild

REM External 빌드.
SET BUILD="LIB MDo"
@echo ====================================================
@echo = Weapons %BUILD% %BUILDMODE% : Begin
@echo ====================================================
REM %MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Weapons\Weapons.sln" /Out %LOGFILE%Weapons_%BUILD%.log /Log 
%MSDEV% %BUILDMODE% %BUILD% "%ARCHANGEL%Weapons\Weapons.sln" >> %LOGFILE%Weapons_%BUILD%.log 
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
