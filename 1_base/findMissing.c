#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 12

int findMissing(int list[SIZE], int n)
{
	int result = 0;
	for (int i = 0; i <= n; i++)
		result += i;

	for (int i = 0; i < n; i++)
		result -= list[i];

	return result;
}

int main()
{
	int A[SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		int item = rand() % (SIZE + 1);
		A[i] = item;

		for (int j = 0; j < i; j++)
			if (A[i] == A[j])
				i--;
	}

	for (int i = 0; i < SIZE; i++)
		printf("%d ", A[i]);
	printf("\n\n");

	printf("%d\n", findMissing(A, SIZE));
	return 0;
}