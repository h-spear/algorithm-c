#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

typedef struct {
	int elem;
	int idx;
}Dict;

void sort(Dict D[])
{
	int elem, i, j, idx;
	for (i = 1; i < SIZE; i++)
	{
		elem = D[i].elem;
		idx = D[i].idx;
		for (j = i - 1; j >= 0 && D[j].elem > elem; j--)
		{
			D[j + 1].elem = D[j].elem;
			D[j + 1].idx = D[j].idx;
		}
		D[j + 1].elem = elem;
		D[j + 1].idx = idx;
	}
}

int findElement(Dict D[], int key)
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

void findIndexPair(Dict D[], int A[], int s)
{
	int j;
	for (int i = 0; i < SIZE; i++)
	{
		int v = s - A[i];
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

void buildDict(Dict D[], int A[])
{
	for (int i = 0; i < SIZE; i++)
	{
		D[i].elem = A[i];
		D[i].idx = i;
	}
	sort(D);
}

int main()
{
	int A[SIZE] = { 2,21,8,3,5,1,13,1 };
	Dict D[SIZE];

	for (int i = 0; i < SIZE; i++)
		printf("%d ", A[i]);
	printf("\n\n");

	buildDict(D, A);
	for (int i = 0; i < SIZE; i++)
	{
		printf("(%d, %d) ", D[i].elem, D[i].idx);
	}
	printf("\n\n");
	findIndexPair(D, A, 13);
	return 0;
}