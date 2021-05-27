#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

typedef struct {
	int V[N];
	int n;
}ArrayList;

void init(ArrayList* L)
{
	L->n = 0;
}

void insertItem(ArrayList* L, int item)
{
	for (int i = L->n - 1; i >= 0; i--)
	{
		L->V[i + 1] = L->V[i];
	}
	L->V[0] = item;
	L->n++;
}

void findElement(ArrayList* L, int item)
{
	int i, j;
	for (i = 0; i < L->n; i++)
	{
		if (L->V[i] == item)
		{
			printf("found!\n");
			for (j = i - 1; j >= 0; j--)
				L->V[j + 1] = L->V[j];
			L->V[0] = item;
			return;
		}
	}
	printf("Not found!\n");
}

void print(ArrayList* L)
{
	for (int i = 0; i < L->n; i++)
		printf("%d ", L->V[i]);
	printf("\n");
}

int main()
{
	ArrayList list;
	init(&list);

	for (int i = 0; i < 10; i++)
		insertItem(&list, i);
	print(&list);

	int n;
	printf("\nfind Element: ");
	scanf_s("%d", &n);
	findElement(&list, n);
	print(&list);
	return 0;
}