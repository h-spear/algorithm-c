#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int findMaxOfUnimodalArray(int A[], int n)
{
	int a, b, mid;
	a = 0;
	b = n - 1;
	while (a < b)
	{
		mid = (a + b) / 2;
		if (A[mid] < A[mid + 1])
			a = mid + 1;
		if (A[mid] > A[mid + 1])
			b = mid;
	}
	return A[a];
}

int main()
{
	int list[SIZE] = { -21,8,12,13,35,41,24,20,17 };
	
	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n\n");

	printf("%d\n", findMaxOfUnimodalArray(list, SIZE));
	return 0;
}