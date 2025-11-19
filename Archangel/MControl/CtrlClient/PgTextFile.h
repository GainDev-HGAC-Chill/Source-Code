#pragma once

class PgTextFile
{
public:
	PgTextFile(void);
	virtual ~PgTextFile(void);
	bool OpenFile(LPCTSTR lpszFilename, DWORD dwBufferSize);
	char* GetNextLine(char* lpszEol ="\r\n");

private:
	HANDLE m_hFile;
	int m_iError;
	int m_iBufferSize;
	char* m_lpszBuffer;
	DWORD m_dwBufferReadPos;
	DWORD m_dwBufferEndPos;
	bool m_bEof;
};
