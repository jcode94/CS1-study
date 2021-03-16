// Justice Smith 2/2021
// Practice with file, pointer and memory handling

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p, size, i;
    FILE *fp;
    // Open the input file.
    fp = fopen("input.txt", "r");
    //First int rad shows how many numbers
    fscanf(fp, "%d", &size);

    //Make memory and read numbers into array.
    p = (int *)malloc(size*sizeof(int));
    for (i = 0; i < size; i++)
        fscanf(fp, "%d", &p[i]);

    //Print out the array elements backwards.
    for (i = size - 1; i >= 0; i--)
        printf("%d\n", p[i]);

    //Close the file and free memory.
    free(p); // we FREE the memory pointed to by fp
    fclose(fp);
    return 0;
}