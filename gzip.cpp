#include <iostream>
#include "zlib.h"


int main(int argc, char** argv)
{
	size_t SIZE = 1024*1024;
	srand(1);

	std::cerr << "Writing" << std::endl;
	auto gzfile = gzopen("test.gz", "wb");
	gzbuffer(gzfile, 131072);
	
	for(size_t ii=0 ; ii<SIZE; ii++) {
		int r = ii;
		gzwrite(gzfile, &r, sizeof(int));
	}
	gzclose(gzfile);
	std::cerr << "Closed" << std::endl;
	
	std::cerr << "Reading" << std::endl;
	gzfile = gzopen("test.gz", "rb");
	gzbuffer(gzfile, 131072);
	
	srand(1);
	for(size_t ii=0 ; ii<SIZE; ii++) {
		int rr = ii;
		int r;
		gzread(gzfile, &r, sizeof(int));
		if(rr != r) {
			std::cerr << "Error, different" << std::endl;
			return -1;
		}

	}
	gzclose(gzfile);
	std::cerr << "Closed" << std::endl;

	return 0;
}
