#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	for(int i = 1 ; i < argc; i++) {
		int num = atoi(argv[i]);
		printf("%02x ", num);
	}
}
