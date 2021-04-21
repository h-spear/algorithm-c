#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t=x),(x=y),(y=t))
#define SIZE 15

typedef struct DListNode {
	int elem;
	struct DListNode* prev, * next;
}DListNode;

typedef struct {
	DListNode* H;
	DListNode* T;
}SetType;

void initNode(DListNode* H, DListNode* T)
{
	H->next = T;
	T->prev = H;
}

DListNode* getnode()
{
	DListNode* p;
	p = (DListNode*)malloc(sizeof(DListNode));
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void initSet(SetType* s)
{
	s->H = getnode();
	s->T = getnode();
	s->H->prev = NULL;
	s->T->next = NULL;
	initNode(s->H, s->T);
}

void addLast(SetType* s, int item)
{
	DListNode* newnode = getnode();
	newnode->elem = item;
	newnode->next = s->T;
	newnode->prev = s->T->prev;
	s->T->prev->next = newnode;
	s->T->prev = newnode;
}

DListNode* removed(SetType* s, DListNode* removed)
{
	if (s->H == removed || s->T == removed)
		return s->H;

	DListNode* p = removed->next;
	removed->prev->next = removed->next;
	removed->next->prev = removed->prev;
	free(removed);
	return p;
}

void print(SetType* s)
{
	for (DListNode* p = s->H->next; p != s->T; p = p->next)
		printf("[%d] ", p->elem);
	printf("\n");
}

void selectionSort(SetType* s)
{
	DListNode* p = s->H->next;
	DListNode* q;
	DListNode* least;
	int temp;
	for (p; p->next->next != NULL; p = p->next)
	{
		least = p;
		for (q = p->next; q->next != NULL; q = q->next)
			if (q->elem < least->elem)
				least = q;
		SWAP(p->elem, least->elem, temp);
	}
}

int main()
{
	SetType* s = (SetType*)malloc(sizeof(SetType));
	initSet(s);

	srand((unsigned)time(NULL));
	for (int i = 0; i < SIZE; i++)
		addLast(s, rand() % 100);


	print(s);
	printf("\n");

	selectionSort(s);
	print(s);
	return 0;
}