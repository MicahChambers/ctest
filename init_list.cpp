#include <vector>
#include <list>
#include <iostream>

void foo(const std::vector<double>& in)
{
	for(auto i:in)
		std::cerr << i << std::endl;
}

void bar(const std::list<double>& in)
{
	for(auto i:in)
		std::cerr << i << std::endl;
}

void gar(std::initializer_list<double> in)
{
	for(auto i:in)
		std::cerr << i << std::endl;
}

int main()
{
	foo({1.1,2,3});
	bar({1.1,2,3});
	
	std::vector<double> v({1.1,2,2});
	gar(v);
}
