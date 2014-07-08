#include <typeinfo>
#include <iostream>

using namespace std;

struct newclass
{
	char a;
	int b;
};

template <typename T>
void print(T val)
{
	if(typeid(newclass) == typeid(val)) cerr << "newclass" << endl;
	else if(typeid(uint8_t) == typeid(T)) cerr << "uint8_t" << endl;
	else if(typeid(int8_t) == typeid(T)) cerr << "int8_t" << endl;
	else if(typeid(uint16_t) == typeid(T)) cerr << "uint16_t" << endl;
	else if(typeid(int16_t) == typeid(T)) cerr << "int16_t" << endl;
	else if(typeid(uint32_t) == typeid(T)) cerr << "uint32_t" << endl;
	else if(typeid(int32_t) == typeid(T)) cerr << "int32_t" << endl;
	else if(typeid(uint64_t) == typeid(T)) cerr << "uint64_t" << endl;
	else if(typeid(int64_t) == typeid(T)) cerr << "int64_t" << endl;
	else if(typeid(float) == typeid(T)) cerr << "float" << endl;
	else if(typeid(double) == typeid(T)) cerr << "double" << endl;
}

int main()
{
	newclass val;
	print(val);
}
