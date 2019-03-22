/*
 * Graph.h
 *
 *  Created on: Mar 22, 2019
 *      Author: yahia
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>


using vertex_t = uint32_t;
using vertexDist_t = uint32_t;
using adjacenyList_t = typename std::map<vertex_t,std::list<std::pair<vertex_t,vertexDist_t>>>;



class Graph {
	adjacenyList_t adjacencyList;
	void addEdge(vertex_t const& v, vertex_t const& w,vertexDist_t const& dist);
	/********* To Make it easy while coding ****/
	vertexDist_t distance(std::pair<vertex_t,vertexDist_t> const& p) const
	{
		return p.second;
	}
	vertex_t value(std::pair<vertex_t,vertexDist_t> const& p) const
	{
		return p.first;
	}
	vertex_t value(std::pair<vertex_t,std::list<std::pair<vertex_t,vertexDist_t>>> const& p) const
	{
		return p.first;
	}
	std::list<std::pair<vertex_t,vertexDist_t>> connectedVerticesList(std::pair<vertex_t,std::list<std::pair<vertex_t,vertexDist_t>>> const& p) const
	{
		return p.second;
	}

public:
	Graph();
	Graph(std::string const& file_path);
	virtual ~Graph();
	void readGraphData(std::string const& file_path);
	void printGraphAdjacenyList();
	uint32_t verticesCount(void);

	// Return the shortest distances for all vertices from v_src.
	std::map<vertex_t,vertexDist_t> dijkstra_navie_impl(vertex_t const& v_src);

	vertexDist_t calculateShortestDistance_Dijkstra(vertex_t const& v_src,vertex_t const& v_dest);
};


vertexDist_t Graph::calculateShortestDistance_Dijkstra(vertex_t const& v_src,vertex_t const& v_dest)
{
	auto A = dijkstra_navie_impl(v_src);
	return A[v_dest];
}

std::map<vertex_t,vertexDist_t> Graph::dijkstra_navie_impl(vertex_t const& v_src)
{
	const vertexDist_t noPathValue = 1000000;
	std::map<vertex_t,vertexDist_t> A; 	//  computed shortest path distances.
	std::vector<vertex_t> X; 			// container of the visited (processed) vertices.
	std::map<vertex_t,vertexDist_t> V_X; // Remaining non calculated vertices for shortest path.

	for(uint32_t i = 1; i <= this->verticesCount();i++) // Assuming vertices are coded from 1 to n
	{
		A[i] = noPathValue;
		V_X[i] = noPathValue;
	}

	// set v_src as 0 so, the algo starts with it.
	A[v_src] = 0;
	V_X[v_src] = 0;

	do
	{
		//Pick the vertex with min distance.
		auto min_dist_it = std::min_element(V_X.begin(),V_X.end(),
				[&](std::pair<vertex_t,vertexDist_t> const& v1,
						std::pair<vertex_t,vertexDist_t> const& v2){
			return  (v1.second < v2.second);
		});

		// look up for the adjacent vertices and update their distances.
		for(auto w : adjacencyList[min_dist_it->first])
		{
			// choose min { A[v] + l_vw , A[v] }
			auto it = std::find_if(X.begin(),X.end(),[&](vertex_t const& v){
				return v == value(w);
			});
			if(it == X.end())
			{
				A[value(w)] = std::min(A[min_dist_it->first] + distance(w), A[value(w)]);
				V_X[value(w)] = A[value(w)];
			}
		}

		// Added Processed Vertex to X
		X.push_back(min_dist_it->first);
		// Remove the picked vertex from V_X
		V_X.erase(min_dist_it);
	}while(X.size() < verticesCount());

	return A;
}

void Graph::printGraphAdjacenyList()
{
	for(auto v : this->adjacencyList)
	{
		printf("[%d] -> ",value(v));
		for(auto w : connectedVerticesList(v))
			printf("(%d,%d) ",value(w),distance(w));
		printf("\n");
	}
}

void Graph::addEdge(vertex_t const& v, vertex_t const& w,vertexDist_t const& dist)
{
	std::pair<vertex_t,vertexDist_t> p(w,dist);
	adjacencyList[v].push_back(p);
}

void Graph::readGraphData(std::string const& file_path)
{
	std::fstream in_file(file_path, std::ios_base::in);
	std::string text_line;
	vertex_t v,w;
	vertexDist_t dist;
	char comma;

	while(getline(in_file,text_line))
	{
		if(text_line.size() > 0)
		{
			std::stringstream stream(text_line);
			stream >> v;
			while (1)
			{
				stream >> w;
				stream >> comma;
				stream >> dist;
				if (!stream)
					break;
				this->addEdge(v,w,dist);
			}
		}
	}
}

uint32_t Graph::verticesCount(void)
{
	return this->adjacencyList.size();
}


Graph::Graph(std::string const& file_path)
{
	this->readGraphData(file_path);
}

Graph::Graph()
{

}
Graph::~Graph()
{

}
#endif /* GRAPH_H_ */
