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

void buildHeap(HeapType* h)
{
	printf("for i <- %d downto 1\n\n", h->heap_size / 2);
	for (int i = h->heap_size / 2; i >= 1; i--)
	{
		printf("buildHeap i = %d\n", i);
		printf("시작 전 : ");
		printHeap(h);
		downHeap(h, i, h->heap_size);
		printf("\n");
	}
	return;
}

int main()
{
	HeapType heap;
	init(&heap);
	srand(time(NULL));
	printf("상향식 힙생성 애니메이션\n");
	printf("====================================\n\n");
	for (int i = 1; i <= 10; i++)
	{
		int item = rand() % 100;
		heap.heap[i] = item;
		heap.heap_size++;
	}
	printf("리스트\n");
	printHeap(&heap);

	printf("\n====================================\n\n");
	printf("buildHeap()\n");

	buildHeap(&heap);
	printf("최종 생성 힙\n");
	printHeap(&heap);
	printf("\n====================================\n\n");

	
}