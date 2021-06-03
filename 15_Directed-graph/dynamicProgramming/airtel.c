#include <stdio.h>
#include <stdlib.h>

#define N 6
#define INF 100000000

int A[N] = { 0,1,3,6,11,17 };		// 항공요금
int H[N] = { 0,2,5,1,5,0 };			// 숙박요금
int m[N];

// 분할통치 O(2^n)
int rAirtelForward(int d)
{
	if (d == 0)
		return 0;
	int mincost = INF;
	int cost;
	for (int k = 0; k < d; k++)
	{
		cost = rAirtelForward(k) + H[k] + A[d - k];
		mincost = min(cost, mincost);
	}
	return mincost;
}

int rAirtelBackward(int s)
{
	if (s == N - 1)
		return 0;
	int mincost = INF;
	int cost;
	for (int k = s + 1; k < N; k++)
	{
		cost = A[k - s] + H[k] + rAirtelBackward(k);
		mincost = min(cost, mincost);
	}
	return mincost;
}

// dynamic prog. O(n^2)
int airtel(int n)
{
	m[0] = 0;
	int cost;
	for (int d = 1; d < n; d++)
	{
		m[d] = INF;
		for (int k = 0; k < d; k++)
		{
			cost = m[k] + H[k] + A[d - k];
			m[d] = min(m[d], cost);
		}
	}
	return m[n - 1];
}

int main()
{
	printf("%d\n", rAirtelForward(N - 1));
	printf("%d\n", rAirtelBackward(0));
	printf("%d\n", airtel(N));
	return 0;
}