#include <stdio.h>

int main()
{
    int shift = 3;
    int samples = 32;
    
    printf("%zu %zu %zu\n", (samples >> (shift)), (samples >> (shift-1)), (samples >> (shift-2)));
}
