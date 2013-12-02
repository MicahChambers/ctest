#include <map>
#include <cstdlib>
#include <iostream>

int main()
{
    std::map<int, size_t> var;
    
    for(int i = 0 ; i < 100 ; i++) {
        std::cout << var[i%10] << std::endl;
        var[i%10] = var[i%10]+rand();
    }

    std::map<int, size_t>::iterator it = var.begin();
    while(it != var.end()) {
        std::cout << it->first  << " " << it->second << std::endl;
        it++;
    }
}

