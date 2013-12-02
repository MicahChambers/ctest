#include <algorithm>
#include <iostream>
#include <cstdlib>

double arrt[10] = {-12.1, -5, 9, 13, 29, 99, 103, 110, 200, 231};
int main(int argc, char** argv)
{
    if(argc != 2) {
        std::cout << "argument needed" << std::endl;
        return -2;
    }
    std::cout << "Ranges: (-inf, ";
    for(int i = 0 ; i < 10 ; i++) {
        std::cout << arrt[i] << "] (" << arrt[i] << ", ";
    }
    std::cout << std::endl;

    double* pos = std::lower_bound(arrt, arrt+10, atof(argv[1]));
    std::cout << *pos << std::endl;
    std::cout << pos-arrt << std::endl;
    //std::cout << "Final: " << pos << " (" << arrt[pos-1] << ", "  << arrt[pos] << "]" << std::endl;
}
