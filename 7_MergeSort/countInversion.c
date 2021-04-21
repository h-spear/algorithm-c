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
	LinkedListType L1;
	LinkedListType L2;
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
	partition_set result;
	LinkedListType L1, L2;

	L1.head = L->head;
	node* p = L->head;
	for (int i = 2; i <= k; i++)
		p = p->next;
	L2.head = p->next;
	p->next = NULL;
	L1.size = k;
	L2.size = L->size - k;

	result.L1 = L1;
	result.L2 = L2;
	return result;
}

LinkedListType merge(LinkedListType* L1, LinkedListType* L2, int* ptr)
{
	LinkedListType L;
	init(&L);

	while (size(L1) != 0 && size(L2) != 0)
	{
		if (get(L1, 1) <= get(L2, 1))
			addLast(&L, removeFirst(L1));
		else
		{
			*ptr += size(L1);
			addLast(&L, removeFirst(L2));
		}
	}
	while (size(L1) != 0)
		addLast(&L, removeFirst(L1));
	while (size(L2) != 0)
		addLast(&L, removeFirst(L2));
	return L;
}

void mergeSort(LinkedListType* L, int* ptr)
{
	if (size(L) > 1)
	{
		partition_set p = partition(L, L->size / 2);
		LinkedListType L1 = p.L1;
		LinkedListType L2 = p.L2;
		mergeSort(&L1, ptr);
		mergeSort(&L2, ptr);
		*L = merge(&L1, &L2, ptr);
	}
	return;
}

int countInversion(LinkedListType* L)
{
	int cnt = 0;
	int* ptr = &cnt;

	mergeSort(L, ptr);
	return cnt;
}

int main()
{
	LinkedListType L;
	init(&L);
	srand(time(NULL));

	addLast(&L, 6);
	addLast(&L, 1);
	addLast(&L, 8);
	addLast(&L, 2);
	addLast(&L, 3);
	addLast(&L, 5);
	addLast(&L, 7);
	addLast(&L, 4);


	print(&L);
	printf("\n");

	printf("%d", countInversion(&L));
	return 0;
}