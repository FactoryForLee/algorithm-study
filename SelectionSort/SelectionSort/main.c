#include "selectionSort.h"
#include "util.h"
#define SIZE 101

// selection sort implementation
// 책의 설명을 그대로 따라가기 위해 1부터

int main()
{
	int array[SIZE] = { 0, };
	makeRandom(array, SIZE);
	printArray(array, SIZE);

	selectionSort(array, SIZE);
	printArray(array, SIZE);

	return 0;
}