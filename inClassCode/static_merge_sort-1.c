
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 100000
#define MAX 1000000

void sort(int * arr, int n) {
    if (n <= 1) return;
    int m = n / 2;
    sort(arr, m);
    sort(arr + m, n - m);
    int tmp[n], fptr = 0, bptr = m;
    for (int i = 0; i < n; i++)
        if (fptr == m || (bptr < n && arr[bptr] >= arr[fptr]))
            tmp[i] = arr[bptr++];
        else
            tmp[i] = arr[fptr++];
    for (int i = 0; i < n; i++)
        arr[i] = tmp[i];
}

// int main(void)
// int main()
// $ gcc source.c
// $ ./a.out <argument 1 for main> <argument 2 for main> ...
// $ ./a.out 1000


int main(int argc, char ** argv) {
    printf("Argument 0 is %s\n", argv[0]);
    int n = DEFAULT;
    if (argc != 1)
        n = atoi(argv[1]);

    int arr[n]; // old c does not like this
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % MAX;
    }
    sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

