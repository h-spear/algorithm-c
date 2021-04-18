#pragma warning(disable: 4996)

#include <stdio.h>

#define SIZE 10

void spans(int X[], int S[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int s = 1;
		while ((s <= i) && (X[i - s] <= X[i]))
			s++;
		S[i] = s;
	}
	return;
}

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%3d ", arr[i]);
	printf("\n");
}

int main()
{
	int X[SIZE] = { 60,30,40,10,20,30,50,40 };
	int S[SIZE];

	printf("X:");
	printArray(X, 8);
	spans(X, S, 8);

	printf("S:");
	printArray(S, 8);
	return 0;
}