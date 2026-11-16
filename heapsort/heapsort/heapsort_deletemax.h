#ifndef _HEAPSORT_DELETE_MAX_H
#define _HEAPSORT_DELETE_MAX_H
#include "util.h"

void percolateDown(int A[], int k, int n)
{
	int left = 2 * k + 1;// 0부터라서 자식 번호가 이렇게 됨
	int right = 2 * k + 2;

	if (left < n)
	{
		int child = left;

		if (right < n && A[right] > A[left])
			child = right;

		if (A[k] < A[child])// 더 큰 자식과 비교 자식 보다 작을 때
		{// 힙 위반
			swap(&A[k], &A[child]);
			percolateDown(A, child, n);// 내려간 자리에서 다시 스며내리기
		}
	}
}

void buildHeap(int A[], int n)
{
	for (int i = (n - 2) / 2; i >= 0; i--)
		percolateDown(A, i, n);
}

int deleteMax(int A[], int n)
{
	int max = A[0];

	A[0] = A[--n];
	percolateDown(A, 0, n);

	return max;
}

void heapSort(int A[], int n)
{
	buildHeap(A, n);
	//printArray(A, n); 구성 단계 버그 확인
	for (int i = n - 1; i > 0; i--)
	{
		// 개정 전 후 차이
		// 단지 swap의 시점 차이
		// 말단과 root를 교환하는 것 동일
		// 재구성시 정렬된 노드들을 제외하는 것도 동일

		A[i] = deleteMax(A, n--);
	}
}
#endif // !_HEAPSORT_DELETE_MAX_H
