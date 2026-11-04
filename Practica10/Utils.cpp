#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "File.h"
#include "Utils.h"
#include "TList.h"

namespace Utils
{
	const unsigned int uBufferSize = 16;

	int CountOcurrences(const char* pszFileName, const char* pszText)
	{
		const unsigned int uSubstringLength = strlen(pszText);
		int iOcurrenceCount = 0;
		char s_Buffer[uBufferSize];

		FILE* myFile = static_cast<FILE*>(File::FileOpen(pszFileName, File::FILE_READ));

		if(myFile == nullptr) //Check if file is valid
		{
			printf("File not found, cancelling operation.");
			return -1;
		}

		if(uSubstringLength == 0)
		{
			printf("The substring to find cannot be empty, cancelling operation.");
			return 0;
		}

		char* pWindow = new char[uSubstringLength];
		unsigned int uFilled = 0;

		char* pTextPointer = s_Buffer;

		unsigned int uBytesRead = 0;

		do
		{
			uBytesRead = File::FileRead(myFile, s_Buffer, uBufferSize);

			for(int i = 0; i < uBytesRead; ++i)
			{

				if(uFilled < uSubstringLength)
				{
					pWindow[uFilled++] = s_Buffer[i]; //If window is not filled completely, continue filling it
				}
				else
				{
					memmove(pWindow, pWindow + 1, uSubstringLength - 1); //Move the reading window each time a new character needs to be read
					pWindow[uSubstringLength - 1] = s_Buffer[i];
				}

				if(uFilled == uSubstringLength && memcmp(pWindow, pszText, uSubstringLength) == 0)
				{
					++iOcurrenceCount;
				}
			}

		} while(uBytesRead == uBufferSize - 1); //if buffer has been filled completely, it will continue reading from after the last character read

		delete[] pWindow;
		File::FileClose(myFile);
		return iOcurrenceCount;

	}

	bool SumNumbers(const char* pszFileName, int& iSum_)
	{
		char s_Buffer[uBufferSize];
		char s_Tmp[uBufferSize] = { '\0' };
		char* ps_Tmp = s_Tmp;
		FILE* myFile = static_cast<FILE*>(File::FileOpen(pszFileName, File::FILE_READ));

		if(myFile == nullptr)
		{
			printf("File not found, cancelling operation.");
			return false;
		}

		unsigned int uBytesRead;

		do
		{
			uBytesRead = File::FileRead(myFile, s_Buffer, uBufferSize);

			for(int i = 0; i < uBytesRead + 1; ++i)
			{
				if(s_Buffer[i] == ',' || (s_Buffer[i] == '\0' && uBytesRead != uBufferSize - 1))
				{
					unsigned int uStringLength = strlen(s_Tmp);
					int iTempNumber = 0;
					for(int j = uStringLength - 1; j >= 0; --j)
					{
						if(s_Tmp[j] >= '0' && s_Tmp[j] <= '9')
						{
							iTempNumber += (s_Tmp[j] - '0') * pow(10, uStringLength - j - 1);
						}
						else if(s_Tmp[j] == '-')
						{
							iTempNumber *= -1;
						}
					}
					iSum_ += iTempNumber;
					ps_Tmp = s_Tmp;
					memset(s_Tmp, '\0', uBufferSize);
				}
				if((s_Buffer[i] >= '0' && s_Buffer[i] <= '9') || s_Buffer[i] == '-')
				{
					*ps_Tmp = s_Buffer[i];
					ps_Tmp++;

				}
			}

		} while(uBytesRead == uBufferSize - 1);
		return true;

	}

	TList ListNumbers(const char* pszFileName)
	{
		TList tList;
		char s_Buffer[uBufferSize];
		char s_Tmp[uBufferSize] = { '\0' };
		char* ps_Tmp = s_Tmp;
		FILE* myFile = static_cast<FILE*>(File::FileOpen(pszFileName, File::FILE_READ));

		if(myFile == nullptr)
		{
			printf("File not found, cancelling operation.");
			return tList;
		}

		unsigned int uBytesRead;

		do
		{
			uBytesRead = File::FileRead(myFile, s_Buffer, uBufferSize);

			for(int i = 0; i < uBytesRead + 1; ++i)
			{
				if(s_Buffer[i] == ',' || (s_Buffer[i] == '\0' && uBytesRead != uBufferSize - 1))
				{
					tList.Push(s_Tmp);
					ps_Tmp = s_Tmp;
					memset(s_Tmp, '\0', uBufferSize);
				}
				if((s_Buffer[i] >= '0' && s_Buffer[i] <= '9') || s_Buffer[i] == '-')
				{
					*ps_Tmp = s_Buffer[i];
					ps_Tmp++;

				}
			}

		} while(uBytesRead == uBufferSize - 1);

		return tList;
	}

	
}

const char* s_tTablaDeCadenas[] =
{
	"enemigo",
	"Enemigo",
	"aa",
	"xyz"
};

int main()
{
	for(const char* sWord : s_tTablaDeCadenas)
	{
		printf("Ocurrences of %s are %d\n", sWord, Utils::CountOcurrences("texto.txt", sWord));
	}


	int iSum = 0;
	Utils::SumNumbers("numeros.txt", iSum);
	printf("The sum of all numbers is %d\n", iSum);

	TList tList = Utils::ListNumbers("numeros.txt");
	for(const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("%s\n", p);
	}

	return 0;
}