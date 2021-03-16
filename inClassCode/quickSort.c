
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

void quick(int * arr, int len) {
	// Base case
	if (len <= 1) {
		return;
	}
	
	int mid = len / 2;
	merge(arr, mid);
	merge(arr + mid, len - mid);
	
	// merge the array
	int *temp = calloc(len, sizeof(int));
	int fptr = 0;
	int bptr = mid;
	for (int i = 0; i < len; ++i) {
		if (fptr < mid && bptr < len) {
			if (arr[fptr] < arr[bptr]) { // front has smaller element
				temp[i] = arr[fptr];
				fptr;
			}
		} else if (fptr < mid) { // front is non-empty, back is not
			temp[i] = arr[fptr];
			fptr++;
		} else { // back is non-empty, front is not
			temp[i] = arr[bptr];
			bptr++;		
		}
	}
	for (int i = 0; i < len; ++i)
		arr[i] = temp[i];
	
	free(temp);
}

void printArray(int * arr, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(int argc, char ** argv) {
	int n = MAX;
	if (argc != 1)
		n = atoi(argv[1]);
	int * arr = calloc(n, sizeof(int))
	for (int i = 0; i < n; ++i) {
	
	}
	printArray(arr, n);
	quick(arr, n);
	printArray(arr, n);
	free(arr);
	return 0;
}