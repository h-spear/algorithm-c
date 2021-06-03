#include <stdio.h>
#include <stdlib.h>

#define N 8
#define INF 100000000

int A[N][N] = {
	{1,4,1,1,0,0,0,5},
	{0,2,3,5,1,5,2,0},
	{1,4,0,2,0,1,0,4},
	{0,1,0,1,1,3,3,0},
	{6,0,3,1,0,0,2,2},
	{0,3,0,0,3,3,0,0},
	{2,5,0,0,1,1,3,3},
	{1,0,1,4,1,0,0,0} };
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

int collectCoin(int arr[][N], int n)
{
	int i, j;
	m[0][0] = A[0][0];

	for (i = 1; i < n; i++)
	{
		m[0][i] = m[0][i - 1] + A[0][i];
		m[i][0] = m[i - 1][0] + A[i][0];
	}

	for (i = 1; i < n; i++)
	{
		for (j = 1; j < n; j++)
			m[i][j] = max(m[i - 1][j], m[i][j - 1]) + arr[i][j];
	}

	print(m, n);
	return m[n-1][n-1];
}

int main()
{
	print(A, N);
	printf("%d\n ", collectCoin(A, N));
	return 0;
}