#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

typedef struct {
	int heap[100];
	int heap_size;
}HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}

void upHeap(HeapType* h, int i)
{
	if (i == 1)
		return;
	if (h->heap[i] >= h->heap[i / 2])
		return;
	int temp;
	SWAP(h->heap[i], h->heap[i / 2], temp);
	upHeap(h, i);
}

void insertItem(HeapType* h, int item)
{
	h->heap_size++;
	h->heap[h->heap_size] = item;
	upHeap(h, h->heap_size);
}

void downHeap(HeapType* h, int i, int last)
{
	int left = 2 * i;
	int right = 2 * i + 1;
	if (left > last)
		return;
	int greater = left;
	if (right <= last)
		if (h->heap[right] > h->heap[greater])
			greater++;
	if (h->heap[i] >= h->heap[greater])
		return;
	int temp;
	SWAP(h->heap[i], h->heap[greater], temp);
	downHeap(h, greater, last);
}

int removeMin(HeapType* h)
{
	int data = h->heap[1];
	h->heap[1] = h->heap[h->heap_size];
	h->heap_size--;
	downHeap(h, 1, h->heap_size);
	return data;
}

void findSmallerKeys(HeapType* h, int v, int x)
{
	if (h->heap[v] >= x)
		return;

	if (v * 2 <= h->heap_size)
		findSmallerKeys(h, v * 2, x);
	if (v * 2 + 1 <= h->heap_size)
		findSmallerKeys(h, v * 2 + 1, x);
	printf("%d ", h->heap[v]);
}

int main()
{
	HeapType h;
	init(&h);
	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 15; i++)
		insertItem(&h, rand() % 100);

	findSmallerKeys(&h, 1, 50);
}