#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include "Array.h"

namespace TianGangLib
{
template < typename T >
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    void init(T* array, int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to init DynamicArray object...");
        }
    }

    T* copy(T* array, int len, int newLen)
    {
        T* ret = new T[newLen];

        if(ret != NULL)
        {
            int size = (len < newLen) ? len : newLen;

            for(int i = 0; i < size; ++i)
            {
                ret[i] = array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object...");
        }

        return ret;
    }

    void update(T* array, int length)
    {
        if(array != NULL)
        {
            T* toDel = this->m_array;

            this->m_array = array;
            this->m_length = length;

            delete[] toDel;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object...");
        }
    }

public:
    DynamicArray(int length = 0)
    {
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    void resize(int length)
    {
        if(length != m_length)
        {
            update(copy(this->m_array, m_length, length), length);
        }
    }

    int length() const
    {
        return m_length;
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};
}


#endif // __DYNAMICARRAY_H__
