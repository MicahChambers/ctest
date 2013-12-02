#include <iostream>

int main()
{
    vector<double> nums = {.1, .8, .11, .9, 2, 2.1, 1.9, 3.1};

    int bins = 3;

    double min = nums[0];
    double max = nums[0];

    for(int i = 1 ; i < nums.size() ; i++) {
        if(nums[i] < min)
            min = nums[i];
        if(nums[i] > max)
            max = nums[i];
    }

    max *=1.000000000000001;
    min *= .999999999999999;
    double binwidth = (max - min)/bins;
    double tol = binwidth/3.;

    for(int i = 0 ; i < nums.size() ; i++) {
        bin = bins*(nums[i]-min)/(max-min)
        std::cout << nums[i] << " -> " << bin << std::endl;
        std::cout << bin*binwidth << "-" << (bin+1)*binwidth << std::endl;
        if(fabs(nums[i] - (bin*binwidth+binwidth/2)) <= (binwidth - tol)/2 ||
                    (bin+1 == bins && nums[i] > bin*binwidth+binwidth/2) ||
                    (bin-1 < 0 && nums[i] < bin*binwidth+binwidth/2))
            std::cout << bin << " += " << 1;
        else if(nums[i] > bin*binwidth+binwidth/2) {
            int bin2 = bin+1;
            if(bin2 >= bins) 
        } else {
            int bin2 = bin-1;

        }
    }


}
