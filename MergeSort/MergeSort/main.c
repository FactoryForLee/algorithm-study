#include "util.h"
#include "mergesort.h"

int main()
{
	int start, end;

	int array[SIZE] = { 0, };
	makeRandom(array, SIZE);
	start = clock();
	mergeSort(array, 0, SIZE - 1);
	end = clock();
	printArray(array, SIZE);
	printf("MS = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}