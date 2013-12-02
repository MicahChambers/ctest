#include <iostream>
using namespace std;

int main()
{
    int A = -2000000000;
    unsigned int B = 4000000000;
    cout << A << endl << B << endl << (int)((unsigned int)A) << endl << (int)(A&B) << 
                endl << (unsigned int)(A&B) << endl;
    
    float C = -200000;
    cout << C << ", " << (float)(C) << ", " << (int)C <<  ", " << (bool)C <<
                ", " << (double)C  << endl;
    
	float D = -0.2;
    cout << D << ", " << (float)(D) << ", " << (int)D <<  ", " << (bool)D <<
                ", " << (double)D  << endl;
	
	float E = 0.2;
    cout << E << ", " << (float)(E) << ", " << (int)E <<  ", " << (bool)E <<
                ", " << (double)E  << endl;
	
	E = 0;
    cout << E << ", " << (float)(E) << ", " << (int)E <<  ", " << (bool)E <<
                ", " << (double)E  << endl;
}
