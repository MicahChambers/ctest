#include <set>
#include <iostream>
#include <iterator>
#include <string>
#include <functional>

using namespace std;
typedef set<string, greater<string> > DecreasingStringSet;

int main()
{
    //lambda expression
    auto comp = [](const string& x, const string& y){ return x > y; };
    set< string , decltype(comp) > s(comp);
    s.insert("one");
    s.insert("two");
    s.insert("three");
    s.insert("four");
    for (auto x : s){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
