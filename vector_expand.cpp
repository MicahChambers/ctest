#include <vector>
#include <string>
#include <iostream>

using namespace std;

void printVVV(const vector<vector<vector<string>>>& in)
{
	for(auto it1 = in.begin(); it1 != in.end(); it1++) {
		for(auto it2 = it1->begin(); it2 != it1->end(); it2++) {
			cerr << "(";
			for(auto it3 = it2->begin(); it3 != it2->end(); it3++) {
				cerr << *it3 << ",";
			}
			cerr << "),";
		}
		cerr << endl;
	}
	cerr << endl;
}

void printVV(const vector<vector<string>>& in)
{
	for(auto it2 = in.begin(); it2 != in.end(); it2++) {
		cerr << "(";
		for(auto it3 = it2->begin(); it3 != it2->end(); it3++) {
			cerr << *it3 << ",";
		}
		cerr << "),";
	}
	cerr << endl;
}

vector<vector<string>> nest(const vector<vector<string>>& a, const vector<vector<string>>& b)
{
	if(a.empty()) {
		return vector<vector<string>>(b);
	}
	if(b.empty()) {
		return vector<vector<string>>(a);
	}

	vector<vector<string>> out(a.size()*b.size());
	for(unsigned int ii = 0 ; ii < a.size(); ii++) {
		for(unsigned int jj = 0 ; jj < b.size(); jj++) {
			out[ii*b.size() + jj].resize(a[ii].size()+b[jj].size());

			for(unsigned int kk = 0 ; kk < a[ii].size(); kk++)
				out[ii*b.size() + jj][kk] = a[ii][kk];
			
			for(unsigned int kk = 0 ; kk < b[jj].size(); kk++)
				out[ii*b.size() + jj][a[ii].size() + kk] = b[jj][kk];
		}
	}

	return out;
}

int main()
{
	vector<vector<string>> a(3,vector<string>(1));
	vector<vector<string>> b(4,vector<string>(1));
	vector<vector<string>> c(4,vector<string>(1));
	vector<vector<string>> unused;
	a[0][0] = "A0";
	a[1][0] = "A1";
	a[2][0] = "A2";
	b[0][0] = "B0";
	b[1][0] = "B1";
	b[2][0] = "B2";
	b[3][0] = "B3";
	c[0][0] = "C0";
	c[1][0] = "C1";
	c[2][0] = "C2";
	c[3][0] = "C3";
	printVV(unused);
	printVV(a);
	printVV(b);
	printVV(c);

	auto d = nest(unused,a);
	printVV(d);
	auto e = nest(d,b);
	printVV(e);
	auto f = nest(e,c);
	printVV(f);
}
