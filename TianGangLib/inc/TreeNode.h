#ifndef __TREENODE_H__
#define __TREENODE_H__

#include "Object.h"

namespace TianGangLib
{

template < typename T >
class TreeNode : public Object
{ 
protected:
    void* operator new (unsigned int size) throw()
    {
        return Object::operator new(size);
    }

    TreeNode(const TreeNode<T>& other);
    TreeNode<T>& operator = (const TreeNode<T>& other);

    bool m_objectFromNew;
public:
    T value;
    TreeNode<T>* parent;

    bool ObjectFromNew() const
    {
        return m_objectFromNew;
    }

    TreeNode() : m_objectFromNew(false), parent(NULL) { }
    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode() { }

}


#endif // __TREENODE_H__
