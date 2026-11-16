#include "util.h"
#define SIZE 101

void insertionSort(int A[], int length) {
	int loc = 0;

	for (int i = 1; i < length; i++)
	{
		int newItem = A[i];
		loc = i - 1;

		while (loc >= 0 && newItem < A[loc]) {
			// 정렬된 배열에서 newItem보다 작거나 같은 요소 찾기
			// 찾기전까진 loc를 밀어내기
			A[loc + 1] = A[loc];
			loc--;
		}


		A[loc + 1] = newItem;
	}
}

int main()
{
	int array[SIZE] = { 0, };
	makeRandom(array, SIZE);
	insertionSort(array, SIZE);
	printArray(array, SIZE);
	return 0;
}