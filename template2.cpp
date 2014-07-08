#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template <typename C>
void foo(const C& arr)
{
	for(size_t ii=0; ii<arr.size(); ii++){
		cerr << arr[ii] << endl;
	}
}

template <typename C>
void foo(C arr)
{
	for(size_t ii=0; ii<arr.size(); ii++){
		cerr << arr[ii] << endl;
	}
}

int main()
{
	std::vector<double> test(10,0);
//	foo(test);
//	foo({1,2,3});
//	foo({(double)1,(double)2,(double)3});
}
