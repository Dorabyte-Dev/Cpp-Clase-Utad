#include <iostream>
#include "TList.h"

int main()
{
	TList tList;
	
	tList.Push("uno");
	printf("Primero: %d\n", tList.Size());
	tList.Push("dos");
	printf("Segundo: %d\n", tList.Size());
	tList.Push("tres");
	printf("Tercero: %d\n", tList.Size());

	for(const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("(original)%s\n", p);
	}

	TList tListInversa;
	tListInversa.GetReverseList(tList);


	const char* pString = tList.Pop();
	printf("(original)Popped string is %s\n", pString);
	delete[] pString;
	pString = tList.Pop();
	printf("(original)Popped string is %s\n", pString);
	delete[] pString;
	pString = tList.Pop();
	printf("(original)Popped string is %s\n", pString);
	delete[] pString;
	pString = tList.Pop();
	printf("(original)Popped string is %s\n", pString);

	printf("(original)Size after Pop() is: %d\n", tList.Size());

	printf("\n");

	tList = tListInversa;

	for(const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("(operador de copia)%s\n", p);
	}

	printf("\n");

	for(const char* p = tListInversa.First(); p != nullptr; p = tListInversa.Next())
	{
		printf("(copia inversa)%s\n", p);
	}

	pString = tListInversa.Pop();
	printf("(copia inversa)Popped string is %s\n", pString);
	delete[] pString;
	pString = tListInversa.Pop();
	printf("(copia inversa)Popped string is %s\n", pString);
	delete[] pString;
	pString = tListInversa.Pop();
	printf("(copia inversa)Popped string is %s\n", pString);
	delete[] pString;
	pString = tListInversa.Pop();
	printf("(copia inversa)Popped string is %s\n", pString);

	printf("(copia inversa)Size after Pop() is: %d\n", tListInversa.Size());

	printf("\n");
}