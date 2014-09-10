#include <iostream>

using namespace std;

double function_name(double h)
{
    cout << __PRETTY_FUNCTION__ << endl;

    return 0;
}

int main(int argc, char** argv)
{
    function_name(10);
}
