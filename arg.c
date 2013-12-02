#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct __args_t {
    char* value;
    char name;
};

int __args_parse(arg** output, int argc, char* argv[])
{
    /* output should by a pointer to a null pointer */
    if(*output)
        return -1;
    if(argc == 1)
        return 0;
    argc--;
    argv++;

    /* this may over-allocate, but that is ok */
    arg* tmpout = (arg*)calloc(argc, sizeof(arg));
   
    //state indicates the continuation of a previous argument
    //position is the argument number currently being processed
    uint32_t state = 0, pos = -1;
    for(uint32_t i = 0 ; i < argc ; i++) {
        //means we are starting a new argument
        if(argv[i][0] == '-') {
            pos++;
            tmpout[pos].name = argv[i][1];
            if(argv[i][2] != '\0') {
                tmpout[pos].value = &argv[i][2];
            } else {
                tmpout[pos].value = NULL;
                state = 1;
            }
        } else if(state) {
            state = 0;
            tmpout[pos].value = argv[i];
        } else {
            pos++;
            tmpout[pos].name = 0;
            tmpout[pos].value = argv[i];
        }
    }
    *output = tmpout;
    return pos+1;
}

int main(int argc, char* argv[])
{
    arg* arguments = NULL;
    int count = parse(&arguments, argc, argv);

    for(uint32_t i = 0 ; i < count ; i++) {
        printf("%c: %s\n", arguments[i].name, arguments[i].value);
    }
    free(arguments);
}
