#include <string>
#include <list>

const std::string MATHOPS = "-+*/^(),|";
const std::string MATHOPP = "112230000";
const std::string MATHOPA = "llllrxxll";


/**
 * @brief Takes a string of infix math operations and converts them to RPN
 *
 * @param str	Input string
 *
 * @return 		Output RPN expression as list
 */
std::list<std::string> reorder(std::string str);

