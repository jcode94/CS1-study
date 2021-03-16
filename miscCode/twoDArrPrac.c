// Justice Smith 1/2021
// Creating, filling, and printing 2D array

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(void) {
    int i, j;
    int x = 5;
    int y = 4;

    srand(time(NULL));

    // static allocation
    int array1[x][y];

    // dynamic allocation
    // How many arrays in my array of arrays?
    // Allocating an array of integer pointers
    int **array2 = (int **) calloc(x, sizeof(int *));

    // How many elements in each array in my array of arrays?
    // Allocating each array of integers
    for (i = 0; i < x; i++) {
        array2[i] = (int *) calloc(y, sizeof(int));
    }

    // Initialize 2D array
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            array2[i][j] = rand() % 100;
            printf("%d ", array2[i][j]);
        }
        printf("\n");

    }

    return 0;
}