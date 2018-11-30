//============================================================================
// Name        : closet_pair.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>


// A structure to represent a Point in 2D plane
struct Point
{
    int x, y;
};

inline float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

std::pair <Point,Point>  closet_pair_BF(std::vector<Point> points);

int main() {

	std::vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
	auto closetPair = closet_pair_BF(points);

	std::cout << "Closet Points are: \n" << "P1: ( " << closetPair.first.x << ", " << closetPair.first.y << " )" << "\n";
	std::cout << "P2: ( " << closetPair.second.x << ", " << closetPair.second.y << " )" << "\n";

	return 0;
}


std::pair <Point,Point> closet_pair_BF(std::vector<Point> points)
{

	std::pair <Point,Point> closet_pair;
	float min_dist = std::numeric_limits<float>::max();
	int n_points = points.size();

	for(int i = 0; i < n_points; ++i)
		for(int j = i + 1; j < n_points; ++j)
		{
			if(dist(points[i],points[j]) < min_dist)
			{
				min_dist = dist(points[i],points[j]);
				closet_pair.first = points[i];
				closet_pair.second = points[j];
				std::cout << min_dist << std::endl;
			}
		}

	return closet_pair;
}
