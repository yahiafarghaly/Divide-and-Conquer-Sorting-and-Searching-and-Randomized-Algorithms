//============================================================================
// Name        : SCCs.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "DirectedGraph.h"

using namespace std;

template<class T>
void readGraphFile(string file_path,DirectedGraph<T>& G);

int main() {

	DirectedGraph<unsigned long> g;
//	readGraphFile("./src/lecture_graph.txt",g); // pass
	readGraphFile("./src/SCC.txt",g);
//	readGraphFile("./src/directed_g1.txt",g); // pass
//	readGraphFile("./src/input_mostlyCycles_68_320000.txt",g); // pass
//	g.printGraphAdjacenyList();
//	g.DFS(8);
//	auto rAdjList = g.reverseGraph();
//	g.printGraphAdjacenyList(rAdjList);
	auto SCCs_size = g.SSCs();

	int i = 0;
	for(auto s : SCCs_size)
	{
		++i;
		std::cout << s << " ";
		if(i == 5)
			break;
	}
	std::cout << "\n";



	return 0;
}

template<class T>
void readGraphFile(string file_path,DirectedGraph<T>& G)
{

	std::fstream in_file(file_path, std::ios_base::in);

	string line;
	vector<T> vertices;
	while(getline(in_file,line))
	{
		if(line.size() > 0)
		{
			stringstream stream(line);
			T vertexName;
			vertices.clear();
			while (1)
			{
				stream >> vertexName;
				if (!stream)
					break;
				vertices.push_back(vertexName);
			}
		}
		if(vertices.size() == 1)
			G.addVertex(vertices[0]);
		else
			G.addArc(vertices[0],vertices[1]);
	}
}
