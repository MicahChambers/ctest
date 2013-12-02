#include <iostream>

using namespace std;
int main()
{
    double a = .9;
    double b = 0;
    cout << a << endl << (bool)a << endl << (int)a << endl << (bool)((int)a) << endl;
    cout << (a || b) << endl << (a || a) << endl << (b || b) << endl;
}
