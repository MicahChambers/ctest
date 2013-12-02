#include <iostream>
#include <cstdlib>

int help_find(double* arr, double p, size_t start, size_t size)
{
    std::cout << start << ", " << size << "\t";
        
    std::cout << "( ";
    for(int i = start ; i < start+size  ; i++)
        std::cout << arr[i] << ", ";
    std::cout << ")" << std::endl;
        
    if(p <= arr[start]) return start;

    //12 13 15 is asking for: [-inf, 12), [12, 13), [13, 15)
    if(p <= arr[start + size/2]) { 
        return help_find(arr, p, start+1, size/2-1);
    } else {
        return help_find(arr, p, start+size/2+1, size-size/2-1);
    }
}

//needs to be sorted, as in an  CDF
int find(double* arr, double p, size_t size)
{
    //this would technically be a glitch
    if(p > arr[size-1]) return size-1; 
    
    return help_find(arr, p, 0, size);
}


double arrt[10] = {-12.1, -5, 9, 13, 29, 99, 103, 110, 200, 231};
int main(int argc, char** argv)
{
    if(argc != 2) {
        std::cout << "argument needed" << std::endl;
        return -2;
    }
    int pos = find(arrt, atof(argv[1]), 10);
    if(pos == 0) {
        std::cout << "Final: " << pos << " (-inf, " << arrt[pos] << "]" << std::endl;
    } else {
        std::cout << "Final: " << pos << " (" << arrt[pos-1] << ", "  << arrt[pos] << "]" << std::endl;
    }
}
