#pragma warning(disable: 4996)

#include <stdio.h>

void rHanoi(int n, char from, char aux, char to)
{
	if (n == 1)
		printf("Disk %d : %c -> %c\n", n, from, to);
	else
	{
		// double recursion
		rHanoi(n - 1, from, to, aux);
		printf("Disk %d : %c -> %c\n", n, from, to);
		rHanoi(n - 1, aux, from, to);
	}
}

void Hanoi(int n)
{
	rHanoi(n, 'A', 'B', 'C');
}

int main()
{
	Hanoi(5);
	return 0;
}