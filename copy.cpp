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
	vector<double> array(size, 0);
	vector<double> array2(size);
	if(argc == 2 && string(argv[1]) == "copy") {
		cout << "std::copy" << endl;
		for(int ii = 0 ; ii < iters; ii++)
			copy(array.begin(), array.end(), array2.begin());
	} else if(argc == 2 && string(argv[1]) == "memcpy") {
		cout << "memcpy" << endl;
		for(int ii = 0 ; ii < iters; ii++)
			memcpy(array2.data(), array.data(), sizeof(array[0])*array.size());
	} else if(argc == 2 && string(argv[1]) == "memmove") {
		cout << "memmove" << endl;
		for(int ii = 0 ; ii < iters; ii++)
			memmove(array2.data(), array.data(), sizeof(array[0])*array.size());
	} else {
		cout << "for" << endl;
		for(int jj = 0 ; jj < iters; jj++)
			for(int ii = 0 ; ii < array.size(); ii++)
				array2[ii] = array[ii];
	}
}
