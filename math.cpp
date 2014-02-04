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

double bigmath(double a, double b, double c, double d, double e, double f, double g, double h)
{
	return pow(a*b-pow(c,pow(d,e)) + f*g,h);
}

int main(int argc, char** argv)
{
	string str = "(3*1-4^1.1^.5 + 3*3)^3.3";
	
	list<string> rpn = reorder(str);
	if(rpn.empty()) {
		return -1;
	}

	std::list<string> args;
	auto foo = makeChain(rpn, args);

	std::vector<double> fargs;
	cerr << "Args: ";
	for(auto it = args.begin() ; it != args.end(); it++) {
		fargs.push_back(atof(it->c_str()));
		cerr << *it << ",";
	}
	cerr << endl;

	cerr << bigmath(3,1,4,1.1,.5,3,3,3.3) << "vs " << foo(fargs) << endl;

	const int ITERS = 1000000;
	cerr << "BigMath: " << endl;
	for(int ii = 0 ; ii < ITERS; ii++) {
		bigmath(3,1,4,1.1,.5,3,3,3.3);
	}
	cerr << "Dynamic: " << endl;
	for(int ii = 0 ; ii < ITERS; ii++) {
		
		foo(fargs);
	}

//	if(eval(rpn) < 0) {
//		return -1;
//	}
}
