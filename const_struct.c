#include <stdio.h>

typedef struct
{
    char foo[348];
} foo;

typedef struct
{
    foo bar;
    int con;
    int two;
} mystr ;

int main()
{
    mystr my;
    printf("%X, %X, %X", &my, &my.bar, &my.con, &my.two);
}
