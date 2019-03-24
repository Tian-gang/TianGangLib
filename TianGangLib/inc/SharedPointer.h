#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__

#include "Exception.h"
#include "Pointer.h"
#include <stdlib.h>

namespace TianGangLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
    int* m_ref;
protected:
    void assign(const SharedPointer<T>& other)
    {
        m_ref = other.m_ref;
        this->m_pointer = other.m_pointer;

        if( m_ref != NULL )
        {
            (*m_ref)++;
        }
    }

public:
    SharedPointer(T* ptr = NULL) : Pointer<T>(NULL)
    {
        if( (m_ref = static_cast<int*>(malloc(sizeof(int)))) )
        {
            *m_ref = 1;
            this->m_pointer = ptr;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer Object...");
        }
    }

    SharedPointer(const SharedPointer<T>& other) : Pointer<T>(NULL)
    {
        assign(other);
    }

    SharedPointer<T>& operator= (const SharedPointer<T>& other)
    {
        if( this != &other )
        {
            clear();
            assign(other);
        }

        return *this;
    }

    void clear()
    {
        int* ref = m_ref;
        T* pointer = this->m_pointer;

        this->m_pointer = NULL;
        m_ref = NULL;

        if(  ref != NULL && --(*ref) == 0 )
        {
            free(ref);
            delete pointer;
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

}


#endif // __SHAREDPOINTER_H__
