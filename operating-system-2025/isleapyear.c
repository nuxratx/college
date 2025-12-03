/*
In the Gregorian calendar
system you can check if it is a leap year if it is divisible by 4 but not by 100 unless it is also divisible by 400.
For example, 1896, 1904, and 2000 were leap years but 1900 was not.
*/

#include <stdio.h>
#include <stdlib.h>

// Main function where the program execution begins
int main(int argc, char** argv) {
    int year;
    if (argc > 1) {
        year = strtol(argv[1], NULL, 10);
    } else {
        scanf("%d", &year);
    }
    
    // Check if the year is a leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        printf("%d was a leap year\n", year);
    } else {
        printf("%d was not a leap year\n", year);
    }
    return 0;
} 
