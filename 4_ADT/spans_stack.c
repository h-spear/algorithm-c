#pragma warning(disable: 4996)

#include <stdio.h>

#define STACK_SIZE 100
#define SIZE 10

typedef struct {
	int data[STACK_SIZE];
	int top;
}StackType;

void init(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

void push(StackType* s, int item)
{
	s->data[++s->top] = item;
}

int pop(StackType* s)
{
	return s->data[s->top--];
}

int top(StackType* s)
{
	return s->data[s->top];
}

// O(n)
void spans(int X[], int S[], int n)
{
	StackType s;
	init(&s);

	for (int i = 0; i < n; i++)
	{
		while (!is_empty(&s) && (X[top(&s)] <= X[i]))
			pop(&s);

		if (is_empty(&s))
			S[i] = i + 1;
		else
			S[i] = i - top(&s);
		push(&s, i);
	}
	while (!is_empty(&s))
		pop(&s);
	return;
}

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%3d ", arr[i]);
	printf("\n");
}

int main()
{
	int X[SIZE] = { 60,30,40,10,20,30,50,40 };
	int S[SIZE];

	printf("X:");
	printArray(X, 8);
	spans(X, S, 8);

	printf("S:");
	printArray(S, 8);
	return 0;
}