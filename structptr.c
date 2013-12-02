#include <stdio.h>
#include <stdlib.h>

typedef struct 
{	
	int a;
	float b;
	char c;
} Foo;

int main()
{
	void* tmp = malloc(sizeof(Foo)*10);
	Foo* it = tmp;
	for(int ii = 0 ; ii < 10; ii++, it++) {
		fprintf(stderr, "%i %p\n", ii, it);
	}
}
