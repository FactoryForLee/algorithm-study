#ifndef _UTIL_H
#define _UTIL_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define SIZE 3001
/// index 0부터 시작으로 변경!

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void makeRandom(int array[], int len) {
	srand(time(NULL));
	for (int i = 1; i <= len; i++)
	{
		array[i] = (rand() % 100) + 1;//10000 => 100로 수정 (1 ~ 100)
	}
}

void printArray(int array[], int len) {
	printf("=========== size: %d ===========\n", len);
	for (int i = 1; i <= len; i++)
	{
		printf("%4d", array[i]);
		if (i % 20 == 0) printf("\n");
		else printf(", ");
	}

	printf("================================\n");
}

#endif // !_UTIL_H
