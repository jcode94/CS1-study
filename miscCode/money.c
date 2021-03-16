
#include <stdlib.h>
#include <stdio.h>

int possible(int *arr, int size, int target)
{
	// Base case
	if (size == 0)
		return 0;

	// Try the size-th bank note
	for (int isIn = 0; isIn < size; isIn++)
		possible(arr, size - 1, target - (isIn) ? arr[size - 1] : 0);


}
int main()
{
	int arr[5] = {7, 8, 22, 4, 7};
	int target = 32;
	if (possible(arr, 5, target))
	{
		printf("We can buy the thing for $%d.\n", target);
	}
	else
	{
		printf("Time to go to the bank.\n");
	}
	return 0;
}