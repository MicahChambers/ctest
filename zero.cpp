#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int size = 100000000;
	int iters = 10;
	vector<double> array(size);
	if(argc == 2 && string(argv[1]) == "fill") {
		cout << "fill" << endl;
		for(int ii = 0 ; ii < iters; ii++)
			fill(array.begin(), array.end(), 0);
	} else if(argc == 2 && string(argv[1]) == "bzero") {
		cout << "bzero" << endl;
		for(int ii = 0 ; ii < iters; ii++)
			bzero(array.data(), sizeof(array[0])*array.size());
	} else if(argc == 2 && string(argv[1]) == "memset") {
		cout << "memset" << endl;
		for(int ii = 0 ; ii < iters; ii++)
			memset(array.data(), 0, sizeof(array[0])*array.size());
	} else {
		cout << "for" << endl;
		for(int jj = 0 ; jj < iters; jj++)
			for(int ii = 0 ; ii < array.size(); ii++)
				array[ii] = 0;
	}
}
