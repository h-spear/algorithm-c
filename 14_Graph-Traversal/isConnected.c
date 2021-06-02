#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define N 16
#define MAX_STACK_SIZE 30

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
	int top;
	Vertex* data[MAX_STACK_SIZE];
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

void printStack(StackType* s)
{
	for (int i = 0; i < s->top; i++)
		printf("%d -> ", s->data[i]->num);
	printf("%d\n",s->data[s->top]->num);
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

void insertEdge(GraphType* g, int v1, int v2)
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
	v = findVertex(g, v2);
	insertIncidentEdge(v, v1, p);
}

void print(GraphType* g)
{
	printf("정점의 개수 : %d, 간선의 개수 : %d\n", g->vCount, g->eCount);
	Vertex* p;
	for (p = g->vHead; p != NULL; p = p->next)
	{
		printf("정점 %d : ",p->num);
		IncidentEdge* q;
		for (q = p->top; q != NULL; q = q->next)
			printf("[%d] ", q->adjVertex);
		printf("\n");
	}
}

void dfs(GraphType* g, Vertex* v, int* ptr)
{
	if (v->visited == FALSE)
	{
		*ptr = *ptr + 1;
		v->visited = TRUE;
	}
	IncidentEdge* q;
	for (q = v->top; q != NULL; q = q->next)
	{
		Vertex* w = findVertex(g, q->adjVertex);
		if (w->visited == FALSE)
			dfs(g, w, ptr);
	}
}

void isConnected(GraphType* g)
{
	int count = 0;
	int* ptr = &count;
	Vertex* p;
	for (p = g->vHead; p != NULL; p = p->next)
		p->visited = FALSE;

	dfs(g, g->vHead, ptr);

	if (count == g->vCount)
		printf("connected graph\n");
	else
		printf("disconnected graph\n");
	return;
}

int main()
{
	GraphType g;
	init(&g);
	for (int i = 1; i <= N; i++)
		insertVertex(&g, i);

	insertEdge(&g, 1, 2);
	insertEdge(&g, 1, 3);
	insertEdge(&g, 2, 4);
	insertEdge(&g, 2, 5);
	insertEdge(&g, 3, 4);
	insertEdge(&g, 3, 6);
	insertEdge(&g, 4, 5);
	insertEdge(&g, 5, 8);
	insertEdge(&g, 6, 7);
	insertEdge(&g, 6, 9);
	insertEdge(&g, 7, 8);
	insertEdge(&g, 7, 10);
	insertEdge(&g, 8, 11);
	insertEdge(&g, 9, 10);
	insertEdge(&g, 9, 12);
	insertEdge(&g, 10, 11);
	insertEdge(&g, 11, 14);
	insertEdge(&g, 12, 13);
	insertEdge(&g, 12, 15);
	insertEdge(&g, 13, 14);
	insertEdge(&g, 13, 15);
	insertEdge(&g, 14, 16);
	insertEdge(&g, 15, 16);
	print(&g);
	printf("\nthis is ");
	isConnected(&g);
	return 0;
}