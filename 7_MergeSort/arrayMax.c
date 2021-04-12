#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
#define MAX(x,y) (x > y) ? x : y

int rArrayMax(int list[], int left, int right)
{
	if (left >= right)
		return list[left];
	int mid = (left + right) / 2;
	return MAX(rArrayMax(list, left, mid), rArrayMax(list, mid + 1, right));
}

int arrayMax(int list[], int n)
{
	return rArrayMax(list, 0, n - 1);
}

int main()
{
	int list[SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		list[i] = rand() % 100;
		for (int j = 0; j < i; j++)
			if (list[i] == list[j])
				i--;
	}
	for (int i = 0; i < SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n");
	getchar();

	printf("%d\n", arrayMax(list, SIZE));
	return 0;
}