#include <iostream>
#include <list>
#include <iterator>

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


	list<double> test({1,2,3,4,5});
	auto it = test.begin();
	cerr << *it << endl;
	advance(it, 2);
	cerr << *it << endl;
	advance(it, -2);
	cerr << *it << endl;
	cerr << "Going negative!"<<endl;
	advance(it, -1);
	cerr << "Reading Negative!"<<endl;
	cerr << *it << endl;
	cerr << "Done"<<endl;
    it = test.end();
	advance(it, -5);
	cerr <<*it<<endl;
}
