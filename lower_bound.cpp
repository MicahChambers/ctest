#include <algorithm>
#include <iostream>

int arr[6] = {1,2,6,12,15,99};

using namespace std;

int main()
{
    cout << (lower_bound(&arr[0], &arr[6], 12) - arr) << endl;
    cout << (lower_bound(&arr[0], &arr[6], 10) - arr) << endl;
    cout << (lower_bound(&arr[0], &arr[6], 13) - arr) << endl;
    cout << (lower_bound(&arr[0], &arr[6], 87) - arr) << endl;
    cout << (lower_bound(&arr[0], &arr[6], 99) - arr) << endl;
    cout << (lower_bound(&arr[0], &arr[6], 1000) - arr) << endl;
}
