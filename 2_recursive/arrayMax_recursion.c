#pragma warning(disable: 4996)

#include <stdio.h>

#define SIZE 10
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int arrayMax(int list[], int n)
{
	if (n == 1)
		return list[0];
	else
	{
		return MAX(list[n - 1], arrayMax(list, n - 1));
	}
}

int main()
{
	// max : 95
	int list[SIZE] = { 1,4,8,2,6,10,21,50,95,23 };
	printf("%d", arrayMax(list, SIZE));
	return 0;
}