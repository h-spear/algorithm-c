#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_ELEMENT 100
#define MAX_STACK_SIZE 100

typedef struct {
	int heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

typedef struct {
	int data[MAX_STACK_SIZE];
	int top;
}StackType;

// stack
void init_stack(StackType *s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return s->top == -1;
}

void push(StackType* s, int item)
{
	s->data[++s->top] = item;
}

int pop(StackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "stack empty\n");
		return -1;
	}
	return s->data[s->top--];
}

// heap
void init_heap(HeapType *h)
{
	h->heap_size = 0;
}

void upHeap(HeapType* h)
{
	int i = h->heap_size;
	int key = h->heap[i];
	while (i != 1 && (key < h->heap[i / 2]))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = key;
}

void insertItem(HeapType* h, int item)
{
	h->heap_size++;
	h->heap[h->heap_size] = item;
	upHeap(h);
}

void printHeap(HeapType* h)
{
	for (int i = 1; i <= h->heap_size; i++)
		printf("[%d] ", h->heap[i]);
	printf("\n");
}

// findLastNode
void binaryExpansion(int i, StackType* s)
{
	while (i >= 2)
	{
		push(s, i % 2);
		i /= 2;
	}
	push(s, i);
	return;
}

int findLastNode(int v, int n)
{
	StackType s;
	init_stack(&s);
	binaryExpansion(n, &s);
	pop(&s);

	while (!is_empty(&s))
	{
		int bit = pop(&s);
		if (bit == 0)
			v = v * 2;
		else
			v = v * 2 + 1;
	}
	return v;
}

int main()
{
	HeapType h;
	init_heap(&h);

	srand(time(NULL));
	for (int i = 0; i < 15; i++)
		insertItem(&h, rand() % 100);

	printHeap(&h);
	printf("\n");

	printf("힙의 마지막 노드 %d의 값은 %d\n", findLastNode(1, h.heap_size), h.heap[findLastNode(1, h.heap_size)]);
	return 0;
}