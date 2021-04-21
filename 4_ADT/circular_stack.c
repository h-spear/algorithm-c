#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef int element;
typedef struct {
	element data[SIZE];
	int top;
	int n;
}StackType;

void init(StackType* s)
{
	s->top = -1;
	s->n = 0;
}

int size(StackType* s)
{
	return s->n;
}

int is_empty(StackType* s)
{
	return s->n == 0;
}

void push(StackType* s, element item)
{
	s->top = (s->top + 1) % SIZE;
	if (s->n != SIZE)
		s->n++;
	s->data[s->top] = item;
}

element pop(StackType* s)
{
	if (!is_empty(s))
	{
		int data = s->data[s->top];
		if (s->n != 0)
			s->n--;
		s->top = (s->top - 1 + SIZE) % SIZE;
		return data;
	}
	return (element)-1;
}

element top(StackType* s)
{
	return s->data[s->top];
}

void print(StackType* s)
{
	int t = s->top;
	for (int i = 0; i < s->n; i++)
	{
		printf("%d ", s->data[t]);
		t = (t - 1 + SIZE) % SIZE;
	}
	printf("\n");
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
	print(&s);

	push(&s, 6);
	push(&s, 7);
	push(&s, 8);
	push(&s, 9);
	print(&s);

	printf("top : %d, size : %d\n", top(&s), size(&s));

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("size : %d\n", size(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));

	return 0;
}