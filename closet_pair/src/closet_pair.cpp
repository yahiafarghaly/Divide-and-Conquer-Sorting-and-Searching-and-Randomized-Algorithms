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
#include <numeric>

// A structure to represent a Point in 2D plane
struct Point
{
    int x, y;
    friend std::ostream &operator<<( std::ostream &output, const Point &P ) {
             output << "(" << P.x << ", " << P.y << ")";
             return output;
          }
};

inline float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

inline float dist(std::pair<Point,Point> p)
{
    return sqrt( (p.first.x - p.second.x)*(p.first.x - p.second.x) +
                 (p.first.y - p.second.y)*(p.first.y - p.second.y)
               );
}

std::pair <Point,Point> closet_pair_BF(std::vector<Point> points);
std::pair <Point,Point> closet_pair_divide_and_conquer(std::vector<Point> points);

int main() {

	std::vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4},{5,8},{0,0}};
	auto closetPair = closet_pair_BF(points);

	std::cout << "Closet Points(BF) are: \n" << "P1: ( " << closetPair.first.x << ", " << closetPair.first.y << " )" << "\n";
	std::cout << "P2: ( " << closetPair.second.x << ", " << closetPair.second.y << " )" << "\n";

	std::cout << " -------------- \n\n";
	closetPair = closet_pair_divide_and_conquer(points);

	std::cout << "Closet Points(Divide And Conquer) are: \n" << "P1: ( " << closetPair.first.x << ", " << closetPair.first.y << " )" << "\n";
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
				//std::cout << min_dist << std::endl;
			}
		}

	return closet_pair;
}


struct comparatorX
{
    bool operator () (Point p1, Point p2) const { return p1.x < p2.x; }
};

struct comparatorY
{
    bool operator () (Point p1, Point p2) const { return p1.y < p2.y; }
};

std::pair <Point,Point> closet_pair(std::vector<Point> Px, std::vector<Point> Py);
std::pair <Point,Point>* closet_split_pair(std::vector<Point> Px, std::vector<Point> Py,float delta);

std::pair <Point,Point> closet_pair_divide_and_conquer(std::vector<Point> points)
{
	if(points.size() <= 3 )
		return closet_pair_BF(points);

	std::vector<Point> Px(points); // Sorted version of points by x-coordinates.
	std::vector<Point> Py(points); // Sorted version of points by y-coordinates.

	std::stable_sort(Px.begin(),Px.end(),comparatorX()); // Usually sort in nlog(n)
	std::stable_sort(Py.begin(),Py.end(),comparatorY());

	return closet_pair(Px,Py);
}


std::pair <Point,Point> closet_pair(std::vector<Point> Px, std::vector<Point> Py)
{
	if(Px.size() <= 3) // Base Case
		return closet_pair_BF(Px);

	std::pair <Point,Point> left_closet_pair,right_closet_pair,*split_pair;
	split_pair = nullptr; // since C++ cannot have a null pair object, so i created a pointer to a pair

	std::vector<Point>Qx(Px.begin(),Px.begin() + Px.size()/2);
	std::vector<Point>Qy(Py.begin(),Py.begin() + Py.size()/2);
	std::vector<Point>Rx(Px.begin() + Px.size()/2, Px.end());
	std::vector<Point>Ry(Py.begin() + Py.size()/2, Py.end());

	left_closet_pair = closet_pair(Qx,Qy);
	right_closet_pair = closet_pair(Rx,Ry);

	float delta = std::min(dist(left_closet_pair),dist(right_closet_pair)); // min distance of R or Q

	split_pair = closet_split_pair(Px,Py,delta); // The unlucky case

	float delta_left,delta_right;

	delta_left = dist(left_closet_pair);
	delta_right = dist(right_closet_pair);

	if(split_pair != nullptr)
		return *split_pair;
	else // no split pair is less than left or right pair
	{
		if(delta_left < delta_right)
			return left_closet_pair;
		else
			return right_closet_pair;
	}
}

std::pair <Point,Point>* closet_split_pair(std::vector<Point> Px, std::vector<Point> Py,float delta)
{
	std::pair <Point,Point> *split_pair = nullptr;

	float x_bar = 0.0; // hold mean of x' values.
	for(Point p : Px)
		x_bar += p.x;
	x_bar = x_bar/Px.size();

	std::vector<Point> Sy; // points within range [ x_bar - delta ,x_bar + delta],sorted by y cordinates.

	for(auto py : Py)
		if (std::abs(py.x - x_bar) <= delta)
			Sy.push_back(py);

	for(size_t i = 0; i < Sy.size(); ++i)
	{
		for(int j = i+1; j < std::min(7,(int)Sy.size()); ++j)
		{
			if(dist(std::make_pair(Sy[i],Sy[j])) < delta)
			{
				delta = dist(std::make_pair(Sy[i],Sy[j]));
				split_pair = new std::pair <Point,Point>(std::make_pair(Sy[i],Sy[j]));
			}
		}
	}

	return split_pair;
}
