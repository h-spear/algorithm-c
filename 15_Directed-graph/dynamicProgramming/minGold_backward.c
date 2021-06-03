#include <stdio.h>
#include <stdlib.h>

#define N 8
#define INF 100000000

int A[N][N] = {
	{ 1, 3, 7, 2,11,17,16,25},
	{ 6, 2, 3, 4, 7, 2,12,15},
	{11, 4, 6, 8, 8, 1, 9,14},
	{20, 8, 8,11, 6, 3, 3, 9},
	{ 0,10, 9, 8, 7,15,17,22},
	{17,12, 7,10, 3, 1, 8,13},
	{19,25,10,15,14,11, 3, 3},
	{21,18,16,20,15,13,19, 0} };

void print(int arr[][N], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%2d ", arr[i][j]);
		printf("\n");
	}
	printf("\n");
}

int m(int i, int j, int n)
{
	if ((i == n - 1) && (j == n - 1))
		return A[n - 1][n - 1];

	int minright = INF, mindown = INF;
	int cost;
	for (int k = j + 1; k < n; k++)
	{
		cost = A[i][j] + m(i, k, n);
		minright = min(minright, cost);
	}

	for (int k = i + 1; k < n; k++)
	{
		cost = A[i][j] + m(k, j, n);
		mindown = min(mindown, cost);
	}
	return min(minright, mindown);
}

int minGold(int arr[][N], int n)
{
	return m(0, 0, n);
}

int main()
{
	print(A, N);
	printf("%d\n", minGold(A, N));
	return 0;
}