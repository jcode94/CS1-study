// Justice Smith 2/2021
// Wrote this test to identify the
// behavior of scanf and its interaction
// the trailing newline after input
// Documentation supports that the newline
// is NOT left in the buffer with a string
// scan, as opposed to an integer scan.

#include <stdio.h>
#define BUFSIZE 1024

int main()
{
    char *buffer;
    char *buffer2;
    int length = 0;

    buffer = malloc(BUFSIZE * sizeof(char));
    buffer2 = malloc(BUFSIZE * sizeof(char));

    printf("Enter a string: ");
    scanf("%s", buffer);

    printf("Enter another: ");
    scanf("%s", buffer2);



    printf("String 1: %s\n", buffer);
    printf("String 2: %s\n", buffer2);

    return 0;
}