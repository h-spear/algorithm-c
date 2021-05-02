#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

typedef struct {
	int key;
	char value[10];
}element;

typedef struct
{
	element dict[SIZE];
	int size;
}DictType;

void init(DictType* d)
{
	d->size = 0;
}

void insertKey(DictType* d)
{
	for (int i = 0; i < SIZE; i++)
	{
		d->dict[i].key = rand() % 30 + 1;
		for (int j = 0; j < i; j++)
			if (d->dict[i].key == d->dict[j].key)
				i--;		// 유일 키 사전
	}
}

void insertValue(DictType* d)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < 5; j++)
			d->dict[i].value[j] = rand() % 26 + 97;
		d->size++;
	}
}

void makeDict(DictType* d)
{
	insertKey(d);
	insertValue(d);
}

void printDict(DictType* d)
{
	printf("key   value \n===========\n");
	for (int i = 0; i < d->size; i++)
	{
		printf(" %2d   ", d->dict[i].key);
		for (int j = 0; j < 5; j++)
			printf("%c", d->dict[i].value[j]);
		printf("\n");
	}
}

void insertion_sort(DictType *d)
{
	int i, j;
	element item;
	for (i = 1; i < SIZE; i++)
	{
		item = d->dict[i];
		for (j = i - 1; j >= 0 && d->dict[j].key > item.key; j--)
			d->dict[j + 1] = d->dict[j];
		d->dict[j + 1] = item;
	}
}

// 재귀 ver.
int rFindElement(DictType* d, int key, int left, int right)
{
	int mid;
	if (left <= right)
	{
		mid = (left + right) / 2;
		if (key == d->dict[mid].key)
			return mid;
		else if (key < d->dict[mid].key)
			return rFindElement(d, key, left, mid - 1);
		else
			return rFindElement(d, key, mid + 1, right);
	}
	return -1;
}

// 반복문 ver.
int findElement(DictType* d, int key, int left, int right)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (key == d->dict[mid].key)
			return mid;
		else if (key < d->dict[mid].key)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

element removeElement(DictType* d, int key)
{
	int index = findElement(d, key, 0, d->size - 1);
	if (index == -1)
	{
		printf("삭제할 요소가 없습니다.");
		return;
	}
	else
	{
		element item = d->dict[index];
		for (int i = index; i < d->size - 1; i++)
			d->dict[i] = d->dict[i + 1];
		d->size--;
		return item;
	}
}

int main()
{
	DictType d;
	init(&d);
	srand((unsigned int)time(NULL));
	makeDict(&d);
	printDict(&d);

	getchar();
	printf("\n");
	insertion_sort(&d);
	printDict(&d);

	int key, index;
	printf("\nSearch Key : ");
	scanf_s("%d", &key);
	index = findElement(&d, key, 0, SIZE - 1);
	//index = rFindElement(&d, key, 0, SIZE - 1);
	if (index == -1)
		printf("\nNo Such Key\n");
	else
	{
		printf("\nfindElement!");
		printf("\nindex : %d, key : %d, value : ", index + 1, key);
		for (int j = 0; j < 5; j++)
			printf("%c", d.dict[index].value[j]);
		printf("\n\n");
	}

	printf("Remove Key : ");
	scanf_s("%d", &key);
	removeElement(&d, key);
	printDict(&d);
	return 0;
}