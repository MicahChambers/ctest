#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Offset	type	bytes 	name
// 0		int 	8		starting UUID
// 8		int 	8		number of files in archive
//
//struct PackArray
//{
//	int64_t firstUUID;
//	int64_t nfiles;
//	struct {
//		int64_t uuid;
//		struct {
//			int16_t slen;
//			char str[];
//		} name;
//		int64_t datalen;
//	} entry;
//};


int main(int argc, char** argv)
{
	if(argc != 3) {
		cerr << "Please provide input file and output directory:" 
			<< argv[0] << " infile outdir" << endl;
		return -1;
	}

	ifstream ifile(argv[1]);

	for(int ii = 0 ; 
}
