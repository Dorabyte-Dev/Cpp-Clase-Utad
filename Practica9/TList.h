// ***************************************************************************************
// TList.h - Práctica 9: lista enlazada de cadenas
//
// La interfaz pública está fijada: no cambiéis los nombres ni los parámetros, porque las
// prácticas 10, 11, 16 y 19 parten de ella.
// La parte privada (cómo se guardan los elementos) la decidís vosotros.
//
// Ejemplo de uso:
//
//     TList lista;
//     lista.Push("uno");
//     lista.Push("dos");
//     lista.Push("tres");                    // lista: uno, dos, tres  -> Size() == 3
//
//     for (const char* p = lista.First(); p != nullptr; p = lista.Next())
//         printf("%s\n", p);                 // uno, dos, tres
//
//     const char* pPrimero = lista.Pop();    // "uno"  -> lista: dos, tres
//     lista.Reset();                         // lista vacía -> Size() == 0
// ***************************************************************************************
#pragma once

class TList
{
public:
    // Crea una lista vacía.
    TList();

    // Libera toda la memoria que haya reservado la lista.
    ~TList();

    // Número de elementos de la lista (0 si está vacía).
    int Size();

    // Añade la cadena AL FINAL de la lista.
    // Retorna el número de elementos que tiene la lista después de añadirla.
    int Push(const char* psz);

    // Retorna el primer elemento de la lista, o nullptr si está vacía.
    // Además, deja la lista preparada para que Next() devuelva el segundo.
    const char* First();

    // Retorna el elemento siguiente al último devuelto por First() o Next().
    // Retorna nullptr cuando ya no quedan más elementos (o si no se ha llamado a First()).
    const char* Next();

    // Quita el primer elemento de la lista y lo retorna.
    // Retorna nullptr si la lista está vacía.
    const char* Pop();

    // Elimina todos los elementos. La lista queda vacía (Size() == 0) y se puede seguir usando.
    void Reset();

private:
    // TODO: los miembros privados los decidís vosotros.
	unsigned int uSize;
	TElem* m_pFirst;
	TElem* m_pLast;
	TElem* m_pCurrent;
};

class TElem {

public:
    TElem(const char* psz);
    const char* m_psz;
    TElem* m_pNext;
};