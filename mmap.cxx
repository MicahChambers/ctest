#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <cstring>

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    char* filename = argv[1];

    struct stat st;
    stat(filename, &st);
    if(!(st.st_mode & S_IFREG)) {
        return -100;
    }
    size_t size = st.st_size;

    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        cerr << "Error: Failed to open " << filename << endl;
        return 0;
    }

    char* data = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    for(size_t i = 0 ; i < size; i++) {
        if(!strcmp("helloworld", &data[i]))
            cout << (void*)&data[i] << endl;
    }

    munmap(data, size);
}
