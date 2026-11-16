#ifndef _UTIL_H
#define _UTIL_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define SIZE 10

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void makeRandom(int array[], int len) {
	srand(time(NULL));
	for (int i = 0; i < len; i++)
	{
		array[i] = rand() % 10000;
	}
}

void printArray(int array[], int len) {
	printf("=========== size: %d ===========\n", len);
	for (int i = 0; i < len; i++)
	{
		printf("%4d", array[i]);
		if (i != 0 && i % 20 == 0) printf("\n");
		else printf(", ");
	}

	printf("\n================================\n");
}

#endif // !_UTIL_H
