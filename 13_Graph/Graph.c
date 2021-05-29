#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

typedef struct Edge {
	int vNum1;
	int vNum2;
	struct Edge* next;
	int directed;
}Edge;

typedef struct IncidentEdge {
	int adjVertex;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int num;
	int isFresh;	// DFS, BFS
	struct Vertex* next;
	IncidentEdge* top;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

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

int vnumVertices(GraphType* G)
{
	return G->vCount;
}

int numEdges(GraphType* G)
{
	return G->eCount;
}

void vertices(GraphType* G)
{
	Vertex* p;
	printf("정점(%02d) : ", G->vCount);
	for (p = G->vHead; p != NULL; p = p->next)
		printf("%d ", p->num);
	printf("\n");
}

void edges(GraphType* G)
{
	Edge* p;
	printf("간선(%02d) : ", G->eCount);
	for (p = G->eHead; p != NULL; p = p->next)
		printf("(%d, %d) ", p->vNum1, p->vNum2);
	printf("\n");
}

Vertex* aVertex(GraphType* G)
{	// 그래프 내 아무 한 정점을 반환
	int r = rand() % G->vCount;
	Vertex* p = G->vHead;
	for (int i = 0; i < r; i++, p = p->next)
		;
	return p;
}

int degree(Vertex* v)
{
	int deg = 0;
	IncidentEdge* p;
	for (p = v->top; p != NULL; p = p->next)
		deg++;
	return deg;
}

void insertVertex(GraphType* G, int num)
{
	Vertex* p = (Vertex*)xmalloc(sizeof(Vertex));
	p->num = num;
	p->top = NULL;
	p->next = NULL;
	p->isFresh = 0;
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
	p->directed = FALSE;
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

void insertDirectedEdge(GraphType* G, int v1, int v2)
{	// v1->v2
	Edge* p = (Edge*)xmalloc(sizeof(Edge));
	p->vNum1 = v1;
	p->vNum2 = v2;
	p->next = NULL;
	p->directed = TRUE;
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
}

void print(GraphType *G)
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

int main()
{
	GraphType G;
	init(&G);
	srand((unsigned int)time(NULL));
	for (int i = 1; i < 10; i++)
		insertVertex(&G, i);

	insertEdge(&G, 1, 2);
	insertEdge(&G, 1, 3);
	insertEdge(&G, 2, 4);
	insertEdge(&G, 2, 5);
	insertEdge(&G, 3, 5);
	insertEdge(&G, 3, 6);
	insertEdge(&G, 4, 7);
	insertEdge(&G, 5, 7);
	insertEdge(&G, 5, 8);
	insertEdge(&G, 6, 8);
	insertEdge(&G, 7, 9);
	insertEdge(&G, 8, 9);
	print(&G);
	return 0;
}