#include <iostream>

template<typename T>
void hello(T in)
{
	std::cerr << in << sizeof(in) << std::endl;
}

template<typename T>
T world(double in)
{
	std::cerr << in << sizeof(in) << std::endl;
	return (T)in;
}
