#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

typedef struct {
	int data[STACK_SIZE];
	int top;
}StackType;

typedef struct {
	StackType s1;
	StackType s2;
}QueueType;

void init_queue(QueueType* q)
{
	q->s1.top = -1;
	q->s2.top = -1;
}

int is_stackFull(StackType* s)
{
	return (s->top == STACK_SIZE - 1);
}

int is_stackEmpty(StackType* s)
{
	return s->top == -1;
}

void push(StackType* s, int data)
{
	s->data[++s->top] = data;
}

int pop(StackType* s)
{
	if (is_stackEmpty(s))
		return -1;
	return s->data[s->top--];
}

int peek(StackType* s)
{
	return s->data[s->top];
}

int is_empty(QueueType* q)
{
	return (is_stackEmpty(&(q->s1)) && is_stackEmpty(&(q->s2)));
}

void enqueue(QueueType* q, int data)
{
	if (is_stackFull(&(q->s1)))
	{
		fprintf(stderr, "stack s1 full!\n");
		exit(1);
	}
	push(&(q->s1), data);
}

int dequeue(QueueType* q)
{
	if (is_stackEmpty(&(q->s2)))
		while (!is_stackEmpty(&(q->s1)))
			push(&(q->s2), pop(&(q->s1)));
	return pop(&(q->s2));
}

int front(QueueType* q)
{
	if (is_stackEmpty(&(q->s2)))
		while (!is_stackEmpty(&(q->s1)))
			push(&(q->s2), pop(&(q->s1)));
	return peek(&(q->s2));
}

int main()
{
	QueueType q;
	init_queue(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);


	printf("%d\n", front(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	return 0;
}