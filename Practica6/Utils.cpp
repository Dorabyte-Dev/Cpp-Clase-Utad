#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "File.h"
#include "Utils.h"

namespace Utils
{
	const unsigned int uBufferSize = 16;

	int CountOcurrences(const char* pszFileName, const char* pszText)
	{
		unsigned int uSubstringLength = strlen(pszText);
		int iOcurrenceCount = 0;
		char s_Buffer[uBufferSize];
		FILE* myFile = static_cast<FILE*>(File::FileOpen(pszFileName, File::FILE_READ));

		//Check if file is valid
		if(myFile == nullptr)
		{
			printf("File not found, cancelling operation.");
			return -1;
		}

		char* pTextPointer = s_Buffer;

		int iNumberOfReads = 0;
		unsigned int uBytesRead = 0;
		unsigned int uBytesReadSecondBuffer = 0;
		unsigned int uLastOccurrenceNumber = 0;

		do
		{
			fseek(myFile, (uBufferSize - 1) * iNumberOfReads, SEEK_SET);

			uBytesRead = File::FileRead(myFile, s_Buffer, uBufferSize);

			if(uLastOccurrenceNumber != 0) //If an occurrence check was cut, it continues the operation on the new buffer
			{
				bool bIsNewOccurrence = true;
				for(int i = uLastOccurrenceNumber; i < uSubstringLength; ++i)
				{
					if(*(pTextPointer + i - uLastOccurrenceNumber) != *(pszText + i))
					{
						bIsNewOccurrence = false;
						break;
					}
				}
				if(bIsNewOccurrence)
				{
					iOcurrenceCount++;
				}
			}

			uLastOccurrenceNumber = 0;

			for(int i = 0; i < uBytesRead; ++i)
			{
				if(*(pTextPointer + i) == *pszText) //same letter encounter
				{
					bool bIsNewOccurrence = true;
					for(int j = 1; j < uSubstringLength; ++j) //for each consecutive letter encounter, breaks when not equal
					{
						if(j >= uBytesRead - i) //if buffer ends while a substring is being read
						{
							uLastOccurrenceNumber = j;
							break;
						}

						if(*(pTextPointer + i + j) != *(pszText + j))
						{
							bIsNewOccurrence = false;
							break;
						}
					}
					if(uLastOccurrenceNumber != 0)
					{
						break;
					}
					if(bIsNewOccurrence)
					{
						iOcurrenceCount++;
					}
				}
			}
			iNumberOfReads++;

		} while(uBytesRead == uBufferSize - 1); //if buffer has been filled completely, it will continue reading from after the last character read


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
			printf("Ocurrences of %s are %d\n", sWord, CountOcurrences("texto.txt", sWord));
		}


		int iSum = 0;
		SumNumbers("numeros.txt", iSum);
		printf("The sum of all numbers is %d\n", iSum);
	}
}