#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

typedef struct {
	int data[STACK_SIZE];
	int top;
}StackType;

StackType s1;
StackType s2;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == STACK_SIZE - 1);
}

void push(StackType* s, int data)
{
	s->data[++s->top] = data;
}

int pop(StackType* s)
{
	return s->data[s->top--];
}

void enqueue(int data)
{
	if (is_full(&s1))
	{
		fprintf(stderr, "stack s1 full!\n");
		exit(1);
	}
	push(&s1, data);
}

int dequeue()
{
	if (is_empty(&s2))
	{
		while (!is_empty(&s1))
			push(&s2, pop(&s1));
	}
	return pop(&s2);
}

int main()
{
	init_stack(&s1);
	init_stack(&s2);

	printf("enqueue : 1,3,5,7,9\n");
	enqueue(1);
	enqueue(3);
	enqueue(5);
	enqueue(7);
	enqueue(9);

	getchar();

	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	return 0;
}