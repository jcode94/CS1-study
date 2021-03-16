// Justice Smith 1/2021
// Basic word counter implementation

#include <stdio.h>

void NumOfWords(char *s, int *);

int main() {
    char str[] = "Hello how are you";
    int res = 1;
    NumOfWords(str, &res);
    printf("Result is: %d\n", res);
    return 0;
}

void NumOfWords(char *s, int *r) {
    int i = 0;
    while (s[i] != '\0') {
        if(s[i] == ' ') {
            *r += 1;
        }
        i++;
    }
}