#include <iostream>

using namespace std;

int main()
{
	int ii = 100;
	cerr << "ii-- < ii ? " << ((ii--) < ii) << endl;
	cerr << "--ii < ii ? " << ((--ii) < ii) << endl;
	cerr << "ii++ < ii ? " << ((ii++) < ii) << endl;
	cerr << "++ii < ii ? " << ((++ii) < ii) << endl;
	cerr << "ii-- > ii ? " << ((ii--) < ii) << endl;
	cerr << "--ii > ii ? " << ((--ii) < ii) << endl;
	cerr << "ii++ > ii ? " << ((ii++) < ii) << endl;
	cerr << "++ii > ii ? " << ((++ii) < ii) << endl;

	size_t jj;

	jj = 0;
	cerr << "jj-- < jj ? " << (jj-- < jj) << endl;
	jj = 0;
	cerr << "--jj < jj ? " << (--jj < jj) << endl;
	jj = 0;
	cerr << "jj++ < jj ? " << (jj++ < jj) << endl;
	jj = 0;
	cerr << "++jj < jj ? " << (++jj < jj) << endl;
	jj = 0;
	cerr << "jj-- > jj ? " << (jj-- < jj) << endl;
	jj = 0;
	cerr << "--jj > jj ? " << (--jj < jj) << endl;
	jj = 0;
	cerr << "jj++ > jj ? " << (jj++ < jj) << endl;
	jj = 0;
	cerr << "++jj > jj ? " << (++jj < jj) << endl;
}
