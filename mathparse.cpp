#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <functional>
#include <list>

#include "mathparse.h"

//using std::list;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
//using std::vector;
//using std::function;
//using std::shared_ptr;
//using std::setw;

struct OperandT
{
	//literal operand
	string lit; 
	
	//Operand consisting of the result of an operation
	char op;
};

bool isnumeric(char c)
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

	if(pos >= str.size())
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
		for(beg = pos; pos < str.size() && isalpha(str[pos]); pos++) continue;

		if(pos > beg)
			str2 = str.substr(beg, pos-beg);

	} else {
		//if it is a number, get the whole number
		for(beg = pos; pos < str.size() && isnumeric(str[pos]);  pos++) 
			continue;
		if(pos > beg)
			str2 = str.substr(beg, pos-beg);
	}

	/* 
	 * check for bracketed expression after literal string
	 */
	
	if(str[pos] == '[') {
		beg = pos++;

		//only allow commas if there is numeric input
		if(isnumeric(str[pos])) {
			for(; pos < str.size() && (str[pos] == ',' || isnumeric(str[pos]));  pos++) 
					continue;

		} else if(isalpha(str[pos])) {
		//if there is a variable in the [] then only allow one
			for(; pos < str.size() && isalpha(str[pos]);  pos++)
				continue;
		}

		if(pos == str.size() || str[pos] != ']') {
			cerr << "Error Parsing input, it looks like you are missing a closing"
				"bracket, or have not provided a legal index " 
				<< endl << str << endl << std::setw(beg+1) << '^' << endl;
			return fail;
		}
		str2 += str.substr(beg, ++pos-beg);
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
	for(int ii = 0; ii < str.length(); ii++) {
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

	return outqueue;
	
}
		
double getV(std::list<double>& args)
{
	double A = args.front();
	args.pop_front();
	return A;
}

double procV(std::list<double>& args, 
		std::function<double(std::list<double>&)> bef1, 
		std::function<double(std::list<double>&)> bef2,
		std::function<double(double,double)> fc)
{
	double A = bef1(args);
	double B = bef2(args);

	return fc(A, B);
}

double wrap(std::list<double> args, std::function<double(std::list<double>&)> f)
{
	return f(args);
}

std::function<double(std::list<double>&)>
makeChain(std::list<string> rpn, std::list<string>& args)
{
	using namespace std::placeholders;
	
	std::vector<string> arglist;

#ifndef NDEBUG
	std::ostringstream ostr("");
	for(auto it = rpn.begin(); it != rpn.end(); it++) {
		ostr << *it << " ";
	}
	cout << "RPN: " << ostr.str() << endl;
#endif //NDEBUG

	std::vector<std::function<double(std::list<double>&)>> funcs;

	for(auto it = rpn.begin(); it != rpn.end(); it++) {

		size_t opi = MATHOPS.find((*it)[0]);
#ifndef NDEBUG
		cerr << "Op: ";
		cerr << "Arglist: ";
		for(auto it = arglist.begin(); it != arglist.end(); it++) 
			cerr << *it << ",";
		cerr << endl;
#endif //NDEBUG
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

				auto newfunc = bind(procV, _1, f2, f1, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				
				//take the used arguments off the arglist
				arglist.pop_back();
				arglist.pop_back();
			} else if(arglist[arglist.size()-1] == "!") {
				auto f1 = funcs.back();
				funcs.pop_back();
				
				auto newfunc = bind(procV, _1, getV, f1, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				
				//take the used arguments off the arglist
				arglist.pop_back();
				arglist.pop_back();
			} else if(arglist[arglist.size()-2] == "!") {
				auto f2 = funcs.back();
				funcs.pop_back();
				
				auto newfunc = bind(procV, _1, f2, getV, MATHFUNC[opi]);
				funcs.push_back(newfunc);
				//take the used arguments off the arglist
				arglist.pop_back();
				arglist.pop_back();
			} else {
				auto newfunc = bind(procV, _1, getV, getV, MATHFUNC[opi]);
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
		if(MATHOPS.find((*it)[0]) == string::npos) {
			args.push_back(it->c_str());
		}
	}

	return bind(wrap, _1, funcs.back());
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


