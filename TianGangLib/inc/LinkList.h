#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "List.h"
#include "Exception.h"

namespace TianGangLib
{

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object
    {
        char placeholder[sizeof(T)];
        Node* next;
    }m_head;

    int m_length;
    mutable int m_step;
    mutable Node* m_current;
    mutable Node* m_tail;

    Node* position(int i) const
    {
        Node* current = reinterpret_cast<Node*>(&m_head);

        for(int p = 0; p < i; ++p)
        {
            current = current->next;
        }

        return current;
    }

    virtual Node* create()
    {
         return new Node();
    }

    virtual void destroy(Node* np)
    {
        delete np;
    }

public:
    LinkList()
    {
        m_step = 0;
        m_current = NULL;
        m_head.next = NULL;
        m_tail = reinterpret_cast<Node*>(&m_head);
        m_length = 0;
    }

    bool insert(int i, const T& e)
    {
        bool ret = (0 <= i) && (i <= m_length);

        if(ret)
        {
            Node* newNode = create();

            if(newNode != NULL)
            {
                Node* prev = position(i);

                newNode->value = e;
                newNode->next = prev->next;
                prev->next = newNode;
                if( i == m_length )
                {
                    m_tail = m_tail->next;
                }
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memory to insert node...");
            }
        }

        return ret;
    }

    bool append(const T& e)
    {
        Node* node = create();
        bool ret = (node != NULL) && (m_tail != NULL);

        if( ret )
        {
            node->value = e;
            node->next = m_tail->next;
            m_tail->next = node;
            m_tail = node;
            m_length++;
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = (0 <= i) && (i < m_length);

        if(ret)
        {
            Node* prev = position(i);
            Node* toDel = prev->next;

            if( toDel == m_current ) m_current = m_current->next;
            if( toDel == m_tail ) m_tail = prev;

            prev->next = toDel->next;
            m_length--;

            destroy(toDel);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = (0 <= i) && (i < m_length);

        if(ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    virtual T& get(int i)
    {
        if( 0 <= i && i < m_length )
        {
            return position(i)->next->value;
        }
        else  THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
    }

    virtual T get(int i) const
    {
        T ret;

        return get(i, ret) ? ret : THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
    }

    bool get(int i, T& e) const
    {
        bool ret = (0 <= i) && (i < m_length);

        if(ret)
        {
            e = position(i)->next->value;
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
        int i = 0;
        Node* current = m_head.next;

        while(current != NULL)
        {
            if(current->value == e)
            {
                ret = i; break;
            }
            else
            {
                current = current->next;
                ++i;
            }
        }

        return ret;
    }

    virtual bool move(int i, int step = 1) const
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);

        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    virtual bool end() const
    {
        return (m_current == NULL);
    }

    virtual T& current()
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is valid...");
        }
    }

    virtual T current() const
    {
        return (const_cast<LinkList<T>*>(this))->current();
    }

    virtual bool next() const
    {
        int i = 0;

        while(i < m_step && !end())
        {
            m_current = m_current->next;
            ++i;
        }

        return (i == m_step);
    }

    T& operator[] (int i)
    {
        if((0 <= i) && (i < m_length))
        {
            return position(i)->next->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
        }
    }

    T operator [](int i) const
    {
        return (const_cast<LinkList<T>&>(*this))[i];
    }

    void clear()
    {
        while(m_head.next != NULL)
        {
            Node* toDel = m_head.next;
            m_head.next = toDel->next;   
            m_length--;
            destroy(toDel);
        }

        m_current = NULL;
    }

    virtual void reverse()
    {
        Node* __pre = NULL;
        Node* current = m_head.next;
        Node* __next = NULL;

        if( current != NULL ) m_tail = current;

        while( current != NULL )
        {
            __next = current->next;
            current->next = __pre;
            __pre = current;
            current = __next;
        }

        m_head.next = __pre;
    }

    ~LinkList()
    {
        clear();
    }
};

}


#endif // __LINKLIST_H__
