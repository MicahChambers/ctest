#include "zlib.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) 
{
	size_t rows = 10;
	size_t cols = 20;
	string filename = "test.csv";

	vector<vector<unsigned int>> data(rows);
	ofstream ofs(filename.c_str());
	for(size_t rr=0; rr<rows; rr++) {
		data[rr].resize(cols);
		for(size_t cc=0; cc<rows; cc++) {
			data[rr][cc] = rand();

			// Test poorly separated data (tab+space+comma)
			if(cc != 0)
				ofs << ",   \t";
			ofs << hex << data[rr][cc];
		}
	}
	ofs.close();

	auto gz = gzopen(filename.c_str(), "rb");
	if(gz == NULL) {
		cerr << "Error opening file" << endl;
		return -1;
	}

	int c;
	while((c = gzgetc(gz)) > 0) {
		cerr << (char)c;
	}
}
