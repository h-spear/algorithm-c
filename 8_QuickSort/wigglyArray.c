#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 16
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

void printArray(int list[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

//O(nlogn)
void wigglyArray(int list[], int n)
{
	int temp;

	quick_sort(list, 0, n - 1);
	for (int i = 0; i < n - 1; i += 2)
		SWAP(list[i], list[i + 1], temp);
}

//O(n)
void wigglyArray2(int list[], int n)
{
	int temp;

	for (int i = 1; i < n; i += 2)
	{
		if ((i - 1) >= 0 && list[i] > list[i - 1])
			SWAP(list[i], list[i - 1], temp);

		if ((i + 1) < n && list[i] < list[i + 1])
			SWAP(list[i], list[i + 1], temp);
	}
}

int main()
{
	int list[SIZE];
	int list2[SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		int item = rand() % 100;
		list[i] = item;
		list2[i] = item;
	}

	printArray(list, SIZE);
	printf("\n");

	wigglyArray(list, SIZE);
	printArray(list, SIZE);
	printf("\n");

	wigglyArray2(list2, SIZE);
	printArray(list2, SIZE);
	return 0;
} 