#pragma once
#include "IListItem.h"
class TElem
{

public:
    TElem(IListItem* item);
    ~TElem();
    IListItem* m_item = nullptr;
    TElem* m_pNext = nullptr;
};
class TList
{
public:
    
    TList();

    TList(const TList& _rOther);

    TList GetReverseList(const TList& _lstSrc);
    
    ~TList();

    int Size() const;

    int Push(const IListItem& _rElem);

    IListItem* First();

    IListItem* Next();

    IListItem* Pop();

    void Print();

    void Reset();

private:
	unsigned int uSize;
	TElem* m_pFirst;
    TElem* m_pLast;
    TElem* m_pCurrent;
};