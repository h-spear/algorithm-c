#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_STACK_SIZE 30

typedef struct {
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	int n;
}GraphType;

typedef struct {
	int top;
	int data[MAX_STACK_SIZE];
}StackType;

int visited[MAX_VERTICES];

void initStack(StackType* s)
{
	s->top = -1;
}

int isEmpty(StackType* s)
{
	return s->top == -1;
}

void push(StackType* s, int item)
{
	s->data[++s->top] = item;
}

int pop(StackType* s)
{
	if (isEmpty(s))
		exit(1);
	return s->data[s->top--];
}

void init(GraphType* G)
{
	G->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			G->adj_mat[i][j] = 0;
}

void error(char* msg)
{
	fprintf(stderr, "%s", msg);
	exit(1);
}

void makeVertex(GraphType* G)
{
	if (G->n >= MAX_VERTICES)
		error("정점 개수 초과\n");
	G->n++;
}

void insertEdge(GraphType* G, int v1, int v2)
{
	if (v1 >= G->n || v2 >= G->n)
		error("정점 번호 에러\n");
	G->adj_mat[v1][v2] = 1;
	G->adj_mat[v2][v1] = 1;
	return;
}

void print(GraphType* G)
{
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
			printf("%2d ", G->adj_mat[i][j]);
		printf("\n");
	}
}

void printStack(StackType* s)
{
	for (int i = 0; i <= s->top; i++)
		printf("%d ", s->data[i]);
	printf("\n");
}

void dfs(GraphType* G, int v, int z, StackType* s)
{
	int w;
	visited[v] = TRUE;
	push(s, v);
	if (v == z)
	{
		printStack(s);
		return;
	}
	for (w = 0; w < G->n; w++)
	{
		if (G->adj_mat[v][w] == 1 && !visited[w])
		{
			dfs(G, w, z, s);
			pop(s);
		}
	}
}

void path(GraphType* G, int v, int z)
{
	StackType s;
	initStack(&s);
	dfs(G, v, z, &s);
}

int main()
{
	GraphType G;
	init(&G);

	for (int i = 0; i < 8; i++)
		makeVertex(&G);

	insertEdge(&G, 0, 4);
	insertEdge(&G, 0, 5);
	insertEdge(&G, 1, 2);
	insertEdge(&G, 1, 7);
	insertEdge(&G, 2, 6);
	insertEdge(&G, 3, 6);
	insertEdge(&G, 5, 6);
	path(&G, 0, 7);
	return 0;
}