#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
#define MAX(x,y) (x > y) ? x : y
#define MIN(x,y) (x < y) ? x : y

typedef struct{
	int Max;
	int Min;
}MaxMin;

MaxMin rArrayMaxMin(int list[], int left, int right)
{
	MaxMin result;
	if (left >= right)
	{
		result.Min = list[left];
		result.Max = list[left];
		return result;
	}
	int mid = (left + right) / 2;
	MaxMin left_result = rArrayMaxMin(list, left, mid);
	MaxMin right_result = rArrayMaxMin(list, mid + 1, right);
	result.Min = MIN(left_result.Min, right_result.Min);
	result.Max = MAX(left_result.Max, right_result.Max);
	return result;
}

MaxMin arrayMaxMin(int list[], int n)
{
	MaxMin result;
	result = rArrayMaxMin(list, 0, n - 1);
	return result;
}

int main()
{
	int list[SIZE];
	MaxMin a;

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

	a = arrayMaxMin(list, SIZE);
	printf("%d %d\n", a.Max, a.Min);
	return 0;
}