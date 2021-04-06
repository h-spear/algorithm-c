#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_ELEMENT 100
#define SIZE 15

#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

struct Heap
{
	int H[MAX_ELEMENT];
	int n;
}_Heap;


void downHeap(int i)
{
	if (i * 2 > _Heap.n)
		return;

	if (_Heap.H[i] < _Heap.H[i * 2] || _Heap.H[i] < _Heap.H[i * 2 + 1])
	{
		int temp;
		if (_Heap.H[i * 2] > _Heap.H[i * 2 + 1])
		{
			SWAP(_Heap.H[i], _Heap.H[i * 2], temp);
			downHeap(i * 2);
		}
		else
		{
			SWAP(_Heap.H[i], _Heap.H[i * 2 + 1], temp);
			downHeap(i * 2 + 1);
		}
	}
}

void buildHeap()
{
	for (int i = _Heap.n / 2; i >= 1; i--)
		downHeap(i);
}

int removeMax()
{
	int key = _Heap.H[1];
	_Heap.H[1] = _Heap.H[_Heap.n--];
	downHeap(1);
	return key;
}

void inPlaceHeapSort()
{
	int size = _Heap.n;
	int key; 

	for (int i = 0; i < size; i++)
	{
		key = removeMax();
		_Heap.H[_Heap.n + 1] = key;
	}
}

void printHeap()
{
	for (int i = 1; i <= _Heap.n; i++)
		printf("[%d] ", _Heap.H[i]);
	printf("\n");
}

void printArray()
{
	for (int i = 1; _Heap.H[i] > 0; i++)
	{
		printf("[%d] ", _Heap.H[i]);
		Sleep(200);
	}
	printf("\n");
}

int main()
{
	_Heap.n = 0;
	srand(time(NULL));

	for (int i = 1; i <= SIZE; i++)
	{
		_Heap.H[i] = (rand() % 99) + 1;
		_Heap.n++;
	}
	printHeap();
	printf("\n");

	// Max Heap 생성
	buildHeap();
	printf("buildHeap\n");
	printHeap();

	// inPlaceHeapSort
	getchar();
	printf("HeapSort\n");
	inPlaceHeapSort();
	printArray();

	return 0;
}