#include "extern_1.h"
#include <iostream>

extern const double external;
extern const double* external_ptr;
using namespace std;

int main()
{
	cout << external_ptr << endl;
	cout << &external << endl;
	
	cout << *external_ptr << endl;
	cout << external << endl;
}
