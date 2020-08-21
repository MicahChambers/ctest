#include <iostream>
#include "foov1.h"

double foo_user1()
{
    Foo foo;
    foo.x = 10;
    foo.y = 10;
    foo.z = 10;
    foo.q = 10;
    std::cerr << "Expect foov1, 10000" << std::endl;
    double out = multiplyElements(foo);
    std::cerr << "Got: " << out << std::endl;
    return out;
}
