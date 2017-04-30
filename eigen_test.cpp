#include <iostream>
#include <Eigen/Dense>

using namespace std;

struct Point
{
    Point() { };
    Point(float x, float y) : x(x), y(y) { };
    ~Point() { };
    Point(const Point& other) : x(other.x), y(other.y) {};

    union {
        struct {
            float x, y;
        };

        float _data[2];
        Eigen::Vector2f _eigen;
    };

    float& operator[](size_t ii)
    {
        assert(ii >= 0 && ii < 2);
        return _data[ii];
    };

    const float& operator[](size_t ii) const
    {
        assert(ii >= 0 && ii < 2);
        return _data[ii];
    };

    Eigen::Vector2f& asEigen() { return _eigen; };
    const Eigen::Vector2f& asEigen() const { return _eigen; };

    friend std::ostream& operator<<(std::ostream& os, const Point& pt);
};

std::ostream& operator<<(std::ostream& os, const Point& pt)
{
    os << pt.asEigen().transpose();
    return os;
}

int main()
{
    Eigen::Vector2f hello;
    Point world;
    Point gar(13258, .3905);

    hello[0] = 1;
    hello[1] = 1;

    cerr << sizeof(hello) << endl;
    cerr << sizeof(world) << endl;

    cerr << hello << endl;

    world.x = 100;
    world.y = 101.123;

    cerr << world.x << ", " << world.y << endl;
    cerr << world._data[0] << ", " << world._data[1] << endl;
    cerr << world._eigen.transpose() << endl;

    cerr << gar << endl;

    cerr << gar.asEigen().transpose() * gar.asEigen() << endl;

    auto gardup = gar;
    cerr << gardup << endl;

    auto gartheft = std::move(gar);
    cerr << gartheft << endl;
}
