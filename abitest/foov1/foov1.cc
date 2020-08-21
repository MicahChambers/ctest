#include <iostream>
#include "foov1.h"

double multiplyElements(Foo foo)
{
    std::cerr << "foov2" << std::endl;
    return foo.x * foo.y * foo.z * foo.q;
}
