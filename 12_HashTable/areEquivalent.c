#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10

typedef struct HashNode {
	int key;
	struct HashNode* next;
}HashType;

typedef struct NODE {
	int data;
	struct NODE* next;
}NODE;

typedef struct {
	NODE* head;
}LinkedListType;

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void initList(LinkedListType* L)
{
	L->head = NULL;
}

void insertItemToList(LinkedListType* L, int item)
{
	NODE* newnode = (NODE*)xmalloc(sizeof(NODE));
	newnode->data = item;
	newnode->next = L->head;
	L->head = newnode;
	return;
}

void printList(LinkedListType* L)
{
	NODE* p;
	for (p = L->head; p != NULL; p = p->next)
		printf("%d ", p->data);
	printf("\n");
}

void init(HashType* HT)
{
	for (int i = 0; i < M; i++)
	{
		HT->key = 0;
		HT->next = NULL;
	}
}

int h(int key)
{
	return key % M;
}

void insertItem(HashType* HT, int key)
{
	int v = h(key);
	HashType* node = (HashType*)xmalloc(sizeof(HashType));
	node->key = key;
	node->next = HT[v].next;
	HT[v].next = node;
}

int findElement(HashType* HT, int key)
{
	int v = h(key);
	HashType* p;
	for (p = HT[v].next; p != NULL; p = p->next)
		if (p->key == key)
			return 1;
	return 0;
}

int areEquivalent(LinkedListType* L1, LinkedListType* L2)
{
	NODE* p = L1->head;
	NODE* q = L2->head;
	for (; p != NULL && q != NULL; p = p->next, q = q->next)
		;
	if (p != NULL || q != NULL)
		return 0;
	
	HashType HT[M];
	init(HT);

	for (p = L1->head; p != NULL; p = p->next)
		insertItem(HT, p->data);

	for (q = L2->head; q != NULL; q = q->next)
	{
		if (!findElement(HT, q->data))
			return 0;
	}
	return 1;
}

int main()
{

	LinkedListType L1, L2;
	initList(&L1);
	initList(&L2);

	for (int i = 20; i >= 1; i--)
	{
		insertItemToList(&L1, i);
		insertItemToList(&L2, i);
	}

	printList(&L1);
	printList(&L2);
	printf("%d\n", areEquivalent(&L1, &L2));
	return 0;
}