

bool GetMainDirectory(LPTSTR lpszPath, int iPathLen);
bool GetPathWithoutFilename(LPCTSTR lpszSource, LPTSTR lpszPathOnly, size_t iPathOnlySize);
bool ReadConfigFile();
void CALLBACK TimerTick(DWORD dwUserData);