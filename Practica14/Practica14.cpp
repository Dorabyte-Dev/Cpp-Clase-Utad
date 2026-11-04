#include <cstdio>
#include <iostream>

class A //Clase padre: Tiene vtable
{
public:
	int a;
	virtual void Test()
	{
		a++;
		printf("a");
	}
};
class B //Clase sin herencia: No tiene vtable
{
public:
	int b;
	void Test()
	{
		printf("b");
	}
};

class A2 : public A //Clase hija: Tiene vtable
{
public:
	virtual void Test() override
	{
		a++;
		printf("a2");
	}
};

int g_globalVar = 1;

int main()
{
	//a: ¿Cuánto espacio ocupa la tabla de funciones virtuales? (Pista: depende de
	//   cuántas funciones virtuales tenga la clase.)

	//La respuesta es 8 bytes, o al menos 8 bytes por cada función virtual que tenga (un puntero por función)

	//b: ¿Dónde está situada la tabla de funciones virtuales?

	//Se encuentra en la zona de memoria estática del ejecutable, donde también se
	//guardan las variables globales. Esto se puede comprobar leyendo la dirección de la vtable 
	//y la de una variable global, y viendo que efectivamente tienen direcciones cercanas en memoria.


	A obj;
	void** vptr = *reinterpret_cast<void***>(&obj); //vtable pointer

	int count = 0;
	while(vptr[count] != nullptr)
	{
		count++;
		if(count > 50) break;
	}

	A* tDynamicObject = new A();

	int iLocalVar = 100;

	int* iHeapVar = new int(100);

	printf("VTable direction:   %p\n", vptr); //00007FF7CB1233D0
	printf("VTable function count: %d\n", count);
	printf("VTable size: %du\n", count * sizeof(void*));
	printf("g_globalVar direction: %p\n", (void*)&g_globalVar); //00007FF7CB125074
	printf("iLocalVar direction: %p\n", (void*)&iLocalVar); //0000008FDD8FFAC0
	printf("iHeapVar direction: %p\n\n", (void*)iHeapVar); //000001D4A08054C0

	//c: ¿Cuánto ocupa de más un objeto por tener funciones virtuales? (Compara el sizeof con y sin virtual.)

	std::cout << "Sizeof(A) = " << sizeof(A) << "\n";   //Sizeof(A) = 12 (vpointer 8 + int 4)
	std::cout << "Sizeof(B) = " << sizeof(B) << "\n";	//Sizeof(B) = 4
	std::cout << "Sizeof(A2) = " << sizeof(A2) << "\n"; //Sizeof(A2) = 12 (vpointer 8 + int 4)


	//d:¿Qué pasa si llamo a un método virtual desde el constructor? ¿Y desde el destructor?
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
	
	//e. Comparar la llamada a una función virtual con la llamada a una función no
	//   virtual.¿Cuántos pasos adicionales tienen que realizarse cuando es virtual?

	A2 a2;
	A* pObj = &a2;
	pObj->Test(); //En teoría, debería realizar varias instrucciones más, en concreto 3(un acceso a memoria  
				  //para leer la dirección del vpointer, la búsqueda de la función a llamar dentro de la 
				  //vtable, y un segundo acceso a memoria para leer la dirección de la función final a llamar),
				  //pero el compilador optimiza los pasos automáticamente así que solo salen 2 pasos en los 2.

	B b;
	b.Test();

}