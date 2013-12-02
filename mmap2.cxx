#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    char test[] = "Super califragilistic expialidocious";
    int FILESIZE = sizeof(test);
    char filename[] = "/tmp/test.test";
    
    int fd = open(filename , O_RDWR | O_CREAT | O_EXCL, mode_t(0600));
    if(fd == -1) {
        std::cerr << "Error, failed to open" << filename << std::endl;
        return -2;
    }  

    /* Stretch the file size to the size of the (mmapped) array of ints
     */
    std::cout << "FILESIZE: " << FILESIZE << std::endl;
    int result = lseek(fd, FILESIZE-2, SEEK_SET);
    if (result == -1) {
        close(fd);
        std::cerr << "Error calling lseek() to 'stretch' the file"<< std::endl;;
        return -4;
    }

    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched 
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
    result = write(fd, "", 1);
    if (result != 1) {
        close(fd);
        std::cerr << "Error writing last byte of the file" << std::endl;;
        return -4;
    }

    void* data = mmap(NULL, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if(!data) {
        std::cerr << "Error couldn't start mmap" << std::endl;
        return -1;
    }
    
    memcpy(data, test, FILESIZE);
    munmap(data, FILESIZE);
    close(fd);
}
