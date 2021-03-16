#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUF_LEN 100

int main()
{
    char** names;
    char* buffer;
    int n; // number of names


    buffer = malloc(BUF_LEN * sizeof(char));
    scanf("%d", &n);
    names = malloc(n * sizeof(char*));


    for (int i = 0; i < n; i++)
    {
        scanf("%s", buffer);
        names[i] = strdup(buffer);    
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s, ", names[i]);
    }

    return 0;
}