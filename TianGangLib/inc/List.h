#ifndef __LIST_H__
#define __LIST_H__

#include "Object.h"

namespace TianGangLib
{

template < typename T >
class List : public Object
{
private:
    List(const List<T>& obj);
    List<T>& operator= (const List<T>& obj);
public:
    List(){}
    virtual bool insert(int i, const T& e) = 0;
    virtual bool append(const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual int length() const = 0;
    virtual int find(const T& e) const = 0;
    virtual void clear() = 0;
};

}


#endif // __LIST_H__
