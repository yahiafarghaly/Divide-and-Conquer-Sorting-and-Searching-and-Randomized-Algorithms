//============================================================================
// Name        : DFS.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "DirectedGraph.h"
using namespace std;

int main() {

	DirectedGraph<char> g;
	g.addArc('s','v');
	g.addArc('s','w');
	g.addArc('w','t');
	g.addArc('v','t');
	g.addSinkVertex('t');
	g.printGraphAdjacenyList();
	g.DFS('t');

	return 0;
}
