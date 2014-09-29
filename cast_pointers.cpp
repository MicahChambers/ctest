
#include <iostream>


double testi64(int64_t* a)
{
    return a[0]*a[1];
};

double testi32(int* a)
{
    return a[0]*a[1];
};

double testz64(size_t* a)
{
    return a[0]*a[1];
};

double testz32(uint32_t* a)
{
    return a[0]*a[1];
};


int main()
{
    size_t arr1[3] = {23,20923,3};
    //testi64((size_t*)arr1);
    //testi32(arr1);
    testz64(arr1);
    //testz32(arr1);

    int64_t arr2[3] = {23,20923,3};
    testi64(arr2);
    //testi32(arr2);
    //testz64(arr2);
    //testz32(arr2);

    uint32_t arr3[3] = {23,20923,3};   
    //testi64(arr3);
    //testi32(arr3);
    //testz64(arr3);
    testz32(arr3);
 
    int32_t arr4[3] = {23,20923,3};   
    //testi64(arr4);
    testi32(arr4);
    //testz64(arr4);
    //testz32(arr4);
}
