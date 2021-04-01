#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* prev, * next;
}node;

node* getnode()
{
	node* newnode = malloc(sizeof(node));
	if (!newnode)
	{
		perror("xmalloc!");
		exit(1);
	}
	newnode->prev = NULL;
	newnode->next = NULL;
	return newnode;
}

typedef struct {
	node* head;
	node* tail;
}LinkedList;

void init(LinkedList* l)
{
	l->head = getnode();
	l->tail = getnode();
	l->head->next = l->tail;
	l->tail->prev = l->head;
}

void addLast(LinkedList* l, int data)
{
	node* new = getnode();
	new->data = data;
	new->next = l->tail;
	new->prev = l->tail->prev; 
	l->tail->prev->next = new;
	l->tail->prev = new;
}

// 홀수개의 node 존재
node* findmiddle(LinkedList* l)
{
	node* front = l->head->next;
	node* back = l->tail->prev;
	while (front != back)
	{
		front = front->next;
		back = back->prev;
	}
	return front;
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
	addLast(&list, 1);
	addLast(&list, 2);
	addLast(&list, 3);
	addLast(&list, 4);
	addLast(&list, 5);
	addLast(&list, 6);
	addLast(&list, 7);
	addLast(&list, 8);
	addLast(&list, 9);
	addLast(&list, 10);
	addLast(&list, 11);
	viewAll(&list);

	node* find = findmiddle(&list);
	printf("find : %d\n", find->data);

	return 0;
}