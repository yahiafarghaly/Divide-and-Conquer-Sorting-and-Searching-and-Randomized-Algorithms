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
	void __DFS_Topological(T const&, std::map<T,bool>&,
			std::map<T,unsigned long>&, unsigned long&);
public:
	DirectedGraph();

	void addArc(T const& v, T const& w);
	void addVertex(T const& v);
	void printGraphAdjacenyList();
	unsigned long verticesCount(void)
	{
		return this->adjacencyList.size();
	}
	void DFS(T const& s);
	std::list<T> topologicalSort_DFS();

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
void DirectedGraph<T>::__DFS(T const& v, std::map<T,bool>& v_discovery)
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
void DirectedGraph<T>::__DFS_Topological(T const& v, std::map<T,bool>& v_discovery
		,std::map<T,unsigned long>& f, unsigned long& current_label)
{
	auto edges = this->adjacencyList[v];
	for(auto w : edges)
	{
		if(!v_discovery[w])
		{
			v_discovery[w] = true;
			std::cout << "Vertex [ " << w << " ] is visited\n";
			this->__DFS_Topological(w,v_discovery,f,current_label);
		}
	}
	f[v] = current_label;
	current_label -= 1;
}

template <class T>
std::list<T> DirectedGraph<T>::topologicalSort_DFS()
{
	std::list<T> topological_sorted_list;
	std::map<T,unsigned long> f;
	std::map<T,bool> v_discovery;
	unsigned long current_label = this->verticesCount();

	for(auto v : this->adjacencyList)
		v_discovery[v.first] = false;

	for(auto v : this->adjacencyList)
	{
		if(!v_discovery[v.first])
		{
			v_discovery[v.first] = true;
			std::cout << "Vertex [ " << v.first << " ] is visited\n";
			this->__DFS_Topological(v.first,v_discovery,f,current_label);
		}
	}

	// sort vertices labels.
	current_label = this->verticesCount();
	while(current_label)
	{
		for(auto v : this->adjacencyList)
		{
			if(f[v.first] == current_label)
			{
				topological_sorted_list.push_front(v.first);
				--current_label;
			}
		}
	}

	return topological_sorted_list;

}

template <class T>
DirectedGraph<T>::DirectedGraph () {
}

template <class T>
DirectedGraph<T>::~DirectedGraph() {
}

#endif /* DIRECTEDGRAPH_H_ */
