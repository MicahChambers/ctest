#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <functional>
#include <list>
#include <cassert>
#include <ctime>
#include <random>

#include "mathparse.h"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

struct OperandT
{
	//literal operand
	string lit; 
	
	//Operand consisting of the result of an operation
	char op;
};

bool isdecimal(char c)
{
	return isdigit(c) || c == '.';
}

/**
 * @brief Reads from input string and returns a whole token 
 * 			(operator/literal/variable). We give [] special
 * 			privilege and allow for string names 
 * 			unlike normal tokenizers. (Assumes no whitespace)
 *
 * @param pos	input/output start searching at this point in the string, 
 * 				gets changed to the start of the next search
 * @param str	string to search for a token
 *
 * @return 		token
 */
OperandT gettoke(int& pos, string str, bool prevop)
{
	OperandT fail = {"", 0};

	if(pos >= (int)str.size())
		return fail;

	int beg;
	string str2;

	//check if its an operator
	if(MATHOPS.find(str[pos]) != string::npos && 
			!(prevop && (str[pos] == '+' || str[pos] == '-'))) {
		pos++;
		OperandT tmp = {"", str[pos-1]};
		return tmp;
	}

	/* 
	 * Check for non-operator string
	 */

	if(isalpha(str[pos])) {
		//if it is a varname, get the whole name
		for(beg = pos; pos < (int)str.size() && isalpha(str[pos]); pos++) continue;

		if(pos > beg)
			str2 = str.substr(beg, pos-beg);
		
		// check for bracketed expression after literal string
		if(str[pos] == '[') {
			beg = pos++;

			//only allow commas if there is numeric input
			if(str[pos] == '-' || str[pos] == '+' || isdecimal(str[pos])) {

				//allow for preceeding +/-
				if(str[pos] == '-' || str[pos] == '+')
					pos++;

				for(; pos < (int)str.size() && (str[pos] == ',' || isdecimal(str[pos]));  pos++) 
						continue;
			} else if(isalpha(str[pos])) {
			//if there is a variable in the [] then only allow one
				for(; pos < (int)str.size() && isalpha(str[pos]);  pos++)
					continue;
			}

			if(pos == (int)str.size() || str[pos] != ']') {
				cerr << "Error Parsing input, it looks like you are missing a closing"
					"bracket, or have not provided a legal index " 
					<< endl << str << endl << std::setw(beg+1) << '^' << endl;
				return fail;
			}
			str2 += str.substr(beg, ++pos-beg);
		}

	} else {
		//if it is a number, get the whole number, including prefix +/-
		beg = pos;
		if(str[pos] == '-' || str[pos] == '+')
			pos++;

		for(; pos < (int)str.size() && isdecimal(str[pos]);  pos++) 
			continue;

		if(pos > beg)
			str2 = str.substr(beg, pos-beg);
	}

	if(str2 != "") {
		OperandT tmp = {str2, 0}; 
		return tmp;
	} else {
		cerr << "Error Parsing input at " << endl
				<< str << endl << std::setw(pos+1) << '^' << endl;
		return fail;
	}
	return fail;
}

string makestring(char c)
{
	string ret(" ");
	ret[0] = c;
	return ret;
}


/**
 * @brief Takes a string of infix math operations and converts them to RPN
 *
 * @param str	Input string
 *
 * @return 		Output RPN expression as list
 */
std::list<string> reorder(std::string str)
{
	int pos = 0;
	int prev = -1;

	std::list<string> outqueue;
	std::list<char> opstack;

	int jj = 0;
	for(int ii = 0; ii < (int)str.length(); ii++) {
		if(!isprint(str[ii])) {
			cerr << "Error, not sure what this character is: " << endl << str
					<< std::setw(ii) << "^" << endl; 
			return outqueue;
		}
		if(!isspace(str[ii])) 
			str[jj++] = str[ii];
	}
	str.resize(jj);

	/* While there are tokens to evaluate */
	bool prevop = true;
	OperandT toke = gettoke(pos, str, prevop);
	while(prev < pos) {

		if(toke.lit != "") {
			// Literal, string or number
			prevop = false;
			outqueue.push_back(toke.lit);
		} else if(toke.op != 0) {
			// Operator 
			prevop = true;
			if(toke.op == '(') {
				// Open Parenthetical
				opstack.push_front(toke.op);
			} else if(toke.op == ')') {
				// Close Parenthetical
				while(opstack.front() != '(') {
					outqueue.push_back(makestring(opstack.front()));
					opstack.pop_front();
					if(opstack.empty()) {
						cerr << "Error, closed paren was never opened" << endl;
						return std::list<string>();
					}
				}
				opstack.pop_front();
			} else {
				// Additional Operator, add to stack
				int opi1 = MATHOPS.find(toke.op);
				while(!opstack.empty()) {
					// Go ahead and evaluate higher priority operators before 
					// the current
					int opi2 = MATHOPS.find(opstack.front()); 
					if((MATHOPA[opi1] == 'l' && MATHOPP[opi1] == MATHOPP[opi2]) || 
							MATHOPP[opi1] < MATHOPP[opi2]) {
						outqueue.push_back(makestring(opstack.front()));
						opstack.pop_front();
					} else {
						break;
					}
				}
				// Add latest operator to stack until we find lower priority op
				opstack.push_front(toke.op);
			}
		}
		prev = pos;
		toke = gettoke(pos, str, prevop);
	}

	// Copy last operators to output queue
	while(!opstack.empty()) {
		if(opstack.front() == '(') {
			cerr << "Error, unmatched paranthesis remains" << endl;
			return std::list<string>();
		}
		outqueue.push_back(makestring(opstack.front()));
		opstack.pop_front();
	}

	size_t varcount = 0;
	size_t opcount = 0; 
	for(auto it = outqueue.begin(); it != outqueue.end(); it++) {
		if(it->length() > 1 || MATHOPS.find(*it) == string::npos) 
			varcount++;
		else
			opcount++;
	}

	std::ostringstream ostr("");
	for(auto it = outqueue.begin(); it != outqueue.end(); it++) {
		ostr << *it << " ";
	}
	cout << "RPN: " << ostr.str() << endl;

	if(opcount+1 > varcount) {
		cerr << "Error, too many operators, not enough arguments" << endl;
		return std::list<string>();
	}
	if(opcount+1 < varcount) {
		cerr << "Error, too many arguments, not enough operators" << endl;
		return std::list<string>();
	}

	return outqueue;
	
}
		
double getV(const std::vector<double>& args, size_t& ii)
{
	return args[ii++];
}

double procV(const std::vector<double>& args, size_t& ii,
		std::function<double(const std::vector<double>&, size_t&)> bef1, 
		std::function<double(const std::vector<double>&, size_t&)> bef2,
		std::function<double(double,double)> fc)
{
	double A = bef1(args, ii);
	double B = bef2(args, ii);

	return fc(A, B);
}

double recurseWrap(const std::vector<double>& args, const size_t sz,
			std::function<double(const std::vector<double>&, size_t&)> f)
{
	size_t ii = 0;
	if(args.size() != sz) {
#ifndef NDEBUG
		cerr << "Error Incorrect Number of Arguments for the given equation" << endl;
#endif //NDEBUG
		return NAN;
	}
	return f(args, ii);	
}

std::function<double(const std::vector<double>&)>
makeRecMath(std::list<string> rpn, std::vector<string>& args)
{
	using namespace std::placeholders;
	
	std::vector<string> arglist;

	std::vector<std::function<double(const std::vector<double>&, size_t&)>> funcs;

	for(auto it = rpn.begin(); it != rpn.end(); it++) {

		// operations should have length 1, literals can sometimes have -+ at 
		// front
		size_t opi = string::npos;
		if(it->length() == 1)
			opi = MATHOPS.find((*it)[0]);

		if(opi != string::npos) {

			if(arglist.size() < 2) {
				cerr << "Error, invalid expression, not enough args!" << endl;
				return NULL;
			}
			
			if(arglist[arglist.size()-1] == "!" && 
					arglist[arglist.size()-2] == "!") {

				auto f1 = funcs.back();
				funcs.pop_back();
				
				auto f2 = funcs.back();
				funcs.pop_back();

				auto newfunc = bind(procV, _1, _2, f2, f1, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				
				//take the used arguments off the arglist
				arglist.pop_back();
				arglist.pop_back();
			} else if(arglist[arglist.size()-1] == "!") {
				auto f1 = funcs.back();
				funcs.pop_back();
				
				auto newfunc = bind(procV, _1, _2, getV, f1, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				
				//take the used arguments off the arglist
				arglist.pop_back();
				arglist.pop_back();
			} else if(arglist[arglist.size()-2] == "!") {
				auto f2 = funcs.back();
				funcs.pop_back();
				
				auto newfunc = bind(procV, _1, _2, f2, getV, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				//take the used arguments off the arglist
				arglist.pop_back();
				arglist.pop_back();
			} else {
				auto newfunc = bind(procV, _1, _2, getV, getV, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				
				std::string a = arglist.back();
				arglist.pop_back();
				std::string b = arglist.back();
				arglist.pop_back();
			} 

			arglist.push_back("!");
		} else {
			//add operand to arg stack
			arglist.push_back(*it);
		}
	}
	
	if(arglist.size() != 1) {
		cerr << "Error Too Many Terms!" << endl;
		return NULL;
	}

	args.clear();
	for(auto it = rpn.begin() ; it != rpn.end(); it++) {
		if(it->length() > 1 || MATHOPS.find((*it)[0]) == string::npos) {
			args.push_back(*it);
		}
	}

	return bind(recurseWrap, _1, args.size(), funcs.back());
}
///**
// * @brief Example Evaluation function
// *
// * @param rpn
// *
// * @return 
// */
//int eval(const list<string>& rpn)
//{
//	// Check the validity of the RPN statement, and create a string for 
//	// user inspection
//	list<string> arglist;
//	std::ostringstream ostr("");
//	for(auto it = rpn.begin(); it != rpn.end(); it++) {
//		ostr << *it << " ";
//	}
//	cout << "RPN: " << ostr.str() << endl;
//
//	int pos = 0;
//	for(auto it = rpn.begin(); it != rpn.end(); it++) {
//		pos += it->length() + 1;
//
//		if(ops.find((*it)[0]) != string::npos) {
//			//simulate performing the operation
//			if(arglist.size() < 2) {
//				cerr << "Error, invalid expression!" << endl;
//				return -1;
//			}
//
//			string tmp = arglist.front();
//			arglist.pop_front();
//			tmp = "(" + tmp + *it + arglist.front() + ")";
//			arglist.pop_front();
//			arglist.push_front(tmp);
//		} else {
//			//add operand to operation stack
//			arglist.push_front(*it);
//		}
//	}
//
//	if(arglist.size() != 1) {
//		cerr << "Error Too Many Terms!" << endl;
//		return -1;
//	}
//	cerr << arglist.front() << endl;
//	return 0;
//}

/**
 * @brief Example Evaluation function
 *
 * @param rpn
 *
 * @return 
 */
double loopMathWrap(const std::vector<double>& args, string ops, size_t sz)
{
	if(args.size() != sz) {
#ifndef NDEBUG
		cerr << "Error Incorrect Number of Arguments for the given equation" << endl;
#endif //NDEBUG
		return NAN;
	}
	std::list<double> stack;
	double lhs, rhs;
	
	auto it = args.begin();
	for(size_t ii = 0 ; ii < ops.length(); ii++) {
		switch (ops[ii]) {
			case '+':
				rhs = stack.back(); 
				stack.pop_back();
				lhs = stack.back(); 
				stack.back() = lhs+rhs;
				break;
			case '-':
				rhs = stack.back(); 
				stack.pop_back();
				lhs = stack.back(); 
				stack.back() = lhs-rhs;
				break;
			case '*':
				rhs = stack.back(); 
				stack.pop_back();
				lhs = stack.back(); 
				stack.back() = lhs*rhs;
				break;
			case '/':
				rhs = stack.back(); 
				stack.pop_back();
				lhs = stack.back(); 
				stack.back() = lhs/rhs;
				break;
			case '^':
				rhs = stack.back(); 
				stack.pop_back();
				lhs = stack.back(); 
				stack.back() = pow(lhs,rhs);
				break;
			case '!': //load
				stack.push_back(*it);
				it++;
				break;
		}
	}
	assert(stack.size() == 1);
	return stack.back();
}

std::function<double(const std::vector<double>&)>
makeLoopMath(std::list<string> rpn, std::vector<string>& args)
{
	using namespace std::placeholders;
	
	std::ostringstream oss;
	args.clear();
	for(auto it = rpn.begin(); it != rpn.end(); it++) {
		if(it->length() > 1 || MATHOPS.find((*it)[0]) == string::npos) {
			oss << '!';
			args.push_back(*it);
		} else {
			oss << (*it)[0];
		}
	}

	return bind(loopMathWrap, _1, oss.str(), args.size());
}

double testmath(double a, double b, double c, double d, double e, double f, double g, double h)
{
	return pow(a*b-pow(c,pow(d,e)) + f*g,h);
}

bool test()
{
	string str = "(3*1-4^1.1^.5 + 3*3)^3.3";

	std::list<string> rpn = reorder(str);
	if(rpn.empty()) {
		return -1;
	}

	std::vector<string> args;
	auto recursiveChain = makeRecMath(rpn, args);
	auto forChain = makeLoopMath(rpn, args);

	std::vector<double> fargs;
	for(auto it = args.begin() ; it != args.end(); it++) {
		fargs.push_back(atof(it->c_str()));
	}

	double a = testmath(3,1,4,1.1,.5,3,3,3.3);
	double b = recursiveChain(fargs);
	double c = forChain(fargs);
	
	bool success = true;
	cerr << "Recursive" << endl;
	cerr << a << " == " << b;
	if(fabs(a-b) < 0.0000000001) {
		cerr << ", True" << endl;
	} else {
		cerr << ", False" << endl;
		success = false;
	}

	cerr << "Iterative" << endl;
	cerr << a << " == " << c;
	if(fabs(a-c) < 0.0000000001) {
		cerr << ", True" << endl;
	} else {
		cerr << ", False" << endl;
		success = false;
	}

	return success;
}

void speedtest(int iters)
{
	string str = "(3*1-4^1.1^.5 + 3*3)^3.3";

	std::list<string> rpn = reorder(str);
	if(rpn.empty()) {
		return ;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 10);

	std::vector<string> args;
	auto recursiveChain = makeRecMath(rpn, args);
	auto forChain = makeLoopMath(rpn, args);

	std::vector<double> fargs(args.size());

	// store the results, so that compiled math doesn't get over optimized
	std::list<double> results;

	/* 
	 * Compiled Math
	 */
	auto c1 = clock();
	for(int ii = 0 ; ii < iters ; ii++) {
		results.push_back(testmath(dis(gen),dis(gen),dis(gen),dis(gen),dis(gen),
					dis(gen),dis(gen),dis(gen)));
	}
	auto c2 = clock();
	double base = ((double)(c2-c1))/CLOCKS_PER_SEC;
	fprintf(stderr, "base %li ticks (%f sec) (%fx)\n", c2-c1, base, base/base);
	results.clear();

	/* 
	 * Test of Recursive 'elegent-but-slow' based math 
	 */
	c1 = clock();
	for(int ii = 0 ; ii < iters ; ii++) {
		for(int jj = 0 ; jj < (int)fargs.size(); jj++)
			fargs[jj] = dis(gen);
		results.push_back(recursiveChain(fargs));
	}
	c2 = clock();
	double recu = ((double)(c2-c1))/CLOCKS_PER_SEC;
	fprintf(stderr, "recursive %li ticks (%f sec) (%fx)\n", c2-c1, recu, recu/base);
	results.clear();

	/* 
	 * Test of For-Loop/Case based math 
	 */
	c1 = clock();
	for(int ii = 0 ; ii < iters ; ii++) {
		for(int jj = 0 ; jj < (int)fargs.size(); jj++) {
			fargs[jj] = dis(gen);
		}
		results.push_back(forChain(fargs));
	}
	c2 = clock();
	double forl = ((double)(c2-c1))/CLOCKS_PER_SEC;
	fprintf(stderr, "for loop %li ticks (%f sec) (%fx)\n", c2-c1, forl, forl/base);
	results.clear();
	
	/* 
	 * Test of non-wrapped math expresssion
	 */
	std::ostringstream oss;
	for(auto it = rpn.begin(); it != rpn.end(); it++) {
		if(MATHOPS.find((*it)[0]) == string::npos) {
			oss << '!';
		} else {
			oss << (*it)[0];
		}
	}
	c1 = clock();
	for(int ii = 0 ; ii < iters ; ii++) {
		for(int jj = 0 ; jj < (int)fargs.size(); jj++)
			fargs[jj] = dis(gen);
		results.push_back(loopMathWrap(fargs, oss.str(), fargs.size()));
	}
	c2 = clock();
	results.clear();
	
	double forlNoWrap = ((double)(c2-c1))/CLOCKS_PER_SEC;
	fprintf(stderr, "for loop (no wrapper) %li ticks (%f sec) (%fx)\n", 
			c2-c1, forlNoWrap, forlNoWrap/base);

}

