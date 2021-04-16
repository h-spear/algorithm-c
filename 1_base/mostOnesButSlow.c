#include <stdio.h>
#define N 8

int mostOnesButSlow(int A[][N], int n)
{
	int row = 0;
	int jmax = 0;
	for (int i = 0; i < n; i++)
	{
		int j;
		for (j = 0; j < n; j++)
			if (A[i][j] != 1)
				break;
		if (j > jmax)
		{
			row = i;
			jmax = j;
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

	// O(n^2)
	printf("\n%d\n",mostOnesButSlow(A, N));
	return 0;
}