#include "hashtable.h"

int collision_count = 0;// 충돌 횟수

int* createTable(int m) {
	int* htable = (int*)calloc(m, sizeof(int));
	return htable;
}

void printTable(int table[], int m) {
	for (int i = 0; i < m; i++)
		printf("key[%2d] : %d\n", i, table[i]);
}

int hashInsert(int table[], int key)
{
	int i = 0;
	int address;

	do {
		// ------ 해시 함수들 ------

		// 1. (1차원)선형 조사
		//address = (key + i) % HASH;
		// 2. 이차원 조사
		//address = (key + (i * i)) % HASH;
		// 3. 더블 해싱
		address = (key + i * (1 + (key % HASH_PRIME))) % HASH;

		// ------ 해시 함수들 ------

		if (table[address] == 0) {// 0이 빈 상태인 것 같음
			table[address] = key;
			return address;
		}
		else {// 충돌일 때
			i++;
			collision_count++;
			printf(">>>>>>>collision: key - %d, address - %d\n", key, address);
		}

	} while (i < HASH);
	printf("overflow\n");
	return -1;
}