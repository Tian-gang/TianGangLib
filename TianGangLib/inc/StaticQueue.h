#ifndef __STATICQUEUE_H__
#define __STATICQUEUE_H__

#include "Queue.h"
#include "Exception.h"

namespace TianGangLib
{

template < typename T, int N >
class StaticQueue : public Queue<T>
{
    T m_space[N];
    int m_length;
    int m_front;
    int m_tail;

public:
    StaticQueue() : m_length(0), m_front(0), m_tail(0) {}

    void enque(const T& e)
    {
        if( !isFull() )
        {
            m_space[m_tail] = e;
            m_tail = (m_tail + 1) % N;
            m_length++;
        }
        else THROW_EXCEPTION(InvalidParameterException, "the queue is full...");
    }

    void deque()
    {
        if( !isEmpty() )
        {
            m_front = (m_front + 1) % N;
            m_length--;
        }
        else THROW_EXCEPTION(InvalidParameterException, "the queue is empty");
    }

    T front() const
    {
        return const_cast<StaticQueue<int, N>*>(this)->front();
    }

    T& front()
    {
        if( !isEmpty() )
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the queue is empty...");
        }
    }

    int size() const
    {
        return m_length;
    }

    int capacity() const
    {
        return N;
    }

    bool isEmpty() const
    {
        return m_front == m_tail && m_length == 0;
    }

    bool isFull() const
    {
        return m_front == m_tail && m_length == N;
    }

    void clear()
    {
        m_tail = m_front = m_length = 0;
    }

    ~StaticQueue()
    {
        clear();
    }
};

}


#endif // __STATICQUEUE_H__
