#include <stdio.h>
#define N 8

// O(n^2)
int countOnesButSlow(int A[][N], int n)
{
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while ((j < n) && (A[i][j] == 1))
		{
			c++;
			j++;
		}
	}
	return c;
}

// O(n)
int countOnes(int A[][N], int n)
{
	int c = 0;
	int i = n - 1, j = 0;
	int ones = 0;

	while (i >= 0)
	{
		if (A[i][j] == 0)
		{
			i--;
			c += ones;
		}
		else
		{
			ones++;
			j++;
		}

		if (j == n)
		{
			c += (ones * (i + 1));
			break;
		}
	}
	return c;
}

int main()
{
	int A[][N] = { {1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,0,0},
					{1,1,1,1,1,1,0,0},
					{1,1,1,1,1,0,0,0},
					{1,1,1,1,1,0,0,0},
					{1,1,1,1,1,0,0,0},
					{1,1,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0} };

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
			printf("%d ", A[r][c]);
		printf("\n");
	}

	// O(n)
	printf("\n%d\n", countOnes(A, N));
	return 0;
}