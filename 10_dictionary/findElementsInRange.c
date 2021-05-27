#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8 

typedef struct {
	int succ;
	int mid;
}dict;

dict findElementIndex(int A[], int key, int left, int right)
{
	dict D;
	if (left > right)
	{
		D.mid = left;
		D.succ = 0;
		return D;
	}

	int mid = (left + right) / 2;
	if (key == A[mid])
	{
		D.mid = mid;
		D.succ = 1;
		return D;
	}
	else if (key < A[mid])
		return findElementIndex(A, key, left, mid - 1);
	else
		return findElementIndex(A, key, mid + 1, right);
}

void findElementsInRange(int A[], int k1, int k2)
{
	int loc1, loc2;
	dict D;
	loc1 = findElementIndex(A, k1, 0, SIZE - 1).mid;
	D = findElementIndex(A, k2, 0, SIZE - 1);
	loc2 = D.succ == 1 ? D.mid + 1 : D.mid;

	for (int i = loc1; i < loc2; i++)
	{
		printf("%d ", A[i]);
	}
}

int main()
{
	int A[SIZE] = { 1,4,6,9,15,22,33,37 };

	for (int i = 0; i < SIZE; i++)
		printf("%d ", A[i]);
	printf("\n");

	findElementsInRange(A, 7, 22);
	return 0;
}