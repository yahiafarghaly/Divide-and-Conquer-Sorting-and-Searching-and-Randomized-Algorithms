//============================================================================
// Name        : BFS.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Graph.h"
using namespace std;


int main() {

    Graph<char> g;
    g.addEdge('s', 'a');
    g.addEdge('s', 'b');

    g.addEdge('a', 's');
    g.addEdge('a', 'c');

    g.addEdge('b', 's');
    g.addEdge('b', 'c');
    g.addEdge('b', 'd');

    g.addEdge('c', 'a');
    g.addEdge('c', 'e');
    g.addEdge('c', 'd');
    g.addEdge('c', 'b');

    g.addEdge('d', 'e');
    g.addEdge('d', 'c');
    g.addEdge('d', 'b');

    g.addEdge('e', 'c');
    g.addEdge('e', 'd');


    g.printGraphAdjacenyList();
    g.BFS('s');

    g.find_ShortestPath('s','e');


	return 0;
}
