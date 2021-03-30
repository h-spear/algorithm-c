#pragma warning(disable: 4996)

#include <stdio.h>

#define SIZE 10
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	int max;
	int min;
}value;

value arrayMaxMin(int list[], int n)
{
	value v;
	if (n == 1)
	{
		v.max = list[0];
		v.min = list[0];
	}
	else
	{
		v.max = MAX(list[n - 1], arrayMaxMin(list, n - 1).max);
		v.min = MIN(list[n - 1], arrayMaxMin(list, n - 1).min);
	}
	return v;
}

int main()
{
	// max : 95, min = 1
	int list[SIZE] = { 1,4,8,2,6,10,21,50,95,23 };
	value out;

	out = arrayMaxMin(list, SIZE);
	printf("MAX : %d\nMIN : %d", out.max, out.min);
	return 0;
}