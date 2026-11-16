#include "util.h"
//#include "heapsort_deletemax.h"

void buildHeap(int A[], int n)
{
	for (int i = (n - 2) / 2; i >= 0; i--)
		percolateDown(A, i, n);
}


int main()
{
	int array[SIZE] = { 0, };
	makeRandom(array, SIZE);
	//printArray(array, SIZE);
	heapSort(array, SIZE);
	printArray(array, SIZE);

	return 0;
}