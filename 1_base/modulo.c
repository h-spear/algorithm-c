#include <stdio.h>

int modulo(int a, int b)
{
	if (a < b)
		return a;
	else
	{
		return modulo(a - b, b);
	}
}

int main()
{
	printf("%d\n",modulo(159484, 51));
	return 0;
}