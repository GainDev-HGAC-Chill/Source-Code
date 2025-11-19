#include "StdAfx.h"
#include "PgTextFile.h"

PgTextFile::PgTextFile(void)
{
	m_hFile = NULL;
	m_iError = ERROR_SUCCESS;
	m_iBufferSize = 0;
	m_lpszBuffer = NULL;
	m_dwBufferReadPos = 0;
	m_dwBufferEndPos = 0;
	m_bEof = false;
}

PgTextFile::~PgTextFile(void)
{
	if (m_hFile != NULL)
	{
		CloseHandle(m_hFile);
	}
}

bool PgTextFile::OpenFile(LPCTSTR lpszFilename, DWORD dwBufferSize)
{
	if (m_hFile != NULL)
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}

	m_hFile = CreateFile(lpszFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		m_hFile = NULL;
		m_iError = GetLastError();
		return false;
	}
	m_bEof = false;
	m_iBufferSize = dwBufferSize;
	m_dwBufferReadPos = m_dwBufferEndPos = 0;
	return true;
}

char* PgTextFile::GetNextLine(char* lpszEol)
{
	if (m_hFile == NULL)
	{
		return NULL;
	}
	if (m_lpszBuffer == NULL)
	{
		m_lpszBuffer = new char[m_iBufferSize+1];
		m_dwBufferReadPos = 0;
		m_dwBufferEndPos = 0;
		memset(m_lpszBuffer, 0, (m_iBufferSize+1) / sizeof(char));
	}
	bool bFind = false;
	while (!bFind)
	{
		if (m_bEof && (m_dwBufferReadPos == m_dwBufferEndPos))
		{
			return NULL;
		}
		// Find
		char* lpszFind = strchr(&m_lpszBuffer[m_dwBufferReadPos], lpszEol[0]);
		if ((lpszFind != NULL) && (lpszFind <= &m_lpszBuffer[m_dwBufferEndPos-1]))
		{
			char* lpszPos = &m_lpszBuffer[m_dwBufferReadPos];
			bFind = true;
			*lpszFind = '\0';
			m_dwBufferReadPos = (lpszPos - m_lpszBuffer) + strlen(lpszEol);
			return lpszPos;
		}
		// Last Line
		if ((lpszFind == NULL) && m_bEof)
		{
			char* lpszBegin = &m_lpszBuffer[m_dwBufferReadPos];
			bFind = true;
			m_lpszBuffer[m_dwBufferEndPos] = '\0';
			m_dwBufferReadPos = m_dwBufferEndPos;
			return lpszBegin;			
		}
		// Buffer Reset
		if (m_dwBufferReadPos > 0)
		{
			char* lpszNew = new char[m_iBufferSize+1];
			memcpy_s(lpszNew, m_iBufferSize, &m_lpszBuffer[m_dwBufferReadPos], m_dwBufferEndPos - m_dwBufferReadPos);
			delete[] m_lpszBuffer;
			m_lpszBuffer = lpszNew;
			m_dwBufferReadPos = 0;
			m_dwBufferEndPos -= m_dwBufferReadPos;
		}
		// Too long line
		if (m_dwBufferEndPos >= m_iBufferSize)
		{
			char* lpszBegin = &m_lpszBuffer[m_dwBufferReadPos];
			bFind = true;
			m_lpszBuffer[m_dwBufferEndPos] = '\0';
			m_dwBufferReadPos = m_dwBufferEndPos;
			return lpszBegin;			
		}
		// Reading Files		
		if ((m_iBufferSize - m_dwBufferEndPos) > 0)
		{
			DWORD dwRead = 0;
			ReadFile(m_hFile, &m_lpszBuffer[m_dwBufferEndPos], m_iBufferSize-m_dwBufferEndPos, &dwRead, NULL);
			m_dwBufferEndPos += dwRead;
			m_bEof = (dwRead == 0) ? true : false;
		}
	}

	return NULL;
}
