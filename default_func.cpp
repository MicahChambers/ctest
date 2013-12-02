#include <iostream>
#include <map>
#include <string>

using std::string;
using std::map;
using std::cerr;
using std::cout;
using std::endl;

double* func0(double* a)
{
    return a;
}

double* func1(double* a)
{
    return a+1;
}

double* func2(double* a)
{
    return a+2;
}

double* func3(double* a)
{
    return a+3;
}

template <typename T>
class LookupT : public std::map<string, T>
{
    public:
    LookupT()
    {
        (*this)["func0"] = &func0;
        (*this)["func1"] = &func1;
        (*this)["func2"] = &func2;
        (*this)["func3"] = &func3;
    }
};

//double* (*const foo[])(double*) = {&func0, &func1, &func2, &func3};
//enum {FUNC0, FUNC1, FUNC2, FUNC3};
//
//map<string, double* (*)(double*)> gen_lookup()
//{
//    map<string, double* (*)(double*)> lookup;
//    lookup["func0"] = &func0;
//    lookup["func1"] = &func1;
//    lookup["func2"] = &func2;
//    lookup["func3"] = &func3;
//}

int main(int argc, char* argv[])
{
    double arr[] = {1, 2, 3, 4};
    LookupT<double* (*)(double*)> lookup;
    cout << &arr[0] << ", " << lookup["func0"](arr) << ", " << *lookup["func0"](arr) << endl;
    cout << &arr[1] << ", " << lookup["func1"](arr) << ", " << *lookup["func1"](arr) << endl;
    cout << &arr[2] << ", " << lookup["func2"](arr) << ", " << *lookup["func2"](arr) << endl;
    cout << &arr[3] << ", " << lookup["func3"](arr) << ", " << *lookup["func3"](arr) << endl;
}
