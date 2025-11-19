@echo off
SETLOCAL
SET SVN_EXE_PATH="C:\Program Files\Subversion\bin\svn.exe"

echo Archangel Update
%SVN_EXE_PATH% update .\Archangel\.

echo Cosmos Update
%SVN_EXE_PATH% update .\Cosmos\.

echo Cosmos_Source Update
%SVN_EXE_PATH% update .\Cosmos_src\.

echo Freedom Update
%SVN_EXE_PATH% update .\freedom\.

echo SFreedom_Dev Update
%SVN_EXE_PATH% update .\SFreedom_Dev\.

echo Á¾·á
ENDLOCAL

pause

