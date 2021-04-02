#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 20

void incInsertionSort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void ShellSort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if (gap % 2 == 0)
			gap++;
		for (i = 0; i < gap; i++)
			incInsertionSort(list, i, n - 1, gap);
	}
}

int main()
{
	int list[SIZE];

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 100;

	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	ShellSort(list, SIZE);

	getchar();
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", list[i]);
		Sleep(100);
	}
	printf("\n");
	return 0;
}