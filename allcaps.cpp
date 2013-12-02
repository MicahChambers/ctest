#include <iostream>

//so we can write 
//cout << "Hello world" << endl
//instead of 
//std::cout << "Hello world" << std::endl;
using std::cout;
using std::endl;

int main()
{
    char string[] = "this should be all caps";
    //recall that the above is equivalent to:
    //const char string[] = {'t', 'h', 'i', 's', ' ', 's', 'h', 'o', 'u',
    //            'l', 'd' ' ', 'b', 'e', ' ', 'a', 'l', 'l', ' ', 'c',
    //            'a', 'p', 's', '\0'};
    cout << string << endl;

    //write a 'for' loop that will iterate through the
    //variable string's characters and make them all
    //caps. Note that there is a way to do this without
    //knowing the length of the string (think null terminator)
    
    for(unsigned int i = 0 ; string[i] != '\0' ; i++) {
        //think about this in terms of the ascii table.
        if(string[i] <= 'z' && string[i] >= 'a') {
            string[i] += 'A' - 'a';
        }
    }
    
/* Equivalent for loop because '\0' = 0 :
    for(unsigned int i = 0 ; string[i] != 0 ; i++) {
        //think about this in terms of the ascii table.
        if(string[i] <= 'z' && string[i] >= 'a') {
            string[i] += 'A' - 'a';
        }
    }
*/

/* Also equivalent for loop, because every non-zero number evaluates to true:
    for(unsigned int i = 0 ; string[i]; i++) {
        //think about this in terms of the ascii table.
        if(string[i] <= 'z' && string[i] >= 'a') {
            string[i] += 'A' - 'a';
        }
    }

*/


    cout << string << endl;

    return 0;
}
