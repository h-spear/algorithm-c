#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

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

int findElement(int A[], int key)
{
	int mid;
	int left = 0, right = SIZE - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (key == A[mid])
			return mid;
		else if (key < A[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

void existPair(int A[], int B[], int x)
{
	int j;
	quick_sort(B, 0, SIZE - 1);
	for (int i = 0; i < SIZE; i++)
	{
		int v = x - A[i];
		j = findElement(B, v);
		if (j != -1)
		{
			printf("true\n");
			return;
		}
	}
	printf("false\n");
	return;
}

int main()
{
	int A[SIZE] = { 75,6,38,4,11,6 };
	int B[SIZE] = { 43,15,4,5,15,3 };
	existPair(A, B, 53);
	return 0;
}