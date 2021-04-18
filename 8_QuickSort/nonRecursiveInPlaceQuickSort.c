#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20
#define STACK_SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

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
	return s->top == -1;
}

void push(StackType* s, int item)
{
	s->data[++s->top] = item;
}

int pop(StackType* s)
{
	return s->data[s->top--];
}

int partition(int list[], int left, int right, int k)
{
	int pivot, low, high, temp;
	pivot = list[k];
	low = left - 1;
	high = right;
	SWAP(list[k], list[right], temp);

	do
	{
		do
			low++;
		while (list[low] < pivot);

		do
			high--;
		while (list[high] > pivot);

		if (high > low)
			SWAP(list[low], list[high], temp);
	} while (high > low);

	SWAP(list[low], list[right], temp);
	return low;
}

void nonRecursiveInPlaceQuickSort(int list[], int left, int right)
{
	StackType s;
	init(&s);
	push(&s, left);
	push(&s, right);

	while (!is_empty(&s))
	{
		int start, end, q;
		end = pop(&s);
		start = pop(&s);
		int k = rand() % (end - start + 1) + start;
		q = partition(list, start, end, k);

		if ((q - 1) > start)
		{
			push(&s, start);
			push(&s, q - 1);
		}

		if ((q + 1) < end)
		{
			push(&s, q + 1);
			push(&s, end);
		}

	}
}

int main()
{
	int list[MAX_SIZE];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_SIZE; i++)
		list[i] = rand() % 100;

	for (int i = 0; i < MAX_SIZE; i++)
		printf("%d ", list[i]);
	printf("\n\n");

	//quick_sort(list, 0, MAX_SIZE - 1);
	nonRecursiveInPlaceQuickSort(list, 0, MAX_SIZE - 1);

	for (int i = 0; i < MAX_SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}