#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 20

void inPlaceInsertionSort(int list[], int n)
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

int main()
{
	int list[SIZE];

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 100;

	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	inPlaceInsertionSort(list, SIZE);

	getchar();
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", list[i]);
		Sleep(100);
	}
	printf("\n");
	return 0;
}