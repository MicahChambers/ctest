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

std::function<double(std::list<double>)>
makeChain(std::list<std::string> rpn, std::list<std::string>& args);

/**
 * @brief Takes a string of infix math operations and converts them to RPN
 *
 * @param str	Input string
 *
 * @return 		Output RPN expression as list
 */
std::list<std::string> reorder(std::string str);

