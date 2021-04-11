#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t=x),(x=y),(y=t))
#define MAX_ELEMENT 100

typedef struct {
	int heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}

void downHeap(HeapType* h, int i, int last)
{
	int left = 2 * i;
	int right = 2 * i + 1;
	if (left > last)
		return;

	int temp;
	int greater = left;
	if (right <= last)
		if (h->heap[right] > h->heap[greater])
			greater = right;
	if (h->heap[i] < h->heap[greater])
	{
		SWAP(h->heap[i], h->heap[greater], temp);
		downHeap(h, greater, last);
	}
}

void buildHeap(HeapType* h)
{
	for (int i = h->heap_size / 2; i >= 1; i--)
		downHeap(h, i, h->heap_size);
}

void rBuildHeap(HeapType* h, int i)
{
	if (i > h->heap_size)
		return;
	if (i * 2 <= h->heap_size)
		rBuildHeap(h, 2 * i);
	if (i * 2 + 1 <= h->heap_size)
		rBuildHeap(h, 2 * i + 1);
	downHeap(h, i, h->heap_size);
}

void printHeap(HeapType* h)
{
	for (int i = 1; i <= h->heap_size; i++)
		printf("[%d] ", h->heap[i]);
	printf("\n");
}

void inPlaceHeapSort(HeapType* h)
{
	int temp;
	//rBuildHeap(h,1);
	buildHeap(h);
	for (int i = h->heap_size; i >= 2; i--)
	{
		SWAP(h->heap[1], h->heap[i], temp);
		downHeap(h, 1, i - 1);
	}
}

int main()
{
	HeapType heap;
	int num;

	init(&heap);

	printf("원소의 개수? : ");
	scanf_s("%d", &num);
	printf("입력 리스트 : ");
	
	for (int i = 1; i <= num; i++)
	{
		int element;
		scanf_s("%d", &element);
		heap.heap[i] = element;
		heap.heap_size++;
	}
	printHeap(&heap);
	printf("\n");

	inPlaceHeapSort(&heap);
	printHeap(&heap);
}