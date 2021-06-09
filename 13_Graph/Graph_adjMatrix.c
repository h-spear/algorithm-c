#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 50

typedef struct {
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	int n;
}GraphType;

void init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->adj_mat[i][j] = 0;
}

void insertVertex(GraphType* g)
{
	if (g->n > MAX_VERTICES - 1)
		return;
	g->n++;
}

void insertEdge(GraphType* g, int v1, int v2, int weight)
{
	if (v1 >= g->n || v2 >= g->n)
		return;
	g->adj_mat[v1][v2] = weight;
	g->adj_mat[v2][v1] = weight;
}

void print(GraphType* g)
{
	for (int i = 0; i < g->n; i++)
	{
		printf("정점 %d : ", i);
		for (int j = 0; j < g->n; j++)
			if (g->adj_mat[i][j] != 0)
				printf("[%d (%d)] ", j, g->adj_mat[i][j]);
		printf("\n");
	}
}

int main()
{
	GraphType g;
	init(&g);

	for (int i = 0; i < 6; i++)
		insertVertex(&g);

	insertEdge(&g, 0, 1, 2);
	insertEdge(&g, 0, 2, 6);
	insertEdge(&g, 0, 4, 7);
	insertEdge(&g, 1, 3, 7);
	insertEdge(&g, 1, 2, 5);
	insertEdge(&g, 2, 3, 9);
	insertEdge(&g, 2, 4, 8);
	insertEdge(&g, 3, 5, 4);
	insertEdge(&g, 4, 5, 3);

	print(&g);

	return 0;
}