#pragma once
class TElem
{

public:
    TElem(const char* psz);
    ~TElem();
    char* m_psz = nullptr;
    TElem* m_pNext = nullptr;
};

class TList
{
public:
    
    TList();

    TList(const TList& _rOther);

    TList& operator=(const TList& _rOther);

    TList GetReverseList(const TList& _lstSrc);
    
    ~TList();

    int Size() const;

    int Push(const char* psz);

    const char* First();

    const char* Next();

    const char* Pop();

    void Reset();

private:
    void Init();
    void CopyFromList(const TList& _rOther);
	unsigned int uSize;
	TElem* m_pFirst;
	TElem* m_pLast;
	TElem* m_pCurrent;
};