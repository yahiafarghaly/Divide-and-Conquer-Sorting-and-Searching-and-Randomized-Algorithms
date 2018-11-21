//============================================================================
// Name        : Normal_MergeSort.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void mergeSort(
		int unsorted_arr[],
		int arr_size,
		int out_sorted_arr[]);

void merge_sorted_arrays(
		int sorted_arr_1[],
		int sorted_arr_2[],
		int merged_sorted_arr[],
		int arr_size);

void show_array(int* arr, int n);

int main() {

	int a[] = {4,3,2,1};
	int b[4] = {0};

	mergeSort(a,4,b);
	show_array(b,4);
	return 0;
}

/*
 * Input: `sorted_arr_1` & `sorted_arr_2` must have the same size which is equal to `arr_size`/2
 * Output: `merged_sorted_arr` of size `arr_size`
 * */
void merge_sorted_arrays(
		int sorted_arr_1[],
		int sorted_arr_2[],
		int merged_sorted_arr[],
		int arr_size)
{
	int i,j,k;
	i = j = 0;
	for(k = 0; k < arr_size; ++k)
	{
		if(sorted_arr_1[i] <= sorted_arr_2[j] && i < arr_size/2)
		{
			merged_sorted_arr[k] = sorted_arr_1[i];
				++i;
		}
		else if (sorted_arr_1[i] > sorted_arr_2[j] && j < arr_size/2)
		{
			merged_sorted_arr[k] = sorted_arr_2[j];
				++j;
		}
	}

	// Append any left elements in any of the sorted arrays.
	if(i < arr_size/2)
	{
		for(k = i + arr_size/2; k < arr_size; ++k,++i)
			merged_sorted_arr[k] = sorted_arr_1[i];
	}

	if(j < arr_size/2)
	{
		for(k = j + arr_size/2; k < arr_size; ++k,++j)
			merged_sorted_arr[k] = sorted_arr_2[j];
	}
}

void split_merge(int unsorted_arr[],
		int* begin_iter,
		int* end_iter,
		int arr_size,
		int sorted_arr[])
{
	if(arr_size == 1)
		return; // consider it sorted.

	int* middle_iter;
	middle_iter = begin_iter + arr_size/2 - 1; // refer to the end of the left halve.
	split_merge(unsorted_arr,begin_iter,middle_iter,arr_size/2,sorted_arr); // left branch.
	split_merge(unsorted_arr,middle_iter + 1,end_iter,arr_size/2,sorted_arr); // right branch

	merge_sorted_arrays(begin_iter,middle_iter + 1,sorted_arr,arr_size);
}

void mergeSort(
		int unsorted_arr[],
		int arr_size,
		int out_sorted_arr[])
{

	split_merge(unsorted_arr,
			&unsorted_arr[0],
			&unsorted_arr[arr_size - 1],
			arr_size,
			out_sorted_arr);
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
