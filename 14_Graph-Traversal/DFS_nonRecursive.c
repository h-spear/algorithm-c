#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 10

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
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

typedef struct {
	Vertex* data[MAX_STACK_SIZE];
	int top;
}StackType;

void initStack(StackType* s)
{
	s->top = -1;
}

int isEmpty(StackType* s)
{
	return s->top == -1;
}

void push(StackType* s, Vertex* item)
{
	s->data[++s->top] = item;
}

Vertex* pop(StackType* s)
{
	if (isEmpty(s))
		exit(1);
	return s->data[s->top--];
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
	G->eCount = G->vCount = 0;
}

void insertVertex(GraphType* G, int num)
{
	Vertex* p = (Vertex*)xmalloc(sizeof(Vertex));
	p->num = num;
	p->top = NULL;
	p->next = NULL;
	p->visited = FALSE;
	G->vCount++;

	Vertex* q = G->vHead;
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
			printf("[%d] ", q->adjVertex);
		printf("\n");
	}
}

void dfs1(GraphType* G, Vertex* v)
{
	StackType s;
	initStack(&s);
	push(&s, v);
	while (!isEmpty(&s))
	{
		v = pop(&s);
		IncidentEdge* q;
		if (v->visited == FALSE)
		{
			printf("%d ", v->num);
			v->visited = TRUE;
		}
		for (q = v->top; q != NULL; q = q->next)
		{
			Vertex* w = findVertex(G, q->adjVertex);
			if (w->visited == FALSE)
				push(&s, w);
		}
	}
	return;
}

void dfs(GraphType* G, int v)
{
	printf("dfs : ");
	Vertex* p;
	for (p = G->vHead; p != NULL; p = p->next)
		p->visited = FALSE;

	p = findVertex(G, v);
	dfs1(G, p);
	printf("\n");
	return;
}

int main()
{
	GraphType G;
	init(&G);
	for (int i = 1; i < 10; i++)
		insertVertex(&G, i);

	insertEdge(&G, 7, 8);
	insertEdge(&G, 5, 8);
	insertEdge(&G, 5, 7);
	insertEdge(&G, 5, 6);
	insertEdge(&G, 4, 7);
	insertEdge(&G, 4, 5);
	insertEdge(&G, 3, 6);
	insertEdge(&G, 2, 5);
	insertEdge(&G, 2, 3);
	insertEdge(&G, 1, 9);
	insertEdge(&G, 1, 2);

	print(&G);
	dfs(&G, 1);
	return 0;
}