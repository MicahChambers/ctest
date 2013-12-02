#include <iostream>
#include <vector>

using namespace std;
int main()
{
	vector<double> test(100, 0);

	cout << &test << endl;
	cout << &test[0] << endl;
	cout << test.data() << endl;
}
