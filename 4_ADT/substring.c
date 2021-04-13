#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 30

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("xmalloc");
		exit(1);
	}
	return p;
}

int substr(char* t, char* s)
{
	for (int i = 0; t[i] != '\0'; i++)
	{
		if (t[i] == s[0])
		{
			int j;
			for (j = 0; s[j] != '\0'; j++)
			{
				if (t[i + j] != s[j])
					break;
			}
			if (s[j] == '\0')
				return i;
		}
	}
	return -1;
}

int main()
{
	char* t, * s;
	t = xmalloc(sizeof(char) * MAX_LENGTH);
	s = xmalloc(sizeof(char) * MAX_LENGTH);


	printf("t: ");
	gets_s(t, sizeof(char) * MAX_LENGTH);

	printf("s: ");
	gets_s(s, sizeof(char) * MAX_LENGTH);

	printf("%d\n", substr(t, s));
	return 0;
}