#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int fib_recursive(int n)
{
	if (n == 0 || n == 1)
		return 1;
	else
		return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// linear space
int fib_linear(int n)
{
	int A[SIZE];
	if (n == 0 || n == 1)
		return 1;

	A[0] = 1;
	A[1] = 1;

	for (int i = 2; i <= n; i++)
		A[i] = A[i - 1] + A[i - 2];
	return A[n];
}

// constant space
int fib(int n)
{
	if (n == 0 || n == 1)
		return 1;
	
	int a, b, c = 0;
	a = 1, b = 1;

	for (int i = 2; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

int main()
{
	printf("%d\n", fib_recursive(7));
	printf("%d\n", fib_recursive(7));
	printf("%d\n", fib(7));
}