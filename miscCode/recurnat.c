// Justice Smith 2/2021
// Top-down implementation of a recursive function
// for printing consecutive natural numbers
#include <stdio.h>
int numPrint(int n) {
    if (n > 0) {
        printf(" %d", 50 - --n);
        numPrint(n);
    }
}
int main() {
    int n = 50;
    printf("\n\n Recursion : print first 50 natural numbers \n");
    printf("-------------------------------------------------\n");
    printf(" The natural numbers :");
    numPrint(n);
    printf("\n\n");
    return 0;
}