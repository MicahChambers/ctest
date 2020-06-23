#include <iostream>
#include <vector>

class Base {
 public:
  virtual ~Base() = default;
};

class Derived : public Base {
 public:
  ~Derived() { std::cerr << "Deallocating derived" << std::endl; }
  std::vector<int> values;
};

int main() {
  Derived* d = new Derived;
  d->values.assign({1, 2, 3});

  Base* b = d;
  delete b;
}
