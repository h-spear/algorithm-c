#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define INF 100000000

int path[N][N];
int A[N][N];
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

void calcPath()
{
	int i, j;
	path[0][0] = 1;
	
	i = 0, j = 0;
	while (i < N && j < N)
	{
		if (m[i + 1][j] > m[i][j + 1])
		{
			path[i + 1][j] = 1;
			i++;
		}
		else
		{
			path[i][j + 1] = 1;
			j++;
		}
	}
	print(path, N);
}

int collectCoin()
{
	int i, j;
	m[0][0] = A[0][0];

	for (i = 1; i < N; i++)
	{
		m[0][i] = m[0][i - 1] + A[0][i];
		m[i][0] = m[i - 1][0] + A[i][0];
	}

	for (i = 1; i < N; i++)
		for (j = 1; j < N; j++)
			m[i][j] = max(m[i - 1][j], m[i][j - 1]) + A[i][j];

	printf("matrix m\n");
	print(m, N);

	printf("path matrix\n");
	calcPath();
	return m[N - 1][N - 1];
}

int main()
{

	srand((unsigned int)time(NULL));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			A[i][j] = rand() % 5;
	}

	print(A, N);
	printf("%d\n", collectCoin());
	return 0;
}