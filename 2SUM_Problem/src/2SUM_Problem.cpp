//============================================================================
// Name        : 2SUM_Problem.cpp
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
#include <numeric>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <thread>



using namespace std;

using Time = std::chrono::steady_clock::time_point;

std::vector<int64_t> readInputData(std::string path);

int numberOfTarget_hash_unorderMap_with_threads(std::vector<int64_t>& numbers, std::vector<int64_t>& t);
int numberOfTarget_hash_unorderMap(std::vector<int64_t>& numbers, std::vector<int64_t>& t);


int main() {

	const string input_file = "./src/prob-2sum.txt";
	auto numbers = readInputData(input_file);
	std::vector<int64_t> t(20001);
	std::iota(t.begin(), t.end(), -10000);

	Time begin,end;
	auto numberOfTargets = 0;


	std::cout<< "unorder_map_sol_threads: \n";
	std::cout<< "Input File: " << input_file << "\n";
	begin = std::chrono::steady_clock::now();
	numberOfTargets =  numberOfTarget_hash_unorderMap_with_threads(numbers,t);
	end = std::chrono::steady_clock::now();
	std::cout << "Time = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " sec" <<std::endl;
	std::cout << numberOfTargets << std::endl;
	std::cout << "----------------------------\n";

	// std::cout<< "unorder_map_sol: \n";
	// begin = std::chrono::steady_clock::now();
	// numberOfTargets =  numberOfTarget_hash_unorderMap(numbers,t);
	// end = std::chrono::steady_clock::now();
	// std::cout << "Time = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " sec" <<std::endl;
	// std::cout << numberOfTargets << std::endl;
	// std::cout << "----------------------------\n";



	return 0;
}

int numberOfTarget_hash_unorderMap(std::vector<int64_t>& numbers, std::vector<int64_t>& t)
{
	unordered_map<int64_t,int> h;
	int noTargets = 0;

	for(auto num : numbers)
		h[num] += 1;

	auto findTarget = [&](int64_t const& t)->bool{
		for(auto x : numbers)
		{
			if(x != t - x)
			{
				auto it = h.find(t - x);
				if(it != h.end())
					return true;
			}
		}
		return false;
	};

	for(auto target : t)
	{
		if(findTarget(target))
			noTargets++;
	}

	return noTargets;
}

int numberOfTarget_hash_unorderMap_with_threads(std::vector<int64_t>& numbers, std::vector<int64_t>& t)
{
	unordered_map<int64_t,int> h;

	const size_t nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(nthreads);
    std::vector<long> 		numberOfTargets(nthreads,0);
    std::cout<<"Parallel ("<<nthreads<<" threads)"<<std::endl;


	for(auto num : numbers)
		h[num] += 1;

	auto findTarget = [&](int64_t const& t)->bool{
		for(auto x : numbers)
		{
			if(x != t - x)
			{
				auto it = h.find(t - x);
				if(it != h.end())
					return true;
			}
		}
		return false;
	};

	unsigned long target_idx = 0;
	unsigned long thread_idx = 0;

	while(target_idx < t.size())
	{
		while(thread_idx < nthreads)
		{
			threads[thread_idx] = std::thread([&](unsigned long const& threadIdx){
				if(findTarget(t[target_idx + threadIdx]))
					++numberOfTargets[threadIdx];
			},thread_idx);
			++thread_idx;
		}

		std::for_each(threads.begin(),threads.end(),[](std::thread& x){x.join();});
		target_idx += nthreads;
		thread_idx = 0;
	}

	return std::accumulate(numberOfTargets.begin(),numberOfTargets.end(),0);
}

std::vector<int64_t> readInputData(std::string path)
{

	std::fstream in_file(path, std::ios_base::in);

	string line;
	std::vector<int64_t> numbers;
	int64_t dummy;
	while(getline(in_file,line))
	{
		if(line.size() > 0)
		{
			stringstream stream(line);

				stream >> dummy;
				if (!stream)
					break;
				numbers.push_back(dummy);
		}
	}
	return numbers;
}

