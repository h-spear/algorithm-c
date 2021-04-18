#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

int sorted[SIZE];

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

void merge(int list[], int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	while (i <= mid)
		sorted[k++] = list[i++];
	while (j <= right)
		sorted[k++] = list[j++];
	for (int k = left; k <= right; k++)
		list[k] = sorted[k];
	return;
}

void mergeSort(int list[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(list, left, mid);
		mergeSort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

void quickSort_limit(int list[], int left, int right, int limit)
{
	if (right - left >= limit)
	{
		int q = partition(list, left, right);
		quickSort_limit(list, left, q - 1, limit);
		quickSort_limit(list, q + 1, right, limit);
	}
}

int partition_reverse(int list[], int left, int right)
{
	int pivot, temp, low, high;
	pivot = list[right];
	low = left - 1;
	high = right;

	do
	{
		do
			low++;
		while (list[low] > pivot);

		do
			high--;
		while (list[high] < pivot);

		if (high > low)
			SWAP(list[low], list[high], temp);

	} while (high > low);
	SWAP(list[low], list[right], temp);
	return low;
}

void quickSort_limit_reverse(int list[], int left, int right, int limit)
{
	if (right - left >= limit)
	{
		int q = partition_reverse(list, left, right);
		quickSort_limit_reverse(list, left, q - 1, limit);
		quickSort_limit_reverse(list, q + 1, right, limit);
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
		int item = rand() % 2000000;
		list1[i] = item;
		list2[i] = item;
	}

	printf("\n합병 정렬 시간 측정...");
	start1 = clock();
	mergeSort(list1, 0, SIZE - 1);
	end1 = clock();

	printf("\n퀵 정렬 시간 측정...");
	start2 = clock();
	quickSort(list2, 0, SIZE - 1);
	end2 = clock();

	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	printf("\n\n합병 정렬 수행시간 : %f\n", res1);
	printf("퀵 정렬 수행시간 : %f\n", res2);


	// 거의 정렬된 리스트 생성
	printf("\n===== 거의 정렬된 리스트 생성...");
	for (int i = 0; i < SIZE; i++)
		list1[i] = rand() % 2000000;
	quickSort_limit(list1, 0, SIZE - 1, 500);
	for (int i = 0; i < SIZE; i++)
		list2[i] = list1[i];

	printf("\n합병 정렬 시간 측정...");
	start1 = clock();
	mergeSort(list1, 0, SIZE - 1);
	end1 = clock();

	printf("\n퀵 정렬 시간 측정...");
	start2 = clock();
	quickSort(list2, 0, SIZE - 1);
	end2 = clock();

	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	printf("\n\n합병 정렬 수행시간 : %f\n", res1);
	printf("퀵 정렬 수행시간 : %f\n", res2);



	// 거의 역정렬된 리스트 생성
	printf("\n===== 거의 역정렬된 리스트 생성...");
	for (int i = 0; i < SIZE; i++)
		list1[i] = rand() % 2000000;
	quickSort_limit_reverse(list1, 0, SIZE - 1, 500);
	for (int i = 0; i < SIZE; i++)
		list2[i] = list1[i];

	printf("\n합병 정렬 시간 측정...");
	start1 = clock();
	mergeSort(list1, 0, SIZE - 1);
	end1 = clock();

	printf("\n퀵 정렬 시간 측정...");
	start2 = clock();
	quickSort(list2, 0, SIZE - 1);
	end2 = clock();

	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	printf("\n\n합병 정렬 수행시간 : %f\n", res1);
	printf("퀵 정렬 수행시간 : %f\n", res2);

	return 0;
}