#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30

typedef struct {
	int value;
	int key;
}element;

typedef struct {
	element dict[N];
	int size;
}DictType;


void init(DictType* D)
{
	D->size = 0;
}

void insertItem(DictType* D, int key, int value)
{
	D->dict[D->size].key = key;
	D->dict[D->size].value = value;
	D->size++;
}

int findElementIndex(DictType* D, int key, int left, int right)
{
	if (left > right)
		return -1;

	int mid = (left + right) / 2;
	if (D->dict[mid].key == key)
	{
		if (mid > left && D->dict[mid].key == D->dict[mid - 1].key)
			return findElementIndex(D, key, left, mid - 1);
		return mid;
	}
	else if (D->dict[mid].key > key)
		return findElementIndex(D, key, left, mid - 1);
	else
		return findElementIndex(D, key, mid + 1, right);

}

void findAllElement(DictType* D, int key)
{
	int i, count = 0;
	int idx = findElementIndex(D, key, 0, D->size);
	for (i = idx; i < D->size && D->dict[i].key == key; i++)
		count++;

	if (idx == -1)
		printf("key %d가 존재하지 않습니다.\n", key);
	else
		printf("key %d가 index %d부터 %d개 존재합니다.\n", key, idx, count);
	return;
}

void printDict(DictType* D)
{
	printf("index      key    value \n");
	for (int i = 0; i < D->size; i++)
	{
		printf("   %2d      %2d     %d\n", i, D->dict[i].key, D->dict[i].value);
	}
	printf("\n");
}

void insertionSort(DictType* D)
{
	int i, j;
	element save;
	for (i = 1; i < D->size; i++)
	{
		save = D->dict[i];
		for (j = i - 1; j >= 0 && D->dict[j].key > save.key; j--)
			D->dict[j + 1] = D->dict[j];
		D->dict[j + 1] = save;
	}
}

int main()
{
	DictType dict;
	init(&dict);

	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++)
		insertItem(&dict, rand() % 20, rand() % 900 + 100);
	insertionSort(&dict);
	printDict(&dict);

	int n;
	printf("findAllElement: ");
	scanf_s("%d", &n);
	findAllElement(&dict, n);
	return 0;
}