#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NORMAL_SWAP

int print_array(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void insertion_sort(int *arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		int index = i;
		while (
#ifdef NORMAL_SWAP
			int tmp = arr[i];
			arr[i] = arr[index];
			arr[index] = tmp;
#else
			arr[i] ^= arr[index];
			arr[index] ^= arr[i];
			arr[i] ^= arr[index];
#endif
		}	
	}
}

int main()
{
	int n; scanf("%d", &n);
	int *arr;
	arr = calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 101;
	print_array(arr, n);
	selection_sort(arr, n);
	print_array(arr, n);
	free(arr);
	return 0;
}