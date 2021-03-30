#pragma warning(disable: 4996)

#include <stdio.h>
#define True 1
#define False 0

int isPalindrome(char* A, int n)
{
	for (int i = 0; i < n / 2; i++)
		if (A[i] != A[n - i - 1])
			return False;
	return True;
}

int main()
{
	printf("isPalindrome(A,n)\n");
	printf("sky is blue : %d\n", isPalindrome("sky is blue", 11));
	printf("over the rainbow : %d\n", isPalindrome("over the rainbow", 16));
	return 0;
}