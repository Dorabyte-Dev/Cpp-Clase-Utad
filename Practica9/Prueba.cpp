#include <iostream>
#include "TList.h"

int main()
{
	TList tList;

	char myString[] = "tres";
	tList.Push("uno");
	printf("Primero: %d\n", tList.Size());
	tList.Push("dos");
	printf("Segundo: %d\n", tList.Size());
	tList.Push(myString);
	printf("Tercero: %d\n", tList.Size());

	for(const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("%s\n", p);
	}
	myString[0] = 'f';
	printf("MyString is %s\n", myString); //String modificada externamente es "fres", pero la que sale de la lista sigue siendo "tres", 
										  //ya que al introducirse en la lista se hizo una copia profunda y la unica modificada es la original.

	const char* pString = tList.Pop();
	printf("Popped string is %s\n", pString);
	delete[] pString;
	pString = tList.Pop();
	printf("Popped string is %s\n", pString);
	delete[] pString;
	pString = tList.Pop();
	printf("Popped string is %s\n", pString);
	delete[] pString;
	pString = tList.Pop();
	printf("Popped string is %s\n", pString);

	printf("Size after Pop() is: %d\n", tList.Size());

	printf("\n");
}