#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "SharedPointer.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace TianGangLib
{

template < typename E >
struct Edge : public Object
{
    int begin;
    int end;
    E value;

    Edge(int i = - 1, int j = -1) : begin(i), end(j) { }
    Edge(int i, int j, const E& value) : begin(i), end(j), value(value) { }

    bool operator ==(const Edge<E>& other) const
    {
        return (begin == other.begin) && (end == other.end);
    }

    bool operator !=(const Edge<E>& other) const
    {
        return !(*this == other);
    }

    bool operator > (const Edge<E>& other) const
    {
        return value > other.value;
    }

    bool operator < (const Edge<E>& other) const
    {
        return value < other.value;
    }

    bool operator >= (const Edge<E>& other) const
    {
        return value >= other.value;
    }

    bool operator <= (const Edge<E>& other) const
    {
        return value <= other.value;
    }
};

template < typename E >
struct ShortestPath : public Object
{
    SharedPointer< Array<int> > path;
    E distance;
};

template < typename V, typename E >
class Graph : public Object
{
    Graph<V, E>& operator = (const Graph<V, E>& other);
    Graph(const Graph<V, E>& other);

protected:
    template < typename T >
    DynamicArray<T>* toArray(LinkQueue<T>& queue) const
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.size());

        if( ret != NULL )
        {
            int i = 0;

            while( !queue.isEmpty() )
            {
                ret->set(i++, queue.front());
                queue.deque();
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create dynamic array...");
        }

        return ret;
    }

    SharedPointer< Array< Edge<E> > > getUndirectEdges() const
    {
        LinkQueue< Edge<E> > ret;

        if( asUndirected() )
        {
            for(int i = 0; i < vCount(); ++i)
            {
                for(int j = i; j < vCount(); ++j)
                {
                    if( isAdjacent(i, j) )
                    {
                        ret.enque(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperatorException, "the graph is not a undirect...");
        }

        return toArray(ret);
    }

    int find(const DynamicArray<int>& array, int i) const
    {
        int ret = i;

        while( array[ret] != -1 )
        {
            ret = array[ret];
        }

        return ret;
    }

public:
    Graph() { }
    virtual V getVertex(int i) const = 0;
    virtual bool getVertex(int i, V& value) const = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) const = 0;
    virtual E getEdge(int i, int j) const = 0;
    virtual bool getEdge(int i, int j, E& value) const = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() const = 0;
    virtual bool isAdjacent(int i, int j) const = 0;
    virtual int eCount() const = 0;
    virtual int ODegree(int i) const = 0;
    virtual int IDegree(int i) const = 0;

    virtual int TDegree(int i) const
    {
        return ODegree(i) + IDegree(i);
    }

    SharedPointer< Array<int> > BFS(int i) const
    {
        DynamicArray<int>* ret = NULL;

        if( (0 <= i) && (i < vCount()) )
        {
            LinkQueue<int> queue;
            LinkQueue<int> result;
            DynamicArray<int> visited(vCount());

            for(int j = 0; j < visited.length(); ++j)
            {
                visited[j] = false;
            }

            queue.enque(i);

            while( !queue.isEmpty() )
            {
                int index = queue.front();

                queue.deque();

                if( !visited[index] )
                {
                    result.enque(index);
                    visited[index] = true;

                    SharedPointer< Array<int> > pArr = getAdjacent(index);

                    for(int j = 0; j < pArr->length(); ++j)
                    {
                        queue.enque((*pArr)[j]);
                    }
                }
            }

            ret = toArray(result);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index is invalid...");
        }

        return ret;
    }

    SharedPointer< Array<int> > DFS(int i) const
    {
        DynamicArray<int>* ret = NULL;

        if( 0 <= i && i < vCount() )
        {
            LinkStack<int> stack;
            LinkQueue<int> result;
            DynamicArray<bool> visited(vCount());

            for(int j = 0; j < visited.length(); ++j)
            {
                visited[j] = false;
            }

            stack.push(i);

            while( !stack.isEmpty() )
            {
                int pos = stack.top();

                stack.pop();

                if( !visited[pos] )
                {
                    visited[pos] = true;
                    result.enque(pos);

                    SharedPointer< Array<int> > aj = getAdjacent(pos);

                    for(int j = aj->length() - 1; j >= 0; --j)
                    {
                        stack.push((*aj)[j]);
                    }
                }
            }

            ret = toArray(result);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index is invalid...");
        }

        return ret;
    }

    bool asUndirected() const
    {
        bool ret = true;

        for(int i = 0; ret && i < vCount(); ++i)
        {
            for(int j = 0; ret && j < vCount(); ++j)
            {
                if( isAdjacent(i, j) )
                {
                    ret = isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    SharedPointer< Array< Edge<E> > > prim(const E LIMIT, const bool MINIUM = true) const
    {
        DynamicArray< Edge<E> >* ret = NULL;

        if( asUndirected() && vCount() > 0 )
        {
            DynamicArray<bool> mask(vCount());
            DynamicArray<E> cost(vCount());
            DynamicArray<int> adjVertex(vCount());
            LinkQueue< Edge<E> > result;

            for(int i = 0; i < vCount(); ++i)
            {
                mask[i] = false;
                cost[i] = LIMIT;
                adjVertex[i] = -1;
            }

            SharedPointer< Array<int> > aj = getAdjacent(0);

            mask[0] = true;

            for(int i = 0; i < aj->length(); ++i)
            {
                cost[(*aj)[i]] = getEdge(0, (*aj)[i]);
                adjVertex[(*aj)[i]] = 0;
            }

            for(int i = 0; i < vCount() - 1; ++i)
            {
                int pos = -1;
                E m = LIMIT;

                for(int j = 0; j < vCount(); ++j)
                {
                    if( !mask[j] && (MINIUM ? cost[j] < m : cost[j] > m) )
                    {
                        m = cost[j];
                        pos = j;
                    }
                }

                if( pos == -1 )
                {
                    break;
                }

                mask[pos] = true;
                result.enque(Edge<E>(adjVertex[pos], pos, getEdge(adjVertex[pos], pos)));
                aj = getAdjacent(pos);

                for(int j = 0; j < aj->length(); ++j)
                {
                    if( !mask[(*aj)[j]] &&
                            (MINIUM ? getEdge(pos, (*aj)[j]) < cost[(*aj)[j]] :
                             getEdge(pos, (*aj)[j]) > cost[(*aj)[j]]) )
                    {
                        cost[(*aj)[j]] = getEdge(pos, (*aj)[j]);
                        adjVertex[(*aj)[j]] = pos;
                    }
                }
            }

            if( result.size() != vCount() - 1 )
            {
                THROW_EXCEPTION(InvalidOperatorException, "the garph is invalid...");
            }

            ret = toArray(result);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperatorException, "the graph not as undirected graph or graph vertex count is zero....");
        }

        return ret;
    }

    SharedPointer< Array< Edge<E> > > kruskal() const
    {
        LinkQueue< Edge<E> > ret;
        DynamicArray<int> p(vCount());
        SharedPointer< Array< Edge<E> > > edges = getUndirectEdges();

        for(int i = 0; i < p.length(); ++i)
        {
            p[i] = -1;
        }

        edges->quickSort();

        for(int i = 0; i < edges->length() && ret.size() < vCount() - 1; ++i)
        {
            int b = find(p, (*edges)[i].begin);
            int e = find(p, (*edges)[i].end);

            if( b != e )
            {
                ret.enque(Edge<E>(b, e, (*edges)[i].value));
                p[e] = b;
            }
        }

        return toArray(ret);
    }

    SharedPointer< ShortestPath<E> > dijkstra(int i, int j, const E& LIMIT) const
    {
        ShortestPath<E>* ret = NULL;

        if( (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) )
        {
            DynamicArray<E> distance(vCount()); // 用于标记最短路径的距离
            DynamicArray<int> path(vCount()); // 用于标记具体的路径
            DynamicArray<bool> mark(vCount()); // 标记哪些顶点已经求出了最短路径

            for(int k = 0; k < vCount(); ++k) // 初始化
            {
                mark[k] = false;
                path[k] = -1;
                distance[k] = (isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT);
            }

            mark[i] = true; // 起点

            for(int k = 0; k < vCount() - 1; ++k)
            {
                int minPos = -1; // 最小值下标
                E min = LIMIT; // 最小值

                for(int w = 0; w < vCount(); ++w) // 寻找最小值
                {
                    if( !mark[w] && min > distance[w] )
                    {
                        min = distance[w];
                        minPos = w;
                    }
                }

                if( minPos == -1 )
                {
                    break;
                }

                mark[minPos] = true; // minPos下标的顶点最短路径已经找到了

                for(int w = 0; w < vCount(); ++w)
                {
                    // Dijkstra算法核心，根据已有最短路径推导其它最短路径。
                    if( !mark[w] && (isAdjacent(minPos, w)) && (distance[w] > distance[minPos] + getEdge(minPos, w)) )
                    {
                        distance[w] = distance[minPos] + getEdge(minPos, w);
                        path[w] = minPos;
                    }
                }
            }

            LinkStack<int> stack; // 因为路径是你逆序，需要用栈来翻转
            LinkQueue<int> queue; //输出具体路径的队列

            stack.push(j); // 终点

            for(int k = path[j]; k != -1; k = path[k]) // 存入路径
            {
                stack.push(k);
            }

            while( !stack.isEmpty() ) // 翻转路径
            {
                queue.enque(stack.top());
                stack.pop();
            }

            if( queue.size() < 2 ) // 代表不可达
            {
                THROW_EXCEPTION(InvalidOperatorException, "the graphic is not connected...");
            }

            ret = new ShortestPath<E>(); // 申请返回对象。

            if( ret != NULL )
            {
                ret->path = toArray(queue);
                ret->distance = distance[j];
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no memort to create ShortestPath object...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the index is invalid...");
        }

        return ret;
    }

    typedef DynamicArray< DynamicArray< ShortestPath<E> > > ShortestPathArray;
    typedef DynamicArray< DynamicArray< int> > PathArray;

    SharedPointer< Array< DynamicArray< ShortestPath<E> > > > floyd(const E& LIMIT) const
    {
        ShortestPathArray* ret = new  ShortestPathArray(vCount());
        PathArray path(vCount());

        if( ret != NULL )
        {
            for(int i = 0; i < vCount(); ++i)
            {
                (*ret)[i].resize(vCount());
                path[i].resize(vCount());
            }

            for(int i = 0; i < vCount(); ++i)
            {
                for(int j = 0; j < vCount(); ++j)
                {
                    path[i][j] = -1;
                    (*ret)[i][j].distance = (isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT);
                }
            }

            for(int k = 0; k < vCount(); ++k)
            {
                for(int i = 0; i < vCount(); ++i)
                {
                    for(int j = 0; j < vCount(); ++j)
                    {
                        if( (*ret)[i][k].distance + (*ret)[k][j].distance < (*ret)[i][j].distance )
                        {
                            (*ret)[i][j].distance = (*ret)[i][k].distance + (*ret)[k][j].distance;
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }

            for(int i = 0; i < vCount(); ++i)
            {
                for(int j = 0; j < vCount(); ++j)
                {
                    int k = i;
                    LinkQueue<int> queue;

                    while(k != - 1 )
                    {
                        queue.enque(k);
                        k = path[k][j];

                        if( k == j )
                        {
                            break;
                        }
                    }

                    queue.enque(j);

                    (*ret)[i][j].path = toArray(queue);
                }
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create ShortestPathArray obj...");
        }

        return ret;
    }
};

}


#endif // __GRAPH_H__
