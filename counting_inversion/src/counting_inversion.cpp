//============================================================================
// Name        : counting_inversion.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

unsigned long sort_and_count_inversion(int in_arr[], int f_idx, int l_idx);
unsigned long merge_and_CountSplitInv(
		int in_arr[],
		int f_idx,
		int m_idx,
		int e_idx);

int main() {

	int input_array[100000] = { -1 };
	int index = 0;

	std::fstream in_file("./src/input_arrays/IntegerArray.txt", std::ios_base::in);

	while(in_file >> input_array[index])
	{
		++index;
	}
	cout << "The read size is = " << index << endl;
	cout << "The number of inversion = " << sort_and_count_inversion(input_array,0,index - 1) << endl;


//	for(int i = 0; i < index; ++i)
//		std::cout << input_array[i] << endl;


	return 0;
}

/*
 * it counts based on Piggybacking on Merge Sort
 * */
unsigned long sort_and_count_inversion(int in_arr[], int f_idx, int l_idx)
{
	if(l_idx == f_idx)
		return 0;

	int m_idx = (l_idx + f_idx) >> 1;

	unsigned long x = sort_and_count_inversion(in_arr,f_idx,m_idx);
	unsigned long y = sort_and_count_inversion(in_arr,m_idx + 1, l_idx);
	unsigned long z = merge_and_CountSplitInv(in_arr,f_idx,m_idx,l_idx);

	return x + y + z;
}

unsigned long merge_and_CountSplitInv(
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
	unsigned long split_conversion_cnt = 0;

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
				split_conversion_cnt += (m_idx - i + 1);
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

    return split_conversion_cnt;
}
