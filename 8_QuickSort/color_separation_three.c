#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 15
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void partition(char list[], int left, int right)
{
	int low = left - 1;
	int high = right + 1;
	char temp;

	do
	{
		do
			low++;
		while (list[low] != 'B');

		do
			high--;
		while (list[high] == 'B');

		if (low < high)
			SWAP(list[low], list[high], temp);

	} while (low < high);

	high = low;
	low = left - 1;

	do
	{
		do
			low++;
		while (list[low] == 'W');

		do
			high--;
		while (list[high] == 'G');

		if (low < high)
			SWAP(list[low], list[high], temp);

	} while (low < high);
}

int main()
{
	char list[MAX_SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_SIZE; i++)
	{
		// Black or White
		if (rand() % 3 == 0)
			list[i] = 'W';
		else if (rand() % 3 == 1)
			list[i] = 'B';
		else
			list[i] = 'G';
	}

	for (int i = 0; i < MAX_SIZE; i++)
		printf("%c ", list[i]);
	printf("\n\n");

	partition(list, 0, MAX_SIZE - 1);

	for (int i = 0; i < MAX_SIZE; i++)
		printf("%c ", list[i]);
	printf("\n");
}