#include <iostream>
#include <map>

typedef struct 
{
    int L1;
    int L2;
} TupleT;

bool operator<(const TupleT& A, const TupleT& B)
{
    if(A.L1 < B.L1)
        return true;
    if(A.L1 == B.L1 && A.L2 < B.L2)
        return true;
    return false;
}

double& std::map<TupleT, double>::operator()(const int A, const int B)
{
    TupleT tmp = {A, B};
    return (*this)[tmp];
}

using namespace std;

int main()
{
    map<TupleT, double> mymap;
    TupleT A = {1, 23};
    TupleT B = {11, 23};
    TupleT C = {1, 11};
    TupleT D = {1, 44};
    mymap[A] = 13.1;
    mymap[B] = 23.1;

    map<TupleT, double>::iterator it = mymap.begin();
    for(it = mymap.begin(); it != mymap.end() ; it++) {
        cout << it->first.L1 << " " << it->first.L2 << ": " << it->second << endl;
    }
    
    mymap(C.L1, C.L2) = 87.1;
    mymap(D.L1, D.L2) = 187.1;
    
    map<TupleT, double>::iterator it = mymap.begin();
    for(it = mymap.begin(); it != mymap.end() ; it++) {
        cout << it->first.L1 << " " << it->first.L2 << ": " << it->second << endl;
    }
}
