#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include "LinuxList.h"
#include "Queue.h"
#include "Exception.h"

namespace TianGangLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
    int m_length;
    list_head m_header;

    struct Node : public Object
    {
        list_head node;
        T value;
    };

public:
    LinkQueue() : m_length(0)
    {
        INIT_LIST_HEAD(&m_header);
    }

    void enque(const T& e)
    {
        Node* node = new Node();

        if( node != NULL )
        {
            node->value = e;
            list_add_tail(&node->node, &m_header);
            ++m_length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create LinkQueue element...");
        }
    }

    void deque()
    {
        if( !isEmpty() )
        {
            Node* toDel = list_entry(m_header.next, Node, node);

            list_del(m_header.next);
            --m_length;
            delete toDel;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the queue is empty...");
        }
    }

    T front() const
    {
        return const_cast<LinkQueue<T>*>(this)->front();
    }

    T& front()
    {
        if( !isEmpty() )
        {
            return list_entry(m_header.next, Node, node)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the queue is empty...");
        }
    }

    bool isEmpty() const
    {
        return m_length == 0;
    }

    void clear()
    {
        while( m_length > 0 )
        {
            deque();
        }
    }

    int size() const
    {
        return m_length;
    }

    ~LinkQueue()
    {
        clear();
    }
};

}


#endif // __LINKQUEUE_H__
