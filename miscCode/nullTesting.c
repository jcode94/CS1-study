// Justice Smith 2/2021
// Evolving in my use of Booleans for evaluation
// My original attempt used scanf for both printing
// and scanning, which did not accurately scan the
// input to the variable, causing the evaluation to
// evaluate based on its pre-scan data.

#include <stdio.h>

int main()
{
	int n;
	printf("Test value (0/1): ");
	scanf("%d", &n);

	if(!n) // When n is 0, this evaluates to 1(True)?
		printf("Test value zero.\n");
	else
		printf("Test value one.\n");

    return 0;
}