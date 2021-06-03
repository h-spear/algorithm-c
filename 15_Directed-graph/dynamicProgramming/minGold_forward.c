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

int m(int i, int j)
{
	if ((i == 0) && (j == 0))
		return A[0][0];
	int minright = INF, mindown = INF;
	int cost;
	for (int k = j - 1; k >= 0; k--)
	{
		cost = m(i, k) + A[i][j];
		minright = min(minright, cost);
	}

	for (int k = i - 1; k >= 0; k--)
	{
		cost = m(k, j) + A[i][j];
		mindown = min(mindown, cost);
	}
	return min(minright, mindown);
}

int minGold(int arr[][N], int n)
{
	return m(n - 1, n - 1);
}

int main()
{
	print(A, N);
	printf("%d\n", minGold(A, N));
	return 0;
}