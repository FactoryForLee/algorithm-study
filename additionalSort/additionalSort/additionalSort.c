#include "util.h"
#define MAX_NUM 100// 원소값이 10000을 넘지 않음
#define MAX_SIZE 101

// =================== 기수 정렬 ===================

typedef struct _queue {
	int head;
	int tail;
	int data[SIZE];
}QUEUE;

int isEmptyQueue(QUEUE* q)
{
	if (q->head == q->tail) return -1;
	else return 0;
}

void enQueue(QUEUE* q, int num)
{
	q->data[q->head++] = num;
	q->head = q->head % SIZE;
}

int deQueue(QUEUE* q)
{
	int num;
	if (!isEmptyQueue(q)) num = q->data[q->tail++];
	else return -1;
	q->tail = q->tail % SIZE;
	return num;
}

int initQueue(QUEUE* q)
{
	q->head = q->tail = 0;
	for (int i = 0; i < SIZE; i++)
	{
		q->data[i] = 0;
	}
}

void initBuckets(QUEUE* q, int k)
{// k번째 자리수에 해당하는 0번 큐부터
	// 9번 큐까지 초기화
	for (int i = 0; i < k; i++)
	{
		initQueue(&q[i]);
	}
}

void sorting(int A[], int n, int k)
{
	QUEUE buckets[10];// 0~9 출현 큐
	int j = 1;
	int position;
	initBuckets(buckets, 10);// 큐 초기화 함수호출
	for (int i = 1; i <= n; i++)
	{
		position = (A[i] / (int)pow(10, k - 1)) % 10;
		// 0~9번 큐 중 어느 큐에 넣을 것인가?
		// k번째 자리 값이 몇인가를 추출
		// ex) k=2인 경우 4321/10 % 10 = 2

		enQueue(&buckets[position], A[i]);
		// position 해당 자리에 큐 넣기
	}
	for (int i = 0; i < 10; i++)
	{// 재정렬 0번큐부터 꺼내오기
		int num;
		while ((num = deQueue(&buckets[i])) != -1) A[j++] = num;
	}
}

void radixSort(int A[], int n, int k)
{// 자리수별로 배열놓고 십진수별로 다 때려박는 알고리즘
	// k = 자리수
	// n = (데이터 개수)
	for (int i = 1; i <= k; i++)
	{
		sorting(A, n, i);
	}
}

// =================== 기수 정렬 ===================



// =================== 계수 정렬 ===================

void countingSort(int A[], int B[], int n)
{
	int C[MAX_SIZE] = { 0, };// 카운팅할 배열
	for (int j = 1; j <= n; j++)// 숫자 카운팅
	{
		C[A[j]]++;
	}
	for (int i = 2; i <= MAX_NUM; i++)// 카운팅 배열 누적합 계산
	{
		C[i] = C[i] + C[i - 1];
	}

	for (int j = n; j >= 1; j--)//카운팅 배열 참조해서 B배열에 정렬
	{
		B[C[A[j]]] = A[j];
		C[A[j]]--;
	}
}

// =================== 계수 정렬 ===================


int main(void) 
{
	int start, end;
	int array[MAX_SIZE];
	int sortedArray[MAX_SIZE] = { 0, };
	makeRandom(array, MAX_SIZE - 1);
	start = clock();
	countingSort(array, sortedArray, MAX_SIZE - 1);
	end = clock();
	printArray(sortedArray, MAX_SIZE - 1);

	/*
	int array[SIZE];
	makeRandom(array, SIZE - 1);
	printArray(array, SIZE - 1);

	start = clock();
	radixSort(array, SIZE - 1, 4);
	printArray(array, SIZE - 1);
	end = clock();
	*/
	printf("Seconds = %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}