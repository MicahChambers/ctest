#include <iostream>
#include <cstdlib>
#include <cmath>
#include <map>

using namespace std;
int main()
{
    map<double, double> tmap;

    for(int i = 0 ; i < 10 ; i++) {
        double tmp = sqrt(rand());
        cout << tmp << endl;
        tmap[tmp] = i;
    }
    
    map<double, double>::reverse_iterator it = tmap.rbegin();
    for(int i = 0 ; i < 10 && it != tmap.rend() ; i++, it++){
        cout << it->first << " " << it->second << endl;
    }

}
