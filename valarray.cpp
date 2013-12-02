#include <valarray>

#include <iostream>

void printarr(double* data, size_t size)
{
    for(int i = 0 ; i < size; i++) {
        std::cout << data[i] << "\t"; 
    }
}

int main()
{
    std::valarray<double> arr;
    arr.resize(100);
    for(int i = 0 ; i < 100; i++) {
        arr[i] = i%7;
    }

    printarr(arr.data(), arr.size());

}
