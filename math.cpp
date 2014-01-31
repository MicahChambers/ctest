#include <string>
#include <iostream>
#include <list>
#include <sstream>

#include "mathparse.h"

using std::string;
using std::list;
using std::cout;
using std::cerr;
using std::endl;

/**
 * @brief Example Evaluation function
 *
 * @param rpn
 *
 * @return 
 */
int eval(const list<string>& rpn)
{
	// Check the validity of the RPN statement, and create a string for 
	// user inspection
	list<string> arglist;
	std::ostringstream ostr("");
	for(auto it = rpn.begin(); it != rpn.end(); it++) {
		ostr << *it << " ";
	}
	cout << "RPN: " << ostr.str() << endl;

	int pos = 0;
	for(auto it = rpn.begin(); it != rpn.end(); it++) {
		pos += it->length() + 1;

		if(it->length() == 1 && MATHOPS.find((*it)[0]) != string::npos) {
			//simulate performing the operation
			if(arglist.size() < 2) {
				cerr << "Error, invalid expression!" << endl;
				return -1;
			}

			string tmp = arglist.front();
			arglist.pop_front();
			tmp = "(" + arglist.front() + *it + tmp + ")";
			arglist.pop_front();
			arglist.push_front(tmp);
		} else {
			//add operand to operation stack
			arglist.push_front(*it);
		}
	}

	if(arglist.size() != 1) {
		cerr << "Error Too Many Terms!" << endl;
		return -1;
	}
	cerr << arglist.front() << endl;
	return 0;
}

int main(int argc, char** argv)
{

	if(argc != 2) {
		std::cerr << "Needs 1 argument" << std::endl;
	}
	
	list<string> rpn = reorder(argv[1]);
	if(rpn.empty()) {
		return -1;
	}
	if(eval(rpn) < 0) {
		return -1;
	}
}
