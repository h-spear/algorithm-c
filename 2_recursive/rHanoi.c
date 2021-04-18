#pragma warning(disable: 4996)

#include <stdio.h>

#define SIZE 100

void printArray(arr[][N])
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
			printf("%3d ", arr[r][c]);
		printf("\n");
	}

}

void zigzag(int n)
{
	int A[SIZE][SIZE];

	value = 1;
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
			for (int j = 0; j < n; j++, value++)
				A[i][j] = value;
		else
			for (int j = n - 1; j >= 0; j--, value++)
				A[i][j] = value;
	}
	printArray(A);
}

int main()
{
	zigzag(5);
	return 0;
}