#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef struct Edge {
	int vNum1;
	int vNum2;
	int isTree;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	int adjVertex;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int num;
	int isVisited;
	IncidentEdge* top;
	struct Vertex* next;
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
	G->vCount = G->eCount = 0;
}

void insertVertex(GraphType* G, int num)
{
	Vertex* p = (Vertex*)xmalloc(sizeof(Vertex));
	p->num = num;
	p->next = NULL;
	p->top = NULL;
	p->isVisited = FALSE;
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

void BFS1(GraphType* G, Vertex* v)
{
	QueueType q[10];
	for (int i = 0; i < 10; i++)
		initQueue(&q[i]);

	enqueue(&q[0], v);
	v->isVisited = TRUE;
	int level = 0;

	while (!isEmpty(&q[level]))
	{
		v = dequeue(&q[level]);
		printf("[%d] ", v->num);

		IncidentEdge* p;
		Vertex* w;
		for (p = v->top; p != NULL; p = p->next)
		{
			w = findVertex(G, p->adjVertex);
			if (w->isVisited == FALSE)
			{
				w->isVisited = TRUE;
				enqueue(&q[level + 1], w);
			}
		}

		if (isEmpty(&q[level]) && !isEmpty(&q[level + 1]))
			level++;
	}

}

void BFS(GraphType* G)
{
	Vertex* p;
	for (p = G->vHead; p != NULL; p = p->next)
		p->isVisited = FALSE;

	Edge* q;
	for (q = G->eHead; q != NULL; q = q->next)
		q->isTree = FALSE;

	BFS1(G, G->vHead);
	printf("\n");
}

int main()
{
	GraphType G;
	init(&G);
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
	BFS(&G);
	BFS(&G);
	BFS(&G);
	return 0;
}