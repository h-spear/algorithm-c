#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_ELEMENT 100
#define SIZE 15

typedef struct {
	int heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType* h)
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

void downHeap(HeapType* h)
{
	int temp = h->heap[1];
	int parent = 1, child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child] > h->heap[child + 1]))
			child++;
		if (temp <= h->heap[child])
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
}

int removeMin(HeapType* h)
{
	int key = h->heap[1];
	h->heap[1] = h->heap[h->heap_size];
	h->heap_size--;
	downHeap(h);
	return key;
}

void HeapSort(int list[], int n)
{
	HeapType h;
	init(&h);

	for (int i = 0; i < n; i++)
		insertItem(&h, list[i]);

	for (int i = 0; i < n; i++)
		list[i] = removeMin(&h);
}

void printArray(int list[], int n)
{
	for (int i = 0; i < n; i++)
		printf("[%d] ", list[i]);
	printf("\n");
}

int main()
{
	int list[SIZE];

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 100;

	printArray(list, SIZE);
	printf("\n");

	getchar();
	HeapSort(list, SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		printf("[%d] ", list[i]);
		Sleep(200);
	}
	printf("\n");
	return 0;
}