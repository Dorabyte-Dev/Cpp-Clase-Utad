#define _CRT_SECURE_NO_WARNINGS // antes de todo
#include <cstdio>
#include "File.h"

void* FileOpen(const char* pszName, EFileMode eMode)
{
	const char* cMode = (eMode == FILE_READ) ? "rb" : "wb";
	FILE* file = fopen(pszName, cMode);
	return file;
}

bool FileClose(void* pFile)
{
	return fclose(static_cast<FILE*>(pFile)) == 0;
}

unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize)
{
	FILE* file = static_cast<FILE*>(pFile);
	if(file == nullptr)
	{
		printf("File is null, cancelling read operation.");
		return 0;
	}

	unsigned int uBytesRead = fread(pBuffer, sizeof(char), uSize - 1, file);
	*(pBuffer + uBytesRead) = '\0';
	return uBytesRead;
}

unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize)
{
	return fwrite(pBuffer, sizeof(char), uSize, static_cast<FILE*>(pFile));
}
const unsigned int uBufferSize = 128;

int main()
{
	//Write in file 
	char s_fileName[] = "copia.txt";
	char s_writeBuffer[] = "Esto es un texto de prueba. 12345. See you next mission";
	unsigned int uWriteBufferSize = sizeof(s_writeBuffer) / sizeof(char);

	void* myFile;
	myFile = FileOpen(s_fileName, FILE_WRITE);


	unsigned int uBytesWritten = FileWrite(myFile, s_writeBuffer, uWriteBufferSize);

	FileClose(myFile);

	//Read file and print it to console
	char s_readBuffer[uBufferSize];
	myFile = FileOpen(s_fileName, FILE_READ);

	unsigned int uBytesRead = FileRead(myFile, s_readBuffer, uBufferSize);

	printf("I have read %d bytes from the file:\n%s\n", uBytesRead, s_readBuffer);

	//Read file that doesn't exist
	myFile = FileOpen("noExiste.txt", FILE_READ);

	unsigned int uBytesRead2 = FileRead(myFile, s_readBuffer, uBufferSize);
}