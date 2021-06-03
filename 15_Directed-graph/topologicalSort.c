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
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

typedef struct {
	int data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

int in[N];

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

void enqueue(QueueType* q, int item)
{
	if (isFull(q))
		exit(1);
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	return;
}

int dequeue(QueueType* q)
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

void inDegree(GraphType *g)
{
	Vertex* p = g->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
		for (q = p->top; q != NULL; q = q->next)
			in[q->adjVertex - 1]++;
}

void topologicalSort(GraphType *g)
{
	QueueType q;
	initQueue(&q);

	Vertex* p;
	IncidentEdge* r;
	inDegree(g);

	for (int i = 0; i < N; i++)
		if (in[i] == 0)
			enqueue(&q, i + 1);

	int i = 1;
	while (!isEmpty(&q))
	{
		int w = dequeue(&q);
		i++;
		printf("[%d] ", w);
		p = findVertex(g, w);
		r = p->top;
		while (r != NULL)
		{
			in[r->adjVertex - 1]--;
			if (in[r->adjVertex - 1] == 0)
				enqueue(&q, r->adjVertex);
			r = r->next;
		}
	}
	if (i <= g->vCount)
		printf("\nG has a directed cycle\n");
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