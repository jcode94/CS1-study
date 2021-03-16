#include <stdio.h>
int rec(int base, int exponent){
    if(exponent <= 0)
        return 1;
    else
        return base * rec(base, exponent - 1);
}
int main(){
    int base, exponent;
    scanf("%d%d", &base, &exponent);
    printf("%d", rec(base, exponent));
    return 0;
}