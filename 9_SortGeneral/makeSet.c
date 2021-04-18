#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

int partition(int list[], int left, int right)
{
	int pivot, temp, low, high;
	pivot = list[right];
	low = left - 1;
	high = right;

	do
	{
		do
			low++;
		while (list[low] < pivot);

		do
			high--;
		while (list[high] > pivot);

		if (high > low)
			SWAP(list[low], list[high], temp);

	} while (high > low);
	SWAP(list[low], list[right], temp);
	return low;
}

void quickSort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quickSort(list, left, q - 1);
		quickSort(list, q + 1, right);
	}
}

void make_set(int list[], int set[], int n)
{
	quickSort(list, 0, n - 1);
	int k = 0;

	for (int i = 0; i < n; i++)
	{
		if (list[i - 1] != list[i])
			set[k++] = list[i];
	}

	while (k < n)
		set[k++] = -1;
}

int main()
{
	int list[SIZE];
	int set[SIZE];

	srand((unsigned int)time(NULL));

	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 100;

	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n\n");

	make_set(list, set, SIZE);
	for (int i = 0; i < SIZE; i++)
		printf("%d ", set[i]);
	printf("\n");
	return 0;
}