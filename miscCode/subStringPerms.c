// Justice Smith Mar 2021
// This program calculates the number of permutations that
// contain a given substring. Grab a drink, you'll be here
// for a while on longer words

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN 1025

void swap(char* x, char* y);
int permute(char* word, char* substring, int stIdx, int enIdx);

int main()
{
    char* buffer;
    char* word;
    char* substring;
    int lenWord;
    int* used;

    buffer = malloc(BUF_LEN * sizeof(char));

    // Get source word to permute
    printf("Word to permute: ");
    scanf("%s", buffer);
    word = strdup(buffer);
    lenWord = strlen(word);

    // Get substring
    printf("Substring: ");
    scanf("%s", buffer);
    substring = strdup(buffer);

    int total = permute(word, substring, 0, lenWord - 1);
    printf("Total permutations that contain the given substring: %d\n", total);

    return 0;

}

void swap(char* x, char* y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


int permute(char* word, char* substring, int start, int end)
{
    int count = 0;
    int i;

    if (start == end)
    {
        if (strstr(word, substring) != NULL)
        {
            // printf("%s\n", word);
            count++;
        }
    }
    else{
        for (i = start; i <= end; ++i)
        {
            swap((word + 1), (word + i));
            count += permute(word, substring, start + 1, end);
            swap((word + 1), (word + i)); // backtrack
        }
    }
    return count;
}
