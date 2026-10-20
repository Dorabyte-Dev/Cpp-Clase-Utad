#include "TList.h"
#include <cstring>

// Crea una lista vacía.
TList::TList()
{
    uSize = 0;
	m_pFirst = nullptr;
	m_pCurrent = nullptr;
	m_pLast = nullptr;
}

// Libera toda la memoria que haya reservado la lista.
TList::~TList()
{
    Reset();
}

// Número de elementos de la lista (0 si está vacía).
int TList::Size()
{
	return uSize;
}

// Añade la cadena AL FINAL de la lista.
// Retorna el número de elementos que tiene la lista después de añadirla.
int TList::Push(const char* psz)
{
	//TODO:Reallocate list to fit new element
	TElem* pNewElem = new TElem(psz);
	//TODO: Recalculate next pointer of the last element
    if (!m_pFirst)
    {
        m_pFirst = pNewElem;
    }
    else
    {
        m_pLast->m_pNext = pNewElem;
    }
	m_pLast = pNewElem;
	uSize++;
	return uSize;
}

// Retorna el primer elemento de la lista, o nullptr si está vacía.
// Además, deja la lista preparada para que Next() devuelva el segundo.
const char* TList::First() 
{
    m_pCurrent = m_pFirst;
	return m_pFirst ? m_pFirst->m_psz : nullptr;
}

// Retorna el elemento siguiente al último devuelto por First() o Next().
// Retorna nullptr cuando ya no quedan más elementos (o si no se ha llamado a First()).
const char* TList::Next() 
{
    if (m_pCurrent) 
    {
		m_pCurrent = m_pCurrent->m_pNext;
        return m_pCurrent->m_psz;
    }
    return nullptr;
}

// Quita el primer elemento de la lista y lo retorna.
// Retorna nullptr si la lista está vacía.
const char* Pop() 
{
    if (m_pCurrent) 
    {
        m_pCurrent--;
		//const char* psz = m_pCurrent->m_psz;
    }

}

// Elimina todos los elementos. La lista queda vacía (Size() == 0) y se puede seguir usando.
void Reset();

// TODO: los miembros privados los decidís vosotros.


class TElem {

public:
    TElem(const char* psz)
    {
		m_psz = new char[strlen(psz) + 1];

    }
    const char* m_psz;
    TElem* m_pNext;	
};