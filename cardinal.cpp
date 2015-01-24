#include <iostream>
#include <cmath>

double magnitude(double xx[3])
{
    double len = 0;
    for(int i = 0 ; i < 3 ; i++) {
        len += xx[i]*xx[i];
    }
    len = sqrt(len);
}

void normalize(double xx[3])
{
    double len = magnitude(xx);
    for(int i = 0 ; i < 3 ; i++) {
        xx[i] /= len; 
    }
}

bool find_uv(double uu[3], double vv[3], double normal[3])
{
    //pick a non-colear vector (default to 0,1,0 but switch if necessary
    double tmp[3] = {0, 1, 0};
    if(normal[0] == 0 && normal[2] == 0) {
        tmp[0] = 1; 
        tmp[1] = 0;
    }

    uu[0] = tmp[1]*normal[2] - tmp[2]*normal[1];
    uu[1] = tmp[2]*normal[0] - tmp[0]*normal[2];
    uu[2] = tmp[0]*normal[1] - tmp[1]*normal[0];

    vv[0] = uu[1]*normal[2] - uu[2]*normal[1];
    vv[1] = uu[2]*normal[0] - uu[0]*normal[2];
    vv[2] = uu[0]*normal[1] - uu[1]*normal[0];

}

double dot(double a[3], double b[3])
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

int main()
{
    double var1[3] = {0,0,0};
    double var2[3] = {1, -1, 1e-50};
        
    double normal[3];
    for(int i = 0 ; i < 3 ; i++)
        normal[i] = var1[i] - var2[i];

    normalize(normal);
    double uu[3];
    double vv[3];
    find_uv(uu, vv, normal);
    normalize(uu);
    normalize(vv);

    std::cout << "N: "; 
    for(int i = 0 ; i < 3; i++) {
        std::cout << normal[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "U: "; 
    for(int i = 0 ; i < 3; i++) {
        std::cout << uu[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "V: "; 
    for(int i = 0 ; i < 3; i++) {
        std::cout << vv[i] << " ";
    }
    std::cout << std::endl;

    std::cout << dot(uu, vv) << " " << dot(vv, normal) << " " << dot(uu, normal) 
                << std::endl;
}
