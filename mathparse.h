

const std::string MATHOPS = "-+*/^()";
const std::string MATHOPP = "1122300";
const std::string MATHOPA = "llllrxx";


/**
 * @brief Takes a string of infix math operations and converts them to RPN
 *
 * @param str	Input string
 *
 * @return 		Output RPN expression as list
 */
std::list<std::string> reorder(std::string str);

