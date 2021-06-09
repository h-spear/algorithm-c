#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define INF 100000000

int lastPlusIndex(int s[], int n)
{
	for (int i = n; i >= 0; i--)
		if (s[i] <= 0)
			return i;
	return -1;
}

// O(n)
void maxSubarray(int A[], int n)
{
	int s[N + 1] = { 0 };
	int maxSum = -INF;
	int maxi = 0, maxj = 0;

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
			}
		}
	}
	printf("interval (%d:%d)  maxSum : %d \n", maxi, maxj, maxSum);
}

// O(nlogn)
int rMaxSubarray_divideConquer(int A[], int s, int e)
{
	if (s == e)
		return A[s];

	int mid = (s + e) / 2;
	int left = -INF;
	int right = -INF;
	int sum = 0;

	for (int i = mid; i >= s; i--)
	{
		sum += A[i];
		left = max(left, sum);
	}

	sum = 0;
	for (int i = mid + 1; i <= e; i++)
	{
		sum += A[i];
		right = max(right, sum);
	}

	int single = max(rMaxSubarray_divideConquer(A, s, mid), rMaxSubarray_divideConquer(A, mid + 1, e));

	return max(left + right, single);
}

int maxSubarray_divideConquer(int A[], int n)
{
	return rMaxSubarray_divideConquer(A, 0, n - 1);
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
	printf("%d\n", maxSubarray_divideConquer(A, N));
	return 0;

}