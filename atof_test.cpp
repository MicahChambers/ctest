#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) 
{
	if(argc != 2)
		return -1;

	cerr << argv[1] << " -> " << setprecision(100) << atof(argv[1]) << endl;
	return 0;
}
