// Justice Smith 1/2021
// Attempted implementation of a strlen-type function

#include <stdio.h>
void NumOfChars(char *s, int *);
int main() {
    char str[] = "Test string";
    int res = 0;
    NumOfChars(str, &res);
    printf("Result is:%d\n", res);
    return 0;
}

void NumOfChars(char *s, int *r) {
    int i = 0;
    while(s[i] != '\0') {
        *r = *r + 1;
        i++;
    }
}