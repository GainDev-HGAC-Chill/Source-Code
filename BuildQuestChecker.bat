@ECHO OFF

SETLOCAL
SET BATCHNAME="BuildQuestChecker"
SET SVN="C:\Program Files\Subversion\bin\svn.exe"
SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com"
SET LOGFILE="BuildQuestChecker.log"


ECHO [Building... %LOGFILE% 파일에 로그가 남습니다.]
DEL %LOGFILE% /F

ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷
ECHO ▷ Toolbin/QuestChecker ExternalRelease Build
ECHO ▷
ECHO ──────────────────────────────────────
ECHO [Start ExternalRelease Build]
ECHO [Start ExternalRelease Build] %DATE:~2,10% %TIME:~0,5% >> %LOGFILE%

REM - 전체 솔루션을 찾아서 컴파일 한다.(내부 Release, 외부 ExternalRelease)
%MSDEV% /rebuild Release .\Tools\QuestChecker\QuestChecker.sln >> %LOGFILE%
REM %MSDEV% /rebuild ExternalRelease .\Tools\QuestChecker\QuestChecker.sln >> %LOGFILE%

REM - 에러 체크
IF ERRORLEVEL 1 GOTO :FAILEDBATCH
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷ SUCCESS %BATCHNAME% ExternalRelease Build
ECHO ──────────────────────────────────────
ECHO %DATE% %TIME% - 컴파일 성공 >> %LOGFILE%
ECHO %DATE% %TIME% - 컴파일 성공
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━



ENDLOCAL
PAUSE
EXIT


:FAILEDBATCH
ECHO ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ECHO ▷ FAILED %BATCHNAME% ExternalRelease Build
ECHO ──────────────────────────────────────
ECHO %DATE% %TIME% - 컴파일 실패 >> %LOGFILE%
ENDLOCAL
PAUSE
EXIT