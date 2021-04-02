#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 20
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void BubbleSort(int list[], int n)
{
	int temp;
	for (int i = n - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
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

	BubbleSort(list, SIZE);

	getchar();
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", list[i]);
		Sleep(100);
	}
	printf("\n");
	return 0;
}