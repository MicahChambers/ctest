#if !defined(SELFINCLUDE_FLOAT_CPP)
	#define SELFINCLUDE_FLOAT_CPP
	#define USE_FLOAT
	#define GO_SELFINCLUDE_CPP
	#define FTYPE float
#elif !define(SELFINCLUDE_DOUBLE_CPP)
	#define SELFINCLUDE_DOUBLE_CPP
	#define USE_DOUBLE
	#define GO_SELFINCLUDE_CPP
	#define FTYPE double
#endif

#ifdef GO_SELFINCLUDE_CPP

#include <iostream>
using namespace std;
int test()
{
	cout << sizeof(FTYPE) << endl;
}

#include "selfinclude.cpp"
#undef GO_SELFINCLUDE_CPP
#endif
