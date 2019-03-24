#ifndef __POINTER_H__
#define __POINTER_H__

#include "Object.h"

namespace TianGangLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* ptr = NULL) : m_pointer(ptr) {}

    bool isEmpty() const
    {
        return m_pointer == NULL;
    }

    T* operator -> ()
    {
        return m_pointer;
    }

    const T* operator -> () const
    {
        return m_pointer;
    }

    T& operator * ()
    {
        return *m_pointer;
    }

    const T& operator * () const
    {
        return *m_pointer;
    }

    T* get()
    {
        return m_pointer;
    }

    const T* get() const
    {
        return m_pointer;
    }

};

}



#endif // __POINTER_H__
