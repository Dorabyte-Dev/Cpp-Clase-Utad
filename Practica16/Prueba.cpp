#include <iostream>
#include "TList.h"
#include "IListItem.h"
int main()
{
	TList tList;
	
	tList.Push(StringItem("uno"));
	printf("Primero: %d\n", tList.Size());
	tList.Push(StringItem("dos"));
	printf("Segundo: %d\n", tList.Size());
	tList.Push(IntItem(3));
	printf("Tercero: %d\n", tList.Size());

	tList.Print();

	TList tListInversa;
	tListInversa.GetReverseList(tList);


	IListItem* pString = tList.Pop();
	printf("(original)Popped string is ");
	pString->Print();
	delete[] pString;
	pString = tList.Pop();
	printf("(original)Popped string is ");
	pString->Print();
	delete[] pString;
	pString = tList.Pop();
	printf("(original)Popped string is ");
	pString->Print();
	delete[] pString;

	printf("(original)Size after Pop() is: %d\n", tList.Size());

	printf("\n");

	tList.Print();

	pString = tListInversa.Pop();
	printf("(copia)Popped string is ");
	pString->Print();
	delete[] pString;
	pString = tListInversa.Pop();
	printf("(copia)Popped string is ");
	pString->Print();
	delete[] pString;
	pString = tListInversa.Pop();
	printf("(copia)Popped string is ");
	pString->Print();
	delete[] pString;

	printf("(copia)Size after Pop() is: %d\n", tListInversa.Size());

	printf("\n");
}