#ifndef __GTREENODE_H__
#define __GTREENODE_H__

#include "TreeNode.h"
#include "LinkList.h"
#include "Exception.h"
#include <map>


namespace TianGangLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if( ret != NULL )
        {
            ret->m_objectFromNew = true;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create GTreeNode object...");
        }

        return ret;
    }
};

}

#endif // __GTREENODE_H__
