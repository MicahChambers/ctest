#include <iostream>

union StartT
    struct 
    {
        float a;
        float b;
    } indiv;
    float all[2];
}

union EndT
{
    struct 
    {
        int a;
        int b;
    } indiv;
    int all[2];
}

  
using namespace std;

int main()
{
    StartT values = {5.2, 1.5};
    EndT outv;
    outv = values;
    cerr << values.a << endl << values.b  << endl;
    cerr << outv.a << endl << outv.b  << endl;

}
