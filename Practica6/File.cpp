#define _CRT_SECURE_NO_WARNINGS // antes de todo
#include <cstdio>
#include "File.h"

namespace File
{
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
}