#ifndef __BTREE_H__
#define __BTREE_H__

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"
#include "LinkStack.h"

namespace TianGangLib
{

enum BTTraversalPos
{
    PreOrder   = 0,
    InOrder    = 1,
    PostOrder  = 2,
    LevelOrder = 3,
};

template < typename T >
class BTree : public Tree<T>
{
    LinkQueue<BTreeNode<T>*> m_queue;

protected:
    BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL && obj != NULL )
        {
            if( node == obj )
            {
                ret = node;
            }
            else
            {
                ret = find(node->left, obj);

                if( ret == NULL )
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                ret = find(node->left, value);

                if( ret == NULL )
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    bool insert(BTreeNode<T>* node, BTreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = (node != NULL) && (parent != NULL);

        if( ret )
        {
            if( pos == ANY )
            {
                if( parent->left == NULL )
                {
                    parent->left = node;
                }
                else if( parent->right == NULL )
                {
                    parent->right = node;
                }
                else
                {
                    ret = false;
                }
            }
            else if( pos == LEFT )
            {
                if( parent->left == NULL )
                {
                    parent->left = node;
                }
                else
                {
                    ret = false;
                  }
            }
            else if( pos == RIGHT )
            {
                if( parent->right == NULL )
                {
                    parent->right = node;
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create BTree object...");
        }
        else
        {
            if( node == this->m_root )
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* __parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( __parent->left == node )
                {
                    __parent->left = NULL;
                }
                else if( __parent->right == node )
                {
                    __parent->right = NULL;
                }
            }

            node->parent = NULL;
            ret->m_root = node;
            m_queue.clear();
        }
    }

    void free(BTreeNode<T>* node)
    {
        if( node != NULL )
        {
            free(node->left);
            free(node->right);

            if( node->ObjectFromNew() )
            {
                delete node;
            }
        }
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            BTreeNode<T>* arr[] = { node->left, node->right };

            ret = (!!node->left + !!node->right);

            for(int i = 0; i < 2 && ret < 2; ++i)
            {
                int d = degree(arr[i]);

                if( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

    int count(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = count(node->left) + count(node->right) + 1;
        }

        return ret;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            int heightLeft  = height(node->left);
            int heightRight = height(node->right);

            ret = (heightLeft > heightRight) ? heightLeft : heightRight;
            ++ret;
        }

        return ret;
    }

    void preOrderRecursion(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if(node != NULL)
        {
            queue.enque(node);
            preOrderRecursion(node->left, queue);
            preOrderRecursion(node->right, queue);
        }
    }

    void inOrderRecursion(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if(node != NULL)
        {
            inOrderRecursion(node->left, queue);
            queue.enque(node);
            inOrderRecursion(node->right, queue);
        }
    }

    void postOrderRecursion(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if(node != NULL)
        {
            postOrderRecursion(node->left, queue);
            postOrderRecursion(node->right, queue);
            queue.enque(node);
        }
    }

    void preOrderNotRecursion(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if( node != NULL )
        {
            LinkStack<BTreeNode<T>*> stack;

            stack.push(node);

            while( !stack.isEmpty() )
            {
                BTreeNode<T>* current = stack.top();

                stack.pop();
                queue.enque(current);

                if( current->right != NULL )
                {
                    stack.push(current->right);
                }

                if( current->left != NULL )
                {
                    stack.push(current->left);
                }
            }
        }
    }

    void inOrderNotRecursion(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        LinkStack<BTreeNode<T>*> stack;

        while( !stack.isEmpty() || node != NULL )
        {
            if( node != NULL )
            {
                stack.push(node);
                node = node->left;
            }
            else
            {
                BTreeNode<T>* cur = stack.top();

                stack.pop();
                queue.enque(cur);
                node = cur->right;
            }
        }
    }

    void postOrderNotRecursion(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if( node != NULL )
        {
            LinkStack<BTreeNode<T>*> stackIn;
            LinkStack<BTreeNode<T>*> stackOut;

            stackIn.push(node);

            while( !stackIn.isEmpty() )
            {
                BTreeNode<T>* temp = stackIn.top();

                stackIn.pop();
                stackOut.push(temp);

                if( temp->left != NULL )
                {
                    stackIn.push(temp->left);
                }

                if( temp->right != NULL )
                {
                    stackIn.push(temp->right);
                }
            }

            while( !stackOut.isEmpty() )
            {
                queue.enque(stackOut.top());
                stackOut.pop();
            }
        }
    }

    void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) const
    {
        if( node != NULL )
        {
            LinkQueue<BTreeNode<T>*> temp;

            temp.enque(node);

            while( !temp.isEmpty() )
            {
                BTreeNode<T>* node = temp.front();

                queue.enque(node);
                temp.deque();

                if( node->left != NULL )
                {
                    temp.enque(node->left);
                }

                if( node->right != NULL )
                {
                    temp.enque(node->right);
                }
            }
        }
    }

    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        if( lh == rh )
        {
            return true;
        }
        else if( lh != NULL && rh != NULL )
        {
            return (lh->value == rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
        }
        else
        {
            return false;
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = node->value;
                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node object...");
            }
        }

        return ret;
    }

    BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = NULL;

        if( lh == NULL && rh != NULL )
        {
            ret = clone(rh);
        }
        else if( lh != NULL && rh == NULL )
        {
            ret = clone(lh);
        }
        else if( lh != NULL && rh != NULL )
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = lh->value + rh->value;
                ret->left  = add(lh->left, rh->left);
                ret->right = add(lh->right, rh->right);

                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new node object...");
            }
        }

        return ret;
    }

    void traversal(BTTraversalPos pos, LinkQueue<BTreeNode<T>*>& queue, bool isRecursion) const
    {
        void (BTree<T>::*pFuncArr[3][2])(BTreeNode<T>*, LinkQueue<BTreeNode<T>*>&) const =
        { {preOrderRecursion, preOrderNotRecursion},
          {inOrderRecursion, inOrderNotRecursion},
          {postOrderRecursion, postOrderNotRecursion}, };

        unsigned int traversalPos = static_cast<unsigned int>(pos);

        if( traversalPos < 0 || 3 < traversalPos )
        {
            THROW_EXCEPTION(InvalidParameterException, "the parameter pos is Invalid...");
        }

        if( pos != LevelOrder )
        {
            (this->*pFuncArr[traversalPos][!isRecursion])(root(), queue);
        }
        else
        {
            levelOrderTraversal(root(), queue);
        }
    }

    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue) const
    {
        BTreeNode<T>* ret = NULL;

        if( !queue.isEmpty() )
        {
            BTreeNode<T>* slider = queue.front();

            queue.deque();
            ret = slider;
            ret->left = NULL;

            while( !queue.isEmpty() )
            {
                slider->right = queue.front();
                queue.front()->left = slider;
                slider = queue.front();
                queue.deque();
            }

            slider->right = NULL;
        }

        return ret;
    }

    BTreeNode<T>* delOddDegree(BTreeNode<T>* node)
    {
        BTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            if( (node->left != NULL) ^ (node->right != NULL) )
            {
                BTreeNode<T>* nodeChild = (node->left != NULL) ? node->left : node->right;
                BTreeNode<T>* __parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( node->parent != NULL )
                {
                    ((__parent->left == node) ? __parent->left : __parent->right) =  nodeChild;
                }

                nodeChild->parent = __parent;
                delOddDegree(nodeChild);

                ret = nodeChild;
            }
            else
            {
                delOddDegree(node->left);
                delOddDegree(node->right);
                ret = node;
            }
        }

        return ret;
    }

    void threadPreOrder(BTreeNode<T>* node, BTreeNode<T>*& pre)
    {
        if( node != NULL )
        {
            BTreeNode<T>* nodeRight = node->right;
            BTreeNode<T>* nodeLeft = node->left;

            node->left = pre;

            if( pre != NULL )
            {
                pre->right = node;
            }
            pre = node;

            threadPreOrder(nodeLeft, pre);
            threadPreOrder(nodeRight, pre);
        }
    }

    void threadInOrder(BTreeNode<T>* node, BTreeNode<T>*& pre)
    {
        if( node != NULL )
        {
            threadInOrder(node->left, pre);

            node->left = pre;

            if( pre != NULL )
            {
                pre->right = node;
            }
            pre = node;

            threadInOrder(node->right, pre);
        }
    }

    void threadPostOrder(BTreeNode<T>* node, BTreeNode<T>*& pre)
    {
        if( node != NULL )
        {
            threadPostOrder(node->left, pre);
            threadPostOrder(node->right, pre);

            node->left = pre;

            if( pre != NULL )
            {
                pre->right = node;
            }

            pre = node;
        }
    }

    void threadLevelOrder(BTreeNode<T>* node, BTreeNode<T>*& pre)
    {
        if( node != NULL )
        {
            LinkQueue<BTreeNode<T>*> queue;

            queue.enque(node);

            while( !queue.isEmpty() )
            {
                BTreeNode<T>* node = queue.front();

                queue.deque();

                if( node->left != NULL )
                {
                    queue.enque(node->left);
                }

                if( node->right != NULL )
                {
                    queue.enque(node->right);
                }

                node->left = pre;

                if( pre != NULL )
                {
                    pre->right = node;
                }

                pre = node;
            }
        }
    }

    void swapNode(BTreeNode<T>* node)
    {
        if( node != NULL )
        {
            swapNode(node->left);
            swapNode(node->right);

            BTreeNode<T>* temp = node->left;

            node->left = node->right;
            node->right = temp;
        }
    }

public:
    virtual bool insert(BTreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if( node != NULL )
        {
            if( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* __parent = find(node->parent);

                if( __parent != NULL )
                {
                    if( __parent->left != node && __parent->right != node )
                    {
                        ret = insert(node, __parent, pos);
                    }
                    else
                    {
                        ret = false;
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "the node parent not exist tree...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(NullPointerException, "the parameter node is nullptr");
        }

        return ret;
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if( node != NULL )
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if( !ret )
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create BTreeNode object...");
        }

        return ret;
    }

    bool insert(TreeNode<T>* node)
    {
        return insert(dynamic_cast<BTreeNode<T>*>(node), ANY);
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;
        BTreeNode<T>* __node = find(node);

        if( __node != NULL )
        {
            remove(dynamic_cast<BTreeNode<T>*>(__node), ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the parameter node not exist from tree..");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = NULL;
        BTreeNode<T>* node = find(value);

        if( node != NULL )
        {
            remove(node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the parameter value not exist from tree..");
        }

        return ret;
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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
        m_queue.clear();
    }

    T current() const
    {
        return const_cast<BTree<T>*>(this)->current();
    }

    T& current()
    {
        return m_queue.front()->value;
    }

    bool begin()
    {
        bool ret = (this->m_root != NULL);

        if( ret )
        {
            m_queue.clear();
            m_queue.enque(dynamic_cast<BTreeNode<T>*>(this->m_root));
        }

        return ret;
    }

    bool end() const
    {
        return m_queue.isEmpty();
    }

    bool next()
    {
        bool ret = !end();

        if( ret )
        {
            BTreeNode<T>* node = m_queue.front();

            m_queue.deque();

            if( node->left != NULL )
            {
                m_queue.enque(node->left);
            }

            if( node->right != NULL )
            {
                m_queue.enque(node->right);
            }
        }

        return ret;
    }

    SharedPointer<DynamicArray<T>> traversal(BTTraversalPos pos, bool isRecursion = false) const
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(pos, queue, isRecursion);
        ret = new DynamicArray<T>(queue.size());

        if( ret != NULL )
        {
            for(int i = 0; i < ret->length(); ++i)
            {
                (*ret)[i] = queue.front()->value;
                queue.deque();
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create DynamicArray object...");
        }

        return ret;
    }

    bool operator == (const BTree<T>& other) const
    {
        return equal(root(), other.root());
    }

    bool operator != (const BTree<T>& other) const
    {
        return !(*this == other);
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new BTree object...");
        }

        return ret;
    }

    SharedPointer< BTree<T> > operator + (const BTree<T>& other) const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root = add(root(), other.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create BTree object...");
        }

        return ret;
    }

    SharedPointer< BTree<T> > add(const BTree<T>& other) const
    {
        return *this + other;
    }

    BTreeNode<T>* threadUseQueue(BTTraversalPos pos, bool isRecursion = false)
    {
        BTreeNode<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(pos, queue, isRecursion);
        ret = connect(queue);
        m_queue.clear();
        this->m_root = NULL;

        return ret;
    }

    BTreeNode<T>* thread(BTTraversalPos pos)
    {
        BTreeNode<T>* ret = NULL;
        BTreeNode<T>* pre = NULL;
        void(BTree::* pFuncArr[])(BTreeNode<T>*, BTreeNode<T>*&) =
        {
            threadPreOrder, threadInOrder, threadPostOrder, threadLevelOrder
        };

        unsigned int traversalPos = static_cast<unsigned int>(pos);

        if( traversalPos < 4 )
        {
            (this->*pFuncArr[traversalPos])(root(), pre);
            this->m_root = NULL;
            m_queue.clear();

            pre->right = NULL;
            while( pre->left != NULL )
            {
                pre = pre->left;
            }

            ret = pre;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the parameter pos is invalid...");
        }

        return ret;
    }

    void delOddDegree()
    {
        if( this->m_root != NULL )
        {
            this->m_root = delOddDegree(root());
            m_queue.clear();
        }
    }

    void swapNode()
    {
        if( this->m_root != NULL )
        {
            swapNode(root());
            m_queue.clear();
        }
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // __BTREE_H__
