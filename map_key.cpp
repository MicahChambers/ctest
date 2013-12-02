#include <iostream>
#include <map>
#include <cstdlib>

using namespace std;

struct key
{
	int A;
	mutable int B;
};
	
bool operator<(const key& lhs, const key& rhs) {
	if(lhs.A < rhs.A)
		return true;
	return false;
}

int main()
{
	srand(103);
	map<key, int> test;
	
	key tmp;

	for(int i = 0; i < 10 ; i++) {
		tmp.A = rand();
		tmp.B = rand();
		test[tmp] = rand();
	}

	map<key, int>::iterator it = test.begin();
	while(it != test.end() ) {
		cout << it->first.A << ", " << it->first.B << " : " << it->second << endl;
		it->first.B = rand();
		it++;
	}
	
	cout << endl;
	
	cout << endl;
	
	it = test.begin();
	while(it != test.end() ) {
		cout << it->first.A << ", " << it->first.B << " : " << it->second << endl;
		it++;
	}
}
