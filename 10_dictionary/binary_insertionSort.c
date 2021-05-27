#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 20

// O(n^2)
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

int binary_search(int A[], int item, int left, int right)
{
	if (right <= left)
		return (item > A[left]) ? (left + 1) : left;
	
	int mid = (left + right) / 2;
	if (item == A[mid])
		return mid + 1;
	else if (item > A[mid])
		return binary_search(A, item, mid + 1, right);
	else
		return binary_search(A, item, left, mid - 1);
}

// O(nlogn)
void binary_insertionSort(int list[], int n)
{
	int i, j, save, location;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		save = list[i];
		location = binary_search(list, save, 0, j);
		while (j >= location)
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = save;
	}
}

int main()
{
	int list[SIZE];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 100;

	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	binary_insertionSort(list, SIZE);

	getchar();
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", list[i]);
		Sleep(100);
	}
	printf("\n");
	return 0;
}