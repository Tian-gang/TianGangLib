#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include "List.h"
#include "Exception.h"
#include <memory>
#include <stdarg.h>

namespace TianGangLib
{

template < typename T >
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;

public:
     bool insert(int i, const T& e)
     {
         bool ret = (0 <= i) && (i <= m_length);

         ret = ret && (m_length < capacity());
         if(ret)
         {
             for(int p = m_length-1; p >= i; p--)
             {
                 m_array[p + 1] = m_array[p];
             }

             m_array[i] = e;
             m_length++;
         }

         return ret;
     }

     bool append(const T& e)
     {
         return this->insert(m_length, e);
     }

     bool remove(int i)
     {
         bool ret = (0 <= i) && (i < m_length);

         if(ret)
         {
             for(int p = i; p < m_length - 1; p++)
             {
                 m_array[p] = m_array[p + 1];
             }

             m_length--;
         }

         return ret;
     }

     bool set(int i, const T& e)
     {
         bool ret = (0 <= i) && (i < m_length);

         if(ret)
         {
             m_array[i] = e;
         }

         return ret;
     }

     bool get(int i, T& e) const
     {
         bool ret = (0 <= i) && (i < m_length);

         if(ret)
         {
             e = m_array[i];
         }

         return ret;
     }

     int length() const
     {
         return m_length;
     }

     int find(const T& e) const
     {
         int ret = -1;

         for(int i = 0; i < m_length; ++i)
         {
             if(m_array[i] == e)
             {
                 ret = i; break;
             }
         }

         return ret;
     }

     void clear()
     {
         m_length = 0;
     }

     T& operator[] (int i)
     {
         if ((0 <= i) && (i < m_length))
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
         return (const_cast<SeqList<T>&>(*this))[i];
     }

     virtual int capacity() const = 0;
};

}


#endif // __SEQLIST_H__
