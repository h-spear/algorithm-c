
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
	int V[SIZE];
	int n;
}ArrayList;

void init(ArrayList* L)
{
	L->n = 0;
}

void add(ArrayList* L, int pos, int item)
{
	if (L->n == SIZE)
	{
		printf("fullListException...\n");
		exit(1);
	}
	if (pos < 0 || pos > L->n)
	{
		printf("invalidPosException...\n");
		exit(1);
	}

	for (int i = L->n - 1; i >= pos; i--)
		L->V[i + 1] = L->V[i];
	L->V[pos] = item;
	L->n++;
}

void buildList(ArrayList* A, int n)
{
	for (int r = 0; r < n; r++)
		add(A, r, r + 1);
	return;
}
int runSimulation(ArrayList* A, int n, int k)
{
	int r = 0;
	while (n > 1)
	{
		int i = 0;
		while (i < k)
		{
			r = (r + 1) % A->n;
			if (A->V[r] != 0)
				i++;
		}
		A->V[r] = 0;
		n--;
		while (A->V[r] == 0)
			r = (r + 1) % A->n;
	}
	return A->V[r];
}

int candle(int n, int k)
{
	ArrayList A;
	init(&A);
	buildList(&A, n);
	return runSimulation(&A, n, k);
}

int main()
{
	int n, k;
	int ans;
	printf("배열_ver.1\n(n, k) 입력 : ");
	scanf("%d %d", &n, &k);
	ans = candle(n, k);
	printf("　　　 　답 : %d\n", ans);
	return 0;
}



