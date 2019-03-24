#ifndef __DYNAMICLIST_H__
#define __DYNAMICLIST_H__

#include "SeqList.h"
#include "Exception.h"

namespace TianGangLib
{
template < typename T >
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;

public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if(this->m_array != NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to apply DynamicList...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    void resize(int capacity)
    {
        if(capacity != m_capacity)
        {
            T* space = new T[capacity];

            if(space != NULL)
            {
                int length = (this->m_length < capacity ? this->m_length : capacity);

                for(int i = 0; i < length; ++i)
                {
                    space[i] = this->m_array[i];
                }

                T* toDel = this->m_array;

                this->m_array = space;
                this->m_length = length;
                this->m_capacity = capacity;

                delete[] toDel;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to recapacity DynamicList obect....");
            }
        }
    }

    ~DynamicList()
    {
        delete[] this->m_array;
    }
};

}



#endif // __DYNAMICLIST_H__
