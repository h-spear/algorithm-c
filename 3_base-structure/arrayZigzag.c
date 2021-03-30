#pragma warning(disable: 4996)

#include <stdio.h>

#define N 100

void printArray(int arr[][N],int n)
{
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
			printf("%3d ", arr[r][c]);
		printf("\n");
	}

}

void zigzag(int n)
{
	int A[N][N];

	int value = 1;
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
			for (int j = 0; j < n; j++, value++)
				A[i][j] = value;
		else
			for (int j = n - 1; j >= 0; j--, value++)
				A[i][j] = value;
	}
	printArray(A,n);
}

int main()
{
	zigzag(5);
	return 0;
}