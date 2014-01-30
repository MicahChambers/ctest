#include <iostream>
#include <string>

using std::string;
using std::cout;

struct OperandT
{
	//literal operand
	string lit; 
	
	//Operand consisting of the result of an operation
	char op;
	OperandT* left;
	OperandT* right;
};

char ops[] = "-+*/^";


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
	int beg;
	string str2;
	//skip starting white space
	for(; pos < str.size() && (str[pos] == ' ') ; pos++) continue;

	//check if its an operator
	for(int ii = 0 ; ii < sizeof(ops); ii++) {
		if(ops[ii] == str[pos]) {
			pos++;
			OperandT tmp = {"", str[pos-1], NULL, NULL};
			return tmp;
		}
	}
	
	/* 
	 * Check for non-operator string
	 */

	//if it is a number, get the whole number
	for(beg = pos; pos < str.size() && (str[pos] == '.' || (str[pos] >= '0' && 
					str[pos] <= '9')); pos++) 
		continue;
	
	//if it is a varname, get the whole name
	for(beg = pos; pos < str.size() && 
			((str[pos] >= 'a' && str[pos] <= 'z') || 
			 (str[pos] >= 'A' && str[pos] <= 'Z')); pos++) 
		continue;

	if(pos > beg)
		str2 = str.substr(beg, pos-beg);

	/* 
	 * check for bracketed expression after literal string
	 */

	//eat white space
	for(; pos < str.size() && str[pos] == ' ' ; pos++) continue;

	//find matching, remove all space inside the brackets
	if(str[pos] == '[') {
		for(; pos < str.size() && str[pos] != ']'; pos++) {
			if(str[pos] != ' ')
				str2 += str[pos];
		}
		str2 += str[pos];
		pos++;
		
		OperandT tmp = {str2, ' ', NULL, NULL};
		return tmp;
	}

	std::cerr << "Unable to parse token from " << str.substr(pos) << std::endl;
	return OperandT();
}

int main(int argc, char** argv)
{
	int pos = 0;
	gettoke(pos, argv[1]);
}
