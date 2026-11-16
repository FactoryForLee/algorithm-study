#ifndef _SELECTIONSORT_H
#define _SELECTIONSORT_H
#include "util.h"

int theLargest(int A[], int last)
{
	int largest = 0;

	for (int i = 1; i <= last; i++)
	{
		if (A[i] > A[largest])
		{
			largest = i;
		}
	}

	return largest;
}

void selectionSort(int A[], int length) {
	for (int i = length - 1; i > 0; i--) // n - 1 번 반복
	{
		int largestIndex = theLargest(A, i);// i번 비교
		swap(&A[i], &A[largestIndex]);// 상수 시간 교환 1번
	}
}
#endif // !_SELECTIONSORT_H
