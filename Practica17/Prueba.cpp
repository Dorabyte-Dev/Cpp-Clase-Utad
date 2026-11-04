#include <cstdio>
#include "NoMacros.cpp"
#include "Macros.cpp"

int main()
{
	char sText_N[] = "Perro";
	Animal_NoMacros::Enum myAnimal_N = Animal_NoMacros::AsEnum(sText_N);

	printf("El enum de No Macros es %s\n", Animal_NoMacros::AsStr(myAnimal_N));

	char sText_M[] = "Conejo";
	Animal_NoMacros::Enum myAnimal_M = Animal_NoMacros::AsEnum(sText_M);

	printf("El enum de Macros es %s\n", Animal_NoMacros::AsStr(myAnimal_M));
}