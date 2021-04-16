#include <stdio.h>

void printDigits(int n)
{
	if (n < 10)
		printf("%d\n", n);
	else
	{
		printDigits(n / 10);
		printf("%d\n", n % 10);
	}
}

int main()
{
	printDigits(378994);
	return 0;
}