#ifndef __BTREENODE_H__
#define __BTREENODE_H__

#include "TreeNode.h"

namespace TianGangLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template < typename T >
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode() : left(NULL), right(NULL) { }

    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if( ret != NULL )
        {
            ret->m_objectFromNew = true;
        }

        return ret;
    }
};

}


#endif // __BTREENODE_H__
