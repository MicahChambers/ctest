#include <iostream>
#include <string>
#include <map>
#include <cassert>

using namespace std;

//order by "\\+\\" members
bool compare(const std::string& A, const std::string& B)
{
    std::string divider = "\\+\\";
#ifdef DEBUG
    cout << A << " and " << B << endl;
#endif // DEBUG
    size_t Astart = 0;
    size_t Bstart = 0;
    size_t Alen = 0;
    size_t Blen = 0;
    for(int ii = 0 ; ii < 4 ; ii++) {
        Alen = A.find(divider, Astart);
        Blen = B.find(divider, Bstart);
        Alen -= Astart;
        Blen -= Bstart;

#ifdef DEBUG
        cout << ii << " - " << Astart << ":" << Alen << " - " << A.substr(Astart, Alen) << " - " 
                    << " - " << Bstart << ":" << Blen <<  " - " << B.substr(Bstart, Blen) << endl;
#endif // DEBUG

        //if either is a *, then automatically match, later on
        // this could be turned into regular expressions
        if(A.substr(Astart, Alen) == "*" || B.substr(Bstart, Blen) == "*") {
            Astart += Alen + divider.length();
            Bstart += Blen + divider.length();
            continue;
        }

        //if one is greater than the other then a solution is found,
        //    if they match then continue to analyze the rest
        if(A.substr(Astart, Alen) < B.substr(Bstart, Blen) ) {
            return true;
        } else if(A.substr(Astart, Alen) > B.substr(Bstart, Blen)) {
            return false;
        }
        
        Astart += Alen + divider.length();
        Bstart += Blen + divider.length();
    }

    //the two are functionally equal, so return false since this is <
    return false;
}

int main()
{
    std::multimap<std::string, int> test;
    std::multimap<std::string, int
    test["test\\+\\one\\+\\two\\+\\three"] = 5; 
    test["test\\+\\one\\+\\two\\+\\three"] = 7; 
    test["test\\+\\alpha\\+\\two\\+\\three"] = 12;
    test["test\\+\\one\\+\\alpha\\+\\three"] = 8;
    test["test\\+\\one\\+\\two\\+\\alpha"] = 13;

    cout << test["test\\+\\one\\+\\two\\+\\three"] << std::endl;
    cout << test["test\\+\\one\\+\\two\\+\\three"] << std::endl;
}
