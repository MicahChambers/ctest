#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	const int SIZE = 10000000;
	string method;
	if(argc == 1)
		method = "vector";
	else
		method = argv[1];

	random_device rng;
	uniform_real_distribution<double> dist(0, 1);

	if(method == "vector") {
		cout << "Vector" << endl;
		//create
		cout << "Creating" << endl;
		vector<double> method(SIZE);
		cout << "Done" << endl;

		//fill
		cout << "Filling" << endl;
		for(int ii = 0 ; ii < method.size(); ii++)
			method[ii] = dist(rng);
		cout << "Done" << endl;

		cout << "Sorting" << endl;
		sort(method.begin(), method.end());
		cout << "Done" << endl;

	} else if(method == "list") {
		cout << "List" << endl;
		//create
		cout << "Creating" << endl;
		list<double> method;
		cout << "Done" << endl;

		//fill
		cout << "Filling" << endl;
		for(int ii = 0 ; ii < SIZE; ii++)
			method.push_back(dist(rng));
		cout << "Done" << endl;

		cout << "Sorting" << endl;
		method.sort();
		cout << "Done" << endl;
	
	} else if(method == "set") {
		cout << "Set" << endl;
		//create
		cout << "Creating" << endl;
		set<double> method;
		cout << "Done" << endl;

		//fill
		cout << "Filling/Sorting" << endl;
		for(int ii = 0 ; ii < SIZE; ii++)
			method.insert(dist(rng));
		cout << "Done" << endl;
	}
}
