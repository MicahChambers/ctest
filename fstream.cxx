#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
    if(argc == 1)
        return 0;
    istream* input;
    fstream infile(argv[1]);
    cout << argv[1] << endl;
    if(!strcmp(argv[1], "-")) {
        cout << "Reading from Cin" << endl;
        input = &cin;
    } else {
        input = &infile;
    }

    std::string tmp;
    while(!input->eof()) {
        *input >> tmp;
        std::cout << tmp;
    }

}
