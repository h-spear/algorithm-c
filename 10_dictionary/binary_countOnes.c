#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int A[N][N];

// O(n^2)
int countOnesButSlow(int  A[][N], int n)
{
	int c = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (A[i][j] == 1)
				c++;
	return c;
}

int countOnesInRow(int A[], int left, int right)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (A[mid] == 1)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return left;
}

// O(nlogn)
int countOnes(int A[][N], int n)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		count += countOnesInRow(A[i], 0, n - 1);
	}
	return count;
}

void printMatrix(int A[][N], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
}

int main()
{
	int n;
	scanf_s("%d", &n);
	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < rand() % n; j++)
			A[i][j] = 1;
	}
	printMatrix(A, n);
	printf("%d\n", countOnes(A, n));
	printf("%d\n", countOnesButSlow(A, n));
	return 0;
}