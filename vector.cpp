#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> test(100, 0);
    for(int i = 0 ; i < test.size() ; i++)
        cout << test[i] << " ";

}
