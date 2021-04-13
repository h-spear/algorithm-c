// 마지막 원소 기준

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void printList(int list[], int left, int right)
{
	for (int i = left; i <= right; i++)
		printf("%d ", list[i]);
}

int partition(int list[], int left, int right)
{
	int low, high, pivot, temp;
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

		if (low < high)
			SWAP(list[low], list[high], temp);

	} while (low < high);
	SWAP(list[right], list[low], temp);
	return low;
}

void rQuickSort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		printf("pivot element : %d\n( ", list[q]);
		printList(list, left, q - 1); printf(") ");
		printf("%d ", list[q]);
		printf("( "); printList(list, q + 1, right); printf(") \n\n");

		rQuickSort(list, left, q - 1);
		rQuickSort(list, q + 1, right);
	}
}

void quickSort(int list[], int n)
{
	rQuickSort(list, 0, n - 1);
	return;
}

int main()
{
	int list[MAX_SIZE] = { 22,15,36,44,10,3,9,25,29,13 };
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");

	quickSort(list, MAX_SIZE);

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n");
	return 0;
}