#include <ctime>
#include <cstdio>

int main()
{
    unsigned int COUNT = 1000000000;
    double a = 100.1;
    double b = .1;
    clock_t start = clock();
    for(unsigned int i = 0 ; i < COUNT ; i++) {
        b /= a;
    }
    clock_t stop = clock();
    double time = (stop - start)/(double)CLOCKS_PER_SEC;
    printf("%u\n", CLOCKS_PER_SEC);
    printf("%f\n", b);
    printf("time: %f\n", time);
}
