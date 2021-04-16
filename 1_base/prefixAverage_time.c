#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30000

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
	clock_t start1, start2, end1, end2;
	float res1, res2;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		X[i] = rand() % 40 + 10;

	//printArray(X, SIZE);
	printf("측정 중..");

	start1 = clock();
	prefixAverage1(X, SIZE);
	end1 = clock();
	//printArray(A, SIZE);
	
	start2 = clock();
	prefixAverage2(X, SIZE);
	end2 = clock();
	//printArray(B, SIZE);

	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;

	printf("slow ver. : %f(%d, %d)\nfast ver. : %f(%d, %d)", res1, start1, end1, res2, start2, end2);
	return 0;
}