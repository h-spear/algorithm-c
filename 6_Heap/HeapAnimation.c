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
	printf("upHeap : ");
	printHeap(h);
	upHeap(h, i / 2);
}

void insertItem(HeapType* h, int item)
{
	printf("삽입 전 : ");
	printHeap(h);
	h->heap_size++;
	h->heap[h->heap_size] = item;
	printf("삽입 후 : ");
	printHeap(h);
	upHeap(h,h->heap_size);
}

/*
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
*/

void downHeap(HeapType* h, int i,int last)
{
	int left = i * 2;
	int right = left + 1;
	if (left > last)
		return;

	int temp;
	int greater = left;
	if (right <= last)
		if (h->heap[greater] < h->heap[right])
			greater = right;
	if (h->heap[i] < h->heap[greater])
	{
		SWAP(h->heap[i], h->heap[greater], temp);
		printf("downHeap : ");
		printHeap(h);
		downHeap(h, greater,last);
	}
}

int removeMax(HeapType* h)
{
	printf("삭제 전 : ");
	printHeap(h);
	int data = h->heap[1];
	h->heap[1] = h->heap[h->heap_size--];
	printf("삭제 후 : ");
	printHeap(h);
	downHeap(h, 1,h->heap_size);
	return data;
}

int main()
{
	HeapType heap;
	init(&heap);
	srand(time(NULL));
	printf("힙 애니메이션 \n");
	printf("====================================\n\n");
	for (int i = 0; i < 10; i++)
	{
		int item = rand() % 100;
		printf("%d번째 원소 삽입(%d)\n", i, item);
		insertItem(&heap, item);
		printf("\n====================================\n\n");
	}

	for (int i = 0; i < 10; i++)
	{
		printf("Max 원소 삭제\n");
		printf("원소 반환 : %d\n", removeMax(&heap));
		printf("\n====================================\n\n");
	}
}