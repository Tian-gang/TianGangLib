#ifndef __TREE_H___
#define __TREE_H___

#include "TreeNode.h"
#include "SharedPointer.h"

namespace TianGangLib
{

template < typename T >
class Tree : public Object
{
    Tree(const Tree<T>& other);
    Tree<T>& operator =(const Tree<T>& other);
protected:
    TreeNode<T>* m_root;
public:
    Tree() : m_root(NULL) { }

    virtual bool insert(TreeNode<T>* node) = 0;
    virtual bool insert(const T& value, TreeNode<T>* parent) = 0;
    virtual SharedPointer< Tree<T> > remove(TreeNode<T>* node) = 0;
    virtual SharedPointer< Tree<T> > remove(const T& value) = 0;
    virtual TreeNode<T>* find(TreeNode<T>* node) const = 0;
    virtual TreeNode<T>* find(const T& value) const = 0;
    virtual TreeNode<T>* root() const = 0;
    virtual int degree() const = 0;
    virtual int count() const = 0;
    virtual int height() const = 0;
    virtual void clear() = 0;
    virtual T current() const = 0;
    virtual T& current() = 0;
    virtual bool begin() = 0;
    virtual bool end() const = 0;
    virtual bool next() = 0;
};

}


#endif // __TREE_H___
