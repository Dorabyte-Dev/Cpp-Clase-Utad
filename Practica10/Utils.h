#pragma once
#include "TList.h"
namespace Utils
{
	int CountOcurrences(const char* pszFileName, const char* pszText);

	bool SumNumbers(const char* pszFileName, int& iSum_);

	TList ListNumbers(const char* pszFileName);
}