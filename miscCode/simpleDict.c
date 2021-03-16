// Justice Smith 1/2021
// Evaluates which word comes first, alphabetically
// through the use of strcmp function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 10


int main() {

    char str1[MAX_STR_LEN + 1]; // + 1 for null terminator
    char str2[MAX_STR_LEN + 1];

    // Reading in both strings
    scanf("%s%s", str1, str2);

    // trie pronounced "try" for dumb reasons (we already have trees)
    // comes from the word retrieval
    // Compare the strings to each other
    if (strcmp(str1, str2) < 0) {
        // str1 - str2 < 0
        // str1 < str2
        printf("%s is smaller\n", str1);
    } else if (strcmp(str1, str2) > 0) {
        // str1 - str2 > 0
        // str2 > str2
        printf("%s is smaller\n", str2);
    } else {
        printf("The strings were the same\n");
    }

    return 0;
}