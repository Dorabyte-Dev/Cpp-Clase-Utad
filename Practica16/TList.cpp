#include "TList.h"
#include "IListItem.h"
#include <cstring>
#include <cstdio>

TElem::TElem(IListItem* item)
{
    m_item = item;
    m_pNext = nullptr;
}
TElem::~TElem()
{
    delete m_item;
}
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

    TElem* m_pTmp = _rOther.m_pFirst;
    while(m_pTmp)
    {
        Push(*m_pTmp->m_item);
        m_pTmp = m_pTmp->m_pNext;
    }
    static int numberOfCalls = 0;
    printf("Number of copies: %d\n", ++numberOfCalls); //2 copias si GetReverseList acepta TList; 1 copia si GetReverseList acepta TList&
}

TList TList::GetReverseList(const TList& _lstSrc) //El parámetro _lstSrc solo puede ser const si hacemos la función Size también const, 
{                                                 //ya que si no es imposible llamar a _lstSrc.Size()

    for(int i = 0; i < _lstSrc.Size(); ++i)
    {
        TElem* pTmp(_lstSrc.m_pFirst);
        for(int j = 0; j < _lstSrc.Size() - 1 - Size(); ++j)
        {
            pTmp = pTmp->m_pNext;
        }
        Push(*pTmp->m_item);
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
	TElem* pNewElem = new TElem(_rElem.Clone());
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
	return m_pFirst->m_item;
}

IListItem* TList::Next()
{
    if (m_pCurrent && m_pCurrent->m_pNext) 
    {
		m_pCurrent = m_pCurrent->m_pNext;
        return m_pCurrent->m_item;
    }
    return nullptr;
}


IListItem* TList::Pop() //Retorna un IListItem* a un elemento en el heap que el usuario tiene que borrar, peligroso!!!
{
    if(m_pFirst)
    {
        TElem* p_Tmp = m_pFirst;
        m_pFirst = m_pFirst->m_pNext;
        p_Tmp->m_pNext = nullptr;
        uSize--;
        return p_Tmp->m_item;
    }
    return nullptr;

}

void TList::Print()
{
    TElem* pTmp(m_pFirst);
    while(pTmp)
    {
        pTmp->m_item->Print();
        pTmp = pTmp->m_pNext;
    }
}

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