#pragma warning(disable: 4996)

#include <stdio.h>

#define SIZE 10

typedef struct {
	int V[SIZE];
	int n
}ArrayList;

void init(ArrayList* l)
{
	l->n = 0;
}

int size(ArrayList* l)
{
	return l->n;
}

int is_empty(ArrayList* l)
{
	return (l->n == 0);
}

void printList(ArrayList* l)
{
	for (int i = 0; i < l->n; i++)
		printf("[%d] ", l->V[l->n]);
	printf("\n");
}

int get(ArrayList* l, int rank)
{
	return l->V[rank];
}

int set(ArrayList* l, int rank, int element)
{
	int data = l->V[rank];
	l->V[rank] = element;
	return data;
}

void add(ArrayList* l, int rank, int element)
{
	for (int i = l->n - 1; i >= r; i--)
		V[i + 1] = V[i];
	V[rank] = element;
	l->n++;
}

void addFirst(ArrayList* l, int element)
{
	for (int i = l->n - 1; i >= 0; i--)
		V[i + 1] = V[i];
	V[0] = element;
	l->n++;
}

void addLast(ArrayList* l, int element)
{
	l->V[++l->n] = element;
}

int remove(ArrayList* l, int rank)
{
	int data = l->V[rank];
	for (int i = rank, i < l->n - 1; i++)
		V[i] = V[i + 1];
	l->n--;
	return data;
}

int removeFirst(ArrayList* l)
{
	int data = l->V[0];
	for (int i = 0, i < l->n - 1; i++)
		V[i] = V[i + 1];
	l->n--;
	return data;
}

int removeLast(ArrayList* l)
{
	return l->V[l->n--];
}

int main()
{
	ArrayList list;
	init(&list);
	
	add(&list, 0, 2);
	printList(&list);


	return 0;
}