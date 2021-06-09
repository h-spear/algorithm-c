#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int trumpets[N];

void print(int A[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int poisonedTrumpet(int A[], int left, int right)
{
	if (left > right)
		return -1;

	int mid = (left + right) / 2;
	if (A[mid] == 1)
		return mid;
	else
		return max(poisonedTrumpet(A, left, mid - 1), poisonedTrumpet(A, mid + 1, right));
	return -1;
}

int main()
{
	srand((unsigned int)time(NULL));
	trumpets[rand() % N] = 1;
	print(trumpets, N);
	
	printf("%d\n", poisonedTrumpet(trumpets, 0, N - 1));
}