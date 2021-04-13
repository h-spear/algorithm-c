// 무작위 선택

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 15
#define LIMIT 3
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void insertionSort(int list[], int n)
{
	int i, j, save;
	for (int i = 1; i < n; i++)
	{
		save = list[i];
		for (j = i - 1; j >= 0 && list[j] > save; j--)
			list[j + 1] = list[j];
		list[j + 1] = save;
	}
}

int partition(int list[], int left, int right, int k)
{
	int low = left - 1, high = right, temp;
	int pivot = list[k];
	SWAP(list[k], list[right], temp);

	do
	{
		do
			low++;
		while (list[low] < pivot);

		do
			high--;
		while (list[high] > pivot);

		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[right], list[low], temp);
	return low;
}

void rQuickSort(int list[], int left, int right)
{
	if (right - left >= LIMIT)
	{
		int k = rand() % (right - left + 1) + left;
		int q = partition(list, left, right, k);
		rQuickSort(list, left, q - 1);
		rQuickSort(list, q + 1, right);
	}
}

void quickSort(int list[], int n)
{
	rQuickSort(list, 0, n - 1);
	insertionSort(list, n);
	return;
}

int main()
{
	int list[MAX_SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_SIZE; i++)
		list[i] = rand() % 100;

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");

	quickSort(list, MAX_SIZE);

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n");
	return 0;
}