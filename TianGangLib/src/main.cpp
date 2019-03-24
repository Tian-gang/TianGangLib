#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace TianGangLib;

class A
{
    int i;
public:
    void func()
    {
        i += 20;
        cout << "func()" << endl;
        cout << "i = " << i << endl;
    }
};

int main()
{
    ListGraph<int, int> graph;

    for(int i = 0; i < 3; ++i)
    {
        graph.addVertex();
    }

    graph.setEdge(0, 1, 4);
    graph.setEdge(1, 0, 6);
    graph.setEdge(0, 2, 11);
    graph.setEdge(2, 0, 3);
    graph.setEdge(1, 2, 2);

    SharedPointer< Array< DynamicArray< ShortestPath<int> > > > path = graph.floyd(65536);

    for(int k = 0; k < graph.vCount(); ++k)
    {
        for(int j = 0; j < graph.vCount(); ++j)
        {
            cout << k << "---"  << j << " 最短路径：" << ends;

            if( (*path)[k][j].distance != 65536 )
            {
                for(int i = 0; i < (*path)[k][j].path->length(); ++i)
                {
                    cout << (*(*path)[k][j].path)[i];

                    if( i != (*path)[k][j].path->length() -1 )
                    {
                        cout << "->";
                    }
                }

                cout << endl << "最短路径花费为：" << (*path)[k][j].distance << endl << endl;
            }
            else
            {
                cout << endl << "该路径不可达" << endl << endl;
            }
        }
    }
    return 0;
}
