#include "Debug.h"
#include <iostream>

int main()
{
	int iIntentos = 0;
	for(int i = 0; i < 5; ++i)
	{
		printf("I is %d\n", i);

		ASSERT(++iIntentos < 3); //En Debug, iIntentos al final vale 3, pero en Release vale 0 siempre, ya que está puesto para que 
								 //se sustituya por un do-while vacío y no ejecute la condición. La regla que podríamos sacar es
								 //que no se haga ninguna operación necesaria para el funcionamiento de un programa dentro de un 
								 //ASSERT, ya que así en Debug todo funcionará pero cuando se pase a Release el programa empezará a fallar.
		printf("%d\n", iIntentos);
	}
}