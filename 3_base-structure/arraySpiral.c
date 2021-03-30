#pragma warning(disable: 4996)

#include <stdio.h>

#define N 100

void printArray(int arr[][N], int n, int m)
{
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
			printf("%3d ", arr[r][c]);
		printf("\n");
	}

}

void spiral(int n, int m)
{
	int A[N][N];
	int top = 0, bottom = n - 1;
	int left = 0, right = m - 1;
	int value = 1;

	while (left <= right && top <= bottom)
	{
		for (int i = left; i <= right; i++,value++)
			A[top][i] = value;
		top++;

		for (int i = top; i <= bottom; i++, value++)
			A[i][right] = value;
		right--;

		for (int i = right; i >= left; i--, value++)
			A[bottom][i] = value;
		bottom--;

		for (int i = bottom; i >= top; i--, value++)
			A[i][left] = value;
		left++;
	}
	printArray(A, n, m);
}

int main()
{
	spiral(4, 5);
	return 0;
}