#pragma once
#include "IListItem.h"

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
	IListItem* m_pFirst;
	IListItem* m_pLast;
	IListItem* m_pCurrent;
};