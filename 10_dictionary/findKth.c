#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
int S[SIZE] = { 1,2,6,7,8,9,13,123 };
int T[SIZE] = { 3,4,5,10,15,16,17,20 };

int rFindKth(int k, int ls, int rs, int lt, int rt)
{
	if (ls > rs)
		return T[lt + k - 1];
	if (lt > rt)
		return S[ls + k - 1];

	int mids = (ls + rs) / 2;
	int midt = (lt + rt) / 2;
	int sl = mids - ls + 1;
	int tl = midt - lt + 1;
	if (k == sl + tl)
	{
		if (S[mids] < T[midt])
			return rFindKth(k - sl, mids + 1, rs, lt, midt);
		else
			return rFindKth(k - tl, ls, mids, midt + 1, rt);
	}
	else if (k < sl + tl)
	{
		if (S[mids] < T[midt])
			return rFindKth(k, ls, rs, lt, midt - 1);
		else
			return rFindKth(k, ls, mids - 1, lt, rt);
	}
	else
	{
		if (S[mids] < T[midt])
			return rFindKth(k - sl, mids + 1, rs, lt, rt);
		else
			return rFindKth(k - tl, ls, rs, midt + 1, rt);
	}
}

int findKth(int k)
{
	return rFindKth(k, 0, SIZE - 1, 0, SIZE - 1);
}

void print(int A[], int n)
{
	for (int i = 0; i < n; i++)
		printf("[%d] ", A[i]);
	printf("\n");
}

int main()
{
	print(S, SIZE);
	print(T, SIZE);
	printf("%d\n", findKth(15));
	return 0;
}