#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

#include "Pointer.h"

namespace TianGangLib
{

template < typename T >
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* ptr = NULL) : Pointer<T>(ptr) {}

    SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(NULL)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if( this != & obj)
        {
            T* toDel = this->m_pointer;

            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete toDel;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }

};

}

#endif // __SMARTPOINTER_H__
