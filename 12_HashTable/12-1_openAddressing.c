#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 11

typedef struct {
	int key;
	int probeCount;
}Bucket;

typedef struct {
	Bucket A[M];
}HashType;

void initHash(HashType* HT)
{
	for (int i = 0; i < M; i++)
	{
		HT->A[i].key = 0;
		HT->A[i].probeCount = 0;
	}
}

int h(int key)
{
	return (2 * key + 5) % M;
}

int h2(int key)
{
	return 7 - (key % 7);
}

int getNextBucketLinear(int v, int i)
{
	return (v + i) % M;
}

int getNextBucketQuadratic(int v, int i)
{
	return (v + i * i) % M;
}

int getNextBucketDouble(int v, int i, int key)
{
	return (v + i * h2(key)) % M;
}

int isEmpty(HashType* HT, int b)
{
	return HT->A[b].key == 0;
}

void insertItem(HashType* HT, int key)
{
	int v = h(key);
	int i = 0;
	int count = 0;

	while (i < M)
	{
		count++;
		int b = getNextBucketLinear(v, i);
		//int b = getNextBucketQuadratic(v, i);
		//int b = getNextBucketDouble(v, i, key);
		if (isEmpty(HT, b))
		{
			HT->A[b].key = key;
			HT->A[b].probeCount = count;
			return;
		}
		else
			i++;
	}
}

void printHashTable(HashType* HT)
{
	printf("Bucket   Key  Probe\n");
	printf("============================\n");

	for (int i = 0; i < M; i++)
		printf("HT[%02d] :  %2d    %d\n", i, HT->A[i].key, HT->A[i].probeCount);
	printf("\n");
}

int main()
{
	HashType HT;
	initHash(&HT);

	insertItem(&HT, 12);
	insertItem(&HT, 44);
	insertItem(&HT, 13);
	insertItem(&HT, 88);
	insertItem(&HT, 23);
	insertItem(&HT, 94);
	insertItem(&HT, 11);
	insertItem(&HT, 39);
	insertItem(&HT, 20);
	insertItem(&HT, 16);
	insertItem(&HT, 5);
	printHashTable(&HT);
	return 0;
}