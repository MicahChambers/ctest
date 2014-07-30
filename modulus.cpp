#include <iostream>
#include <cmath>
using namespace std;


template <typename T>
T wrap(T len, T v)
{
	return v < 0 ? len-((-v)%len) : v%len; 
}

template <typename T>
T wrap(T inf, T sup, T v)
{
	T len = sup-inf+1;
	T vtmp = v-inf;
	T out = vtmp < 0 ? sup-((-vtmp-1)%len) : inf+(vtmp%len); 
	return out;
}


int main()
{
	cerr << "Wrapping: "<< endl;
	int length = 10;
	for(int ii = 0; ii < length; ii++) {
		for(int ll = -5; ll <=5 ; ll++) {
            cout << ii << "+" << ll << " = " << wrap(0, 9, ii+ll) << endl;
        }
    }
	
	cerr << "[ 5, 9 ]" << endl;
	for(int ii = 5; ii < 9; ii++) {
		for(int ll = -5; ll <=5 ; ll++) {
            cout << ii << "+" << ll << " = " << wrap(5, 9, ii+ll) << endl;
        }
    }

}
