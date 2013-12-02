#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

void commaToVec(std::vector<int>& out, char* input)
{
    out.clear();
    int length = strlen(input);
    char* pos = input;
    char* prev;
    while(pos < input+length+1) {
        prev = pos;
        int tmp = strtol(pos, &pos, 0); 
        if(pos != prev) out.push_back(tmp);
        pos += 1;
    }
}

int main(int argc, char** argv)
{
    std::vector<int> store;
    for(int i = 1; i < argc ; i++) {
        std::cout << argv[i] << std::endl;
        commaToVec(store, argv[i]);
        for(int j = 0 ; j < store.size() ; j++) {
            std::cout << store[j] << " ";
        }
        std::cout << std::endl;
    }

}
