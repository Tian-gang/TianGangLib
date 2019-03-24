#ifndef __STATICARRAY_H__
#define __STATICARRAY_H__

#include "Array.h"

namespace TianGangLib
{

template < typename T, int N >
class StaticArray : public Array<T>
{
protected:
    T m_space[N];
public:
    StaticArray()
    {
        this->m_array = m_space;
    }

    StaticArray(const StaticArray<T, N>& obj)
    {
        this->m_array = m_space;
        for(int i = 0; i < N; ++i)
        {
            m_space[i] = obj.m_space[i];
        }
    }

    StaticArray<T, N>& operator =(const StaticArray<T, N>& obj)
    {
        if(this != &obj)
        {
            for(int i = 0; i < N; ++i)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return *this;
    }

    int length() const
    {
        return N;
    }
};

}

#endif // __STATICARRAY_H__
