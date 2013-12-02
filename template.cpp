#include <vector>

template <class TYPE, unsigned int DIM>
class stupid
{
    public:
    
    class sub {
        public:
        std::vector<TYPE> mydata;
    };

};

template <class TYPE, unsigned int DIM2>
void test(typename stupid<TYPE, DIM2>::sub& input)
{

}

int main()
{
    typename stupid<double, 3>::sub myvar;
    test(myvar);
}
