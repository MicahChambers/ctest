#include <string>
#include <list>
#include<functional>
#include<cmath>
#include<memory>
#include<vector>

const std::string MATHOPS = "-+*/^(),|";
const std::string MATHOPP = "112230000";
const std::string MATHOPA = "llllrxxll";

#include <iostream>
using std::cerr;
using std::endl;

//std::function<double(double,double)> a  = [](double v1, double v2){return v1-v2;};
//std::binary_function<double,double,double> tmp = &std::minus<double>;
const std::function<double(double,double)> MATHFUNC[] = {
	[](double v1, double v2){return v1-v2;},
	[](double v1, double v2){return v1+v2;},
	[](double v1, double v2){return v1*v2;},
	[](double v1, double v2){return v1/v2;},
	[](double v1, double v2){return pow(v1,v2);},
	[](double v1, double v2){return 0;},
	[](double v1, double v2){return 0;},
	[](double v1, double v2){return 0;},
	[](double v1, double v2){return 0;}
};


/**
 * @brief Creates a single function that recursively calls the operations
 * neeeded to perform the math problem given by rpn. 
 *
 * @param rpn		Reverse polish notation version of the math problem
 * @param args		Output argument strings. Create a matching vector of
 * 						doubles to pass to the returned function, in order
 * 						to execute the equation
 *
 * @return 			Function that takes a vector where each member is the 
 * 						value for the matching string from vector "args"
 */
std::function<double(const std::vector<double>&)>
makeChain(std::list<std::string> rpn, std::vector<std::string>& args);

/**
 * @brief Takes a string of infix math operations and converts them to RPN
 *
 * @param str	Input string
 *
 * @return 		Output RPN expression as list
 */
std::list<std::string> reorder(std::string str);


/**
 * @brief Performs a conversion for a single problem then compares
 * the compiled result versus the parsed one
 *
 * @return Success
 */
bool test();
