#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* prev, * next;
}node;

typedef struct {
	node* head;
	node* tail;
}LinkedList;

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("xmalloc!");
		exit(1);
	}
	return p;
}

node* newnode(int data)
{
	node* newnode = xmalloc(sizeof(node));
	newnode->data = data;
	newnode->prev = NULL;
	newnode->next = NULL;
	return newnode;
}

void init(LinkedList *l)
{
	l->head = xmalloc(sizeof(node));
	l->tail = xmalloc(sizeof(node));
	l->head->next = l->tail;
	l->tail->prev = l->head;
}

void addFirst(LinkedList* l, int data)
{
	node* new = newnode(data);
	new->next = l->head->next;
	new->prev = l->head;
	l->head->next->prev = new;
	l->head->next = new;
}

void addLast(LinkedList* l, int data)
{
	node* new = newnode(data);
	new->next = l->tail;
	new->prev = l->tail->prev;
	l->tail->prev->next = new;
	l->tail->prev = new;
}

int removeFirst(LinkedList* l)
{
	node* removed = l->head->next;
	int data = removed->data;
	removed->next->prev = l->head;
	l->head->next = removed->next;
	free(removed);
	return data;
}

int removeLast(LinkedList* l)
{
	node* removed = l->tail->prev;
	int data = removed->data;
	removed->prev->next = l->tail;
	l->tail->prev = removed->prev;
	free(removed);
	return data;
}

void viewAll(LinkedList* l)
{
	printf("head -> ");
	for (node* p = l->head->next; p != l->tail; p = p->next)
		printf("| %d | -> ", p->data);
	printf("tail\n");
}

int main()
{
	LinkedList list;
	init(&list);

	addFirst(&list, 1);
	addFirst(&list, 2);
	addFirst(&list, 3);

	addLast(&list, 4);
	addLast(&list, 5);
	addLast(&list, 6);
	viewAll(&list);

	printf("\nremovedFirst : %d\n", removeFirst(&list));
	viewAll(&list);

	printf("\nremovedLast : %d\n", removeLast(&list));
	viewAll(&list);

	return 0;
}