#include <iostream>

#include "foo.pb.h"

int main() {
  Foo foo;
  std::cerr << foo.ByteSizeLong() << std::endl;
  foo.set_single_uint(0);
  std::cerr << foo.ByteSizeLong() << std::endl;
  foo.set_single_uint(100000);
  std::cerr << foo.ByteSizeLong() << std::endl;

  foo.mutable_rep_int()->Add(0);
  std::cerr << foo.ByteSizeLong() << std::endl;
  foo.mutable_rep_int()->Add(0);
  foo.mutable_rep_int()->Add(0);
  std::cerr << foo.ByteSizeLong() << std::endl;
}
