#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
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

void rDFS(GraphType* G, Vertex* v)
{
	IncidentEdge* q; 
	if (v->visited == FALSE)
	{
		printf("[%d] ", v->num);
		v->visited = TRUE;
	}
	for (q = v->top; q != NULL; q = q->next)
	{
		v = findVertex(G, q->adjVertex);
		if (v->visited == FALSE)
			rDFS(G, v);
	}
}

void dfs(GraphType* G, int v)
{
	printf("dfs : ");
	Vertex* p;
	for (p = G->vHead; p != NULL; p = p->next)
		p->visited = FALSE;

	p = findVertex(G, v);
	rDFS(G, p);
	printf("\n");
	return;
}

void BFS1(GraphType* G, Vertex* v)
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
			Vertex* w = findVertex(G, p->adjVertex);
			if (w->visited == FALSE)
			{
				w->visited = TRUE;
				printf("[%d] ", w->num);
				enqueue(&q, w);
			}
		}
	}
}

void bfs(GraphType* G, int v)
{
	printf("bfs : ");
	Vertex* p;
	for (p = G->vHead; p != NULL; p = p->next)
		p->visited = FALSE;

	p = findVertex(G, v);
	BFS1(G, p);
	printf("\n");
	return;
}

int main()
{
	GraphType G;
	init(&G);
	for (int i = 1; i < 9; i++)
		insertVertex(&G, i);

	insertEdge(&G, 1, 2);
	insertEdge(&G, 1, 3);
	insertEdge(&G, 1, 4);
	insertEdge(&G, 2, 3);
	insertEdge(&G, 2, 4);
	insertEdge(&G, 3, 4);
	insertEdge(&G, 4, 6);
	insertEdge(&G, 5, 6);
	insertEdge(&G, 5, 7);
	insertEdge(&G, 5, 8);
	insertEdge(&G, 6, 7);
	insertEdge(&G, 7, 8);

	print(&G);
	dfs(&G, 1);
	bfs(&G, 1);
	return 0;
}