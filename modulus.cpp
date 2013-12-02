#include <iostream>
using namespace std;


int main()
{
    for(int ll = 0; ll <=5 ; ll++) {
        cout << "ll = " << ll << endl;
        for(int ii = 0; ii < 11; ii++) {
            cout << "ii = " << ii << " " << (ii+ll)%11 << endl;
        }
    }
    for(int ll = 1; ll <=5 ; ll++) {
        cout << "ll = " << ll << endl;
        for(int ii = 0; ii < 11; ii++) {
            cout << "ii = " << (ii+ll)%11 << " " << ii << endl;
        }
    }

}
