// Justice Smith 2/2021
// Dynamic memory allocation practice
// Solution to a challenge posted by Santy,
// the CS1 SARC peer tutor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNTRY_COUNT 4
#define BUF_SIZE 1024

typedef struct Country
{
    char *name;
} Country;

int main()
{
    Country **list;
    char *buffer;
    int string_length = 0, i;

    list = malloc(COUNTRY_COUNT * sizeof(Country *));
    buffer = malloc(BUF_SIZE * sizeof(char));


    printf("Enter 2 North American country names and 2 European country names: \n");
    for (i = 0; i < COUNTRY_COUNT; ++i)
    {
        fgets(buffer, BUF_SIZE, stdin);
        string_length = strlen(buffer);
        list[i] = malloc(sizeof(Country));
        list[i]->name = malloc(string_length * sizeof(char));
        strcpy(list[i]->name, buffer);
    }

    for (i = 0; i < COUNTRY_COUNT; ++i)
    {
        printf("Country %d: %s", i + 1, list[i]->name);
        free(list[i]->name);
        free(list[i]);
    }

    free(list);
    free(buffer);

    return 0;
}