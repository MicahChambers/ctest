#include <iostream>
#include "foo_user1.h"
#include "foo_user2.h"

int main()
{
    const double a = foo_user1();
    const double b = foo_user2();
    std::cerr << "Foo1 got: " << a << std::endl;
    std::cerr << "Foo2 got: " << b << std::endl;
}
