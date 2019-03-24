#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include "Graph.h"
#include "DynamicArray.h"

namespace TianGangLib
{

template < int N, typename V, typename E >
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexs[N];
    E* m_edges[N][N];
    int m_ECount;

public:
    MatrixGraph() : m_ECount(0)
    {
        for(int i = 0; i < N; ++i)
        {
            m_vertexs[i] = NULL;

            for(int j = 0; j < N; ++j)
            {
                m_edges[i][j] = NULL;
            }
        }
    }

    V getVertex(int i) const
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "the argument is invalid...");
        }

        return ret;
    }

    bool getVertex(int i, V& value) const
    {
        bool ret = (0 <= i) && (i < vCount());

        if( ret )
        {
            if( m_vertexs[i] != NULL )
            {
                value = *m_vertexs[i];
            }
            else
            {
                THROW_EXCEPTION(InvalidOperatorException, "the position is not exist vertex...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = (0 <= i) && (i < vCount());

        if( ret )
        {
            if( m_vertexs[i] != NULL )
            {
                *m_vertexs[i] = value;
            }
            else
            {
                V* data = new V();

                if( data != NULL )
                {
                    *data = value;
                    m_vertexs[i] = data;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create vertex...");
                }
            }
        }

        return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i) const
    {
        DynamicArray<int>* ret = NULL;

        if( 0 <= i && i < vCount() )
        {
            int len = 0;

            for(int j = 0; j < N; ++j)
            {
                if( m_edges[i][j] != NULL )
                {
                    ++len;
                }
            }

            ret = new DynamicArray<int>(len);

            if( ret != NULL )
            {
                for(int j = 0, t = 0; j < N; ++j)
                {
                    if( m_edges[i][j] != NULL )
                    {
                        (*ret)[t++] = j;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create dynamic array object...");
            }
        }

        return ret;
    }

    E getEdge(int i, int j) const
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "the argument is invalid...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value) const
    {
        bool ret = (0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount());

        if( ret )
        {
            if( m_edges[i][j] != NULL )
            {
                value = *m_edges[i][j];
            }
            else
            {
                THROW_EXCEPTION(InvalidOperatorException, "the argument is invalid...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = (0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount());

        if( ret )
        {
            if( m_edges[i][j] != NULL )
            {
                *m_edges[i][j] = value;
            }
            else
            {
                E* data = new E();

                if( data != NULL )
                {
                    *data = value;
                    m_edges[i][j] = data;
                    ++m_ECount;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create edge...");
                }
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret = (0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount());


        if( ret )
        {
            if( m_edges[i][j] != NULL )
            {
                E* toDel = m_edges[i][j];

                m_edges[i][j] = NULL;
                --m_ECount;

                delete toDel;
            }
        }

        return ret;
    }

    int vCount() const
    {
        return N;
    }

    int eCount() const
    {
        return m_ECount;
    }

    int ODegree(int i) const
    {
        int ret = 0;

        if( 0 <= i && i < vCount() )
        {
            for(int j = 0; j < N; ++j)
            {
                if( m_edges[i][j] != NULL )
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the argument is invalid...");
        }

        return ret;
    }

    int IDegree(int i) const
    {
        int ret = 0;

        if( 0 <= i && i < vCount() )
        {
            for(int j = 0; j < N; ++j)
            {
                if( m_edges[j][i] != NULL )
                {
                    ++ret;
                }
            }
        }

        return ret;
    }

    bool isAdjacent(int i, int j) const
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_edges[i][j] != NULL);
    }

    ~MatrixGraph()
    {
        for(int i = 0; i < N; ++i)
        {
            delete m_vertexs[i];

            for(int j = 0; j < N; ++j)
            {
                delete m_edges[i][j];
            }
        }
    }
};

}

#endif // __MATRIXGRAPH_H__
