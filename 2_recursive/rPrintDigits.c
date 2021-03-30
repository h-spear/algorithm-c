#pragma warning(disable: 4996)

#include <stdio.h>

void rPrintDigits(int num)
{

	if (num < 10)
		printf("%d\n", num);
	else
	{
		rPrintDigits(num / 10);
		printf("%d\n", num % 10);
	}
}

void PrintDigits()		// driver
{
	int n;
	printf("Enter a number : ");
	scanf("%d", &n);

	if (n < 0)
		printf("Negative number!");
	else
		rPrintDigits(n);

}

int main()
{
	PrintDigits();
	return 0;
}