#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include "Stack.h"
#include "LinkList.h"

namespace TianGangLib
{

template < typename T >
class LinkStack : public Stack<T>
{
    LinkList<T> m_list;
public:
    void push(const T& e)
    {
        m_list.insert(0, e);
    }

    void pop()
    {
        m_list.remove(0);
    }

    T& top()
    {
        if( m_list.length() > 0 )
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the stack is Empty...");
        }
    }

    T top() const
    {
        return const_cast<LinkStack<T>*>(this)->top();
    }

    int size() const
    {
        return m_list.length();
    }

    bool isEmpty() const
    {
        return m_list.length() == 0;
    }

    void clear()
    {
        m_list.clear();
    }

    ~LinkStack()
    {
        clear();
    }
};

}


#endif // __LINKSTACK_H__
