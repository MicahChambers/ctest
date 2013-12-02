#include <stdio.h>

int main()
{
	int C = 1;
	unsigned int D = 1;
	printf("%i\n", C);
	printf("%u\n", D);
	
	C = (C<<1);
	D = (D<<1);
	
	printf("%i\n", C);
	printf("%u\n", D);
	
	C = (C<<1);
	D = (D<<1);
	
	printf("%i\n", C);
	printf("%u\n", D);
}
