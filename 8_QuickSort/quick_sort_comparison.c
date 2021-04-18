#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX(x,y) (x>y) ? x : y
#define MIN(x,y) (x<y) ? x : y

int mid(int x, int y, int z)
{
	int result = x + y + z;
	result -= MAX(MAX(x, y), z);
	result -= MIN(MIN(x, y), z);
	return result;
}

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

int partition(int list[], int left, int right, int k)
{
	int pivot, low, high, temp;
	pivot = list[k];
	low = left - 1;
	high = right;
	SWAP(list[k], list[right], temp);

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

	SWAP(list[low], list[high], temp);
	return low;
}

int findPivot(int list[], int left, int right, int index)
{

	if (index == 1)			// 결정적 1
		return right;
	else if (index == 2)	// 무작위 1
		return (rand() % (right - left + 1) + left);
	else if (index == 3)	// 결정적 3
	{
		if (right - left + 1 < 3)
			return left;
		else
		{
			int m = mid(list[left], list[right], list[(left + right) / 2]);
			if (list[left] == m)
				return left;
			else if (list[right] == m)
				return right;
			else
				return (left + right) / 2;
		}
	}
	else if (index == 4)	// 무작위 3
	{
		if (right - left + 1 < 3)
			return left;
		else
		{
			int k[3];
			for (int i = 0; i < 3; i++)
			{
				k[i] = rand() % (right - left + 1) + left;
				for (int j = 0; j < i; j++)
					if (k[i] == k[j])
					{
						i--;
						break;
					}
			}

			int m = mid(k[0], k[1], k[2]);
			if (list[k[0]] == m)
				return k[0];
			else if (list[k[1]] == m)
				return k[1];
			else
				return k[2];
		}
	}
	return 0;
}

void rQuickSort(int list[], int left, int right, int limit, int index)
{
	if (right - left >= limit)
	{
		int k = findPivot(list, left, right, index);
		int q = partition(list, left, right, k);
		rQuickSort(list, left, q - 1, limit, index);
		rQuickSort(list, q + 1, right, limit, index);
	}
}

void quickSort(int list[], int n, int limit, int index)
{
	rQuickSort(list, 0, n - 1, limit, index);
	if (limit != 1)
		insertionSort(list, n);
	return;
}

int main()
{
	int list[SIZE];
	int list1[SIZE];
	int list2[SIZE];
	int list3[SIZE];
	int list4[SIZE];
	clock_t start0, start1, start2, start3, start4;
	clock_t end0, end1, end2, end3, end4;
	float res0, res1, res2, res3, res4;

	printf("측정 중...");

	srand((unsigned int)time(NULL));

	for (int i = 0; i < SIZE; i++)
	{
		int item = rand() % 100000;
		list[i] = item;
		list1[i] = item;
		list2[i] = item;
		list3[i] = item;
		list4[i] = item;
	}

	int limit = 100;

	start0 = clock();
	quickSort(list, SIZE, 1, 1);
	end0 = clock();

	start1 = clock();
	quickSort(list1, SIZE, limit, 1);
	end1 = clock();

	start2 = clock();
	quickSort(list2, SIZE, limit, 2);
	end2 = clock();

	start3 = clock();
	quickSort(list3, SIZE, limit, 3);
	end3 = clock();

	start4 = clock();
	quickSort(list4, SIZE, limit, 4);
	end4 = clock();

	res0 = (float)(end0 - start0) / CLOCKS_PER_SEC;
	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	res3 = (float)(end3 - start3) / CLOCKS_PER_SEC;
	res4 = (float)(end4 - start4) / CLOCKS_PER_SEC;

	printf("\n퀵 정렬 원형 : %f\n", res0);
	printf("퀵 정렬 결정적1 : %f\n", res1);
	printf("퀵 정렬 무작위1 : %f\n", res2);
	printf("퀵 정렬 결정적3 : %f\n", res3);
	printf("퀵 정렬 무작위3 : %f\n", res4);

	return 0;
}