// Justice Smith 2/2021
// Binary search function for Exam 1 practice
#include <stdlib.h>
#include <stdio.h>
/*
int main() {
    int i;
    int * arr;
    int * arr2;
    int   arr3[10]; // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    arr = (int *) calloc(3, sizeof(int));
    if (arr == NULL)
        return -1;
    for (i = 0; i < 3; i++)
        arr[i] = i + 1;

    arr2 = (int *) realloc(arr, 6 * sizeof(int));

    free(arr);
    arr = NULL;
    free(arr2);
    arr2 = NULL;

    return 0;
}
*/

int bsearch(int start, int end, int * array, int target)
{
    if (start == end)
    {
        return array[start]; // same as array[end]
    }

    int mid = (start + end + 1) / 2;
    if (array[mid] <= target)
    {
        return function(mid, end, array, target);
    }
    return function(start, mid - 1, array, target);
}

int main() {

    int target = 25;
    int arr[5] = {3, 24, 26, 28, 68};

    int found_num = function(0, 4, arr, target);

    printf("Greatest Value <= %d is %d", target, found_num);
    return 0;
}