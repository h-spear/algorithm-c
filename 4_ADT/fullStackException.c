#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
	int data[SIZE];
	int top;
}StackType;

void init(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return s->top == -1;
}

int is_full(StackType* s)
{
	return (s->top == SIZE - 1);
}

void fullStackException(StackType *s)
{
	for (int i = 0; i < s->top; i++)
		s->data[i] = s->data[i + 1];
	s->top--;
}

void push(StackType* s, int data)
{
	if (is_full(s))
	{
		fullStackException(s);
	}
	s->data[++s->top] = data;
}

int pop(StackType* s)
{
	if (is_empty(s))
	{
		perror("empty!\n");
		exit(1);
	}
	return s->data[s->top--];
}
int main()
{
	StackType s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	push(&s, 4);
	push(&s, 5);
	push(&s, 6);
	push(&s, 7);
	push(&s, 8);
	push(&s, 9);
	push(&s, 10);
	push(&s, 11);
	push(&s, 12);

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));

	return 0;
}