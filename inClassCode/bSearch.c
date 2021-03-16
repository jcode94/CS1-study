// Justice Smith 2/2021
// Binary Search implementation for practice
// in preparation for the CS1 first exam

#include <stdio.h>

int function(int start, int end, int * array, int target)
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