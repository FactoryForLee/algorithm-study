#include "util.h"
#include "mergesort.h"
#include "selectionsort.h"
#include "quicksort.h"
#include <string.h>

int main()
{
	clock_t start, end;

	int array[SIZE] = { 0, };
	int array2[SIZE] = { 0, };
	int array3[SIZE] = { 0, };
	makeRandom(array, SIZE);
	memcpy(array2, array, sizeof(int) * SIZE);
	memcpy(array3, array, sizeof(int) * SIZE);
	// makeRandom, printArray는 인덱스 0기준으로 변경하였습니다.
	start = clock();
	quickSort(array, 0, SIZE - 1);
	end = clock();
	printArray(array, SIZE);
	printf("quickSort SEC = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	mergeSort(array2, 0, SIZE - 1);
	end = clock();
	printf("mergeSort SEC = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	selectionSort(array3, SIZE);
	end = clock();
	printf("selectionSort SEC = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}