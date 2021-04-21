#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node* next;
}node;

typedef struct {
	node* head;
	int size;
}LinkedListType;

typedef struct {
	LinkedListType LT;
	LinkedListType EQ;
	LinkedListType GT;
}partition_set;

void init(LinkedListType* L)
{
	L->head = NULL;
	L->size = 0;
}

node* getnode()
{
	node* p;
	p = (node*)malloc(sizeof(node));
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void addLast(LinkedListType* L, int item)
{
	node* new = getnode();
	node* p = L->head;

	new->data = item;
	new->next = NULL;

	if (p == NULL)
	{
		L->head = new;
		L->size++;
		return;
	}
	
	for(;p->next!=NULL;p=p->next)
		;
	p->next = new;
	L->size++;
}

int get(LinkedListType* L, int pos)
{
	node* p = L->head;
	for (int i = 1; i < pos; i++)
		p = p->next;
	return p->data;
}

int removeFirst(LinkedListType* L)
{
	node* removed = L->head;
	if (removed == NULL)
		return -1;

	int data = removed->data;
	L->head = removed->next;
	L->size--;
	free(removed);
	return data;
}

int size(LinkedListType* L)
{
	return L->size;
}

void print(LinkedListType* L)
{
	for (node* p = L->head; p != NULL; p = p->next)
		printf("%d -> ", p->data);
	printf("NULL\n");
}

partition_set partition(LinkedListType* L, int k)
{
	int p = get(L, k);
	LinkedListType LT, EQ, GT;
	partition_set result;
	init(&LT);
	init(&EQ);
	init(&GT);

	while (size(L) != 0)
	{
		int e = removeFirst(L);
		if (e < p)
			addLast(&LT, e);
		else if (e == p)
			addLast(&EQ, e);
		else
			addLast(&GT, e);
	}
	result.LT = LT;
	result.EQ = EQ;
	result.GT = GT;
	return result;
}

LinkedListType merge(LinkedListType* LT, LinkedListType* EQ, LinkedListType* GT)
{
	LinkedListType L;
	init(&L);

	while (size(LT) != 0)
		addLast(&L, removeFirst(LT));
	while (size(EQ) != 0)
		addLast(&L, removeFirst(EQ));
	while (size(GT) != 0)
		addLast(&L, removeFirst(GT));

	return L;
}

void quickSort(LinkedListType* L)
{
	if (size(L) > 1)
	{
		int k = rand() % size(L) + 1;
		partition_set q = partition(L, k);
		quickSort(&q.LT);
		quickSort(&q.GT);
		*L = merge(&q.LT, &q.EQ, &q.GT);
	}
}

int main()
{
	LinkedListType L;
	init(&L);
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 15; i++)
		addLast(&L, rand() % 100);

	print(&L);
	printf("\n");

	quickSort(&L);
	print(&L);
	return 0;
}