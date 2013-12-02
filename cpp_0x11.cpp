#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	auto test1 = 1;
	auto test2 = 1.0;

	cout << test1 << endl;
	cout << test2 << endl;
	cout << test1/1000 << endl;
	cout << test2/1000 << endl;
	cout << test1/1000. << endl;
	cout << test2/1000. << endl;
}
