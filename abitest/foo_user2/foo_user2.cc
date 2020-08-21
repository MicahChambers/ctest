#include <iostream>
#include "foo_user2.h"
#include "foov2.h"

double foo_user2()
{
    Foo foo;
    foo.x = 10;
    foo.y = 10;

    std::cerr << "Expect foov2, 100" << std::endl;
    double out = multiplyElements(foo);
    std::cerr << "Got: " << out << std::endl;
    return out;
}
