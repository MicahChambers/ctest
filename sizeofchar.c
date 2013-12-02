#include <stdio.h>

int main()
{

	fprintf(stderr, "size: %i\n", sizeof(int));
	fprintf(stderr, "size: %i\n", sizeof("REALSPHARMCOEFFS\0"));
	fprintf(stderr, "size: %i\n", sizeof("DISCSPHFUNC\0"));
	fprintf(stderr, "size: %i\n", sizeof("REALSPHARMCOEFFS"));
	fprintf(stderr, "size: %i\n", sizeof("DISCSPHFUNC"));

}
