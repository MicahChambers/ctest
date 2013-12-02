#include <iostream>
#include <cmath> 

namespace test
{
#include <string>
};

using std::cout;
using std::endl;

class classfail{};
class englishfail : public classfail {};
class mathfail  : public classfail {};

int main(int argc, char* argv[])
{
    for(unsigned int i = 0 ; i < argc ; i++) {
        cout << argv[i] << endl;
    }
    try {
        if(argc == 1) {
            throw(englishfail());
        }

        if(argc == 2) {
            throw(mathfail());
        }
        
        cout << "End of try block reached!" << endl;
    } catch (class classfail) {
        cout << "A Class was failed!!" << endl;
    } catch (class englishfail) {
        cout << "English failed!!" << endl;
    } catch (class mathfail) {
        cout << "Math failed!!" << endl;
    }

	std::string a;
//	test::string a;
//	test::std::string a;
}


