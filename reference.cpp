#include <iostream>

using namespace std;

void foo(int* data)
{
    cout << &data << "\t" << *data << endl;
}

int main()
{
    int x = 12;
    int y& = x;
    foo(&y);
    foo(&(&x));
}
