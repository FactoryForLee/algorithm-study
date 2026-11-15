#include "hashtable.h"

extern int collision_count;

int main()
{
	int key = 0;
	int address = 0;
	int* table;
	int n = 0;
	double lf = 0;

	srand(time(NULL));

	// lf < LF일때까지 계속 Insert
	table = createTable(HASH);
	while (lf < LF) {
		key = rand() + 1;
		address = hashInsert(table, key);
		if (address != -1)
			n++;
		lf = (double)n / HASH;
		printf("Address: %2d, Key: %10d\n", address, key);
	}
	printTable(table, HASH);
	printf("total collision: %d\n", collision_count);

	free(table);

	return 0;
}