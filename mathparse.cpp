#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <list>

#include "mathparse.h"

using std::list;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::setw;

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
 * 			unlike normal tokenizers
 *
 * @param pos	input/output start searching at this point in the string, 
 * 				gets changed to the start of the next search
 * @param str	string to search for a token
 *
 * @return 		token
 */
OperandT gettoke(int& pos, string str)
{
	OperandT fail = {"", 0};

	if(pos >= str.size())
		return fail;

	int beg;
	string str2;
	//skip starting white space
	for(; pos < str.size() && isspace(str[pos]) ; pos++) continue;

	//check if its an operator
	if(MATHOPS.find(str[pos]) != string::npos) {
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

	//eat white space
	for(; pos < str.size() && isspace(str[pos]) ; pos++) continue;
	
	if(str[pos] == '[') {
		pos++;
		str2 += '[';
		
		//eat white space
		for(; pos < str.size() && isspace(str[pos]) ; pos++) continue;

		//check for variables (string/number) again
		if(isalpha(str[pos])) {
			//if it is a varname, get the whole name
			for(beg = pos; pos < str.size() && isalpha(str[pos]); pos++) continue;

			if(pos > beg)
				str2 = str2+str.substr(beg, pos-beg);

		} else {
			//if it is a number, get the whole number
			for(beg = pos; pos < str.size() && isnumeric(str[pos]);  pos++) 
				continue;
			if(pos > beg)
				str2 = str2+str.substr(beg, pos-beg);
		}

		cerr << str[pos] << endl;
		//eat white space
		for(; pos < str.size() && isspace(str[pos]) ; pos++) continue;
		cerr << str[pos] << endl;
		if(str[pos] != ']') {
			cerr << "Error Parsing input, it looks like you are missing a closing"
				"bracket at " << endl << str << endl << setw(pos+1) << '^' << endl;
			return fail;
		}
		cerr << str[pos] << endl;
		str2 += ']';
		pos++;
	}

	if(str2 != "") {
		OperandT tmp = {str2, 0}; 
		return tmp;
	} else {
		cerr << "Error Parsing input at " << endl
				<< str << endl << setw(pos+1) << '^' << endl;
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
list<string> reorder(std::string str)
{
	int pos = 0;
	int prev = -1;

	list<string> outqueue;
	list<char> opstack;

	/* While there are tokens to evaluate */
	OperandT toke = gettoke(pos, str);
	while(prev < pos) {

		if(toke.lit != "") {
			// Literal, string or number
			outqueue.push_back(toke.lit);
		} else if(toke.op != 0) {
			// Operator 
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
						return list<string>();
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
		toke = gettoke(pos, str);
	}

	// Copy last operators to output queue
	while(!opstack.empty()) {
		if(opstack.front() == '(') {
			cerr << "Error, unmatched paranthesis remains" << endl;
			return list<string>();
		}
		outqueue.push_back(makestring(opstack.front()));
		opstack.pop_front();
	}

	return outqueue;
	
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


