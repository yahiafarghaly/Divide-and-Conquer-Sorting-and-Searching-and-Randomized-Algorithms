//============================================================================
// Name        : Normal_MergeSort.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;



void mergeSort(int in_arr[],int first_idx,int last_idx);
void show_array(int* arr, int n);

int main() {

	int a[100000] = { 0 };
	int sz = 0;
	std::fstream in_file("./src/IntegerArray.txt", std::ios_base::in);

	while(in_file >> a[sz])
	{
		++sz;
	}
	cout << "The read size is = " << sz << endl;

	mergeSort(a,0,sz - 1);
	show_array(a,sz);
	return 0;
}


void merge_sorted_arrays(
		int in_arr[],
		int f_idx,
		int m_idx,
		int e_idx)
{
	int i,j,k;
	int arr_sorted [e_idx - f_idx + 1] = { 0 };
	i = f_idx;
	j = m_idx + 1;
	k = 0; // idx of arr_sorted.

	while(i <= m_idx && j <= e_idx)
	{
		if(in_arr[i] <= in_arr[j])
		{
				arr_sorted[k] = in_arr[i];
				++i;
		}
		else
		{
				arr_sorted[k] = in_arr[j];
				++j;
		}
		++k;
	}

	// Append any left elements in any of the halves.
	while(i <= m_idx)
	{
			arr_sorted[k] = in_arr[i];
			++k;
			++i;
	}

	while(j <= e_idx)
	{
			arr_sorted[k] = in_arr[j];
			++k;
			++j;
	}

    //copy the merged temporary array to the original array
    for(k = 0, i = f_idx; i <= e_idx; ++i, ++k)
        	in_arr[i] = arr_sorted[k];

}

void mergeSort(
		int in_arr[],
		int first_idx,
		int last_idx
		)
{

	if(last_idx == first_idx)
		return; // 0 or 1 element ==> consider it sorted.

	int mid_idx = (last_idx + first_idx) >> 1;
	mergeSort(in_arr,first_idx,mid_idx); // left
	mergeSort(in_arr,mid_idx + 1, last_idx); // right

	merge_sorted_arrays(in_arr,first_idx,mid_idx,last_idx);

}


void show_array(int* arr, int n)
{
	cout << "{ ";
	for(int i = 0; i < n; ++i)
	{
		cout << arr[i];
		if(i != n - 1)
			cout << ", ";
	}
	std::cout << " }";
	std::cout << " ==> n = " << "[ " << n << " ]" << endl;
}
