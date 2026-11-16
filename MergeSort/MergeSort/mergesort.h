#ifndef _MERGESORT_H
#define _MERGESORT_H

int tmp[SIZE] = { 0, };// util헤더 파일에 SIZE를 선언하였습니다.
void merge(int A[], int p, int q, int r);

/// <summary>
/// merge sort implementation
/// </summary>
/// <param name="A">정렬할 배열</param>
/// <param name="p">배열의 시작</param>
/// <param name="r">배열의 끝</param>
void mergeSort(int A[], int p, int r)
{
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

void merge(int A[], int p, int q, int r)
{
	int i = p;
	int j = q + 1;
	int t = 0;
	while (i <= q && j <= r) {// 작은 놈은 index가 ++됨
		if (A[i] <= A[j]) tmp[t++] = A[i++];
		else tmp[t++] = A[j++];
	}

	while (i <= q) tmp[t++] = A[i++];
	while (j <= r) tmp[t++] = A[j++];
	i = p;
	t = 0;
	while (i <= r)A[i++] = tmp[t++];
}

#endif // !_MERGESORT_H
