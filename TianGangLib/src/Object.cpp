#include "Object.h"
#include <cstdlib>
#include <iostream>

namespace TianGangLib
{

void* Object::operator new (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete (void* p)
{
    free(p);
}

void* Object::operator new[] (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

bool Object::operator == (const Object& obj) const
{
    return (this == &obj);
}

bool Object::operator != (const Object& obj) const
{
    return (this != &obj);
}


Object::~Object() {}

}
