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

void split_array(int arr[],int arr_size, int* out_left_halve,int* out_right_halve);
void show_array(int* arr, int n);

int main() {

	int a[] = {4,3,2,1,0,8,10,11};
	int b[4] = {0};

	mergeSort(a,8,b);
	show_array(b,8);
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

void split_array(int arr[],int arr_size, int* out_left_halve,int* out_right_halve)
{
	for(int i = 0; i < arr_size/2; i++)
		out_left_halve[i] = arr [i];
	for(int i = arr_size/2; i < arr_size; i++)
		out_right_halve [i - arr_size/2] = arr[i];
}


void mergeSort(
		int unsorted_arr[],
		int arr_size,
		int out_sorted_arr[])
{
	if(arr_size == 1)
	{
		out_sorted_arr[0] = unsorted_arr[0];
		return;
	}
	int left_arr [arr_size/2] = {0};
	int right_arr [arr_size/2] = {0};
	split_array(unsorted_arr,arr_size,&left_arr[0],&right_arr[0]);

	mergeSort(left_arr,arr_size/2,left_arr);
	mergeSort(right_arr,arr_size/2,right_arr);

	merge_sorted_arrays(left_arr,right_arr,out_sorted_arr,arr_size);
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
