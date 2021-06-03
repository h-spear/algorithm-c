#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define INF 100000000

int m[1000];

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

int rAirtel(int H[], int A[], int d)
{
	if (d == 0)
		return 0;

	int mincost, cost, k;
	mincost = INF;
	for (k = 0; k < d; k++)
	{
		cost = rAirtel(H, A, k) + H[k] + A[d - k];
		mincost = min(mincost, cost);
	}
	return mincost;
}

int airtel(int H[], int A[], int n)
{
	m[0] = 0;
	int cost, d, k;
	for (d = 1; d < n; d++)
	{
		m[d] = INF;
		for (k = 0; k < d; k++)
		{
			cost = m[k] + H[k] + A[d - k];
			m[d] = min(m[d], cost);
		}
	}
	return m[n - 1];
}

int main()
{
	int n;
	int* H, * A;

	scanf_s("%d", &n);

	H = (int*)xmalloc(sizeof(int) * n);
	A = (int*)xmalloc(sizeof(int) * n);

	printf("항공요금 (A[1] ~ A[%d]) : ", n - 1);
	for (int i = 1; i < n; i++)
		scanf_s("%d", &A[i]);

	printf("숙박요금 (H[1] ~ H[%d]) : ", n - 2);
	for (int i = 1; i < n - 1; i++)
		scanf_s("%d", &H[i]);

	H[0] = A[0] = H[n - 1] = 0;

	printf("\nA : ");
	for (int i = 0; i < n; i++)
		printf("%2d ", A[i]);

	printf("\nH : ");
	for (int i = 0; i < n; i++)
		printf("%2d ", H[i]);

	printf("\n%d\n", rAirtel(H, A, n - 1));
	printf("%d\n", airtel(H, A, n));
}