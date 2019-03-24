#ifndef __SORT_H__
#define __SORT_H__

#include "Object.h"
#include "Exception.h"
#include <cstdlib>

namespace TianGangLib
{

class Sort : public Object
{
    Sort();
    Sort(const Sort& other);
    Sort& operator =(const Sort& other);

protected:
    template  < typename T >
    static void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template < typename T >
    static int partition(T array[], int left, int right, bool isAscendingSort)
    {
        int ret = -1;

        if( array != NULL )
        {
            T temp = array[left];
            int i = left;
            int j = right;

            while( i != j )
            {
                while( i < j && (isAscendingSort ? array[j] >= temp : array[j] <= temp) )
                {
                    --j;
                }

                if( i < j )
                {
                    array[i++] = array[j];
                }

                while( i < j && (isAscendingSort ? array[i] <= temp : array[i] >= temp) )
                {
                    ++i;
                }

                if( i < j )
                {
                    array[j--] = array[i];
                }
            }

            array[i] = temp;
            ret = i;
        }

        return ret;
    }

    template < typename T >
    static void quick(T array[], int left, int right, bool isAscendingSort)
    {
        if( array == NULL || left < 0 || right < 0 ) return;

        if( left < right )
        {
            int i = partition(array, left, right, isAscendingSort);

            quick(array, left, i - 1, isAscendingSort);
            quick(array, i + 1, right, isAscendingSort);
        }
    }

    template < typename T >
    static void merge(T array[], T space[], int left, int mid, int right, bool isAscendingSort)
    {
        if( array == NULL || left < 0 || right < 0 || left >= right ) return;

        int i = left;
        int j = mid + 1;
        int k = left;

        while( i <= mid && j <= right )
        {
            space[k++] = (isAscendingSort ? array[i] < array[j] : array[i] > array[j]) ?
                        array[i++] : array[j++];
        }

        while( i <= mid )
        {
            space[k++] = array[i++];
        }

        while( j <= right )
        {
            space[k++] = array[j++];
        }

        for(i = left; i <= right; ++i)
        {
            array[i] = space[i];
        }
    }

    template < typename T >
    static void mergeSort(T array[], T space[], int left, int right, bool isAscendingSort)
    {
        if( array == NULL || left < 0 || right < 0 || left >= right ) return;

        int mid = ((left >> 1) + (right >> 1));

        mergeSort(array, space, left, mid, isAscendingSort);
        mergeSort(array, space, mid + 1, right, isAscendingSort);
        merge(array, space, left, mid, right, isAscendingSort);
    }

public:
    template < typename T >
    static void select(T array[], int len, bool isAscendingSort = true)
    {
        if( array == NULL || len <= 0) return;

        for(int i = 0; i < len - 1; ++i)
        {
            int min = i;

            for(int j = i + 1; j < len; ++j)
            {

                if( isAscendingSort ? array[min] > array[j] : array[min] < array[j] )
                {
                    min = j;
                }
            }

            if( min != i )
            {
                swap(array[i], array[min]);
            }
        }
    }

    template < typename T >
    static void bubble(T array[], int len, bool isAscendingSort = true)
    {
        if( array == NULL || len <= 0) return;

        bool exchange = true;

        for(int i = 0; exchange && i < len - 1; ++i)
        {
            exchange = false;
            for(int j = 0; j < len - i - 1; ++j)
            {
                if( isAscendingSort ? array[j] > array[j + 1] : array[j] < array[j + 1])
                {
                    swap(array[j], array[j + 1]);
                }

                exchange = true;
            }
        }
    }

    template < typename T >
    static void insert(T array[], int len, bool isAscendingSort = true)
    {
        if( array == NULL || len <= 0) return;

        for(int i = 1; i < len; ++i)
        {
            int insertPos = i;
            T insertValue = array[i];

            for(int j = i - 1; j >= 0 && (isAscendingSort ? insertValue < array[j] : insertValue > array[j]); --j)
            {
                array[j + 1] = array[j];
                insertPos = j;
            }

            if( insertPos != i )
            {
                array[insertPos] = insertValue;
            }
        }
    }

    template < typename T >
    static void shell(T array[], int len, bool isAscendingSort = true)
    {
        if( array == NULL || len <= 0 ) return;

        int step = len;

        do
        {
            step = step / 3 + 1;

            for(int i = step; i < len; i += step)
            {
                int insertPos = i;
                T insertValue = array[i];

                for(int j = i - step; j >= 0 && (isAscendingSort ? insertValue < array[j] : insertValue > array[j]); j -= step )
                {
                    array[j + step] = array[j];
                    insertPos = j;
                }

                if( insertPos != i )
                {
                    array[insertPos] = insertValue;
                }
            }
        } while(step > 1);

    }

   template < typename T >
   static void quick(T array[], int len, bool isAscendingSort = true)
   {
       quick(array, 0, len - 1, isAscendingSort);
   }

   template < typename T >
   static void merge(T array[], int len, bool isAscendingSort = true)
   {
       T* space = new T[len];

       if( space != NULL )
       {
           mergeSort(array, space, 0, len - 1, isAscendingSort);
       }
       else
       {
           THROW_EXCEPTION(NoEnoughMemoryException, "no enought memory to mergeSort....");
       }

       delete[] space;
   }

};


}

#endif // __SORT_H__
