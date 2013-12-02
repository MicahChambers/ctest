#include <iostream>

const size_t state_size = 3;
const size_t particles = 5;

double data[state_size*particles] = {4, 2, .6,
                    4.2, 2.1, .59,
                    3.9, 2, .58,
                    4.3, 2.1, .62,
                    4.1, 2.2, .63};

double mu[state_size] = {4.1, 2.08, .604};

double weights[particles] = {1,1,1,1,1};

void update_cov()
{
    double total = 0;
    for(int i = 0 ; i < particles; i++) {
        total += weights[i];
    }
    
    double norm = 0;
    for(int i = 0 ; i < particles; i++) {
        weights[i] /= total;
        norm += weights[i]*weights[i];
    }
    norm = 1 - norm;

    double* covtmp = new double[state_size*state_size];
    double** cov = new double*[state_size];
    for(int i = 0 ; i < state_size ; i++) 
        cov[i] = &covtmp[i*state_size];

    //set all components to 0
    std::fill(covtmp, covtmp+state_size*state_size, 0);
    
    for(int pp = 0 ; pp < particles ; pp++) {
        for(int i = 0 ; i < state_size ; i++) {
            for(int j = 0 ; j <= i; j++) {
                if(weights[pp] > 0) {
                    cov[i][j] += weights[pp]*
                        (data[state_size*pp + i]-mu[i])*
                        (data[state_size*pp + j]-mu[j]);
                }
            }
        }
    }

    for(int i = 0 ; i < state_size ; i++) {
        for(int j = 0 ; j <= i; j++) {
            cov[i][j] /= norm;
        }
    }
    
    for(int i = 0 ; i < state_size ; i++) {
        for(int j = i+1 ; j < state_size; j++) {
            cov[i][j] = cov[j][i];
        }
    }
    
    for(int i = 0 ; i < state_size ; i++) {
        for(int j = 0 ; j < state_size; j++) {
            std::cout << cov[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    update_cov();
}
