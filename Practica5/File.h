#pragma once


enum		 EFileMode { FILE_READ, FILE_WRITE };
void*		 FileOpen(const char* pszName, EFileMode eMode);					// nullptr si falla
bool		 FileClose(void* pFile);
unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize);			// leídos
unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize);   // escritos