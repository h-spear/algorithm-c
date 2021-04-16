#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

int A[SIZE];
int B[SIZE];

void movingAverages1(int X[SIZE], int n, int k)
{
	for (int i = k - 1; i < n; i++)
	{
		int sum = 0;
		for (int j = i; j >= i - k + 1; j--)
		{
			sum += X[j];
		}
		A[i] = sum / k;
	}
}

void movingAverages2(int X[SIZE], int n, int k)
{
	int sum = 0;
	int i;
	for (i = 0; i < k; i++)
		sum += X[i];
	B[k - 1] = sum / k;

	for (i = k; i < n; i++)
	{
		sum -= X[i - k];
		sum += X[i];
		B[i] = sum / k;
	}
}

int main()
{
	int X[SIZE];
	clock_t start1, start2, end1, end2;
	float res1, res2;
	int k = 100;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		X[i] = rand() % 1000;

	start1 = clock();
	movingAverages1(X, SIZE, k);
	end1 = clock();

	start2 = clock();
	movingAverages2(X, SIZE, k);
	end2 = clock();

	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	printf("%f %f", res1, res2);
	return 0;
}