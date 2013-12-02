#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include <cstdlib>
#include <cstring>

#include <limits>

typedef int16_t DataType;

using namespace std;

void usage(char* exe)
{
    using namespace std;
    cout << exe << " <output>" << endl
         << "\tThis will generate a 4D Image with N(0, 1) voxels. " << endl 
         << endl << "\tOptions" << endl;
    cout << setw(20) << "-s <scale>" << " scale parameters (usually sigma, default 1)" << endl;
    cout << setw(20) << "-l <loc>" << " location parameters (usually mean, default 0)" << endl;
    cout << setw(20) << "-d <dist>" << " distribution (default Normal, options are: Normal, Uniform)" << endl;
    cout << setw(20) << "-c <src>" << " copy image information" << endl;
    cout << setw(20) << "-S <sz0> <sz1> <sz2> <sz3> " << " image size (default 5 5 5 180" << endl;
}

int foo(int argc, char* argv[])
{
    string  source;
    enum Distribution {Normal, Uniform};
    Distribution dist = Normal;
    double loc = 0;
    double scale = 1;
    std::vector<std::string> fnames;
    
    for(int i = 1 ; i < argc ; i++) {
        if(!strcmp(argv[i], "-s")) {
            if(i+1 >= argc) {
                cout << "Not enough inputs to -s" << endl;
                usage(argv[0]);
                return -3;
            }
            scale = atof(argv[++i]);
        } else if(!strcmp(argv[i], "-l")) {
            if(i+1 >= argc) {
                cout << "Not enough inputs to -l" << endl;
                usage(argv[0]);
                return -3;
            }
            loc = atof(argv[++i]);
        } else if(!strcmp(argv[i], "-d")) {
            if(i+1 >= argc) {
                cout << "Not enough inputs to -d" << endl;
                usage(argv[0]);
                return -3;
            }
            string tmp(argv[++i]);
            if(tmp == "Uniform") {
                dist = Uniform;
            } else {
                dist = Normal;
            }
        } else if(!strcmp(argv[i], "-c")) {
            if(i+1 >= argc) {
                cout << "Not enough inputs to -c" << endl;
                usage(argv[0]);
                return -3;
            }
            string tmp(argv[++i]);
            source = tmp;
        } else if(!strcmp(argv[i], "-S")) {
            if(i+4 >= argc) {
                cout << "Not enough inputs to -S" << endl;
                usage(argv[0]);
                return -3;
            }
        } else if(!strcmp(argv[i], "-h")) {
            usage(argv[0]);
            return 0;
        } else {
            fnames.push_back(argv[i]);
        }
    }

    if(fnames.size() < 1) {
        cout << "Not enough input files" << endl;
        usage(argv[0]);
        return -3;
    }

    /* 
     * Set Up the Random Numer Generator 
     */
    const gsl_rng_type * T;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    gsl_rng* rng = gsl_rng_alloc (T);

    cout << "Generator: " << gsl_rng_name(rng) << endl;
    cout << "Seed: " << gsl_rng_default_seed << endl;
    cout << "5 Samples: " << endl;

    if(dist == Uniform) {
        cout << "Flat: " << endl;
        cout << gsl_ran_flat(rng, loc-scale/2., loc+scale/2) << endl;
        cout << gsl_ran_flat(rng, loc-scale/2., loc+scale/2) << endl;
        cout << gsl_ran_flat(rng, loc-scale/2., loc+scale/2) << endl;
        cout << gsl_ran_flat(rng, loc-scale/2., loc+scale/2) << endl;
        cout << gsl_ran_flat(rng, loc-scale/2., loc+scale/2) << endl;
    } else {
        cout << "Gaussian: " << endl;
        cout << loc+gsl_ran_gaussian(rng, scale) << endl;
        cout << loc+gsl_ran_gaussian(rng, scale) << endl;
        cout << loc+gsl_ran_gaussian(rng, scale) << endl;
        cout << loc+gsl_ran_gaussian(rng, scale) << endl;
        cout << loc+gsl_ran_gaussian(rng, scale) << endl;
    }
}
