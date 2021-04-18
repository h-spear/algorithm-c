#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

void insertionSort(int list[], int n)
{
	int i, j, save;
	for (i = 1; i < n; i++)
	{
		save = list[i];
		for (j = i - 1; j >= 0 && list[j] > save; j--)
			list[j + 1] = list[j];
		list[j + 1] = save;
	}
}

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

int main()
{
	int list1[SIZE], list2[SIZE];
	clock_t start1, end1, start2, end2;
	float res1, res2;

	srand((unsigned int)time(NULL));

	// 무작위로 나열된 리스트 생성
	printf("===== 무작위 리스트 생성...");
	for (int i = 0; i < SIZE; i++)
	{
		int item = rand() % 1000000;
		list1[i] = item;
		list2[i] = item;
	}

	printf("\n선택 정렬 시간 측정...");
	start1 = clock();
	insertionSort(list1, SIZE);
	end1 = clock();

	printf("\n퀵 정렬 시간 측정...");
	start2 = clock();
	quickSort(list2, 0, SIZE - 1);
	end2 = clock();

	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	printf("\n\n선택 정렬 수행시간 : %f\n", res1);
	printf("퀵 정렬 수행시간 : %f\n", res2);

	return 0;
}