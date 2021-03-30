#pragma warning(disable: 4996)

#include <stdio.h>

int product(int a, int b)
{
	if (b == 1)
		return a;
	else
		return a + product(a, b - 1);
}

int modulo(int a, int b)
{
	if (a < b)
		return a;
	else
		return modulo(a - b, b);
}

int quotient(int a, int b)
{
	if (a < b)
		return 0;
	else
		return 1 + quotient(a - b, b);
}

int main()
{
	printf("product(111, 7) : %d\n", product(111, 7));
	printf("modulo(111, 7) : %d\n", modulo(111, 7));
	printf("quotient(111, 7) : %d\n", quotient(111, 7));
	return 0;
}