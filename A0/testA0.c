#include <stdio.h>
#include <string.h>

int main() {
    int numberNames;
    char nameArr[100000];
    scanf("%d", &numberNames);
    getchar();


    for(int i = 0; i < numberNames; i++) {
        fgets(nameArr, 100000, stdin);
        printf("%c", nameArr[0]); //First and last letter aren't around whitespace nooooo
        for(int j = 0; j < strlen(nameArr); j++) {
            if(nameArr[j] == ' ')
                printf("%c%c", nameArr[j - 1], nameArr[j + 1]);
        }
        printf("%c\n", nameArr[strlen(nameArr) - 2]); //There's a pesky newline at the end of the array

    }

}