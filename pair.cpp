#include <iostream>
#include <unordered_map>
#include <functional>

using namespace std;

void printPairs(size_t num, size_t in[][2])
{
	for(size_t ii=0; ii<num; ii++) {
		cerr << "(" << in[ii][0] << "," << in[ii][1] << ")" << endl;
	}
}

namespace std {
template <>
struct hash<std::pair<int, int>>
{
public:
	std::size_t operator()(std::pair<int, int> const& v) const
	{
		const static hash<int> h;
		size_t seed = 0;
		seed ^= h(v.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= h(v.second)+ 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};
}

int main()
{
//	size_t pairarr[5][2];
	size_t ARRAYSIZE = 5;
	auto pairarr = new size_t[ARRAYSIZE][2];
	for(size_t ii=0; ii<5; ii++) {
		pairarr[ii][0] = ii*1;
		pairarr[ii][1] = ii*2;
	}

	printPairs(5, pairarr);

	std::unordered_map<std::pair<int, int>, double> pmap;
	std::pair<int, int> v;
	v.first = 1;
	v.second = 2;
	pmap[v] = 1.2;
}
