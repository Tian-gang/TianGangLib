#ifndef __GTREE_H__
#define __GTREE_H__

#include "GTreeNode.h"
#include "Tree.h"
#include "LinkQueue.h"

namespace TianGangLib
{

template < typename T >
class GTree : public Tree<T>
{
    LinkQueue<GTreeNode<T>*> m_queue;

protected:
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if( node != NULL && obj != NULL )
        {
            if( node == obj )
            {
                ret = node;
            }
            else
            {
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if( ret != NULL)
        {
            if( node == root() )
            {
                this->m_root = NULL;
            }
            else
            {
                GTreeNode<T>* __parent = dynamic_cast<GTreeNode<T>*>(node->parent);

                if( __parent != NULL )
                {
                    __parent->child.remove(__parent->child.find(node));
                }
            }

            node->parent = NULL;
            m_queue.clear();
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create tree object...");
        }
    }

    void free(GTreeNode<T>* node)
    {
        if( node != NULL )
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            if( node->ObjectFromNew() )
            {
                delete node;
            }
        }
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = node->child.length();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int __degree = degree(node->child.current());

                ret = (ret > __degree) ? ret : __degree;
            }
        }

        return ret;
    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = 0;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int __height = height(node->child.current());

                ret = (ret > __height) ? ret : __height;
            }

            ++ret;
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = (node != NULL);

        if( ret )
        {
            if( root() == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* __parent = find(node->parent);

                ret = ret && (__parent != NULL) && (__parent->child.find(dynamic_cast<GTreeNode<T>*>(node)) < 0);

                if( ret )
                {
                    __parent->child.append(dynamic_cast<GTreeNode<T>*>(node));
                }
            }
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = GTreeNode<T>::NewNode();

        ret = (node != NULL);

        if( ret )
        {
            node->value = value;
            node->parent = parent;
            ret = insert(node);
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* __node = find(node);

        if( __node != NULL )
        {
            remove(__node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the node is Invalid...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if( node != NULL )
        {
            remove(node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the node is Invalid...");
        }

        return ret;
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());
        this->m_root = NULL;
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            m_queue.clear();
            m_queue.enque(root());
        }

        return ret;
    }

    bool end() const
    {
        return m_queue.isEmpty();
    }

    T& current()
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "no element....");
        }
    }

    T current() const
    {
        return (const_cast<GTree<T>*>(this))->current();
    }

    bool next()
    {
        bool ret = (!end());

        if( ret )
        {
            GTreeNode<T>* node = m_queue.front();

            m_queue.deque();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.enque(node->child.current());
            }
        }

        return ret;
    }

    ~GTree()
    {
        clear();
        m_queue.clear();
    }
};

}


#endif // __GTREE_H__
