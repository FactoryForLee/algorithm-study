#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int matrix[5][5] = {
	{0,0,0,0,0},
	{0,6,7,12,5},
	{0,5,3,11,18},
	{0,7,17,3,3},
	{0,8,10,14,9},
};

// 경로 데이터 저장
int path[5][5] = { 0, };

void printArray(int n) {
	printf("MATRIX: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("PATH: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%2d ", path[i][j]);
		}
		printf("\n");
	}
}

/// <summary>
/// 동적 프로그래밍 알고리즘 | 오른쪽, 아래만 움직이는 버전
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
/*
int matrixPath(int n)
{
	// path구하는 건 n=4로 놓는다

	// 0번째 방들 세팅
	for (int i = 0; i <= n; i++)
	{
		path[i][0] = 0;
	}

	for (int j = 1; j <= n; j++)
	{
		path[0][j] = 0;
	}
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			path[i][j] = matrix[i][j] + MAX(path[i - 1][j], path[i][j - 1]);
		}
	}

	// (n,n)이 가장 큰 값
	return path[n][n];
}
*/

/// <summary>
/// 동적 프로그래밍 알고리즘 | 오른쪽, 아래, 대각선만 움직이는 버전
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
int matrixPath(int n)
{
	// path구하는 건 n=4로 놓는다

	// 0번째 방들 세팅
	for (int i = 0; i <= n; i++)
	{
		path[i][0] = 0;
	}

	for (int j = 1; j <= n; j++)
	{
		path[0][j] = 0;
	}

	// 최대 점수 계산
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			path[i][j] = matrix[i][j] + MAX(MAX(path[i - 1][j], path[i][j - 1]), path[i-1][j-1]);
		}
	}

	// (n,n)이 가장 큰 값
	return path[n][n];
}

int main()
{
	int result;
	result = matrixPath(4);
	printf("result = %d\n", result);

	printArray(5);

	return 0;
}