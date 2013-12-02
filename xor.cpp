#include <iostream>

using namespace std;


int main(int argc, char** argv)
{

	bool A = false;
	bool B = true;
	bool C = true;
	bool D = false;
	cout << (int)(0x1001^0x0011) << endl;
	cout << (bool)(A^B) << endl; //false xor true 1
	cout << (bool)(A^D) << endl; //false xor false 0
	cout << (bool)(B^C) << endl; //true xor true 0
	cout << (bool)(B^D) << endl; //true xor false 1
}
