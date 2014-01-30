#include "template_shared_object.h"
#include "template_shared_object.txx"

int force()
{
	hello<double>(1.1);
	hello<int>(1);
	hello<char>('a');
	world<double>(1.1);
	world<int>(1.1);
}
