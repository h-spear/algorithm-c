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
int m[N][N];

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

int minGold()
{
	int i, j, k;
	int minright, mindown;
	int cost;

	m[0][0] = A[0][0];
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (i == 0 && j == 0)
				continue;

			minright = INF;
			for (k = j - 1; k >= 0; k--)
			{
				cost = m[i][k] + A[i][j];
				minright = min(minright, cost);
			}

			mindown = INF;
			for (k = i - 1; k >= 0; k--)
			{
				cost = m[k][j] + A[i][j];
				mindown = min(mindown, cost);
			}
			m[i][j] = min(minright, mindown);
		}
	}
	return m[N - 1][N - 1];
}

int main()
{
	print(A, N);
	printf("%d\n", minGold());
	return 0;
}