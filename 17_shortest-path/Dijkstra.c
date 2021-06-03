#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 10
#define INF 10000
#define TRUE 1
#define FALSE 0

int selected[SIZE] = { FALSE };
int distance[SIZE];

typedef struct {
	int n;
	int weight[SIZE][SIZE];
}GraphType;

void print_status(GraphType* g)
{
	static int step = 1;
	printf("STEP %d : ", step++);
	printf("distance : ");
	for (int i = 0; i < g->n; i++)
	{
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("         selected : ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", selected[i]);
	printf("\n\n");
}

int choose(int n)
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !selected[i])
		{
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest_path(GraphType* g, int s)
{
	int i, u, v;
	for (i = 0; i < g->n; i++)
		distance[i] = g->weight[s][i];
	selected[s] = TRUE;
	for (i = 0; i < g->n; i++)
	{
		print_status(g);
		u = choose(g->n);

		selected[u] = TRUE;
		for (v = 0; v < g->n; v++)
			if (!selected[v])
				if (distance[u] + g->weight[u][v] < distance[v])
					distance[v] = distance[u] + g->weight[u][v];
	}
}

int main()
{

	GraphType g = { 7,
		{{0,2,INF,1,INF,INF,INF},
		{INF,0,INF,3,10,INF,INF},
		{4,INF,INF,INF,INF,5,INF},
		{INF,INF,2,0,2,8,4},
		{INF,INF,INF,INF,0,INF,6},
		{INF,INF,INF,INF,INF,0,INF},
		{INF,INF,INF,INF,INF,1,0}}
	};
	shortest_path(&g, 0);
}