#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX(x,y) ((x>y) ? x : y)

int partition(int list[], int left, int right, int k)
{
	int pivot, temp, low, high;
	pivot = list[k];
	SWAP(list[k], list[right], temp);
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

	SWAP(list[low], list[right], temp);
	return low;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int k = rand() % (right - left + 1) + left;
		int q = partition(list, left, right, k);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

int voted(int list[], int n)
{
	quick_sort(list, 0, n - 1);
	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	int cnt = 1;
	int candidate = -1;
	int max = -1;
	for (int i = 0; i < n - 1; i++)
	{
		if (list[i] == list[i + 1])
		{
			cnt++;
		}
		else
		{
			if (cnt > max)
			{
				max = cnt;
				candidate = list[i];
			}
			cnt = 1;
		}
	}
	if (cnt > max)
		candidate = list[n - 1];

	return candidate;
}

int main()
{
	int list[SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 10;

	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	printf("%d\n", voted(list, SIZE));
	return 0;
}