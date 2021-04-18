#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int data;
	struct NODE* prev, * next;
}NODE;

typedef struct {
	NODE* head;
	NODE* tail;
}LinkedQueue;

NODE* getnode()
{
	NODE* p;
	p = (NODE*)malloc(sizeof(NODE));
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void init(LinkedQueue* q)
{
	q->head = getnode();
	q->tail = getnode();
	q->head->next = q->tail;
	q->tail->prev = q->head;
}

int is_empty(LinkedQueue* q)
{
	return ((q->head->next == q->tail) && (q->tail->prev == q->head));
}

int front(LinkedQueue* q)
{
	return q->head->next->data;
}

void enqueue(LinkedQueue* q, int item)
{
	NODE* newnode = getnode();
	newnode->data = item;
	newnode->next = q->tail;
	newnode->prev = q->tail->prev;
	q->tail->prev->next = newnode;
	q->tail->prev = newnode;
}

int dequeue(LinkedQueue* q)
{
	if (is_empty(q))
	{
		printf("empty\n");
		return -1;
	}
	int data;
	NODE* removed = q->head->next;
	data = removed->data;
	removed->next->prev = q->head;
	q->head->next = removed->next;
	free(removed);
	return data;
}

void printQueue(LinkedQueue* q)
{
	for (NODE* p = q->head->next; p != q->tail; p = p->next)
		printf("%d ", p->data);
	printf("\n");
}

int main()
{
	LinkedQueue queue;
	init(&queue);

	enqueue(&queue, 1);
	enqueue(&queue, 2);
	enqueue(&queue, 3);
	enqueue(&queue, 4);
	enqueue(&queue, 5);
	printQueue(&queue);

	printf("\n%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	return 0;
}