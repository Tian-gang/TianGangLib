#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include "Graph.h"
#include "LinkList.h"
#include "DynamicArray.h"

namespace TianGangLib
{

template < typename V, typename E >
class ListGraph : public Graph<V, E>
{
     struct Vertex : public Object
     {
         V* data;
         LinkList<Edge<E>> edges;
     };

     LinkList<Vertex*> m_vertexs;
public:
     ListGraph(int n = 0)
     {
         for(int i = 0; i < n; ++i)
         {
             addVertex();
         }
     }

     int addVertex()
     {
         int ret = -1;
         Vertex* vertex = new Vertex();

         if( vertex != NULL )
         {
             m_vertexs.append(vertex);
             ret = m_vertexs.length() - 1;
         }
         else
         {
             THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create vertex...");
         }


         return ret;
     }

     int addVertex(const V& data)
     {
         int ret = addVertex();

         setVertex(ret, data);

         return ret;
     }

     void removeVertex()
     {
         if( m_vertexs.length() > 0 )
         {
             int index = m_vertexs.length() - 1;
             Vertex* toDel = m_vertexs.get(index);

             m_vertexs.remove(index);

             for(int i = (m_vertexs.move(0), 0); !m_vertexs.end(); ++i, m_vertexs.next())
             {
                 int pos = m_vertexs.current()->edges.find(Edge<E>(i, index));

                 if( pos >= 0 )
                 {
                     m_vertexs.current()->edges.remove(pos);
                 }
             }

             delete toDel->data;
             delete toDel;
         }
         else
         {
             THROW_EXCEPTION(InvalidOperatorException, "the list graph not have any vertex...");
         }
     }

     V getVertex(int i) const
     {
         V ret;

         if( !getVertex(i, ret) )
         {
             THROW_EXCEPTION(InvalidParameterException, "the argument i is invalid...");
         }

         return ret;
     }

     bool getVertex(int i, V& value) const
     {
         bool ret = (0 <= i) && (i < vCount());

         if( ret )
         {
             V* data = m_vertexs.get(i)->data;

             if( data != NULL )
             {
                 value = *data;
             }
             else
             {
                 THROW_EXCEPTION(InvalidOperatorException, "the vertex is not exist data");
             }
         }

         return ret;
     }

     bool setVertex(int i, const V& value)
     {
         bool ret = (0 <= i) && (i < vCount());

         if( ret )
         {
             Vertex* vertex = m_vertexs.get(i);

             if( vertex->data != NULL )
             {
                 *vertex->data = value;
             }
             else
             {
                 V* data = new V();

                 if( data != NULL )
                 {
                     *data = value;
                     vertex->data = data;
                 }
                 else
                 {
                     THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create vertex data...");
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
             LinkList<Edge<E>>& list = m_vertexs.get(i)->edges;

             ret = new DynamicArray<int>(list.length());

             if( ret != NULL )
             {
                 for(int i = (list.move(0), 0); !list.end(); ++i, list.next())
                 {
                     ret->set(i, list.current().end);
                 }
             }
             else
             {
                 THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create dynamic array...");
             }
         }
         else
         {
             THROW_EXCEPTION(InvalidParameterException, "the argument i is invalid...");
         }

         return ret;
     }

     E getEdge(int i, int j) const
     {
         E ret;

         if( !getEdge(i, j, ret) )
         {
             THROW_EXCEPTION(InvalidParameterException, "the argument i is invalid...");
         }

         return ret;
     }

     bool getEdge(int i, int j, E& value) const
     {
         bool ret = (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount());

         if( ret )
         {
             LinkList<Edge<E>>& list = m_vertexs.get(i)->edges;
             int pos = list.find(Edge<E>(i, j));

             if( pos >= 0 )
             {
                 value = list.get(pos).value;
             }
             else
             {
                 THROW_EXCEPTION(InvalidOperatorException, "the position not exist any edge...");
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
             LinkList<Edge<E>>& list = m_vertexs.get(i)->edges;
             int pos = list.find(Edge<E>(i, j));

             ret = (pos >= 0) ? list.set(pos, Edge<E>(i, j, value)) : list.append(Edge<E>(i, j, value));
         }

         return ret;
     }

     bool removeEdge(int i, int j)
     {
         bool ret = (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount());

         if( ret )
         {
             LinkList<Edge<E>>& list = m_vertexs.get(i)->edges;
             int pos = list.find(Edge<E>(i, j));

             if( pos >= 0 )
             {
                 list.remove(pos);
             }
         }

         return ret;
     }

     int vCount() const
     {
         return m_vertexs.length();
     }

     int eCount() const
     {
         int ret = 0;

         for(m_vertexs.move(0); !m_vertexs.end(); m_vertexs.next())
         {
             ret += m_vertexs.current()->edges.length();
         }

         return ret;
     }

     int ODegree(int i) const
     {
         int ret = 0;

         if( 0 <= i && i < vCount() )
         {
             ret = m_vertexs.get(i)->edges.length();
         }
         else
         {
             THROW_EXCEPTION(InvalidParameterException, "the argument i is invalid...");
         }

         return ret;
     }

     int IDegree(int i) const
     {
         int ret = 0;

         if( 0 <= i && i < vCount() )
         {
             for(int j = (m_vertexs.move(0), 0); !m_vertexs.end(); ++j, m_vertexs.next())
             {
                 if( m_vertexs.current()->edges.find(Edge<E>(j, i)) >= 0 )
                 {
                     ++ret;
                 }
             }
         }
         else
         {
             THROW_EXCEPTION(InvalidParameterException, "the argument i is invalid...");
         }

         return ret;
     }

     bool isAdjacent(int i, int j) const
     {
         return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_vertexs.get(i)->edges.find(Edge<E>(i, j)) >= 0);
     }

     ~ListGraph()
     {
         while( m_vertexs.length() > 0 )
         {
             Vertex* toDel = m_vertexs.get(0);

             m_vertexs.remove(0);

             delete toDel->data;
             delete toDel;
         }
     }
};

}



#endif // __LISTGRAPH_H__
