// Justice Smith 1/2021
// Iterative implementation of sumDigits

#include <stdio.h>
int SumDigit(int);
int main()
{
    int res;
    res = SumDigit(1223);
    printf("The sum of digits %d\n", res);
    return 0;
}

int SumDigit(int num)
{
    int sum = 0, rem;
    while(num > 9)
    {
        rem = num%10;
        sum += rem;
        num /= 10;
    }
    sum += num;
    return sum;
}