#include <stdio.h>
#define N 5

void printMatrix(int A[][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%3d ", A[i][j]);
		printf("\n");
	}
	printf("\n");
}

int findRow(int A[], int x)
{
	for (int i = 0; i < N; i++)
		if (A[i] == x)
			return i;
	return -1;
}

void findMatrix(int A[][N], int x)
{
	int i;
	for (int r = 0; r < N; r++)
	{
		i = findRow(A[r], x);
		if (i >= 0)
		{
			printf("found at (%d,%d)\n", r, i);
			return;
		}
	}
	printf("not found\n");
	return;
}

int main()
{
	int A[N][N];
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] = 10 * i + j;

	printMatrix(A);
	findMatrix(A, 23);
	return 0;
}