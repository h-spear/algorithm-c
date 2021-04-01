#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef int element;
typedef struct {
	element data[SIZE];
	element mins[SIZE];
	int min;
	int top;
}StackType;

void init(StackType* s)
{
	s->top = -1;
	s->min = 2000000000;
}

void push(StackType* s, int data)
{
	s->top++;
	s->data[s->top] = data;
	
	if (data < s->min)
		s->min = data;
	s->mins[s->top] = s->min;
}

element pop(StackType* s)
{
	return s->data[s->top--];
}

element findMin(StackType* s)
{
	return s->mins[s->top];
}

void printStack(StackType* s)
{
	printf("%d", s->data[s->top]);
	for (int i = s->top - 1; i >= 0; i--)
		printf("-%d", s->data[i]);
	printf("\n");
}

int main()
{
	StackType s;
	init(&s);
	char cmd[10];

	while (1)
	{
		printf("> ");
		scanf("%s", cmd);
		if (!strcmp(cmd, "p"))
		{
			element n;
			scanf("%d", &n);
			push(&s, n);
			printStack(&s);
		}
		else if (!strcmp(cmd, "o"))
		{
			pop(&s);
			printStack(&s);
		}
		else if (!strcmp(cmd, "f"))
			printf("%d\n", findMin(&s));
		else if (!strcmp(cmd, "q"))
			break;
		else
			printf("존재하지 않는 커맨드\n");
	}
	printf("(프로그램 종료)\n");
	return 0;
}