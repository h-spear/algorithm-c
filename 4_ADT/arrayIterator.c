#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

typedef struct {
	int V[SIZE];
	int n;
}arrayList;

void init(arrayList* A)
{
	A->n = 0;
}

void append(arrayList* A, int item)
{
	A->V[A->n] = item;
	A->n++;
}

void iterator(arrayList* A)
{
	for (int i = 0; i < A->n; i++)
		printf("[%d] ", A->V[i]);
	printf("\n");
}

int main()
{
	arrayList list;
	init(&list);

	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		append(&list, rand() % 100);
	
	iterator(&list);
	return 0;
}