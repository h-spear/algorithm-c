#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
	int l;
	int r;
}Boundary;

Boundary partition(int list[], int left, int right, int k)
{
	int pivot, temp, low, high;
	Boundary q;

	pivot = list[k];
	low = left - 1;
	high = right + 1;

	do
	{
		do
			low++;
		while (pivot != list[low]);

		do
			high--;
		while (pivot == list[high]);

		if (high > low)
			SWAP(list[low], list[high], temp);

	} while (high > low);

	high = low;
	low = left - 1;
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

	q.l = high;
	low = high;
	high = right + 1;
	do
	{
		do
			low++;
		while (pivot == list[low]);

		do
			high--;
		while (pivot != list[high]);

		if (high > low)
			SWAP(list[low], list[high], temp);

	} while (high > low);

	q.r = low;
	return q;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int k = rand() % (right - left + 1) + left;
		Boundary q = partition(list, left, right, k);
		quick_sort(list, left, q.l);
		quick_sort(list, q.r, right);
	}
}

int main()
{
	int list[MAX_SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_SIZE; i++)
		list[i] = rand() % 10;

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");

	quick_sort(list, 0, MAX_SIZE - 1);

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");
	return 0;
}