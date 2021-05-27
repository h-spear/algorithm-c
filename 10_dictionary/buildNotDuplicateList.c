#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define N 30

int partition(int list[], int left, int right)
{
	int pivot, temp, low, high;

	pivot = list[left];
	low = left;
	high = right + 1;

	do
	{
		do
			low++;
		while (pivot > list[low]);

		do
			high--;
		while (pivot < list[high]);

		if (high > low)
			SWAP(list[low], list[high], temp);

	} while (high > low);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

int binary_search(int A[], int item, int left, int right)
{
	int mid;

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (A[mid] == item)
			if (A[mid] == A[mid + 1])
				left = mid + 1;
			else
				return mid;
		else if (A[mid] > item)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;	//error
}

void print(int list[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int buildNotDuplicateList(int A[], int B[], int n)
{
	quick_sort(A, 0, n - 1);
	int i, j = 0;

	for (i = 0; i < n; i++)
	{
		B[j++] = A[i];
		i = binary_search(A, A[i], 0, n - 1);
	}
	return j;
}

int main()
{
	int A[N];
	int B[N];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < N; i++)
		A[i] = rand() % 30;

	printf("A: ");
	print(A, N);

	int k = buildNotDuplicateList(A, B, N);
	
	printf("B: ");
	print(B, k);
	return 0;
}