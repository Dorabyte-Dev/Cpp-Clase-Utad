#define _CRT_SECURE_NO_WARNINGS // antes de todo
#include <cstdio>
#include "File.h"

TFile::TFile() : m_pFile(nullptr)
{

}
TFile::~TFile()
{
	if(m_pFile != nullptr)
	{
		FileClose();
	}
}

void TFile::FileOpen(const char* pszName, EFileMode eMode) 
{
	const char* cMode = (eMode == FILE_READ) ? "rb" : "wb";
	FILE* file = fopen(pszName, cMode);
	m_pFile = file;
}
bool TFile::FileClose() 
{
	bool bCloseSucceed = fclose(static_cast<FILE*>(m_pFile)) == 0;
	m_pFile = nullptr;
	return bCloseSucceed;
}
unsigned int TFile::FileRead(char* pBuffer, unsigned int uSize)
{
	FILE* file = static_cast<FILE*>(m_pFile);
	if(file == nullptr)
	{
		printf("File is null, cancelling read operation.");
		return 0;
	}

	unsigned int uBytesRead = fread(pBuffer, sizeof(char), uSize - 1, file);
	*(pBuffer + uBytesRead) = '\0';
	return uBytesRead;
}
unsigned int TFile::FileWrite(const char* pBuffer, unsigned int uSize)
{
	return fwrite(pBuffer, sizeof(char), uSize, static_cast<FILE*>(m_pFile));
}

const unsigned int uBufferSize = 128;

int main()
{
	//Write in file 
	char s_fileName [] = "copia.txt";
	char s_writeBuffer[] = "Esto es un texto de prueba. 12345. See you next mission";
	unsigned int uWriteBufferSize = sizeof(s_writeBuffer) / sizeof(char);
	
	TFile myFile;
	myFile.FileOpen(s_fileName, TFile::FILE_WRITE);


	unsigned int uBytesWritten = myFile.FileWrite(s_writeBuffer, uWriteBufferSize);

	myFile.FileClose();

	//Read file and print it to console
	char s_readBuffer[uBufferSize];
	myFile.FileOpen(s_fileName, TFile::FILE_READ);

	unsigned int uBytesRead = myFile.FileRead(s_readBuffer, uBufferSize);

	printf("I have read %d bytes from the file:\n%s\n", uBytesRead, s_readBuffer);

	//Read file that doesn't exist
	myFile.FileOpen("noExiste.txt", TFile::FILE_READ);

	unsigned int uBytesRead2 = myFile.FileRead(s_readBuffer, uBufferSize);
}