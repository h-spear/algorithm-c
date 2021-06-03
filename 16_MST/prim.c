#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define INF 100000000
#define N 6

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

int distance[10];

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

int getMinVertex(GraphType *G)
{
	int v = -1;
	Vertex* p = G->vHead;
	for (; p != NULL; p = p->next)
	{
		if (p->isFresh == FALSE)
		{
			v = p->num - 1;
			break;
		}
	}
	
	for (p = G->vHead; p != NULL; p = p->next)
		if (p->isFresh == FALSE && (distance[p->num - 1] < distance[v]))
			v = p->num - 1;

	return v;
}

void prim(GraphType* G, Vertex* v)
{
	IncidentEdge* q;
	Vertex* p;
	int u;

	for (int i = 0; i < N; i++)
		distance[i] = INF;

	distance[v->num - 1] = 0;

	for (int i = 0; i < N; i++)
	{
		u = getMinVertex(G);
		p = findVertex(G, u + 1);
		p->isFresh = TRUE;
		printf("[%d] ", p->num);
		for (q = p->top; q != NULL; q = q->next)
		{
			p = findVertex(G, q->adjVertex);
			if (p->isFresh == 0)
				distance[q->adjVertex - 1] = q->weight;
		}
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
	prim(&G,G.vHead);
	return 0;
}