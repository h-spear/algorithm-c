#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

typedef struct {
	float elem;
	int idx;
}Dict;

int findElement(Dict D[], float key)
{
	int mid;
	int left = 0, right = SIZE - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (key == D[mid].elem)
			return mid;
		else if (key < D[mid].elem)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

void findIndexPair(Dict D[], float A[], float s)
{
	int j;
	for (int i = 0; i < SIZE; i++)
	{
		float v = s - A[i];
		j = findElement(D, v);
		if (j != -1)
		{
			printf("(%d, %d)\n", i, j);
			return;
		}
	}
	if (j == -1)
		printf("Not Found\n");
}

void buildDict(Dict D[], float A[])
{
	for (int i = 0; i < SIZE; i++)
	{
		D[i].elem = A[i];
		D[i].idx = i;
	}
}

int main()
{
	float A[SIZE] = { 1,1,2,3,5,8,13,21 };
	Dict D[SIZE];

	for (int i = 0; i < SIZE; i++)
		printf("[%2.1f] ", A[i]);
	printf("\n\n");

	buildDict(D, A);
	for (int i = 0; i < SIZE; i++)
	{
		printf("(%2.1f, %d) ", D[i].elem, D[i].idx);
	}
	printf("\n\n");
	findIndexPair(D, A, 13);
	findIndexPair(D, A, 2);
	findIndexPair(D, A, 12);
	return 0;
}