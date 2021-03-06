#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define N 16
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
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;
typedef struct {
	Vertex* data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void initQueue(QueueType* q)
{
	q->front = q->rear = 0;
}

int isEmpty(QueueType* q)
{
	return q->front == q->rear;
}

int isFull(QueueType* q)
{
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType* q, Vertex* item)
{
	if (isFull(q))
		exit(1);
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	return;
}

Vertex* dequeue(QueueType* q)
{
	if (isEmpty(q))
		exit(1);
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
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
	printf("????????? ?????? : %d, ????????? ?????? : %d\n", g->vCount, g->eCount);
	Vertex* p;
	for (p = g->vHead; p != NULL; p = p->next)
	{
		printf("?????? %d : ",p->num);
		IncidentEdge* q;
		for (q = p->top; q != NULL; q = q->next)
			printf("[%d] ", q->adjVertex);
		printf("\n");
	}
}

void rDFS(GraphType* g, Vertex* v)
{
	IncidentEdge* q;
	if (v->visited == FALSE)
	{
		printf("[%d] ", v->num);
		v->visited = TRUE;
	}
	for (q = v->top; q != NULL; q = q->next)
	{
		Vertex* w = findVertex(g, q->adjVertex);
		if (w->visited == FALSE)
			rDFS(g, w);
	}
}

void dfs(GraphType* g, int num)
{
	Vertex* p = g->vHead;
	for (; p != NULL; p = p->next)
		p->visited = FALSE;

	p = findVertex(g, num);
	rDFS(g, p);
	printf("\n");
}

void BFS1(GraphType* g, Vertex* v)
{
	QueueType q;
	initQueue(&q);
	v->visited = TRUE;
	enqueue(&q, v);
	printf("[%d] ", v->num);

	while (!isEmpty(&q))
	{
		v = dequeue(&q);
		IncidentEdge* p;
		for (p = v->top; p != NULL; p = p->next)
		{
			Vertex* w = findVertex(g, p->adjVertex);
			if (w->visited == FALSE)
			{
				w->visited = TRUE;
				printf("[%d] ", w->num);
				enqueue(&q, w);
			}
		}
	}
}

void bfs(GraphType* g, int num)
{
	Vertex* p = g->vHead;
	for (; p != NULL; p = p->next)
		p->visited = FALSE;

	p = findVertex(g, num);
	BFS1(g, p);
	printf("\n");
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
	dfs(&g, 1);
	bfs(&g, 1);
	return 0;
}