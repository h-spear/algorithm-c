#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8

typedef struct {
	int idx;
	int num;
}DictType;

void makeDict(DictType D[], int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		D[i].idx = i;
		D[i].num = A[i];
	}
}

void calcCost(DictType d[], int left, int right)
{
	int mid, cost  = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		cost++;
		if (d[mid].num == d[mid].idx)
		{
			printf("서랍 %d의 비밀번호 %d를 찾는데 비용이 %d원 들었습니다.\n", d[mid].num, d[mid].idx, cost);
			return;
		}
		else if (d[mid].num < d[mid].idx)
			left = mid + 1;
		else
			right = mid - 1;
	}
	printf("비밀번호가 일치하는 서랍이 없습니다.\n");
	return;
}

void unlockCost(int lock[], int n)
{
	DictType D[N];
	makeDict(D, lock, n);
	calcCost(D, 0, n - 1);
	return;
}

int main()
{
	int lock1[N] = { -3,-1,1,2,4,7,9,11 };
	int lock2[N] = { 2,4,6,8,10,12,14,16 };
	int lock3[N] = { -1,0,1,2,3,4,5,7 };
	int lock4[N] = { 0,3,4,6,9,10,11,13 };

	unlockCost(lock1, N);
	unlockCost(lock2, N);
	unlockCost(lock3, N);
	unlockCost(lock4, N);
	return 0;
}