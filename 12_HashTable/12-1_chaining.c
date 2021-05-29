#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 11

typedef struct HashNode {
	int key;
	struct HashNode* next;
}HashType;

void* xmalloc(size_t size)
{
	void* p = malloc(size);
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void init(HashType* HT)
{
	for (int i = 0; i < M; i++)
	{
		HT[i].key = 0;
		HT[i].next = NULL;
	}
}

int h(int key)
{
	return (2 * key + 5) % M;
}

void insertItem(HashType* HT, int key)
{
	int v = h(key);
	HashType* node = (HashType*)xmalloc(sizeof(HashType));
	node->key = key;
	node->next = HT[v].next;
	HT[v].next = node;
}

void printHash(HashType* HT)
{
	HashType* p;
	for (int i = 0; i < M; i++)
	{
		printf("HT[%02d] : ", i);
		for (p = HT[i].next; p != NULL; p = p->next)
			printf("(%d) ", p->key);
		printf("\n");
	}
}

int main()
{
	HashType HT[M];
	init(HT);
	insertItem(HT, 12);
	insertItem(HT, 44);
	insertItem(HT, 13);
	insertItem(HT, 88);
	insertItem(HT, 23);
	insertItem(HT, 94);
	insertItem(HT, 11);
	insertItem(HT, 39);
	insertItem(HT, 20);
	insertItem(HT, 16);
	insertItem(HT, 5);
	printHash(HT);
	return 0;
}