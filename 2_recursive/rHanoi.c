#pragma warning(disable: 4996)

#include <stdio.h>

void rHanoi(int n, char from, char aux, char to)
{
	if (n == 1)
	{
		printf("Disk %d : %c -> %c\n", n, from, to);
		return;
	}
	else
	{
		rHanoi(n - 1, from, to, aux);
		printf("Disk %d : %c -> %c\n", n, from, to);
		rHanoi(n - 1, aux, from, to);
	}
}

void hanoi(int n)
{
	rHanoi(n, 'A', 'B', 'C');
	return;
}

int main()
{
	hanoi(4);
	return 0;
}