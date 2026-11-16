#ifndef _QUICKSORT_H
#define _QUICKSORT_H
#include "util.h"

int partition(int A[], int p, int r)
{
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++)// 이 구역 전부 훑기
	{
		if (A[j] < x)
			swap(&A[j], &A[++i]);
	}

	swap(&A[++i], &A[r]);// 피벗 교환

	return i;
}

void quickSort(int A[], int p, int r)// p = 0, r = 10
{
	if (p < r)
	{
		int q = partition(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}
#endif // !_QUICKSORT_H
