#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define INF 100000000

void maxSubarray_straightforward(int A[], int n)
{
	int sum, maxi = 0, maxj = 0;
	int maxSum = -INF;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			sum = 0;
			for (int k = i; k <= j; k++)
				sum = sum + A[k];
			if (maxSum < sum)
			{
				maxSum = sum;
				maxi = i;
				maxj = j;
			}
		}
	}
	printf("interval (%d:%d)  maxSum : %d \n", maxi, maxj, maxSum);
}

int lastPlusIndex(int s[],int n)
{
	for (int i = n; i >= 0; i--)
		if (s[i] <= 0)
			return i; 
	return -1;
}

void maxSubarray(int A[], int n)
{
	int s[N + 1] = { 0 };
	int maxSum = -INF;
	int maxi = 0, maxj = 0;
	int maxCount = 0;

	for (int i = 0; i < n; i++)
	{
		if (s[i] > 0)
		{
			s[i + 1] = s[i] + A[i];
			if (maxSum < s[i + 1])
			{
				maxSum = s[i + 1];
				maxi = lastPlusIndex(s, i);
				maxj = i;
				maxCount = i - maxi + 1;
			}
			if (maxSum == s[i + 1])
			{
				int count = i - lastPlusIndex(s, i);
				if (count > maxCount)
				{
					maxCount = count;
					maxi = lastPlusIndex(s, i);
					maxj = i;
				}
			}
		}
		else
		{
			s[i + 1] = A[i];
			if (maxSum < s[i + 1])
			{
				maxi = i;
				maxj = i;
				maxSum = s[i + 1];
				maxCount = 1;
			}
		}
	}
	printf("interval (%d:%d)  maxSum : %d  elementCount : %d\n", maxi, maxj, maxSum,maxCount);
}

int main()
{
	int A[N];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < N; i++)
		A[i] = rand() % 200 - 100;

	for (int i = 0; i < N; i++)
		printf("%3d ", A[i]);
	printf("\n\n");

	maxSubarray(A, N);
	maxSubarray_straightforward(A, N);
	return 0;

}