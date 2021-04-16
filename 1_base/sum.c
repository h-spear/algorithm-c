#include <stdio.h>

// O(n)
int sum(int n)
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum += i;
	return sum;
}

int main()
{
	printf("%d\n", sum(10));
	return 0;
}