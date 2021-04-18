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
	while (i != 1 && (key > h->heap[i / 2]))
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
		if ((child < h->heap_size) && (h->heap[child] < h->heap[child + 1]))
			child++;
		if (temp >= h->heap[child])
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
}

int removeMax(HeapType* h)
{
	int key = h->heap[1];
	h->heap[1] = h->heap[h->heap_size];
	h->heap_size--;
	downHeap(h);
	return key;
}

void printHeap(HeapType* h)
{
	for (int i = 1; i <= h->heap_size; i++)
		printf("[%d] ", h->heap[i]);
	printf("\n");
}

void inPlaceHeapSort(HeapType* h)
{
	int size = h->heap_size;
	int key;

	for (int i = 0; i < size; i++)
	{
		key = removeMax(h);
		h->heap[h->heap_size + 1] = key;
	}
}

int main()
{
	HeapType heap;
	init(&heap);

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		insertItem(&heap, (rand() % 99) + 1);
	}

	printHeap(&heap);
	printf("\n");


	getchar();
	inPlaceHeapSort(&heap);

	for (int i = 1; heap.heap[i] > 0; i++)
	{
		printf("[%d] ", heap.heap[i]);
		Sleep(200);
	}
	printf("\n");
	return 0;
}