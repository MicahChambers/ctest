#include <iostream>

class base 
{
public:
	base() : a(5) {} ;
	const double a;
};

class derived : public virtual base
{
};

std::ostream& operator<<(std::ostream& os, const base& b)
{
	os << b.a << std::endl;
	return os;
};

int main()
{
	derived a;
	base& abase = a;
	base* apoint = &a;
	std::cerr << a << std::endl;
	std::cerr << abase << std::endl;
	std::cerr << *apoint << std::endl;
}
