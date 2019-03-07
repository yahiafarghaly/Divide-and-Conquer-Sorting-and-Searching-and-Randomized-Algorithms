/*
 * Graph.h
 *
 *  Created on: Mar 4, 2019
 *      Author: yahia
 */

#ifndef DIRECTEDGRAPH_H_
#define DIRECTEDGRAPH_H_

#include <list>
#include <stack>
#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

//#define printVisited(v) std::cout << "Vertex [ "<< v << " ] is explored\n";

#define printVisited(v)

template <typename T>
using AdjacencyList = typename std::map<T,std::list<T>>; // C++11 and above.

template <typename T>
using FinishingTimeList = typename std::map<T,unsigned long>;

template <typename T>
using VertexLeaderList = typename std::map<T,unsigned long>;


template <class T>
class DirectedGraph {
	AdjacencyList<T> 		adjacencyList;
	FinishingTimeList<T> 	ftList;
	VertexLeaderList<T> 	vLeaderList;

	unsigned long 	__ft;
	unsigned long 	__vleader;
	bool 			__calculateLeaders;


	void __DFS(T const&, std::map<T,bool>&,AdjacencyList<T>& );

public:
	DirectedGraph();

	void addArc(T const& v, T const& w);
	void addVertex(T const& v);
	void printGraphAdjacenyList();
	void printGraphAdjacenyList(AdjacencyList<T>& adlist);
	unsigned long verticesCount()
	{
		return this->adjacencyList.size();
	}
	void DFS(T const& s);

	std::map<T,std::list<T>> reverseGraph();
	std::vector<unsigned long> SSCs(); // return the sizes of the 5 largest SCCs (in decreasing order).
	void DFS_loop(AdjacencyList<T>& adlist);

	virtual ~DirectedGraph();
};


template <class T>
void DirectedGraph<T>::addArc(T const& v, T const& w)
{
	this->adjacencyList[v].push_back(w);
}


template <class T>
void DirectedGraph<T>::addVertex(T const& v)
{
	this->adjacencyList[v];
}

template <class T>
void DirectedGraph<T>::printGraphAdjacenyList()
{
	this->printGraphAdjacenyList(this->adjacencyList);
}

template <class T>
void DirectedGraph<T>::printGraphAdjacenyList(AdjacencyList<T>& adlist)
{
	for(auto s: adlist)
	{
		std::cout << s.first << " | " << "{ ";
		for(auto w : s.second)
			std::cout << w << " ";
		std::cout << "}\n";
		std::cout << "------------------------------------\n";
	}
}

template <class T>
void DirectedGraph<T>::DFS(T const& s)
{
	if(this->adjacencyList.find(s) == this->adjacencyList.end())
	{
		std::cout << "Vertex [ "<< s << " ] is not a part of this graph\n";
		return;
	}

	std::map<T,bool> v_discovery;
	for(auto v : this->adjacencyList)
		v_discovery[v.first] = false;

	this->__DFS(s,v_discovery,this->adjacencyList);

}


template <class T>
std::map<T,std::list<T>> DirectedGraph<T>::reverseGraph()
{
	std::shared_ptr<AdjacencyList<T>> revAdjList = std::make_shared<AdjacencyList<T>>();

	for(auto v : this->adjacencyList)
	{
		if(v.second.empty());
			// Needs somethinking to get it right but for now, it doesn't affect on the final result !
		for(auto w : v.second)
			(*revAdjList)[w].push_back(v.first);
	}

	return *revAdjList;
}


template <class T>
void DirectedGraph<T>::__DFS(T const& v, std::map<T,bool>& v_discovery,AdjacencyList<T>& adlist)
{
	// set v as explored
	v_discovery[v] = true;
	printVisited(v);

	if(this->__calculateLeaders)
		this->vLeaderList[this->__vleader] += 1 ; // we calculate it early to accelerate the final result.

	auto edges = adlist[v];
	for(auto w : edges)
		if(!v_discovery[w])
			this->__DFS(w,v_discovery,adlist);

	(this->__ft)++;
	this->ftList[v] = this->__ft;
}


template<class T>
void DirectedGraph<T>::DFS_loop(AdjacencyList<T>& adlist)
{
	__ft = 0;
	__vleader = 0;

	std::map<T,bool> v_discovery;
	for(auto v : adlist)
		v_discovery[v.first] = false;

	for(auto v = adlist.rbegin(); v != adlist.rend(); v++)
	{
		if(!v_discovery[(*v).first])
		{
			__vleader = (*v).first;
			if(this->__calculateLeaders)
				this->vLeaderList[this->__vleader] = 0;
			__DFS((*v).first,v_discovery,adlist);
		}
	}
}

template <class T>
std::vector<unsigned long> DirectedGraph<T>::SSCs()
{
	std::vector<unsigned long> SSCsList;
	this->ftList.clear();
	this->vLeaderList.clear();
	this->__calculateLeaders = false;

	// Run DFS_loop on Grev to get finishing time.
	auto revAdjacencyList = this->reverseGraph();
	DFS_loop(revAdjacencyList);


//	for(auto v : this->ftList)
//		std::cout << "V_t["<< v.first << "]: " << v.second << "\n";

	// Make another G with original directions and set vertex names to finishing times
	// to use DFS-loop to run on it in decreasing order.
	AdjacencyList<unsigned long> G_original_ft;
	for(auto v : this->adjacencyList)
	{
		if(v.second.empty())
			G_original_ft[this->ftList[v.first]];
		for(auto w : v.second)
			G_original_ft[this->ftList[v.first]].push_back(this->ftList[w]);
	}

	this->__calculateLeaders = true;
	DFS_loop(G_original_ft);

	// Free some memory here
	revAdjacencyList.clear();
	G_original_ft.clear();

//	for(auto v : this->vLeaderList)
//		std::cout << "V_l["<< v.first << "]: " << v.second << "\n";

	for(auto v : this->vLeaderList)
		SSCsList.push_back(v.second);

	while(SSCsList.size() < 5)
		SSCsList.push_back(0);

	std::sort(SSCsList.rbegin(),SSCsList.rend());
	return SSCsList;
}



template <class T>
DirectedGraph<T>::DirectedGraph () {
}

template <class T>
DirectedGraph<T>::~DirectedGraph() {
}

#endif /* DIRECTEDGRAPH_H_ */
