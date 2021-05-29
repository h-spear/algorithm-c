#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 13
#define NoSuchKey -99999999

typedef struct {
	int key; 
	int active;
}BUCKET;

typedef struct {
	BUCKET A[M];
}HashType;

void initHash(HashType* HT)
{
	for (int i = 0; i < M; i++)
	{
		HT->A[i].key = 0;
		HT->A[i].active = 0;
	}
}

int h(int key)
{
	return key % M;
}

int getNextBucketLinear(int v, int i)
{
	return (v + i) % M;
}

int isEmpty(HashType *HT, int b)
{
	return HT->A[b].key == 0;
}

void activate(HashType* HT, int b)
{
	HT->A[b].active = 1;
}

void deactivate(HashType* HT, int b)
{
	HT->A[b].active = 0;
}

int active(HashType* HT, int b)
{
	return HT->A[b].active == 1;
}

int inactive(HashType* HT, int b)
{
	return HT->A[b].active != 1;
}

int findElement(HashType* HT, int key)
{
	int v = h(key);
	int i = 0;
	while (i < M)
	{
		int b = getNextBucketLinear(v, i);
		if (isEmpty(HT, b))
			return NoSuchKey;
		else if (active(HT, b) && HT->A[b].key == key)
			return key;
		else
			i++;
	}
	return NoSuchKey;
}

void overflowException()
{
	printf("overflow\n");
	exit(1);
}

void insertItem(HashType* HT, int key)
{
	int v = h(key);
	int i = 0;
	while (i < M)
	{
		int b = getNextBucketLinear(v, i);
		if (isEmpty(HT, b) || inactive(HT, b))
		{
			HT->A[b].key = key;
			activate(HT, b);
			return;
		}
		else
			i++;
	}
	overflowException();
	return;
}

int removeElement(HashType* HT, int key)
{
	int v = h(key);
	int i = 0;
	while (i < M)
	{
		int b = getNextBucketLinear(v, i);
		if (isEmpty(HT, b))
			return NoSuchKey;
		else if (active(HT, b) && (key == HT->A[b].key))
		{
			deactivate(HT, b);
			return HT->A[b].key;
		}
		else
			i++;
	}
	return NoSuchKey;
}

void printHash(HashType* HT)
{
	printf("Bucket    Key    Active\n");
	printf("=============================\n");

	for (int i = 0; i < M; i++)
		printf("HT[%02d] :  %2d        %d \n", i, HT->A[i].key, HT->A[i].active);
	printf("\n");
}

int main()
{
	HashType HT;
	initHash(&HT);

	char cmd;
	while (1)
	{
		scanf_s("%c", &cmd, sizeof(char));

		if (cmd == 'f')
		{
			int num, e;
			scanf_s("%d", &num);
			e = findElement(&HT, num);
			if (e == NoSuchKey)
				printf("NoSuchKey\n");
			else
				printf("%d\n", e);
		}

		if (cmd == 'i')
		{
			int num;
			scanf_s("%d", &num);
			insertItem(&HT, num);
			printHash(&HT);
		}

		if (cmd == 'r')
		{
			int num;
			scanf_s("%d", &num);
			removeElement(&HT, num);
			printHash(&HT);
		}

		if (cmd == 'q')
			break;
	}
	return 0;
}