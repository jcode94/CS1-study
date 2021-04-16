#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void revStr(char *letter)
{
    if (*letter)
    {
        revStr(letter++);
        printf("%c", *letter);
    }
}

int main()
{
    char word[21]; // max len 20
    printf("Enter word: ");
    scanf("%s", word);
    // int len;
    // len = strlen(word);

    /* iterative solution
    while (len > 0)
    {
        printf("%c", word[len - 1]);
        len--;
    }
    printf("\n");
    */

    // recursive solution
    revStr(word);

    return 0;
}