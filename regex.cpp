#include <regex>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    string pattern("19[0-9]{2}");
    std::regex re(pattern);

    std::vector<string> test({"199", "1997", "199832", "1999", "198"});
    for(auto& str : test) {
        if(regex_match(str, re)) {
            cerr << pattern << " matches " << str << endl;
        } else {
            cerr << pattern << " does not matche " << str << endl;
        }
    }

    return 0;
}
