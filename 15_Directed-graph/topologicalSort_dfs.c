#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define N 6
#define MAX_QUEUE_SIZE 10

typedef struct Edge {
	int vNum1;
	int vNum2;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	int adjVertex;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int num;
	IncidentEdge* top;
	struct Vertex* next;
	int visited;
	int rank;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

int n;

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

void init(GraphType* g)
{
	g->vHead = NULL;
	g->eHead = NULL;
	g->eCount = g->vCount = 0;
}

void insertVertex(GraphType* g, int num)
{
	Vertex* p = (Vertex*)xmalloc(sizeof(Vertex));
	p->num = num;
	p->next = NULL;
	p->top = NULL;
	p->rank = -1;

	g->vCount++;
	Vertex* q = g->vHead;
	if (q == NULL)
		g->vHead = p;
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
	p->e = e;
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

Vertex* findVertex(GraphType* g, int v)
{
	Vertex* p = g->vHead;
	while (p->num != v)
		p = p->next;
	return p;
}

void insertDirectEdge(GraphType* g, int v1, int v2)
{
	Edge* p = (Edge*)xmalloc(sizeof(Edge));
	p->next = NULL;
	p->vNum1 = v1;
	p->vNum2 = v2;
	g->eCount++;

	Edge* q = g->eHead;
	if (q == NULL)
		g->eHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
	Vertex* v = findVertex(g, v1);
	insertIncidentEdge(v, v2, p);
}

void print(GraphType* g)
{
	Vertex* p;
	for (p = g->vHead; p != NULL; p = p->next)
	{
		printf("정점 %d : ", p->num);
		IncidentEdge* q;
		for (q = p->top; q != NULL; q = q->next)
			printf("[%d] ", q->adjVertex);
		printf("\n");
	}
}

void dfs(GraphType* g, Vertex* v)
{
	static int i = 1;
	IncidentEdge* p;
	v->visited = TRUE;
	for (p = v->top; p != NULL; p = p->next)
	{
		Vertex* q = findVertex(g, p->adjVertex);
		if (q->visited == FALSE)
		{
			dfs(g, q);
		}
		else if (q->rank == -1)
		{
			if (i == 1)
			{
				printf("G has a directed cycle. \n");
				i--;
			}
			return;
		}
	}
	v->rank = n;
	n--;
}

void insertion_sort(GraphType* g, Vertex* v[])
{
	int i, j;
	Vertex* save;
	for (i = 1; i < g->vCount; i++)
	{
		save = v[i];
		for (j = i - 1; j >= 0 && v[j]->rank > save->rank; j--)
			v[j + 1] = v[j];
		v[j + 1] = save;
	}
}

void topologicalSort(GraphType* g)
{
	n = g->vCount;
	Vertex* p = g->vHead;
	for (; p != NULL; p = p->next)
		p->visited = FALSE;

	for (p = g->vHead; p != NULL; p = p->next)
		if (p->visited == FALSE)
			dfs(g, p);

	int i = 0;
	Vertex* v[N];
	for (p = g->vHead; p != NULL; p = p->next)
		v[i++] = p;

	insertion_sort(g, v);
	for (i = 0; i < g->vCount; i++)
		printf("[%d] ", v[i]->num);
}

int main()
{
	GraphType g;
	init(&g);
	for (int i = 1; i <= N; i++)
		insertVertex(&g, i);

	insertDirectEdge(&g, 1, 2);
	insertDirectEdge(&g, 1, 5);
	insertDirectEdge(&g, 2, 3);
	insertDirectEdge(&g, 4, 5);
	insertDirectEdge(&g, 5, 2);
	insertDirectEdge(&g, 5, 3);
	insertDirectEdge(&g, 5, 6);
	insertDirectEdge(&g, 6, 3);
	print(&g);

	topologicalSort(&g);
	return 0;
}