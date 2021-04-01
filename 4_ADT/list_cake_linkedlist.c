
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int data;
	struct ListNode* link;
}ListNode;

typedef struct {
	ListNode* head;
}LinkedListType;

void init(LinkedListType* L)
{
	L->head = NULL;
}

ListNode* getNode()
{
	ListNode* p;
	p = (ListNode*)malloc(sizeof(ListNode));
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

LinkedListType* buildList(LinkedListType* L, int n)
{
	ListNode* p = getNode();
	L->head = p;
	p->data = 1;
	for (int i = 2; i <= n; i++)
	{
		p->link = getNode();
		p = p->link;
		p->data = i;
	}
	p->link = L->head;
	return L;
}

int runSimulation(LinkedListType* L, int n, int k)
{
	ListNode* p;
	p = L->head;
	while (p != p->link)
	{
		for (int i = 1; i < k; i++)
		{
			p = p->link;
		}

		ListNode* pnext = p->link;
		p->link = pnext->link;
		free(pnext);
		p = p->link;
	}
	return p->data;
}

int candle(LinkedListType* L, int n, int k)
{
	L = buildList(L, n);
	return runSimulation(L, n, k);
}

int main()
{
	int n, k;
	int ans;
	printf("원형연결리스트_ver\n(n, k) 입력 : ");
	scanf("%d %d", &n, &k);

	LinkedListType L;
	ans = candle(&L, n, k);
	printf("　　　 　답 : %d\n", ans);
	return 0;
}







