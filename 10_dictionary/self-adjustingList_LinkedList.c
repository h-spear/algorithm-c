#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {
	struct NDOE* next;
	int data;
}NODE;

typedef struct {
	NODE* head;
}LinkedListType;

void init(LinkedListType* L)
{
	L->head = NULL;
}

NODE* getNode()
{
	NODE* p = (NODE*)malloc(sizeof(NODE));
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void insertItem(LinkedListType* L, int item)
{
	NODE* newnode = getNode();
	newnode->data = item;
	newnode->next = L->head;
	L->head = newnode;
}

void findElement(LinkedListType* L, int item)
{
	NODE* p, * before = NULL;
	for (p = L->head; p != NULL; p = p->next)
	{
		if (p->data == item)
		{
			printf("found!\n");
			if (before == NULL)
				return;

			before->next = p->next;
			p->next = L->head;
			L->head = p;
			return;
		}
		before = p;
	}
	printf("Not found!\n");
}

void print(LinkedListType* L)
{
	NODE* p;
	for (p = L->head; p != NULL; p = p->next)
		printf("%d ", p->data);
	printf("\n");
}

int main()
{
	LinkedListType list;
	init(&list);

	for (int i = 0; i < 10; i++)
		insertItem(&list, i);
	print(&list);

	int n;
	printf("\nfind Element: ");
	scanf_s("%d", &n);
	findElement(&list, n);
	print(&list);
	return 0;
}