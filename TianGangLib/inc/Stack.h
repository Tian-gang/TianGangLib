#ifndef __STACK_H__
#define __STACK_H__

#include "Object.h"

namespace TianGangLib
{

template < typename T >
class Stack : public Object
{
public:
    virtual void push(const T& e) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual T& top() = 0;
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
};

}


#endif // __STACK_H__
