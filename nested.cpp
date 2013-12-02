#include <iostream>

using namespace std;

class hello
{

	public:
	class foo
	{
		public:
		void print();
	};

};

void hello::foo::print()
{
	cout << "Hello" << endl;
}

int main()
{
	hello::foo tmp;
	tmp.print();
}
