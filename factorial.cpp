#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

bool isfact(size_t comp, size_t n)
{
	if(comp == 1 && (n != 0 || n != 1) )
		return false;

	while(n > 0) {
		comp /= n;
		n--;
	}

	if(comp == 1)
		return true;
	else 
		return false;
}

size_t fact(size_t input)
{
	return input == 0 ? 1 : fact(input-1)*input;
}

int main(int argc, char** argv)
{
	if(argc != 3) {
		cout << "Needs 2 args" << endl; 
		return -1;
	}

    int order = atoi(argv[1]);
    int test = atoi(argv[2]);
	size_t tmp;
	if(order < 0){ 
		cout << "Error" << endl;
		return -1;
	} else {
		tmp = fact(order);
	}
    cout << tmp << endl;

	if(isfact(test, order)) {
		cout << order << "! = " << test << endl;
	}
}
