#ifndef __STATICLINKLIST_H__
#define __STATICLINKLIST_H__

#include "LinkList.h"
using namespace std;

namespace TianGangLib
{

template < typename T, int N >
class StaticLinkList : public LinkList<T>
{
    typedef typename LinkList<T>::Node Node;
    unsigned char m_space[sizeof(Node) * N];
    bool m_use[N];

    struct SNode : public Node
    {
        void* operator new (unsigned int size, void* ptr)
        {
            (void) size;
            return ptr;
        }
    };

protected:
    Node* create()
    {
        SNode* ret = NULL;

        for(int i = 0; i < N; ++i)
        {
            if( !m_use[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret) SNode();
                m_use[i] = true;

                break;
            }
        }

        return ret;
    }

    void destroy(Node* np)
    {
        SNode* snp = dynamic_cast<SNode*>(np);
        Node* sp = reinterpret_cast<Node*>(m_space);

        for(int i = 0; i < N; ++i)
        {
            if( np == (sp + i) )
            {
                m_use[i] = false;
                snp->~SNode();
                break;
            }
        }
    }

public:
    StaticLinkList()
    {
        for(int i = 0; i < N; ++i)
        {
            m_use[i] = false;
        }
    }

    int capacity() const
    {
        return N;
    }

    ~StaticLinkList()
    {
        this->clear();
    }

};

}



#endif // __STATICLINKLIST_H__
