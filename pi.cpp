#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    cerr << M_PI << ", err: "  << scientific << fabs(M_PI-M_PI) << endl;
    cerr << acos(-1) << ", err: "  << scientific << fabs(acos(-1)-M_PI) <<  endl;
    cerr << 4*atan(1) << ", err: "  << scientific << fabs(4*atan(1)-M_PI) << endl;
}
