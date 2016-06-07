#pragma once
#include <string.h>

namespace triebWerk
{
    template <class T>
    class CFrameContainer
    {
    private:
        T* m_pElements;
        size_t m_MaxSize;
        size_t m_Size;
        size_t m_ElementSize;

    public:
        CFrameContainer();
        CFrameContainer(size_t a_ElementCount);
        ~CFrameContainer();

        void Add(const T& a_rValue);
        bool Contains(const T& a_rValue);
        void Reset();
        void Resize(size_t a_Elements);
        size_t GetSize() const;
        size_t GetMaxSize() const;

        T& operator[](size_t a_Index);
    };

    template <class T>
    inline CFrameContainer<T>::CFrameContainer() :
        m_pElements(nullptr),
        m_MaxSize(32),
        m_Size(0)
    {
        m_pElements = new T[m_MaxSize];
        m_ElementSize = sizeof(T);
    }

    template<class T>
    inline CFrameContainer<T>::CFrameContainer(size_t a_ElementCount) : 
        m_pElements(nullptr),
        m_MaxSize(a_ElementCount),
        m_Size(0)
    {
        m_pElements = new T[m_MaxSize];
        m_ElementSize = sizeof(T);
    }

    template <class T>
    inline CFrameContainer<T>::~CFrameContainer()
    {
        delete[] m_pElements;
    }

    template<class T>
    inline void CFrameContainer<T>::Add(const T& a_rValue)
    {
        m_pElements[m_Size] = a_rValue;
        m_Size++;
    }

    template<class T>
    inline bool CFrameContainer<T>::Contains(const T& a_rValue)
    {
        for (size_t i = 0; i < m_Size; ++i)
        {
            if (m_pElements[i] == a_rValue)
                return true;
        }

        return false;
    }

    template<class T>
    inline void CFrameContainer<T>::Reset()
    {
        m_Size = 0;
    }

    template<class T>
    inline void CFrameContainer<T>::Resize(size_t a_Elements)
    {
        // get byte count that shall be copied
        if (m_Size > a_Elements)
            m_Size = a_Elements;

        size_t copyAmount = m_Size * m_ElementSize;

        // alloc new memory
        m_MaxSize = a_Elements;
        T* newAlloc = new T[m_MaxSize];

        // switch the memory
        memcpy(newAlloc, m_pElements, copyAmount);
        delete[] m_pElements;
        m_pElements = newAlloc;
    }

    template<class T>
    inline size_t CFrameContainer<T>::GetSize() const
    {
        return m_Size;
    }

    template<class T>
    inline size_t CFrameContainer<T>::GetMaxSize() const
    {
        return m_MaxSize;
    }

    template<class T>
    inline T& CFrameContainer<T>::operator[](size_t a_Index)
    {
        return m_pElements[a_Index];
    }
}