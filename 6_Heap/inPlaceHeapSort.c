#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_ELEMENT 100
#define SIZE 15
#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

typedef struct {
	int heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void printHeap(HeapType* h)
{
	for (int i = 1; i <= h->heap_size; i++)
		printf("[%d] ", h->heap[i]);
	printf("\n");
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

void downHeap(HeapType* h, int i, int last)
{
	int left = 2 * i;
	int right = 2 * i + 1;
	int temp;


	if (left > last)
		return;
	int greater = left;
	if (right <= last)
		if (h->heap[right] > h->heap[greater])
			greater++;
	if (h->heap[i] < h->heap[greater])
	{
		SWAP(h->heap[i], h->heap[greater], temp);
		downHeap(h, greater, last);
	}
}

void buildHeap(HeapType* h, int i)
{
	/*
	if (i * 2 <= h->heap_size)
		buildHeap(h, i * 2);
	if (i * 2 + 1 <= h->heap_size)
		buildHeap(h, i * 2 + 1);
	downHeap(h, i, h->heap_size);
	*/
	for (int i = h->heap_size / 2; i >= 1; i--) 
		downHeap(h, i, h->heap_size);
	return;
}

void inPlaceHeapSort(HeapType* h)
{
	int temp;
	buildHeap(h, 1);
	for (int i = h->heap_size; i > 1; i--)
	{
		SWAP(h->heap[1], h->heap[i], temp);
		downHeap(h, 1, i - 1);
	}
	return;
}

int main()
{
	HeapType heap;
	init(&heap);

	srand(time(NULL));
	for (int i = 1; i <= SIZE; i++)
	{
		heap.heap[i] = rand() % 100;
		heap.heap_size++;
	}
	printHeap(&heap);
	printf("\n");
	inPlaceHeapSort(&heap);
	printHeap(&heap);
}