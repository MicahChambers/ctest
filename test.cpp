#include <cmath>
#include <iostream>

using namespace std;
int main()
{
    double test = 1./0;
    double test2 = 5;;
    cout << test << " " << test2 << endl 
                << test << "< " << test2 << "? " << (test < test2 ) << endl
                << test << "> " << test2 << "? " << (test > test2 ) << endl
                << test2 << "< " << test << "? " << (test2 < test ) << endl
                << test2 << "> " << test << "? " << (test2 > test ) << endl
                << test << "= " << test2 << "? " << (test == test2) << endl
                << test << "!=" << test2 << "? " << (test != test2) << endl;

}
