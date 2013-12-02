#include <iostream>
#include <fstream>

using namespace std;

ostream* openFile(string filename) 
{
    ostream* os = NULL;
    
    if(filename == "-" || filename.empty()) {
        os = &cout;
    } else { 
        ofstream* filestream = new ofstream(filename.c_str());
        if(!filestream->is_open()) {
            delete filestream;
            return 0;
        }
        os = filestream;
    }
    return os;
}


int main(int argc, char** argv)
{
	if(argc != 2) 
		return -1;
	ostream* A = openFile("-");
	ostream* B = openFile(argv[1]);
	cout <<  A->is_open() << endl;
	cout <<  B->is_open() << endl;
}
