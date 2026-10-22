#include "TList.h"
#include "IListItem.h"
#include <cstring>
#include <cstdio>

TList::TList()
{
    uSize = 0;
	m_pFirst = nullptr;
	m_pCurrent = nullptr;
	m_pLast = nullptr;
}

TList::TList(const TList& _rOther)
{
    uSize = 0;
    m_pFirst = nullptr;
    m_pCurrent = nullptr;
    m_pLast = nullptr;

    IListItem* m_pTmp = _rOther.m_pFirst;
    while(m_pTmp)
    {
        Push(*m_pTmp);
        m_pTmp = m_pTmp->m_pNext;
    }
    static int numberOfCalls = 0;
    printf("Number of copies: %d\n", ++numberOfCalls); //2 copias si GetReverseList acepta TList; 1 copia si GetReverseList acepta TList&
}

TList TList::GetReverseList(const TList& _lstSrc) //El parámetro _lstSrc solo puede ser const si hacemos la función Size también const, 
{                                                 //ya que si no es imposible llamar a _lstSrc.Size()

    for(int i = 0; i < _lstSrc.Size(); ++i)
    {
        IListItem* pTmp(_lstSrc.m_pFirst);
        for(int j = 0; j < _lstSrc.Size() - 1 - Size(); ++j)
        {
            pTmp = pTmp->m_pNext;
        }
        Push(*pTmp);
    }
    
    return *this;
}

TList::~TList()
{
    Reset();
}

int TList::Size() const 
{
	return uSize;
}

int TList::Push(const IListItem& _rElem)
{
	IListItem* pNewElem = _rElem.Clone();
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

IListItem* TList::First() 
{
    m_pCurrent = m_pFirst;
	return m_pFirst;
}

IListItem* TList::Next() 
{
    if (m_pCurrent && m_pCurrent->m_pNext) 
    {
		m_pCurrent = m_pCurrent->m_pNext;
        return m_pCurrent;
    }
    return nullptr;
}


IListItem* TList::Pop() //Retorna un const char* a un elemento en el heap que el usuario tiene que borrar, peligroso!!!
{
    if(m_pFirst)
    {
        IListItem* p_Tmp = m_pFirst;
        m_pFirst = m_pFirst->m_pNext;
        p_Tmp->m_pNext = nullptr;
        uSize--;
        return p_Tmp;
    }
    return nullptr;

}

void TList::Print()
{
    IListItem* pTmp(m_pFirst);
    while(pTmp)
    {
        pTmp->Print();
        pTmp = pTmp->m_pNext;
    }
}

void TList::Reset()
{
    IListItem* pTmp(m_pFirst);
    while(pTmp)
    {
        IListItem* pToDelete = pTmp;
		pTmp = pTmp->m_pNext;

		delete pToDelete;
    }
    m_pFirst = nullptr;
    m_pLast = nullptr;
    m_pCurrent = nullptr;
    uSize = 0;
}