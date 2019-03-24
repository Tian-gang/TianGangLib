#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__

#include "LinkList.h"

namespace TianGangLib
{

template < typename T >
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const
    {
        return this->m_length == 0 ? 0 : i % this->m_length;
    }

    Node* last() const
    {
        return this->m_tail;
    }

    void last_to_first() const
    {
        last()->next = this->m_head.next;
    }

public:
    bool append(const T& e)
    {
        bool ret = LinkList<T>::append(e);

        if( ret && this->m_length == 1 ) {
            last_to_first();
        }

        return ret;
    }

    bool insert(int i, const T& e)
    {
        bool ret = false;

        i = i % (this->m_length + 1);
        ret = LinkList<T>::insert(i, e);

        if( ret && i == 0 )
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = false;

        i = mod(i);
        ret = LinkList<T>::remove(i);

        if( ret )
        {
            if( this->m_length == 0 )
            {
                this->m_head.next = NULL;
                this->m_current = NULL;
            }
            else if( i == 0 )
            {
                last_to_first();
            }
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        Node* slider = this->m_head.next;

        for(int i = 0; i < this->m_length; ++i)
        {
            if( slider->value == e )
            {
                ret = i; break;
            }
            slider = slider->next;
        }

        return ret;
    }

    bool move(int i, int step = 1) const
    {
        return LinkList<T>::move(mod(i), step);
    }

    T& get(int i)
    {
        return LinkList<T>::get(mod(i));
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i, const T& e) const
    {
        return LinkList<T>::get(mod(i), e);
    }

    bool set(int i, const T &e)
    {
        return LinkList<T>::set(mod(i), e);
    }

    void reverse()
    {
        Node* __pre = NULL;
        Node* __current = this->m_head.next;
        Node* __next = NULL;
        Node* temp = __current;

        if( __current != NULL )
        {
            this->m_tail = __current;
        }

        do
        {
            __next = __current->next;
            __current->next = __pre;
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

    ~CircleList()
    {
        clear();
    }
};

}


#endif // __CIRCLELIST_H__
