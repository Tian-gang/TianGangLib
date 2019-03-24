#ifndef __STATICSTACK_H__
#define __STATICSTACK_H__

#include "Stack.h"
#include "Exception.h"

namespace TianGangLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
    T m_space[N];
    int m_top;
    int m_length;

public:
    StaticStack() : m_top(-1), m_length(0) {}

    void push(const T& e)
    {
        if( !isFull() )
        {
            m_space[m_top + 1] = e;
            m_top++;
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the stack is Full...");
        }
    }

    void pop()
    {
        if( !isEmpty() )
        {
            m_top--;
            m_length--;
        }
       else
        {
            THROW_EXCEPTION(InvalidParameterException, "the statck is Empty....");
        }
    }

    T& top()
    {
        if( !isEmpty() )
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the statck is Empty....");
        }
    }

    T top() const
    {
        return const_cast<StaticStack<T, N>*>(this)->top();
    }

    int size() const
    {
        return m_length;
    }

    bool isEmpty() const
    {
        return m_length == 0;
    }

    bool isFull() const
    {
        return m_length == N;
    }

    void clear()
    {
        m_top = -1;
        m_length = 0;
    }

    int capacity() const
    {
        return N;
    }

    ~StaticStack()
    {
        clear();
    }
};

}


#endif // __STATICSTACK_H__
