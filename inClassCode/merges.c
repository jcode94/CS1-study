// Justice Smith 2/2021
// mergeSort practice with hardcoded array

#include <stdio.h>

void mergeS(int st, int en, int * x) {
    if (st == en)
        return;

    int mid = (st + en) / 2, i;
    int frontPtr = st;
    int backPtr = mid + 1;
    int mergedPtr = 0;
    int vals[en - st + 1];
    mergeS(st, mid, x); mergeS(mid + 1, en, x);

    while (mergedPtr <= en - st) {
        if (frontPtr == mid + 1 ||(backPtr != en + 1 && x[frontPtr] > x[backPtr]))
            vals[mergedPtr++] = x[backPtr++];
        else
            vals[mergedPtr++] = x[frontPtr++];
    }
    for (i = st; i <= en; i++)
        x[i] = vals[i - st];
}

int main() {
    int vals[] = {5, 6, 1, 7, 2};
    mergeS(0, 5, vals);

    for(int i = 0; i < 5; ++i) {
        printf("%d ", vals[i]);
    }
    printf("\n");

    return 0;
}
