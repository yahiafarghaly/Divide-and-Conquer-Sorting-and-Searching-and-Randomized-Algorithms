/*
 ============================================================================
 Name        : QuickSort.c
 Author      : YF
 Version     :
 Copyright   : Your copyright notice
 Description : QuickSort in C, Ansi-style
 ============================================================================
 */


#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void showArray(int A[],int sz)
{
	for(int i = 0; i < sz; ++i)
		printf("%d\n",A[i]);
	printf("\n");
}

void quickSort(int A[],int s_idx, int l_idx);

unsigned long long comparsion_cnt = 0;

void incr_comp_cnt(int s_idx, int l_idx)
{
	/*
	 * when there is a recursive call on a subarray of length m,
	 * you should simply add m−1 to your running total of comparisons.
	 *  */
	comparsion_cnt += ((l_idx - s_idx + 1) - 1);
}

int main(void) {

	int index = 8;

//	int A[] = {3,8,2,5,1,4,7,6};
	int A[100000] = { -1 };

	std::fstream in_file("./src/input_arrays/quick_sort_data.txt", std::ios_base::in);
	index = 0;
	while(in_file >> A[index])
	{
		++index;
	}
	cout << "The read size is = " << index << endl;


	quickSort(A,0,index - 1);
	showArray(A,index);

	cout << "Pivot Comparsion Count = " << comparsion_cnt << endl;
	return EXIT_SUCCESS;
}
// is B median of A and C
bool isMedian(int A,int B, int C)
{
	if(B >= A && B <= C)
		return true;
	if(B <= A && B >= C)
		return true;
	return false;
}
int median_idx(int A[],int s_idx, int l_idx)
{
	int sz = l_idx - s_idx + 1;
	int m_idx = 0;

	if(sz % 2 == 0)
		m_idx = sz/2 - 1 + s_idx; 	// even
	else
		m_idx = sz/2 + s_idx;		// odd

	if(isMedian(A[m_idx],A[s_idx],A[l_idx]))
		return s_idx;

	if(isMedian(A[s_idx],A[m_idx],A[l_idx]))
		return m_idx;

	if(isMedian(A[s_idx],A[l_idx],A[m_idx]))
		return l_idx;

	throw std::invalid_argument( "unknown median value" );
}

int choose_pivot(int A[],int s_idx, int l_idx)
{
	//return s_idx; // choose first element as a pivot.
	// return l_idx;  // choose final element as a pivot.
	return median_idx(A,s_idx,l_idx); // choose median element as a pivot.
}

void swap(int *p1, int *p2)
{
	int tmp  = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int partition_array(int A[],int s_idx, int l_idx,int p_idx)
{
	int pivot_element = A[p_idx];
	int i,j;
	i  = s_idx + 1;
	for(j = s_idx + 1; j <= l_idx; ++j)
	{
		if(A[j] < pivot_element)
		{
			swap(&A[j],&A[i]);
			++i;
		}
	}
	swap(&A[i - 1],&A[p_idx]);
	return i - 1;
}

void quickSort(int A[],int s_idx, int l_idx)
{
	if(l_idx == s_idx) // size of 1
		return;
	incr_comp_cnt(s_idx,l_idx);

	int pivot_idx = choose_pivot(A,s_idx,l_idx);

	swap(A[s_idx],A[pivot_idx]);
	pivot_idx = s_idx; // reset pivot idx

	pivot_idx = partition_array(A,s_idx,l_idx,pivot_idx);

	if(pivot_idx == s_idx)
		quickSort(A,s_idx,pivot_idx);
	else
		quickSort(A,s_idx,pivot_idx - 1);

	if(pivot_idx !=  l_idx)
		quickSort(A,pivot_idx + 1,l_idx);
}
