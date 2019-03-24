#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "Object.h"
#include "Exception.h"
#include "Sort.h"

namespace TianGangLib
{
template < typename T >
class Array : public Object
{
protected:
    T* m_array;
public:
    bool set(int i, const T& e)
    {
        bool ret = (0 <= i) && (i < length());

        if(ret)
        {
            m_array[i] = e;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = (0 <= i) && (i < length());

        if(ret)
        {
            e = m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
        }
    }

    T& operator[] (int i)
    {
        if((0 <= i) && (i < length()))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
        }
    }

    T operator[] (int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }

    void selectSort(bool isAscendingSort = true)
    {
        Sort::select(m_array, length(), isAscendingSort);
    }

    void bubbleSort(bool isAscendingSort = true)
    {
        Sort::bubble(m_array, length(), isAscendingSort);
    }

    void insertSort(bool isAscendingSort = true)
    {
        Sort::insert(m_array, length(), isAscendingSort);
    }

    void shellSort(bool isAscendingSort = true)
    {
        Sort::shell(m_array, length(), isAscendingSort);
    }

    void quickSort(bool isAscendingSort = true)
    {
        Sort::quick(m_array, length(), isAscendingSort);
    }

    void mergeSort(bool isAscendingSort = true)
    {
        Sort::merge(m_array, length(), isAscendingSort);
    }

    virtual int length() const = 0;
};
}

#endif // __ARRAY_H__
