#include "util.h"

void bubbleSort(int A[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (A[j] > A[j + 1])
				swap(&A[j], &A[j + 1]);
		}
	}
}

int main()
{
	int array[SIZE] = { 0, };
	makeRandom(array, SIZE);
	bubbleSort(array, SIZE);
	printArray(array, SIZE);

	return 0;
}