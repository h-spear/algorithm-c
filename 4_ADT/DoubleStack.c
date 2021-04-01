#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef int element;
typedef struct {
	element data[SIZE];
	int top1, top2;
}DoubleStackType;

void initStack(DoubleStackType* s)
{
	s->top1 = -1;
	s->top2 = SIZE;
}

int size(DoubleStackType* s, int index)
{
	if (index == 1)
		return s->top1 - 0 + 1;
	else if (index == 2)
		return SIZE - s->top2;
	return -1;
}

int is_empty(DoubleStackType* s, int index)
{
	if (index == 1)
		return s->top1 == -1;
	else if (index == 2)
		return s->top2 == SIZE;
	return -1;
}

int is_full(DoubleStackType* s, int index)
{
	if (index == 1)
		return s->top1 == SIZE / 2 - 1;
	else if (index == 2)
		return s->top2 == SIZE / 2;
	return -1;
}

element top(DoubleStackType* s, int index)
{
	if (index == 1)
		return s->data[s->top1];
	else if (index == 2)
		return s->data[s->top2];
	return -1;
}

void push(DoubleStackType* s, int index, element item)
{
	if (!is_full(s, index))
	{
		if (index == 1)
		{
			s->data[++s->top1] = item;
		}
		else if (index == 2)
			s->data[--s->top2] = item;
	}
}

element pop(DoubleStackType* s, int index)
{
	if (!is_empty(s, index))
	{
		if (index == 1)
			return s->data[s->top1--];
		else if (index == 2)
			return s->data[s->top2++];
	}
	return -1;
}

int main()
{
	DoubleStackType s;
	initStack(&s);

	// Stack1's Max Size = SIZE / 2
	// Stack2's Max Size = SIZE / 2     (SIZE is even)
	// Stack2's Max Size = SIZE / 2 + 1 (SIZE is odd)

	for (int i = 1; i <= SIZE; i++)
	{
		push(&s, 1, i);
		push(&s, 2, i+10);
	}

	printf("Stack1(%d) : pop %d\n", size(&s, 1), pop(&s, 1));
	printf("Stack1(%d) : pop %d\n", size(&s, 1), pop(&s, 1));
	printf("Stack1(%d) : top %d\n", size(&s, 1), top(&s, 1));
	printf("Stack1(%d) : pop %d\n", size(&s, 1), pop(&s, 1));
	printf("Stack1(%d) : pop %d\n", size(&s, 1), pop(&s, 1));
	printf("Stack1(%d) : pop %d\n\n", size(&s, 1), pop(&s, 1));

	printf("Stack2(%d) : pop %d\n", size(&s, 2), pop(&s, 2));
	printf("Stack2(%d) : pop %d\n", size(&s, 2), pop(&s, 2));
	printf("Stack2(%d) : top %d\n", size(&s, 2), top(&s, 2));
	printf("Stack2(%d) : pop %d\n", size(&s, 2), pop(&s, 2));
	printf("Stack2(%d) : pop %d\n", size(&s, 2), pop(&s, 2));
	printf("Stack2(%d) : pop %d\n", size(&s, 2), pop(&s, 2));
	return 0;
}