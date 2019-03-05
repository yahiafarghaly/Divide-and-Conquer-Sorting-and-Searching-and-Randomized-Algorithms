//============================================================================
// Name        : DFS.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "DirectedGraph.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<class T>
void readGraphDataFromFile(DirectedGraph<T>& g,string file_path);

int main() {

	DirectedGraph<char> g;
	g.addArc('s','v');
	g.addArc('s','w');
	g.addArc('w','t');
	g.addArc('v','t');
	g.addVertex('t');
	g.printGraphAdjacenyList();
	//g.DFS('t');

	auto sequence = g.topologicalSort_DFS();

	for(auto v : sequence)
		std::cout << v << " " ;
	std::cout << "\n";

	std::cout << "###############################\n";

	DirectedGraph<int> g2;
	readGraphDataFromFile(g2,"./src/directed_graph1.txt");
	g2.printGraphAdjacenyList();

	auto sequence2 = g2.topologicalSort_DFS();
	/*
	 * Can be either
	 * 1 2 5 4 3 7 6
	 * 1 2 5 4 7 3 6
	 * */
	for(auto v : sequence2)
		std::cout << v << " " ;
	std::cout << "\n";
	return 0;
}


template<class T>
void readGraphDataFromFile(DirectedGraph<T>& g,string file_path)
{
	std::fstream in_file(file_path, std::ios_base::in);

	string line;
	list<T> vertices;
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
				{
					g.addVertex(vertexName);
					break;
				}
				vertices.push_back(vertexName);
			}

			auto s = vertices.begin();
			auto v = s;
			v++;

			while(v != vertices.end())
			{
				g.addArc(*s,*v);
				v++;
			}
		}
	}
}
