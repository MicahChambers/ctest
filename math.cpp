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

double bigmath(const std::vector<double>& in)
{
	const double& a = in[0];
	const double& b = in[1];
	const double& c = in[2];
	const double& d = in[3];
	const double& e = in[4];
	const double& f = in[5];
	const double& g = in[6];
	const double& h = in[7];
	return bigmath(a,b,c,d,e,f,g,h);
}


int main(int argc, char** argv)
{
	if(argc != 2) {
		return test() == true;
	}
	
	list<string> rpn = reorder(argv[1]);
	if(rpn.empty()) {
		return -1;
	}

	std::vector<string> args;
	std::vector<double> fargs;
	
	auto foo = makeChain(rpn, args);
	if(!foo) 
		return -1;

	for(auto it = args.begin() ; it != args.end(); it++) 
		fargs.push_back(atof(it->c_str()));

	cerr << foo(fargs) << endl;

}
