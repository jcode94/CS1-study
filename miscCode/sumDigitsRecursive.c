// Justice Smith 2/2021
// Recursive implementation of sumDigits

#include <stdio.h>
int recurSumDigit(int);
int main() {
    int res, n;
    printf("Enter a number: ");
    scanf("%d", &n);
    res = recurSumDigit(n);
    printf("The sum of digits is %d\n", res);
    return 0;
}

int recurSumDigit(num) {
    if (num < 10)
        return num;
    return (num % 10) + recurSumDigit(num / 10);
}