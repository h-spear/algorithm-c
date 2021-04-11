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

void upHeap(HeapType* h, int i)
{
	if (i == 1)
		return;
	if (h->heap[i / 2] >= h->heap[i])
		return;
	int temp;
	SWAP(h->heap[i / 2], h->heap[i], temp);
	upHeap(h, i / 2);
}

void downHeap(HeapType* h, int i)
{
	int left = i * 2;
	int right = left + 1;
	if (left > h->heap_size)
		return;

	int temp;
	int greater = left;
	if (right <= h->heap_size)
		if (h->heap[greater] < h->heap[right])
			greater = right;
	if (h->heap[i] < h->heap[greater])
	{
		SWAP(h->heap[i], h->heap[greater], temp);
		downHeap(h, greater);
	}
}

void insertItem(HeapType* h, int item)
{
	h->heap_size++;
	h->heap[h->heap_size] = item;
	upHeap(h, h->heap_size);
}

void replaceKey(HeapType* h, int r, int item)
{
	h->heap[r] = item;
	if (r != 1 && (h->heap[r] > h->heap[r / 2]))
		upHeap(h, r);
	else if (r * 2 <= h->heap_size)
	{
		int greater = r * 2;
		if (r * 2 + 1 <= h->heap_size && (h->heap[greater] < h->heap[r * 2 + 1]))
			greater++;
		if (h->heap[r] < h->heap[greater])
			downHeap(h, r);
	}
	return;
}

int main()
{
	HeapType heap;
	init(&heap);
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int item = rand() % 100;
		insertItem(&heap, item);
	}
	printHeap(&heap);

	replaceKey(&heap, 5, 500);
	printHeap(&heap);
	return 0;
}