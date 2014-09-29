#include <sstream>
#include <string>
#include <iostream>

using namespace std;
int main()
{
    string str;
    int ival;
    size_t zval;
    double dval;

    cerr << "1" << endl;
    istringstream iss(" this is a test, ");
    iss >> str;
    while(!iss.eof()) {
        cerr << "\"" << str << "\"" << endl;;
        iss >> str;
    }
    if(iss.bad()) { 
        cerr << "Fail!" << endl;
        return -1;
    }

    cerr << "2" << endl;
    iss.clear();
    iss.str(" 1 2  3 4, 5 6 7 9 ");
    while(!iss.eof() && !iss.fail()) {
        cerr << "\"" << ival << "\"" << endl;
        iss >> ival;
    }
    if(iss.bad()) { 
        cerr << "Fail!" << endl;
        return -1;
    }
    
    cerr << "3" << endl;
    iss.clear();
    iss.str(" 1 2 , 3 4,5 6, 7 9");
    while(!iss.eof() && !iss.fail()) {
        cerr << "\"" << zval << "\"" << endl;
        iss >> zval;
    }
    if(iss.bad()) { 
        cerr << "Fail!" << endl;
        return -1;
    }
    
    cerr << "4" << endl;
    iss.clear();
    iss.str(" 1 2 , -3 4,-5 6, 7 9");
    while(!iss.eof() && !iss.fail()) {
        cerr << "\"" << zval << "\"" << endl;
        iss >> zval;
    }
    if(iss.bad()) { 
        cerr << "Fail!" << endl;
        return -1;
    }
    
    cerr << "5" << endl;
    iss.clear();
    iss.str(" 1 2 , -3 4,-5 6, 7 9");
    while(!iss.eof() && !iss.fail()) {
        cerr << "\"" << ival << "\"" << endl;
        iss >> ival;
    }
    if(iss.bad()) { 
        cerr << "Fail!" << endl;
        return -1;
    }
    
    cerr << "6" << endl;
    iss.clear();
    iss.str(" 1e-5 2 , -3 4,-5 6, 7 9");
    while(!iss.eof() && !iss.fail()) {
        cerr << "\"" << ival << "\"" << endl;
        iss >> ival;
    }
    if(iss.bad()) { 
        cerr << "Fail!" << endl;
        return -1;
    }
}
