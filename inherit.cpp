#include <iostream>

using namespace std;

class base
{
	public:
		virtual void hello() { cerr << "base"; };;
};

class der1 : base
{
	private:
		virtual void hello() { cerr << "der1"; };;
};

class der2 : public base
{
	private:
		virtual void hello() { cerr << "der2"; };;
};

class der3 : protected base
{
	private:
		virtual void hello() { cerr << "der3"; };;
};

class der4 : private base
{
	private:
		virtual void hello() { cerr << "der4"; };;
};

int main()
{
	base b;
	b.hello();
	der1 d1;
//	d1.hello();
	der2 d2;
//	d2.hello();
	der3 d3;
//	d3.hello();
	der4 d4;
//	d4.hello();
}
