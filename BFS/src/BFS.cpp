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

    /* NOT CONNECTED*/
    g.addEdge('F','G');

    g.addEdge('G','F');
    g.addEdge('G','H');

    g.addEdge('H','G');

    /* NOT CONNECTED */
    g.addEdge('M','N');

    g.addEdge('N','M');
    g.addEdge('N','N');



    /*g.printGraphAdjacenyList();
    g.BFS('s');

    g.find_ShortestPath('s','e');*/

    std::list<Graph<char>> cg = g.getConnectedComponents();

    for(auto graph : cg)
    {
    	std::cout << "A CONNECTED COMPONENT\n";
    	graph.printGraphAdjacenyList();
    	std::cout << "###########################################\n";
    }


	return 0;
}
