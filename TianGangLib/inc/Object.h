#ifndef __OBJECT_H__
#define __OBJECT_H__


namespace TianGangLib
{

#ifndef NULL
#define NULL 0
#endif

class Object
{
public:
    void* operator new (unsigned int size) throw();
    void  operator delete (void* p);
    void* operator new[] (unsigned int size) throw();
    void  operator delete[] (void* p);
    bool  operator == (const Object& obj) const;
    bool  operator != (const Object& obj) const;
    virtual ~Object() = 0;
};
}


#endif // __OBJECT_H__
