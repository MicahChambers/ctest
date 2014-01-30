// hash example
#include <iostream>
#include <functional>
#include <string>

struct HashMe
{
	int a;
	int b;
	int c;
	std::string d;
};

namespace std {
template<>
struct hash<HashMe>
{
public:
    std::size_t operator()(HashMe const& s) const 
    {
        std::size_t h1 = std::hash<int>()(s.a);
        std::size_t h2 = std::hash<int>()(s.b);
        std::size_t h3 = std::hash<int>()(s.c);
        std::size_t h4 = std::hash<std::string>()(s.d);
        return h1 ^ (h2 << 1) ^ (h3 >> 1) ^ (h4 << 2);
    }
};
}

int main ()
{
	char nts1[] = "Test";
	char nts2[] = "Test";
	std::string str1 (nts1);
	std::string str2 (nts2);

	std::hash<char*> ptr_hash;
	std::hash<std::string> str_hash;

	std::cout << "same hashes:\n" << std::boolalpha;
	std::cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
	std::cout << "str1 and str2: " << (str_hash(str1)==str_hash(str2)) << '\n';

	std::hash<HashMe> special_hash;
	HashMe test1;
	test1.a = 1;
	test1.b = 1;
	test1.c = 1;
	test1.d = "hello";

	HashMe test2;
	test2.a = 1;
	test2.b = 1;
	test2.c = 1;
	test2.d = "world";
	
	HashMe test3;
	test3.a = 1;
	test3.b = 1;
	test3.c = 1;
	test3.d = "hello";

	std::cout << special_hash(test1) << std::endl;
	std::cout << special_hash(test2) << std::endl;
	std::cout << special_hash(test3) << std::endl;
	return 0;
}
