#pragma warning(disable: 4996)

#include <stdio.h>
#define True 1
#define False 0


int rIsPalindrome(char* A, int l, int r)
{
	if (l / 2 == r)
		return True;
	else
	{
		if (A[r] == A[l - r - 1])
			return rIsPalindrome(A, l, r + 1);
		else
			return False;
	}
}

int isPalindrome(char* A, int n)
{
	return rIsPalindrome(A, n, 0);
}

int main()
{
	printf("isPalindrome(A,n)\n");
	printf("sky is blue : %d\n", isPalindrome("sky is blue", 11));
	printf("over the rainbow : %d\n", isPalindrome("over the rainbow", 16));
	return 0;
}