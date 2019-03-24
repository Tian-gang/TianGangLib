#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Object.h"

namespace TianGangLib
{

template < typename T >
class Queue : public Object
{
public:
    virtual void enque(const T& e) = 0;
    virtual void deque() = 0;
    virtual T front() const = 0;
    virtual T& front()  = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual int size() const = 0;
};

}


#endif // __QUEUE_H__
