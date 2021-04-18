#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000
#define SWAP(x,y,t) ((t=x),(x=y),(y=t))
#define MIN(x,y) (x<y) ? x : y
#define A_SIZE 6
#define B_SIZE 8

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

int is_same(int A[], int B[], int A_size, int B_size)
{
	int set1[MAX_SIZE];
	int set2[MAX_SIZE]; 

	make_set(A, set1, A_size);
	make_set(B, set2, B_size);

	int n = MIN(A_size, B_size);

	for (int i = 0; i < n; i++)
	{
		if (set1[i] != set2[i])
			return 0;
	}
	return 1;
}

int main()
{
	
	int list1[A_SIZE] = { 75, 6, 38, 4, 11, 6};
	int list2[B_SIZE] = { 38,11,4,75,4,75,6,4 };

	srand((unsigned int)time(NULL));

	printf("list1 : ");
	for (int i = 0; i < A_SIZE; i++)
		printf("%d ", list1[i]);
	printf("\n");

	printf("list2 : ");
	for (int i = 0; i < B_SIZE; i++)
		printf("%d ", list2[i]);
	printf("\n\n");

	if (is_same(list1, list2, A_SIZE, B_SIZE))
		printf("두 리스트는 동일한 원소의 집합을 가집니다.\n");
	else
		printf("두 리스트는 동일한 원소의 집합을 가지지 않습니다.\n");

	return 0;
}