#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 15
int sorted[SIZE];


void merge(int list[], int left, int mid, int right)
{
	int i = left;		// L1 접근
	int j = mid + 1;	// L2 접근
	int k = left;
	int l;

	while (i <= mid && j <= right)
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int main()
{
	int list[SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		list[i] = rand() % 100;
		for (int j = 0; j < i; j++)
			if (list[i] == list[j])
				i--;
	}
	for (int i = 0; i < SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n");
	getchar();

	merge_sort(list, 0, SIZE - 1);
	for (int i = 0; i < SIZE; i++)
	{
		printf("[%d] ", list[i]);
		Sleep(200);
	}
	printf("\n");
	return 0;
}