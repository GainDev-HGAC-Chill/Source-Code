#pragma once 
#include <string>
extern void InitPack();
extern void RecursivePackWork(LPCWSTR pTargetDir);
extern void OneFilePackWork(LPCWSTR pTargetDir, LPCWSTR pResultFileName, LPCWSTR pPatchVer);
extern bool HeaderMerge(LPCWSTR pTargetDir, LPCWSTR pResultFileName);
extern bool MakeVersion(LPCWSTR pTargetDir, LPCWSTR pOutputDir);
extern bool PatchProcess(LPCWSTR pTargetDir, LPCWSTR pOutputDir);

extern void DoMakeVersion(void *pDlg);
extern void DoMergeFile(void *pDlg);
extern void DoMakeOnePack(void *pDlg);

extern bool SetPatchVer(std::wstring strName, std::wstring strVersionNum);