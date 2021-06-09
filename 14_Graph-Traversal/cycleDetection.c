#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

typedef struct Edge {
	int vNum1;
	int vNum2;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	int adjVertex;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int num;
	int visited;
	IncidentEdge* top;
	struct Vertex* next;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

int checkCycle;

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

void insertIncidentEdge(Vertex* v, int av)
{
	IncidentEdge* p = (IncidentEdge*)xmalloc(sizeof(IncidentEdge));
	p->adjVertex = av;
	p->next = NULL;

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

void insertEdge(GraphType* G, int v1, int v2)
{
	Edge* p = (Edge*)xmalloc(sizeof(Edge));
	p->vNum1 = v1;
	p->vNum2 = v2;
	p->next = NULL;
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
	insertIncidentEdge(v, v2);
	v = findVertex(G, v2);
	insertIncidentEdge(v, v1);
}

void print(GraphType* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("정점 %d : ", p->num);
		for (q = p->top; q != NULL; q = q->next)
			printf("[%d] ", q->adjVertex);
		printf("\n");
	}
}

void dfs(GraphType* G, Vertex* v, Vertex* parent)
{
	IncidentEdge* p;
	if (v->visited == FALSE)
		v->visited = TRUE;

	for (p = v->top; p != NULL; p = p->next)
	{
		Vertex* w = findVertex(G, p->adjVertex);
		if (w->visited == FALSE)
			dfs(G, w, v);
		else if (w->num != parent->num)
		{
			checkCycle = TRUE;
			return;
		}
	}
}

int cycle(GraphType* G)
{
	Vertex* p = G->vHead;
	for (; p != NULL; p = p->next)
		p->visited = FALSE;

	dfs(G, G->vHead, G->vHead);
	return checkCycle;
}

int main()
{
	GraphType G;
	init(&G);
	for (int i = 1; i <= 5; i++)
		insertVertex(&G, i);

	insertEdge(&G, 1, 2);
	insertEdge(&G, 2, 3);
	insertEdge(&G, 3, 1);
	insertEdge(&G, 3, 4);
	insertEdge(&G, 4, 5);
	print(&G);

	if (cycle(&G))
		printf("Graph has cycle.\n");
	else
		printf("Graph doesn't have cycle.\n");
	return 0;
}