//============================================================================
// Name        : MedianMaintanceUsingHeap.cpp
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
#include "heap.h"
#include <algorithm>
#include <numeric>
#include <stdlib.h>

using namespace std;

std::vector<int> readInputData(std::string const& file_path);
std::vector<int> medianMaintance_navie_impl(std::vector<int>const & input_vector);
std::vector<int> medianMaintance_heap_impl(std::vector<int>const & input_vector);

int main() {

	auto input_vector = readInputData("./src/Median.txt");
//	std::vector<int> input_vector = {5,2,3,4,1};
	input_vector.resize(36);

	auto m_navie = medianMaintance_navie_impl(input_vector);
	std::cout << "########################\n";
	auto m_heap = medianMaintance_heap_impl(input_vector);

	if(m_navie.size() != m_heap.size())
	{
		std::cout << "Not the same size !\n";
		std::cout << "N: " << m_navie.size() << "\n";
		std::cout << "H: " << m_heap.size() << "\n";
		return -1;
	}


	for(auto i = 0; i < m_navie.size(); i++)
	{
		if(m_navie[i] != m_heap[i])
		{
			printf("Not equal m[%d] , m_navie = %d, m_heap = %d\n",i+1,m_navie[i],m_heap[i]);
			std::cin.get();
		}
	}

	int sum = std::accumulate(m_heap.begin(),m_heap.end(), 0);
	std::cout << sum % 10000 << "\n";

	return 0;
}


std::vector<int> medianMaintance_heap_impl(std::vector<int>const & input_vector)
{
	std::vector<int> m; // medians
	MinHeap h_min(input_vector.size());
	MaxHeap h_max(input_vector.size());


	int current_median = 0;

	for(auto x : input_vector)
	{
		// insert current int inside one of heaps.
		if(x < current_median)
			h_max.insert(x);
		else
			h_min.insert(x);

		// make sure that the size difference is at most 1.
		if(abs((int)h_max.size() - (int)h_min.size()) > 1 )
		{
			if(h_max.size() > h_min.size())
			{
				auto key = h_max.extractTop();
				h_min.insert(key);
			}
			else
			{
				auto key = h_min.extractTop();
				h_max.insert(key);
			}
		}

		// choose the median.
		if(h_max.size() == h_min.size())
			current_median = std::min(h_max.getTop(),h_min.getTop());
		else
		{
			if(h_max.size() >  h_min.size())
				current_median = h_max.getTop();
			else
				current_median = h_min.getTop();
		}

		std::cout << "x = " << x << "\n";
		std::cout << "h_max: \n";
		h_max.show();
		std::cout << "h_min: \n";
		h_min.show();
		std::cout << " m = " << current_median << "\n";
		std::cout << "######################\n";
		m.push_back(current_median);
	}

	return m;
}

std::vector<int> medianMaintance_navie_impl(std::vector<int>const &  input_vector)
{
	std::vector<int> running_ints;
	std::vector<int> m; // medians

	for(auto x : input_vector)
	{
		running_ints.push_back(x);
		std::sort(running_ints.begin(),running_ints.end());
		auto median_idx = (running_ints.size() % 2) ? (running_ints.size() + 1)/2 : running_ints.size()/2;
		m.push_back(running_ints[median_idx - 1]);
	}
	return m;
}



std::vector<int> readInputData(std::string const& file_path)
{
	std::fstream in_file(file_path, std::ios_base::in);
	std::string text_line;
	int num;
	std::vector<int> c;

	while(getline(in_file,text_line))
	{
		if(text_line.size() > 0)
		{
			std::stringstream stream(text_line);
			stream >> num;
			c.push_back(num);
		}
	}
	return c;
}
