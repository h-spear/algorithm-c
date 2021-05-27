#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8

typedef struct {
	int x;
	int y;
}coordinates;

void printCoord(coordinates C)
{
	printf("(%d,%d) ", C.x, C.y);
}

void print(coordinates C[], int n)
{
	for (int i = 0; i < n; i++)
		printCoord(C[i]);
	printf("\n");
}

// O(logn)
coordinates findTopCoord(coordinates C[], int n)
{
	int a = 0;
	int b = n - 1;
	while (a < b)
	{
		int mid = (a + b) / 2;
		if (C[mid].y < C[mid + 1].y)
			a = mid + 1;
		if (C[mid].y > C[mid + 1].y)
			b = mid;
	}
	return C[a];
}

coordinates findRightCoord(coordinates C[], int n)
{
	int a = 0;
	int b = n - 1;
	while (a < b)
	{
		int mid = (a + b) / 2;
		if (C[mid].x < C[mid + 1].x)
			a = mid + 1;
		if (C[mid].x > C[mid + 1].x)
			b = mid;
	}
	return C[a];
}

coordinates findBottomCoord(coordinates C[], int n)
{
	int a = 0;
	int b = n - 1;
	while (a < b)
	{
		int mid = (a + b) / 2;
		if (C[mid].y > C[mid + 1].y)
			a = mid + 1;
		if (C[mid].y < C[mid + 1].y)
			b = mid;
	}
	return C[a];
}

coordinates findLeftCoord(coordinates C[], int n)
{
	int a = 0;
	int b = n - 1;
	while (a < b)
	{
		int mid = (a + b) / 2;
		if (C[mid].x > C[mid + 1].x)
			a = mid + 1;
		if (C[mid].x < C[mid + 1].x)
			b = mid;
	}
	return C[a];
}

int main()
{
	coordinates C[N] = { {-10,20},{-2,11},{4,-4},{9,14},{15,17},{16,20},{3,35},{1,37} };

	print(C, N);
	printf("\n가장 오른쪽으로 돌출한 정점: ");
	printCoord(findRightCoord(C, N));

	printf("\n가장 왼쪽으로 돌출한 정점: ");
	printCoord(findLeftCoord(C, N));

	printf("\n가장 위로 돌출한 정점: ");
	printCoord(findTopCoord(C, N));

	printf("\n가장 아래로 돌출한 정점: ");
	printCoord(findBottomCoord(C, N));

	return 0;
}