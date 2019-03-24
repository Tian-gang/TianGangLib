#ifndef __DULLINKLIST_H__
#define __DULLINKLIST_H__


#include "List.h"
#include "Exception.h"

using namespace std;

namespace TianGangLib
{

template < typename T >
class DulLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* pre;
        Node* next;
    };

    mutable struct : public Object
    {
        char placeholder[sizeof(T)];
        Node* pre;
        Node* next;
    }m_head;

    int m_length;
    mutable int m_step;
    mutable Node* m_current;
    Node* m_tail;

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
    DulLinkList()
    {
        m_step = 0;
        m_current = NULL;
        m_head.next = NULL;
        m_head.pre = NULL;
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

                if( newNode->next != NULL )
                {
                    newNode->next->pre = newNode;
                }

                m_tail = m_tail->next;
                newNode->pre = (prev == reinterpret_cast<Node*>(&m_head))  ? NULL : prev;

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
        bool ret = true;
        Node* node = create();
        ret = (node != NULL) && (m_tail != NULL);

        if( ret )
        {
            node->value = e;
            node->pre = (m_tail == reinterpret_cast<Node*>(&m_head)) ? NULL : m_tail;
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

            if( toDel == m_current )
            {
                m_current = m_current->next;
            }

            if( toDel == m_tail )
            {
                m_tail = m_tail->pre;
            }

            prev->next = toDel->next;
            if( toDel->next != NULL )
            {
                toDel->next->pre = prev;
            }

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
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is valid...");
        }
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
        return (const_cast<DulLinkList<T>*>(this))->current();
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

    virtual bool pre() const
    {
        int i = 0;

        while( i < m_step && !end() )
        {
            m_current = m_current->pre;
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
        return (const_cast<DulLinkList<T>&>(*this))[i];
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove(0);
        }

        m_current = NULL;
    }

    virtual void reverse()
    {
        Node* __pre = NULL;
        Node* __current = m_head.next;
        Node* __next = NULL;

        if( __current != NULL )
        {
            m_tail = __current;
        }

        while( __current != NULL )
        {
            __next = __current->next;
            __current->next = __pre;
            __current->pre = __next;
            __pre = __current;
            __current = __next;
        }

        m_head.next = __pre;
    }

    ~DulLinkList()
    {
        clear();
    }
};

}

#endif // __DULLINKLIST_H__
