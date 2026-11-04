#include <iostream>
#include "TList.h"


class CText
{
public:
	void Print() const
	{
		printf("%s\n", sText);
	}
	const char* sText = "";
};

int main()
{
	TList<CText> tList;

	CText tText;
	tText.sText = "uno";

	CText tText2;
	tText2.sText = "dos";

	CText tText3;
	tText3.sText = "tres";
	
	tList.Push(tText);
	printf("Primero: %d\n", tList.Size());
	tList.Push(tText2);
	printf("Segundo: %d\n", tList.Size());
	tList.Push(tText3);
	printf("Tercero: %d\n", tList.Size());


	TList<CText> tListInversa;
	tListInversa = GetReverseList(tList);


	CText tString;
	while(tList.Pop(tString))
	{
		printf("(original)Popped string is ");
		tString.Print();
	}

	printf("(original)Size after Pop() is: %d\n", tList.Size());

	printf("\n");


	while(tListInversa.Pop(tString))
	{
		printf("(copia) Popped string is ");
		tString.Print();
	}

	printf("(copia)Size after Pop() is: %d\n", tListInversa.Size());

	printf("\n");
}


