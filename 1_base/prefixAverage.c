#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int A[SIZE];
int B[SIZE];

// O(n^2)
void prefixAverage1(int X[], int n)
{
	int sum;
	for (int i = 0; i < n; i++)
	{
		sum = 0;
		for (int j = 0; j <= i; j++)
			sum += X[j];
		sum /= i + 1;
		A[i] = sum;
	}
}

// O(n)
void prefixAverage2(int X[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + X[i];
		B[i] = sum / (i + 1);
	}
}

void printArray(int list[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int main()
{
	int X[SIZE];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		X[i] = rand() % 40 + 10;

	printArray(X, SIZE);

	prefixAverage1(X, SIZE);
	printArray(A, SIZE);

	prefixAverage2(X, SIZE);
	printArray(B, SIZE);

	return 0;
}