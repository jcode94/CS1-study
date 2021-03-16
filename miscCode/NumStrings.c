// Justice Smith 1/2021
// Evaluation the number of valid strings
// in an array of strings

#include <stdio.h>
char *StringSet[] = {
    "string1 1 0 2 0",
    "string2 1 2 0 5 9",
    "string3 0 9 2",
    ""
};

int main() {
    int i = 0;
    while(*StringSet[i] != '\0') {
        printf("String %s\n", StringSet[i]);
        i++;
    }
}

