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
}ListQueue;

node* getnode()
{
	node* p;
	p = malloc(sizeof(node));
	if(!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void initQueue(ListQueue* l)
{
	l->head = getnode();
	l->tail = getnode();
	l->head->next = l->tail;
	l->tail->prev = l->head;
}

int is_empty(ListQueue* l)
{
	return (l->head->next == l->tail && l->tail->prev == l->head);
}

int front(ListQueue* l)
{
	return l->head->next->data;
}

void enqueue(ListQueue* l, int data)
{
	node* newnode = getnode();
	newnode->data = data;
	newnode->next = l->tail;
	newnode->prev = l->tail->prev;
	l->tail->prev->next = newnode;
	l->tail->prev = newnode;
}

int dequeue(ListQueue* l)
{
	if (!is_empty(l))
	{
		node* front = l->head->next;
		int data = front->data;
		front->next->prev = l->head;
		l->head->next = front->next;
		free(front);
		return data;
	}
}


int main()
{
	ListQueue queue;
	initQueue(&queue);

	enqueue(&queue, 1);
	enqueue(&queue, 2);
	enqueue(&queue, 3);
	enqueue(&queue, 4);
	enqueue(&queue, 5);

	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));

	return 0;
}