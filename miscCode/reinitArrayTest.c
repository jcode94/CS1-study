// Justice Smith 2/2021
// Storing alphabetic characters as their
// ascii values and then printing the characters
// then I overwrite them and print the integer values

#include <stdio.h>

int main() {
    char str[15];
    for(int i = 0; i < 15; i++) {
        str[i] = 'a' + i;
        printf("%c ", str[i]);
    }
    printf("\n");
    str[15];
    for(int i = 0; i < 15; i++) {
        str[i] = i;
    }
    printf("\n");
    for(int i = 0; i < 15; i++) {
        printf("%d ", str[i]);
    }

    return 0;
}