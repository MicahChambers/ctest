#include <tuple>
#include <unordered_map>
#include <functional>

template <typename T>
class hasher
{
public:
	std::size_t operator()(const std::pair<T, T>& v) const
	{
		const static std::hash<int> h;
		size_t seed = 0;
		seed ^= h(v.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= h(v.second)+ 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};


int main()
{
	std::unordered_map<std::pair<int,int>, double, hasher<int>> map;
	std::pair<int,int> v(1,2);
	map[v] = 12.3;
	return 0;
}
