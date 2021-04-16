#include <stdio.h>

void isPrime(int r)
{
	for(int p=2;p<r;p++)
		if (r % p == 0)
		{
			printf("비밀 메세지는 %d다!\n", p);
			return;
		}
	printf("소수\n");
	return;
}

int main()
{
	isPrime(37156667);
	return 0;
}