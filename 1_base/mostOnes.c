#include <stdio.h>
#define N 8

/*
int mostOnes(int A[][N], int n)		//ver.1
{
	int i = 0, j = 0;
	int row;
	while (1)
	{
		while (A[i][j] == 1)
		{
			j++;
			if (j == n)
				return i;
		}
		row = i;
		while (A[i][j] == 0)
		{
			i++;
			if (i == n)
				return row;
		}
	}
}
*/

int mostOnes(int A[][N], int n)		//ver.2
{
	int i = 0, j = 0, row = 0;
	while ((i < n) && (j < n))
	{
		if (A[i][j] == 0)
			i++;
		else
		{
			row = i;
			j++;
		}
	}
	return row;
}

int main()
{
	int A[][N] = { {1,1,1,1,0,0,0,0},
					{1,1,1,1,1,0,0,0},
					{1,0,0,0,0,0,0,0},
					{1,1,1,1,1,1,0,0},
					{1,1,1,1,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{1,1,1,1,1,1,1,0},
					{1,1,1,1,1,0,0,0} };

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
			printf("%d ", A[r][c]);
		printf("\n");
	}

	// O(n)
	printf("\n%d\n",mostOnes(A, N));
	return 0;
}