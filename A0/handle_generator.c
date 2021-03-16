// Justice Smith 1/2021
// First attempt at a handle generator that scans through an arbitrarily long
// line of characters and prints certain characters based on the concurrent
// types of adjacent characters. Can be visualized as a crawling, 2 character
// 'window' that either prints or moves forward.

#include <stdio.h>
#include <ctype.h>

int main() {

    int n;
    char a, b;
    scanf("%d", &n); //leading space skips the newline at the end

    for(int i = 0; i < n; i++) {
        a = getchar(); //we have to leave this out of the loop init to use the logic of crawl
        while(1) {
            b = getchar();
            if(b == '\n') {
                if(a == ' ') { //accomodates trailing space
                    break;
                }
                else {
                    printf("%c\n", a);
                    break;
                }

            }
            if(isupper(a) != 0) {
                printf("%c", a);
                a = getchar();
                continue;
            }
            else {
                if(b == ' ') {
                    if(a == ' ')
                        a = b;
                    else {
                        printf("%c", a);
                        a = b;
                        continue;
                    }
                }
                else {
                    if(a == ' ') {
                        printf("%c", b);
                        a = getchar();
                    }
                    else
                        a = b; //the CRAWL
                }
            }
        }
    }

    return 0;
}