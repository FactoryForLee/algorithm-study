#include <stdio.h>
#define LENGTH 8
#define START 0
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
enum PATTERN { P1, P2, P3, P4 };

int w[3][LENGTH] = {
	{6,7,12,-5,5,3,11,3},
	{-8,10,14,9,7,13,8,5},
	{11,12,7,4,8,-2,9,4}
};
int peb[4][LENGTH] = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

void printPebble(int n) {
	for (int i = P1; i <= P4; i++)
	{
		printf("P%d: ", i + 1);
		for (int j = START; j <= n; j++)
		{
			if (i != P4) printf("%4d(%2d)", peb[i][j], w[i][j]);
			else		 printf("%4d(%2d)", peb[i][j], w[P1][j] + w[P3][j]);
		}
		printf("\n");
	}
}

int MaxPattern(int n)
{
	int maxIndex = 0;

	for (int i = P1; i <= P4; i++)
	{
		if (peb[i][n] > peb[maxIndex][n])
		{
			maxIndex = i;
		}
	}

	return maxIndex;
}

int pebble(int n) {
	// 초기화(첫 열)
	for (int i = P1; i <= P4; i++)
	{
		if (i != P4) peb[i][START] = w[i][START];
		else		 peb[i][START] = w[P1][START] + w[P3][START];
	}

	for (int i = START + 1; i <= n; i++) {
		peb[P1][i] = w[P1][i] + MAX(peb[P2][i - 1], peb[P3][i - 1]);
		peb[P2][i] = w[P2][i] + MAX(MAX(peb[P1][i - 1], peb[P3][i - 1]), peb[P4][i - 1]);
		peb[P3][i] = w[P3][i] + MAX(peb[P2][i - 1], peb[P1][i - 1]);
		peb[P4][i] = w[P1][i] + w[P3][i] + peb[P2][i - 1];
	}

	return MaxPattern(n);
}

int main()
{
	int maxIndex = pebble(LENGTH - 1);
	printf("%d\n", peb[maxIndex][LENGTH - 1]);
	printPebble(LENGTH - 1);
	return 0;
}