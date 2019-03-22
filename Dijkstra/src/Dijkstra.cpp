//============================================================================
// Name        : Dijkstra.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Graph.h"
using namespace std;

int main() {

	Graph g("./src/dijkstraData.txt");



	auto A = g.dijkstra_navie_impl(1);

	printf("Shortest Path Distances to the vertices 7,37,59,82,99,115,133,165,188,197:\n");
	printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			A[7],A[37],A[59],A[82],A[99],A[115],A[133],A[165],A[188],A[197]);

//	printf("%d,%d,%d,%d\n",A[1],A[2],A[3],A[4]);



	return 0;
}
