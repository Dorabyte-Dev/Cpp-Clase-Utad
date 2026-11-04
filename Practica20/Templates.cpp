#include "Templates.h"
#include "TVector2.h"

int main()
{
	Clamp(150, 0, 100); 
	Clamp(-0.5f, 0.0f, 1.0f); 
	Clamp(5, 0.0f, 10); 

	TStack<int, 4> tNumbers;
	tNumbers.Push(1); // true
	tNumbers.Push(2); // true
	tNumbers.Push(3); // true
	tNumbers.Push(4); // true
	tNumbers.Push(5); // false
	int iValue = 0;
	while(tNumbers.Pop(iValue)) 
	{
		printf("Pop result is: %d\n", iValue);
	};
	
	TStack<TVector2, 8> tPath;


	printf("Sizeof(TStack<int, 4>) = %d\n", sizeof(TStack<int, 4>)); //20
	printf("Sizeof(TStack<int, 100>) = %d\n", sizeof(TStack<int, 100>)); //404
	
	// ¿Son el mismo tipo?
	// No, ya que el compilador, al trabajar con templates, crea una clase nueva cada vez que
	// se usa TStack con parámetros distintos. Da igual que ambas TStack sean int, porque como
	// el parámetro SIZE cambia, el compilador crea una clase diferente para cada una y las 
	// trata como tipos diferentes.
}