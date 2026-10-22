#include <cstdio>

class A //Clase padre: Tiene vtable
{
	int a;
	virtual void Test()
	{

	}
};
class B //Clase sin herencia: No tiene vtable
{
	int b;
	void Test()
	{

	}
};

class A2 : public A //Clase hija: Tiene vtable
{
	virtual void Test() override
	{

	}
};


int main()
{
	//1: Con código documentado que lo demuestre, en Visual Studio x64: ¿cuánto ocupa la vtable? ¿Dónde está?

	//2: ¿Cuánto ocupa de más un objeto por tener funciones virtuales? (Compara el sizeof con y sin virtual.)

	printf("Sizeof(A) = %d\n", sizeof(A));  //Sizeof(A) = 12 (vpointer 8 + int 4)
	printf("Sizeof(B) = %d\n", sizeof(B));	//Sizeof(B) = 4
	printf("Sizeof(A2) = %d\n", sizeof(A2));//Sizeof(A2) = 12 (vpointer 8 + int 4)

	//3:¿Qué pasa si llamo a un método virtual desde el constructor? ¿Y desde el destructor?
	// 
	// No compila. No tiene sentido llamar a un método virtual desde el constructor de la clase padre,
	// ya que en el momento de ejecución del mismo, la parte derivada de la clase de donde se quiere llamar 
	// al método no está creada todavía.
	//
	// Desde el destructor sí que se puede llamar. Es más, es la mejor opción hacerlo virtual de cara a
	// evitar posibles errores, ya que en el caso contrario podría ocurrir lo siguiente:
	// 
	// 
	// int main() {
	//		A padre = new A2();
	// } <- Se sale del scope, y se llama solo a ~A(), pero no a ~A2()
	// 
	// 
	// Un objeto de la clase padre (A, en este caso) que haya sido inicializado con el hijo (A2), 
	// sería efectivamente un objeto tipo A2, pero en cuanto se destruya, al ser la variable tipo A, 
	// solo se llamaría al destructor de A. Si el destructor en A se hiciera virtual, esto no pasaría.

}