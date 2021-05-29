#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 50

typedef struct {
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	int n;
}GraphType;

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

void insertVertex(GraphType* G)
{
	if (G->n > MAX_VERTICES - 1)
		error("정점 개수 초과\n");
	G->n++;
}

void insertEdge(GraphType* G, int v1, int v2)
{
	if (v1 >= G->n || v2 >= G->n)
		error("존재하지 않는 정점 번호");
	G->adj_mat[v1][v2] = 1;
	G->adj_mat[v2][v1] = 1;
}

void insertDirectedEdge(GraphType* G, int v1, int v2)
{
	if (v1 >= G->n || v2 >= G->n)
		error("존재하지 않는 정점 번호");
	G->adj_mat[v1][v2] = 1;
}

int areAdjacent(GraphType* G, int v1, int v2)
{
	return G->adj_mat[v1][v2];
}

void adjacentVertices(GraphType* G, int v)
{
	printf("%d의 인접정점 : ", v);
	for (int i = 0; i < G->n; i++)
		if (G->adj_mat[v][i] == 1)
			printf("%d ", i);
	printf("\n");
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

int main()
{
	GraphType G;
	init(&G);

	for (int i = 0; i < 4; i++)
		insertVertex(&G);
	insertEdge(&G, 0, 1);
	insertEdge(&G, 0, 2);
	insertEdge(&G, 0, 3);
	insertEdge(&G, 1, 2);
	insertEdge(&G, 2, 3);
	print(&G);
	return 0;
}