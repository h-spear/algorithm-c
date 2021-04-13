// 중간 원소 기준

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 200000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void printList(int list[], int left, int right)
{
	for (int i = left; i <= right; i++)
		printf("[%d] ", list[i]);
	printf("\n");
}

int partition(int list[], int left, int right)
{
	int low, high, pivot, temp;
	int mid = (left + right) / 2;
	pivot = list[mid];
	SWAP(list[mid], list[right], temp);
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
	int list[MAX_SIZE];
	srand((unsigned int)time(NULL));
	printf("20만개의 랜덤 원소를 가진 리스트 생성\n");
	for (int i = 0; i < MAX_SIZE; i++)
		list[i] = rand() % 10000000;
	printf("완료\n\n");

 
	clock_t start, end, start2,end2;
	float res,res2;

	printf("정렬되지 않은 리스트를 정렬하고 시간 측정\n");
	start = clock();
	quickSort(list, MAX_SIZE);
	end = clock();
	printf("완료\n\n");

	printf("정렬이 완료된 리스트를 정렬하고 시간 측정\n");
	start2 = clock();
	quickSort(list, MAX_SIZE);
	end2 = clock();
	printf("완료\n\n");

	res = (float)(end - start) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;

	printf("\n결과\n");
	printf("정렬되지 않은 리스트를 정렬하는 수행시간: %.3f초 (%d %d)\n", res, start, end);
	printf("  이미 정렬된 리스트를 정렬하는 수행시간: %.3f초 (%d %d)\n", res2, start2, end2);
	return 0;
}