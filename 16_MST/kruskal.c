#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define INF 100000000
#define N 6
#define SWAP(x,y,t) ((t=x), (x=y), (y=t))

typedef struct Edge {
	int vNum1;
	int vNum2;
	int weight;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	int adjVertex;
	int weight;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int num;
	int isFresh;
	IncidentEdge* top;
	struct Vertex* next;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

int v[N];	//sack

void initSack()
{
	for (int i = 0; i < N; i++)
		v[i] = -1;
}

int vFind(int vNum)
{
	if (v[vNum] == -1)
		return vNum;
	while (v[vNum] != -1)
		vNum = v[vNum];
	return vNum;
}

void vUnion(int vNum1, int vNum2)
{
	int r1 = vFind(vNum1);
	int r2 = vFind(vNum2);

	if (r1 != r2)
		v[r2] = r1;
}

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void init(GraphType* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
	G->vCount = G->eCount = 0;
}

void insertVertex(GraphType* G, int num)
{
	Vertex* p = (Vertex*)xmalloc(sizeof(Vertex));
	p->num = num;
	p->next = NULL;
	p->top = NULL;
	p->isFresh = FALSE;
	Vertex* q = G->vHead;
	G->vCount++;

	if (q == NULL)
		G->vHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}

void insertIncidentEdge(Vertex* v, int av, Edge* e)
{
	IncidentEdge* p = (IncidentEdge*)xmalloc(sizeof(IncidentEdge));
	p->adjVertex = av;
	p->e = e;
	p->next = NULL;
	p->weight = e->weight;

	IncidentEdge* q = v->top;
	if (q == NULL)
		v->top = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}

Vertex* findVertex(GraphType* G, int v)
{
	Vertex* p = G->vHead;
	while (p->num != v)
		p = p->next;
	return p;
}

void insertEdge(GraphType* G, int v1, int v2, int weight)
{
	Edge* p = (Edge*)xmalloc(sizeof(Edge));
	p->vNum1 = v1;
	p->vNum2 = v2;
	p->next = NULL;
	p->weight = weight;
	G->eCount++;

	Edge* q = G->eHead;
	if (q == NULL)
		G->eHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
	Vertex* v = findVertex(G, v1);
	insertIncidentEdge(v, v2, p);
	v = findVertex(G, v2);
	insertIncidentEdge(v, v1, p);
}

void print(GraphType* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("정점 %d : ", p->num);
		for (q = p->top; q != NULL; q = q->next)
			printf("[%d (%d)] ", q->adjVertex, q->weight);
		printf("\n");
	}
}

void edge_sort(GraphType* G, Edge* e[])
{
	Edge* p = G->eHead;
	int i = 0;

	for (; p != NULL; p = p->next)
		e[i++] = p;

	int least;
	Edge* temp;
	for (i = 0; i < G->eCount - 1; i++)
	{
		least = i;
		for (int j = i + 1; j < G->eCount; j++)
			if (e[j]->weight < e[least]->weight)
				least = j;
		SWAP(e[i], e[least], temp);
	}
	/*
	for (i = 0; i < G->eCount - 1; i++)
		printf("(%d,%d) [%d]\n", e[i]->vNum1, e[i]->vNum2, e[i]->weight);
	printf("\n");
	*/
}

void kruskal(GraphType* G, Vertex* v)
{
	int eCount = 0;
	int v1, v2;
	int i = 0;
	Edge* p;

	// priority queue
	Edge* e[N * N];
	edge_sort(G, e);
	initSack();

	while (eCount < N - 1)
	{
		p = e[i];
		v1 = vFind(p->vNum1 - 1);
		v2 = vFind(p->vNum2 - 1);

		if (v1 != v2)
		{
			printf("간선 [%d - %d (%d)] 선택 \n", p->vNum1, p->vNum2, p->weight);
			eCount++;
			vUnion(v1, v2);
		}
		i++;
	}
}

int main()
{
	GraphType G;
	init(&G);
	for (int i = 1; i <= N; i++)
		insertVertex(&G, i);

	insertEdge(&G, 1, 2, 2);
	insertEdge(&G, 1, 3, 6);
	insertEdge(&G, 1, 5, 7);
	insertEdge(&G, 2, 3, 5);
	insertEdge(&G, 2, 4, 7);
	insertEdge(&G, 3, 4, 9);
	insertEdge(&G, 3, 5, 8);
	insertEdge(&G, 4, 6, 4);
	insertEdge(&G, 5, 6, 3);
	print(&G);
	printf("\nkruskal\n");
	kruskal(&G, G.vHead);
	return 0;
}