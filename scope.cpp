#include <iostream>

using std::cout;
using std::endl;

class test
{
	public:
		test(int var);
		int var;
};

test::test(int var)
{
	cout << "this->var " << this->var << endl;
	cout << "var " << var << endl;
	cout << "::var " << var << endl;

}

int main()
{
	test(5);
}
