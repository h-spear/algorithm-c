#include <stdio.h>
#include <stdlib.h>

#define N 6

typedef struct Edge {
	int vNum1;
	int vNum2;
	int weight;
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
}Vertex;

Vertex* vHead;
Edge* eHead;
int vCount;
int eCount;

// sack
int v[N];
Edge* e[N * N];

void initSack()
{
	for (int i = 0; i < N; i++)
		v[i] = -1;
}

int vFind(int vNum)
{
	while (v[vNum] != -1)
		vNum = v[vNum];
	return vNum;
}

void vUnion(int v1, int v2)
{
	int r1 = vFind(v1);
	int r2 = vFind(v2);
	if (r1 != r2)
		v[r2] = r1;
}

void init()
{
	vHead = NULL;
	eHead = NULL;
	vCount = eCount = 0;
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

void insertVertex()
{
	Vertex* p = (Vertex*)xmalloc(sizeof(Vertex));
	p->num = ++vCount;
	p->next = NULL;
	p->top = NULL;

	Vertex* q = vHead;
	if (q == NULL)
		vHead = p;
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
	p->next = NULL;
	p->e = e;

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

Vertex* findVertex(int v)
{
	Vertex* p = vHead;
	while (p->num != v)
		p = p->next;
	return p;
}

void insertEdge(int v1, int v2, int w)
{
	Edge* p = (Edge*)xmalloc(sizeof(Edge));
	p->vNum1 = v1;
	p->vNum2 = v2;
	p->weight = w;
	p->next = NULL;
	eCount++;

	Edge* q = eHead;
	if (q == NULL)
		eHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}

	Vertex* v = findVertex(v1);
	insertIncidentEdge(v, v2, p);
	v = findVertex(v2);
	insertIncidentEdge(v, v1, p);
}

void print()
{
	Vertex* p = vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("정점 %d : ", p->num);
		for (q = p->top; q != NULL; q = q->next)
			printf("[%d (%d)] ", q->adjVertex, q->e->weight);
		printf("\n");
	}
	printf("\n");
}

void edge_sort(Edge* e[])
{
	Edge* p = eHead;
	int i = 0;

	for (; p != NULL; p = p->next)
		e[i++] = p;

	int j;
	Edge* save;
	for (i = 1; i < eCount; i++)
	{
		save = e[i];
		for (j = i - 1; j >= 0 && e[j]->weight < save->weight; j--)
			e[j + 1] = e[j];
		e[j + 1] = save;
	}
}

void kruskal(Vertex* v)
{
	int eCount = 0;
	int i = 0;
	initSack();
	edge_sort(e);
	while (eCount < N - 1)
	{
		Edge* p = e[i];
		int v1 = vFind(p->vNum1);
		int v2 = vFind(p->vNum2);
		if (v1 != v2)
		{
			printf("간선 [%d - %d (%d)] 선택 \n", p->vNum1, p->vNum2, p->weight);
			eCount++;
			vUnion(v1, v2);
		}
		i++;
	}
}

int main()
{
	init();
	for (int i = 0; i < N; i++)
		insertVertex();

	insertEdge(1, 2, 2);
	insertEdge(1, 3, 6);
	insertEdge(1, 5, 7);
	insertEdge(2, 3, 5);
	insertEdge(2, 4, 7);
	insertEdge(3, 4, 9);
	insertEdge(3, 5, 8);
	insertEdge(4, 6, 4);
	insertEdge(5, 6, 3);
	print();
	kruskal(vHead);

	return 0;
}