#ifndef __GETMINSTACK_H__
#define __GETMINSTACK_H__

#include "LinkStack.h"

namespace TianGangLib
{

template < typename T >
class GetMinStack : public Stack<T>
{
    LinkStack<T> stack;
    LinkStack<T> minStack;
public:
     void push(const T& e)
     {
         if( minStack.isEmpty() || e < minStack.top() )
         {
             minStack.push(e);
         }
         else
         {
             minStack.push(minStack.top());
         }

         stack.push(e);
     }

     void pop()
     {
         minStack.pop();
         stack.pop();
     }

     T top() const
     {
         return stack.top();
     }

     T& top()
     {
         return stack.top();
     }

     int size() const
     {
         return stack.size();
     }

     bool isEmpty() const
     {
         return stack.isEmpty();
     }

     T getMin() const
     {
         return minStack.top();
     }

     void clear()
     {
         stack.clear();
     }
};

}

#endif // __GETMINSTACK_H__
