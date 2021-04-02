#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 20
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void inPlaceSelectionSort(int list[], int n)
{
	int least, temp;
	for (int i = 0; i < n - 1; i++)
	{
		least = i;
		for (int j = i + 1; j < n; j++)
			if (list[j] < list[least])
				least = j;
		SWAP(list[i], list[least], temp);
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

	inPlaceSelectionSort(list, SIZE);

	getchar();
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", list[i]);
		Sleep(100);
	}
	printf("\n");
	return 0;
}