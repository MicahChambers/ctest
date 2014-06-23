#include <iostream>

using namespace std;

void arraytest(int arr[3])
{
    for(int ii = 0 ; ii < 3 ; ii++) {
        cerr << arr[ii] << endl;
    }
}

int main()
{
	int arr[3] = {1,2,3};
	arraytest(arr);
}
