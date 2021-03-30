#pragma warning(disable: 4996)

#include <stdio.h>

typedef struct {
	int quotient;
	int modulo;
}Value;

Value divide(int a, int b)
{
	Value out;
	if (a < b)
	{
		out.quotient = 0;
		out.modulo = a;
		return out;
	}
	else
	{
		Value d = divide(a - b, b);
		out.quotient = 1 + d.quotient;
		out.modulo = d.modulo;
		return out; 
	}
}

int main()
{
	Value v;
	v = divide(111, 7);
	printf("divide(111,7)\nquotient : %d\nmodulo : %d\n\n",v.quotient, v.modulo);
	return 0;
}