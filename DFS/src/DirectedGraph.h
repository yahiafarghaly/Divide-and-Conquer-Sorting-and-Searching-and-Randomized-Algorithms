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
#include <iostream>

template <class T>
class DirectedGraph {
	std::map<T,std::list<T>> adjacencyList;
	void __DFS(T const&, std::map<T,bool>&);
public:
	DirectedGraph();

	void addArc(T const& v, T const& w);
	void addSinkVertex(T const& v);
	void printGraphAdjacenyList();
	unsigned long verticesCount(void)
	{
		return this->adjacencyList.size();
	}
	void DFS(T const& s);

	virtual ~DirectedGraph();
};


template <class T>
void DirectedGraph<T>::addArc(T const& v, T const& w)
{
	this->adjacencyList[v].push_back(w);
}


template <class T>
void DirectedGraph<T>::addSinkVertex(T const& v)
{
	this->adjacencyList[v];
}

template <class T>
void DirectedGraph<T>::printGraphAdjacenyList(void)
{
	for(auto s: this->adjacencyList)
	{
		std::cout << s.first << " | " << "{ ";
		for(auto w : s.second)
			std::cout << w << " ";
		std::cout << "}\n";
		std::cout << "------------------------------------\n";
	}

}


template <class T>
void DirectedGraph<T>::__DFS(T const& v,std::map<T,bool>& v_discovery)
{
	auto edges = this->adjacencyList[v];
	for(auto w : edges)
	{
		if(!v_discovery[w])
		{
			v_discovery[w] = true;
			std::cout << "Vertex [ " << w << " ] is visited\n";
			this->__DFS(w,v_discovery);
		}
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

	v_discovery[s] = true;
	std::cout << "Vertex [ " << s << " ] is visited\n";
	this->__DFS(s,v_discovery);

}


template <class T>
DirectedGraph<T>::DirectedGraph () {
}

template <class T>
DirectedGraph<T>::~DirectedGraph() {
}

#endif /* DIRECTEDGRAPH_H_ */
