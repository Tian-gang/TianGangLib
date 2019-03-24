#ifndef __DULCIRLIST_H__
#define __DULCIRLIST_H__

#include "DulLinkList.h"

namespace TianGangLib
{

template < typename T >
class DulCirList : public DulLinkList<T>
{
protected:
    typedef typename DulLinkList<T>::Node Node;

    int mod(int i) const
    {
        return this->m_length == 0 ? 0 : i % this->m_length;
    }

    Node* last() const
    {
        return this->m_tail;
    }

    void last_to_first()
    {
        Node* __last = last();

        __last->next = this->m_head.next;
        this->m_head.next->pre = __last;
    }

public:
    bool append(const T& e)
    {
        bool ret = DulLinkList<T>::append(e);

        if( ret && this->m_length == 1 )
        {
            last_to_first();
        }

        return ret;
    }

    bool insert(int i, const T& e)
    {
        bool ret = false;

        i = i % (this->m_length + 1);

        ret = DulLinkList<T>::insert(i, e);

        if(ret && i == 0)
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = false;

        i = mod(i);

        ret = DulLinkList<T>::remove(i);

        if( ret )
        {
            if( this->m_length == 0 )
            {
                this->m_step = 0;
                this->m_current = NULL;
                this->m_head.next = NULL;
            }
            else if( i == 0 )
            {
                last_to_first();
            }
        }

        return ret;
    }

    bool move(int i, int step = 1) const
    {
        return DulLinkList<T>::move(mod(i), step);
    }

    T& get(int i)
    {
        return DulLinkList<T>::get(mod(i));
    }

    T get(int i) const
    {
        return DulLinkList<T>::get(mod(i));
    }

    bool get(int i, const T& e) const
    {
        return DulLinkList<T>::get(mod(i), e);
    }

    bool set(int i, const T &e)
    {
        return DulLinkList<T>::set(mod(i), e);
    }

    void reverse()
    {
        Node* __pre = NULL;
        Node* __current = this->m_head.next;
        Node* __next = NULL;
        Node* temp = __current;

        if( __current != NULL ) this->m_tail = __current;

        do
        {
            __next = __current->next;
            __current->next = __pre;
            __current->pre = __next;
            __pre = __current;
            __current = __next;
        } while( __current != temp );

        __current->next = __pre;
        this->m_head.next = __pre;
    }

    void clear()
    {
        while( this->m_length > 1 )
        {
            remove(1);
        }

        if( this->m_length == 1 )
        {
            Node* toDel = this->m_head.next;

            this->m_head.next = NULL;
            this->m_current = NULL;
            this->m_length = 0;

            this->destroy(toDel);
        }
    }

    ~DulCirList()
    {
        clear();
    }
};

}


#endif // __DULCIRLIST_H__
