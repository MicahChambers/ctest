#include <iostream>

using namespace std;

void printPairs(size_t num, size_t in[][2])
{
	for(size_t ii=0; ii<num; ii++) {
		cerr << "(" << in[ii][0] << "," << in[ii][1] << ")" << endl;
	}
}

int main()
{
//	size_t pairarr[5][2];
	size_t ARRAYSIZE = 5;
	auto pairarr = new size_t[ARRAYSIZE][2];
	for(size_t ii=0; ii<5; ii++) {
		pairarr[ii][0] = ii*1;
		pairarr[ii][1] = ii*2;
	}

	printPairs(5, pairarr);
}
