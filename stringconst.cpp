#include <iostream>

static const char* strings[] = {".nii", ".nii.gz", ""};

class Test
{
    public:
        Test() : str(strings) {};
        const char* const* extents() { return str;} ;
    private:
        const char* const* str;
};

int main()
{
    Test test;
    char oops[] = "newstring";
    const char* const* tmp = test.extents();
    for(int i = 0 ; tmp[i][0] ; i++) {
        tmp[i][0] = '1';
        std::cout << tmp[i] << std::endl;
    }
}
