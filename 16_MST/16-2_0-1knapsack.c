#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 7

typedef struct {
	float gain;
	float weight;
}obj;

typedef struct {
	obj S;
	float gainPerWeight;
	int idx;
}DictType;

void buildDict(obj S[], DictType D[])
{
	for (int i = 0; i < N; i++)
	{
		D[i].S = S[i];
		D[i].gainPerWeight = S[i].gain / S[i].weight;
		D[i].idx = i;
	}
}

void printDict(DictType D[], int n)
{
	for (int i = 0; i < n; i++)
		printf("weight %.0f of idx %d (gain = %.1f)\n", D[i].S.weight, D[i].idx, D[i].S.gain);
	printf("\n");
}

void insertion_sort(DictType D[])
{
	int i, j;
	DictType save;
	for (i = 1; i < N; i++)
	{
		save = D[i];
		for (j = i - 1; j >= 0 && D[j].gainPerWeight < save.gainPerWeight; j--)
			D[j + 1] = D[j];
		D[j + 1] = save;
	}
}

void calcDict(DictType D[], int n)
{
	float gain = 0, weight = 0;
	for (int i = 0; i < n; i++)
	{
		gain = gain + D[i].S.gain;
		weight = weight + D[i].S.weight;
	}
	printf("total weight = %.0f\ntotal gain = %.1f\n", weight, gain);
}

void zeroOne_Knapsack(obj S[], float w)
{
	DictType D[N];
	buildDict(S, D);
	insertion_sort(D);
	DictType result[N];
	int i = 0;
	float weight = 0;

	while (1)
	{
		if (D[i].S.weight > w)
			break;

		w = w - D[i].S.weight;
		result[i++] = D[i];
	}
	printDict(result, i);
	calcDict(result, i);
}

int main()
{
	obj S[N] = {
		{12,4},
		{10,6},
		{8,5},
		{11,7},
		{14,3},
		{7,1},
		{9,6}
	};
	zeroOne_Knapsack(S, 18);
	return 0;
}