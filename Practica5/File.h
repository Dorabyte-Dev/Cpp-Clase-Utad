#pragma once

class TFile
{
public:
	TFile();
	~TFile();
	enum EFileMode { FILE_READ, FILE_WRITE };
	void FileOpen(const char* pszName, EFileMode eMode);					// nullptr si falla
	bool FileClose();
	unsigned int FileRead(char* pBuffer, unsigned int uSize);			// leídos
	unsigned int FileWrite(const char* pBuffer, unsigned int uSize);   // escritos
private:
	void* m_pFile;
};
