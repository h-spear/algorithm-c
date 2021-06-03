#include <stdio.h>
#include <stdlib.h>

#define N 8

void gemGuard(int X[],int k)
{
	int i = 0, j = 0;
	int x, g;
	int G[N];

	x = X[i++];
	g = x + k / 2;
	G[j++] = g;

	while (i < N)
	{
		x = X[i];
		if (x - g > k / 2)
		{
			g = x + k / 2;
			G[j++] = g;
		}
		else
			i++;
	}
	for (int k = 0; k < j; k++)
		printf("%d ", G[k]);
}

int main()
{
	int X[N] = { 1, 3, 6, 8, 9, 13, 17, 19 };
	gemGuard(X, 4);
	return 0;
}