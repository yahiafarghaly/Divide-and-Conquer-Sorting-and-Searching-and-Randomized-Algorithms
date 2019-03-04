/*
 * Graph.h
 *
 *  Created on: Mar 4, 2019
 *      Author: yahia
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <queue>
#include <map>
#include <memory>

template <class T>
class Graph {
	std::map<T,std::list<T>> adjacencyList;
public:
	Graph();

	void addEdge(T const& v, T const& w);
	void removeEdge(T const& v, T const& w);
	void printGraphAdjacenyList();
	unsigned long verticesCount(void)
	{
		return this->adjacencyList.size();
	}

	void BFS(T s);
	unsigned long find_ShortestPath(T s, T const &d);
	std::list<Graph<T>> getConnectedComponents(void);
	virtual ~Graph();
};


template <class T>
void Graph<T>::addEdge(T const& v, T const& w)
{
	this->adjacencyList[v].push_back(w);
}

template <class T>
void Graph<T>::removeEdge(T const& v, T const& w)
{
	this->adjacencyList[v].remove(w);
}

template <class T>
void Graph<T>::printGraphAdjacenyList(void)
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
void Graph<T>::BFS(T s)
{
	if(this->adjacencyList.find(s) == this->adjacencyList.end())
	{
		std::cout << "Vertex [ "<< s << " ] is not a part of this graph\n";
		return;
	}

	std::map<T,bool> v_discovery;
	for(auto v : this->adjacencyList)
		v_discovery[v.first] = false;

	std::queue<T> vQ;

	v_discovery[s] = true;
	vQ.push(s);

	while(!vQ.empty())
	{
		s = vQ.front();
		vQ.pop();
		std::cout << "Vertex [ " << s << " ] is visited\n";
		auto edges = this->adjacencyList[s];
		for(auto w : edges)
		{
			if(!v_discovery[w])
			{
				v_discovery[w] = true;
				vQ.push(w);
			}
		}
	}

}

template <class T>
unsigned long Graph<T>::find_ShortestPath(T s, T const &d)
{
	if(this->adjacencyList.find(s) == this->adjacencyList.end())
	{
		std::cout << "Not valid vertex [ " << s <<" ]\n";
		return -1;
	}

	if(this->adjacencyList.find(d) == this->adjacencyList.end())
	{
		std::cout << "Not valid vertex [ " << d <<" ]\n";
		return -1;
	}

	if(s == d)
	{
		std::cout << "Source: " << s << " ,Destination: " << d << "\n";
		std::cout << "Distance = " << 0 << "\n";
		std::cout << "Path: " << s;
		return 0;
	}


	std::map<T,bool> v_discovery;
	std::map<T,unsigned long> distance;
	std::map<T,T> predecessor_vertex;
	T src_vertex = s;
	for(auto v : this->adjacencyList)
	{
		v_discovery[v.first] = false;
		distance[v.first] = -1; // very big
	}

	std::queue<T> vQ;

	v_discovery[s] = true;
	distance[s] = 0;
	vQ.push(s);

	while(!vQ.empty())
	{
		s = vQ.front();
		vQ.pop();
		auto edges = this->adjacencyList[s];
		for(auto w : edges)
		{
			if(!v_discovery[w])
			{
				v_discovery[w] = true;
				distance[w] = distance[s] + 1;
				predecessor_vertex[w] = s;
				vQ.push(w);
				if(w == d) // we stop when find the destination
				{
					while(!vQ.empty())
						vQ.pop();
					break;
				}
			}
		}
	}


	std::cout << "Source: " << src_vertex << " ,Destination: " << d << "\n";
	std::cout << "Distance = " << distance[d] << "\n";
	std::cout << "Path: ";

	std::list<T>path;
	T v = d;

	path.push_front(v);
	while(v != src_vertex)
	{
		path.push_front(predecessor_vertex[v]);
		v = path.front();
	}

	for(auto v : path)
		std::cout << v << " ";
	std::cout << "\n";

	// Distance(d) = i (i.e d is in i_th layer, shortest #edges from s to d).
	return distance[d];
}

template <class T>
std::list<Graph<T>> Graph<T>::getConnectedComponents(void)
{
	std::map<T,bool> v_discovery;
	for(auto v : this->adjacencyList)
		v_discovery[v.first] = false;

	std::queue<T> vQ;
	T s;
	std::list<Graph<T>> connectedComponents;
	std::shared_ptr<Graph<T>>G_Component;

	for(auto v : this->adjacencyList)
	{
		s = v.first;

		if(!v_discovery[s])
		{
			G_Component = std::make_shared<Graph<T>>();
			v_discovery[s] = true;
			vQ.push(s);
			while(!vQ.empty())
			{
				s = vQ.front();
				vQ.pop();
				std::cout << "Vertex [ " << s << " ] is visited\n";
				auto edges = this->adjacencyList[s];
				for(auto w : edges)
				{
					G_Component->addEdge(s,w);
					if(!v_discovery[w])
					{
						v_discovery[w] = true;
						vQ.push(w);
					}
				}
			}
			connectedComponents.push_back(*G_Component);
		}
	}

	return connectedComponents;
}

template <class T>
Graph<T>::Graph () {
}

template <class T>
Graph<T>::~Graph() {
}

#endif /* GRAPH_H_ */
