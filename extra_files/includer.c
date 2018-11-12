#include "included.h"
#include "stdio.h"

int plusOne(int x)
{
	return factorial(x + 1) + 1;
}

int main()
{
	int c;
	scanf("%d", &c);
	printf("%d", plusOne(c));
	return 0;
}
