#include <iostream>
#include <cmath>

int main()
{
    const int ylen = 4;
    const int xlen = 10;
    double yd[ylen] = {12, 13, 1,3};
    double xd[xlen] = {.9, .3, .8, .1, 1.1, 2.1, 3, 0, 9,5};
    int yp, yn;
    double yinterp;
    for(int xx = 0 ; xx < xlen ; xx++) {
        yp = floor(xx*ylen/(double)xlen);
        yn = ceil(xx*ylen/(double)xlen);
        std::cout << yd[yp] << " " << (yn - xx*ylen/(double)xlen) << std::endl;
        std::cout << yd[yn] << " " << (xx*ylen/(double)xlen - yp) << std::endl;
        yinterp = yd[yp]*(yn - xx*ylen/(double)xlen) + 
                    yd[yn]*(xx*ylen/(double)xlen - yp);
        std::cout << xd[xx] << " -> " << yinterp << std::endl;
    }

}
