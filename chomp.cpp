#include <string>
#include <iostream>
using namespace std;

string chomp(string str)
{
	int begin = str.find_first_not_of("\t \n\r");
	if(begin == string::npos)
		return string("");
	
	int end = str.find_last_not_of("\t \n\r");
	if(end == string::npos)
		end = str.length()-1;
	
	return str.substr(begin, end-begin+1);
}

int main(int argc, char** argv)
{
	for(int ii = 0 ; ii < argc ; ii++) {
		string in(argv[ii]);
		cout << "\"" << in << "\" -> \"" << chomp(in) << "\"" << endl;
	}
}
