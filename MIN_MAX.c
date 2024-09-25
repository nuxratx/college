#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

   /* my first program in C */
   //printf("Hello, World! \n");
   
   // below is for "<" redirection
   //Setting memory to only input 15 bytes
   //char buffer[15] = { '\0' };
   //built-in standard input and writes for up to 15 bytes
   //read(stdin,buffer,15);

    // argv[0] -> name of executable
    // argv[1] -> first arg
    // ...
    if(argc > 16 || argc < 2){
        return 1;
    }

    float max;
    float min;
 
    for(int i = 1; i < argc; i++){
        char* e;
        int errno = 0;
        double curr = strtod(argv[i], &e);

        if (*e != '\0' ||  // error if we didn't consume the entire string
            errno != 0 )   // error if overflow or underflow
        {
            return 1;
        }
        
        if (i == 1){
            max=curr;
            min=curr;
        } else {
            if (curr > max){
                max=curr;
            }

            if (curr < min){
                min=curr;
            }
        }
    }

    printf("Numbers entered: %d\nMinimum number is: %f\nMaximum number is: %f", argc-1, min, max);
    return 0;
}



/*If your input is the following 6 numbers:
46
78
22
13
9
38

The expected output of your program would be: 

Numbers entered: 6
Minimum number is: 9
Maximum number is: 78  

C is a lower level language, only does what it is assigned to do and nothing extra and that's why it uses
less RAM. Whereas python takes up more ram but the progam is actually slower than program in C 
standard input 
standard outpput 
POSIX -> To interact between differet OS 

*/