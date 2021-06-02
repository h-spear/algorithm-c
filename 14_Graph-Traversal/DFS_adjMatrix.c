#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 50

#define TRUE 1
#define FALSE 0

typedef struct {
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	int n;
}GraphType;

int visited[MAX_VERTICES];

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

void dfs(GraphType* G, int v)
{
	int w;
	visited[v] = TRUE;
	printf("[%d] ", v);
	for (w = 0; w < G->n; w++)
		if (G->adj_mat[v][w] && !visited[w])
			dfs(G, w);
}

int main()
{
	GraphType G;
	init(&G);

	for (int i = 0; i < 6; i++)
		makeVertex(&G);

	insertEdge(&G, 0, 1);
	insertEdge(&G, 0, 2);
	insertEdge(&G, 0, 3);
	insertEdge(&G, 1, 4);
	insertEdge(&G, 2, 4);
	insertEdge(&G, 2, 5);
	insertEdge(&G, 4, 5);
	dfs(&G, 0);
	return 0;
}