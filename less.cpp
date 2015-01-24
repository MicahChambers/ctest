#include <iostream>
#include <map>


/**
 * @brief Less Function that prioritizes row (row major)
 */
struct RowLess
{
	bool operator()(const std::pair<int,int>& lhs, const std::pair<int,int>& rhs)
	{
		if(lhs.first < rhs.first)
			return true;
		if(lhs.first > rhs.first)
			return false;
		if(lhs.second < rhs.second)
			return true;
		if(lhs.second > rhs.second)
			return false;
		return false;
	};
};

/**
 * @brief A less function that prioritizes col. So iterating will
 * iterate down the col.
 */
struct ColLess
{
	bool operator()(const std::pair<int,int>& lhs, const std::pair<int,int>& rhs)
	{
		if(lhs.second<rhs.second)
			return true;
		if(lhs.second>rhs.second)
			return false;
		if(lhs.first<rhs.first)
			return true;
		if(lhs.first> rhs.first)
			return false;
		return false;
	};
};

using namespace std;

int main()
{
	std::map<std::pair<int,int>, double, RowLess> rowmap;
	std::map<std::pair<int,int>, double, ColLess> colmap;

	std::pair<int,int> tpair;
	for(int ii=0; ii<10; ii++) {
		for(int jj=0; jj<10; jj++) {
			colmap[{ii, jj}] = rand();
			rowmap[{ii, jj}] = rand();
		}
	}

	cerr << "Row Map:" << endl;
	for(auto it=rowmap.begin(); it != rowmap.end(); ++it) {
		cerr << it->first.first << "," << it->first.second<<endl;
	}

	cerr << "Col Map:" << endl;
	for(auto it=colmap.begin(); it != colmap.end(); ++it) {
		cerr << it->first.first << "," << it->first.second<<endl;
	}
}
