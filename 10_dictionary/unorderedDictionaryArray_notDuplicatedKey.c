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

	printDict(&dict);

	int key;
	element elem;
	printf("\nfind key: ");
	scanf_s("%d", &key);
	elem = findElement(&dict, key);
	printElement(elem);

	printf("\nremove key: ");
	scanf_s("%d", &key);
	elem = removeElement(&dict, key);
	printElement(elem);

	printf("\n");
	printDict(&dict);

	return 0;
}