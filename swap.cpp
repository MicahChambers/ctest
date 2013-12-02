#include <iostream>
#include <cstring>

void swap(char* in, int len)
{
    char tmp;
    for(int i = 0 ; i < len/2 ; i++) {
        tmp = in[len-i-1];
        in[len-i-1] = in[i];
        in[i] = tmp;
    }
}

int main(int argc, char** argv)
{
    char buffer[1024];
    for(int i = 1 ; i < argc ; i++) {
        strncpy(buffer, argv[i], 1024);
        std::cout << buffer << " " ;
        swap(buffer, strlen(buffer));
        std::cout << buffer << std::endl ;
    }
}
