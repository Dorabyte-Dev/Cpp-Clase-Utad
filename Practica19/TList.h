#pragma once

template <class T>
class TList
{
    friend GetReverseList
public:
    
    TList()
    {
        uSize = 0;
        m_pFirst = nullptr;
        m_pCurrent = nullptr;
        m_pLast = nullptr;
    }

    TList(const TList& _rOther)
    {
        uSize = 0;
        m_pFirst = nullptr;
        m_pCurrent = nullptr;
        m_pLast = nullptr;

        TElem* m_pTmp = _rOther.m_pFirst;
        while(m_pTmp)
        {
            Push(m_pTmp->m_item);
            m_pTmp = m_pTmp->m_pNext;
        }
        static int numberOfCalls = 0;
        printf("Number of copies: %d\n", ++numberOfCalls);
    }
    TList& operator=(const TList& _rOther)
    {
        if(this != _rOther)
        {
            Reset();
            for(TElem* p = _rOther.m_pFirst; p != nullptr; p = p->m_pNext)
            {
                Push(p->m_item);
            }
            return *this;
        }
    }
    
    ~TList()
    {
        Reset();
    }

    friend TList GetReverseList(const TList<T>& _lstSrc);

    int Size() const
    {
        return uSize;
    }

    int Push(const T& _rElem)
    {
        TElem* pNewElem = new TElem;
        pNewElem->m_item = _rElem;
        if(!m_pFirst)
        {
            m_pFirst = pNewElem;
        }
        else
        {
            m_pLast->m_pNext = pNewElem;
        }
        m_pLast = pNewElem;
        return ++uSize;
    }

    T* First()
    {
        m_pCurrent = m_pFirst;
        return m_pFirst->m_item;
    }

    T* Next()
    {
        if(m_pCurrent && m_pCurrent->m_pNext)
        {
            m_pCurrent = m_pCurrent->m_pNext;
            return m_pCurrent->m_item;
        }
        return nullptr;
    }

    bool Pop(T& _rRet)
    {
        if(!m_pFirst) return false;

        TElem* p_Tmp = m_pFirst;
        m_pFirst = m_pFirst->m_pNext;

        if(!m_pFirst) m_pLast = nullptr;
        if(m_pCurrent == p_Tmp) m_pCurrent = nullptr;

        
        uSize--;
        _rRet = p_Tmp->m_item;
        p_Tmp->m_pNext = nullptr;
        delete p_Tmp;
        return true;
        
    }

    void Reset()
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

    class TElem
    {

    public:
        T m_item;
        TElem* m_pNext = nullptr;
    };

private:
	unsigned int uSize;
	TElem* m_pFirst;
    TElem* m_pLast;
    TElem* m_pCurrent;
};

template <class T>
TList<T> GetReverseList(const TList<T>& _lstSrc)
{
    for(int i = 0; i < _lstSrc.Size(); ++i)
    {
        TElem* pTmp(_lstSrc.m_pFirst);
        for(int j = 0; j < _lstSrc.Size() - 1 - Size(); ++j)
        {
            pTmp = pTmp->m_pNext;
        }
        Push(pTmp->m_item);
    }

    return *this;
}