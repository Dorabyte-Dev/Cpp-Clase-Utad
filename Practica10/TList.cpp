#include "TList.h"
#include <cstring>

TElem::TElem(const char* psz)
{
    if(psz)
    {
        unsigned int uLen = strlen(psz);
        m_psz = new char[uLen + 1];
        strcpy_s(m_psz, uLen + 1, psz);
    }
}
TElem::~TElem()
{
	delete[] m_psz;
}
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
	TElem* pNewElem = new TElem(psz);
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
    if (m_pCurrent && m_pCurrent->m_pNext) //Si el siguiente es null, Next() no debería de moverse ya que no está devolviendo nada
    {
		m_pCurrent = m_pCurrent->m_pNext;
        return m_pCurrent->m_psz;
    }
    return nullptr;
}

// Quita el primer elemento de la lista y lo retorna.
// Retorna nullptr si la lista está vacía.

const char* TList::Pop() //Retorna un const char* a un elemento en el heap que el usuario tiene que borrar, peligroso!!!
{
    if (m_pLast) 
    {
        const char* psz = m_pLast->m_psz;
        
        m_pLast->m_psz = nullptr;
        
        if(m_pLast != m_pFirst)
        {
            TElem* pTmp(m_pFirst);
            while(pTmp->m_pNext != m_pLast)
            {
                pTmp = pTmp->m_pNext;
            }

            if(m_pCurrent == m_pLast)
            {
                m_pCurrent = pTmp;
            }
            delete m_pLast;
            m_pLast = pTmp;
            m_pLast->m_pNext = nullptr;
        }
        else
        {
            m_pFirst = nullptr;
            m_pCurrent = nullptr;
            m_pLast = nullptr;
            delete m_pLast;
        }
        uSize--;
        return psz;
    }
    return nullptr;

}

// Elimina todos los elementos. La lista queda vacía (Size() == 0) y se puede seguir usando.
void TList::Reset()
{
    TElem* pTmp(m_pFirst);
    while(pTmp)
    {
        TElem* pToDelete = pTmp;
		pTmp = pTmp->m_pNext;

		delete pToDelete;
    }
    m_pFirst = nullptr;
    m_pLast = nullptr;
    m_pCurrent = nullptr;
    uSize = 0;
}