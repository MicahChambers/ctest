#include <iostream>
#include "foov2.h"

double multiplyElements(Foo foo)
{
    std::cerr << "foov2" << std::endl;
    return foo.x * foo.y;
}
