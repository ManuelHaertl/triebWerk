#pragma once
#include <string.h>

namespace triebWerk
{
    template <class T>
    class CElementContainer
    {
    private:
        T* m_pElements;
        size_t m_Size;
        size_t m_MaxSize;
        size_t m_ElementSize;

    public:
        CElementContainer();
        CElementContainer(size_t a_ElementCount);
        ~CElementContainer();

        void Add(const T& a_rElement);
        void Remove(const T& a_pElement);
        void Resize(size_t a_ElementCount);
        void Clear();
        bool Contains(const T& a_rElement);
        
        size_t GetSize() const;
        size_t GetMaxSize() const;

        T& operator[](size_t a_Index) const;
    };
    
    template<class T>
    inline CElementContainer<T>::CElementContainer() :
        m_Size(0),
        m_MaxSize(1)
    {
        m_ElementSize = sizeof(T);
        m_pElements = new T[m_MaxSize];
    }

    template<class T>
    inline CElementContainer<T>::CElementContainer(size_t a_ElementCount) :
        m_Size(0),
        m_MaxSize(a_ElementCount)
    {
        m_ElementSize = sizeof(T);
        m_pElements = new T[m_MaxSize];
    }

    template<class T>
    inline CElementContainer<T>::~CElementContainer()
    {
        delete[] m_pElements;
    }

    template<class T>
    inline void CElementContainer<T>::Add(const T& a_rElement)
    {
		if (m_Size == m_MaxSize)
		{
			Resize(m_MaxSize * 2);
		}

        m_pElements[m_Size] = a_rElement;
        m_Size++;
    }

    template<class T>
    inline void CElementContainer<T>::Remove(const T& a_pElement)
    {
        for (size_t i = 0; i < m_Size; ++i)
        {
            if (m_pElements[i] == a_pElement)
            {
                // check that the element that gets removed isn't at the end of the list
                size_t lastElement = m_Size - 1;
                if (lastElement != i)
                {
                    // put the last element where the removed is
                    m_pElements[i] = m_pElements[lastElement];
                }

                m_Size--;
                break;
            }
        }
    }

    template<class T>
    inline void CElementContainer<T>::Resize(size_t a_ElementCount)
    {
        // get byte count that shall be copied
        if (m_Size > a_ElementCount)
            m_Size = a_ElementCount;

        size_t copyAmount = m_Size * m_ElementSize;

        // alloc new memory
        m_MaxSize = a_ElementCount;
        T* newAlloc = new T[m_MaxSize];

        // switch the memory
        memcpy(newAlloc, m_pElements, copyAmount);
        delete[] m_pElements;
        m_pElements = newAlloc;
    }

    template<class T>
    inline void CElementContainer<T>::Clear()
    {
        m_Size = 0;
    }

    template<class T>
    inline bool CElementContainer<T>::Contains(const T& a_rElement)
    {
        for (size_t i = 0; i < m_Size; ++i)
        {
            if (m_pElements[i] == a_rElement)
                return true;
        }

        return false;
    }

    template<class T>
    inline size_t CElementContainer<T>::GetSize() const
    {
        return m_Size;
    }

    template<class T>
    inline size_t CElementContainer<T>::GetMaxSize() const
    {
        return m_MaxSize;
    }

    template<class T>
    inline T& CElementContainer<T>::operator[](size_t a_Index) const
    {
        return m_pElements[a_Index];
    }
}