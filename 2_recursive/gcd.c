#pragma warning(disable: 4996)

#include <stdio.h>

int gcd1(int a, int b)
{
	if (b == 0)
		return a;
	else
	{
		return gcd1(b, a % b);
	}
}

int gcd2(int a, int b)
{
	if (a == b)
		return a;
	else
	{
		if (a > b)
			return gcd2(a - b, b);
		else
			return gcd2(a, b - a);
	}
}

int main()
{
	printf("greatest common divisor, GCD(ver1)\n");
	printf("gcd1(48,16) : %d\n", gcd1(48, 16));
	printf("gcd1(78,104) : %d\n", gcd1(78, 104));
	printf("gcd1(368,138) : %d\n\n", gcd1(368, 138));

	printf("greatest common divisor, GCD(ver2)\n");
	printf("gcd2(48,16) : %d\n", gcd2(48, 16));
	printf("gcd2(78,104) : %d\n", gcd2(78, 104));
	printf("gcd2(368,138) : %d\n", gcd2(368, 138));
	return 0;
}