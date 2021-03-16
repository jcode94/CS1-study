// Justice Smith, 2/5/2020
// cats_game program for normal 1 + 2 * ceil(log2(n)) binary search 
// Program guesses twice for every chop, only utilizing every other 
// cat response.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main()
{
	int upper_bound, lower_bound, mid;
	char *buffer;
	size_t bufsize = 32;
	
	buffer = malloc(sizeof(char) * bufsize);
	if (buffer == NULL) {
	    printf("Unable to allocate memory.\n");
		return;
	}
	
	// Getting range max
	scanf("%d", &upper_bound);
	mid = (upper_bound + lower_bound) / 2;
	printf("%d\n", mid);
	fflush(stdout);
	
	// Used one time to check if we get it right the first guess
	getline(&buffer, &bufsize, stdin);
	if(strcmp(buffer, "Yes!!!") == 0) {
	    // Lucker dog
		return 0;
	}
	
	// Continue with normal operation
	printf("%d\n", mid + 1);
	fflush(stdout);
	
	getline(&buffer, &bufsize, stdin);
	
	// Runs until our range contains only 1 number or 
	// we find the number with a response of "Yes!!!"
	while ((upper_bound - lower_bound) > 0 && (strcmp(buffer, "Yes!!!") != 0)) {
		if(strcmp(buffer, "No. Colder.") {
			upper_bound = mid;
			mid = (upper_bound + lower_bound) / 2;
			printf("%d\n", mid + 1);
			fflush(stdout);
		}
		
		else if(strcmp(buffer, "No. Warmer.") {
			lower_bound = mid;
			mid = (upper_bound + lower_bound) / 2;
			printf("%d\n", mid + 1);
			fflush(stdout);
		}
		// In the case of "No. No change.", which I don't believe will
		// ever happen with this method, because of the proximity of my 
		// two guesses. Either one of them will be correct or neither,
		// in which the range will again be split
		else {
			printf("%d", mid)
		}
		
		// Get evaluation from cat on my guess
		getline(&buffer, &bufsize, stdin);
	}
	
	// We found the number
	if((upper_bound - lower_bound) == 0) {
		printf("%d", upper_bound);
	}
	
	return 0;
}