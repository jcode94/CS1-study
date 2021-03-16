// Justice Smith 2/2021
// Runtime calculation practice

#include <stdio.h>

int f(int n) {
    int ans;
    int i;
    if (n < 3)
        return n;
    ans = f(n / 2);
    for (i = 0; i < n; i++)
        ans += f(i);
    return ans;
}

int main() {
    int a, b, c;
    int a_ans, b_ans, c_ans;
    printf("Enter 3 arguments: ");
    scanf("%d %d %d", &a, &b, &c);

    a_ans = f(a);
    b_ans = f(b);
    c_ans = f(c);

    printf("f(%d) is %d\n", a, a_ans);
    printf("f(%d) is %d\n", b, b_ans);
    printf("f(%d) is %d\n", c, c_ans);

    return 0;
}