// 무작위 선택
// 제자리 퀵 정렬

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 15
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int partition(int list[], int left, int right, int k)
{
	int pivot, temp, low, high;

	pivot = list[k];
	SWAP(list[k], list[right], temp);
	
	low = left - 1;
	high = right;

	//printf("pivot : %d\n", pivot);
	//for (int i = 0; i < MAX_SIZE; i++)
	//	printf("[%d] ", list[i]);
	//printf("\n\n");

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
	SWAP(list[low], list[right], temp);
	return low;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int k = rand() % (right - left + 1) + left;
		int q = partition(list, left, right, k);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
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

	quick_sort(list, 0, MAX_SIZE - 1);

	for (int i = 0; i < MAX_SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");
	return 0;
}