#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15
#define MAX_LENGTH 10

typedef struct {
	int key;
	char value[MAX_LENGTH];
}element;

typedef struct {
	element dict[SIZE];
	int size;
}DictType;

element NoSuchKey = { -1,"NoSuchKey" };

void init(DictType* d)
{
	d->size = 0;
}

int size(DictType* d)
{
	return d->size;
}

int isEmpty(DictType* d)
{
	return d->size == 0;
}

element findElement(DictType* d, int key)
{
	for (int i = 0; i < d->size; i++)
	{
		if (d->dict[i].key == key)
			return d->dict[i];
	}
	return NoSuchKey;
}

// O(nlogn)
element orderedDictFindElement(DictType* d, int key, int left, int right)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (key == d->dict[mid].key)
			return d->dict[mid];
		else if (key < d->dict[mid].key)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return NoSuchKey;
}

// O(nlogn)
element rOrderedDictFindElement(DictType* d, int key, int left, int right)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (key == d->dict[mid].key)
			return d->dict[mid];
		else if (key < d->dict[mid].key)
			return rOrderedDictFindElement(d, key, left, mid - 1);
		else
			return rOrderedDictFindElement(d, key, mid + 1, right);
	}
	return NoSuchKey;
}

void insertItem(DictType* d, int key, char* value)
{
	element elem;
	elem.key = key;
	for (int i = 0; i < MAX_LENGTH; i++)
		elem.value[i] = value[i];

	d->dict[d->size++] = elem;
}

element removeElement(DictType* d, int key)
{
	for (int i = 0; i < d->size; i++)
	{
		if (d->dict[i].key == key)
		{
			element elem = d->dict[i];
			for (int j = i; j < d->size - 1; j++)
				d->dict[j] = d->dict[j + 1];
			d->size--;
			return elem;
		}
	}
	return NoSuchKey;
}

void printDict(DictType* d)
{
	printf(" key     value    \n");
	for (int i = 0; i < d->size; i++)
	{
		printf("%3d   ", d->dict[i].key);
		for (int j = 0; j < MAX_LENGTH; j++)
			printf("%c", d->dict[i].value[j]);
		printf("\n");
	}
}

void printElement(element elem)
{
	printf("(%d, ", elem.key);
	for (int i = 0; i < MAX_LENGTH; i++)
		printf("%c", elem.value[i]);
	printf(")\n");
}

void insertion_sort(DictType* d)
{
	int i, j;
	element elem;
	for (i = 1; i < d->size; i++)
	{
		elem = d->dict[i];
		for (j = i - 1; j >= 0 && d->dict[j].key > elem.key; j--)
			d->dict[j + 1] = d->dict[j];
		d->dict[j + 1] = elem;
	}
}

int main()
{
	DictType dict;
	init(&dict);

	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		int key = rand() % 100;
		char value[MAX_LENGTH];
		for (int j = 0; j < MAX_LENGTH; j++)
			value[j] = rand() % 26 + 97;

		if (findElement(&dict, key).key == key)
			i--;		// 유일 키 사전
		else
			insertItem(&dict, key, value);
	}

	// 순서사전
	insertion_sort(&dict);
	printDict(&dict);

	int key;
	element elem;
	printf("\nfind key: ");
	scanf_s("%d", &key);
	elem = rOrderedDictFindElement(&dict, key, 0, SIZE - 1);
	printElement(elem);
	return 0;
}