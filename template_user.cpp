#include "template_shared_object.h"

int main()
{
	double a = 1;
	int b = 1;
	char c = 1;
	hello(a);
	hello(b);
	hello(c);

	a = world(1.1);
	b = world(1.1);
}
