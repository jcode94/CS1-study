// Justice Smith
// Cats game binary search utilizing reflection method

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Assignment defined intial lower boundary
#define INIT_MIN 1

int main() {
    int high, low, last_guess, cur_guess;
    size_t buf_size = 32;
    char *buffer = malloc(sizeof(char) * buf_size);

    low = INIT_MIN;
    cur_guess = last_guess = 0; // To ensure that initial response is always No.

    scanf("%d", &high);         // Setting initial upper boundary
    getchar();                  // To get the newline character


    // This loop runs until the range includes two numbers,
    // at which time it does a linear search to find the number.
    // This avoids the bounce issue with the reflection method where
    // it keeps guessing the boundary values in repetition
    do {
        // printf("Hi: %d Lo: %d: cur: %d last: %d\n", high, low, cur_guess, last_guess);
        printf("%d\n", cur_guess);
        last_guess = cur_guess;
        fflush(stdout);

        getline(&buffer, &buf_size, stdin);
        // This replaces the newline in the grabbed string with a NTC
        buffer[strcspn(buffer, "\n")] = 0;

        // Cat eval was Yes or Game over, so we prematurely trigger our
        // while loop failure condition
        if (buffer[0] == 'Y' || buffer[0] == 'G')
        {
            return 0;
        }
        else
        {
            if (strcmp(buffer, "No. Warmer.") == 0)
            {
                // Move toward our last guess
                if (last_guess > ((high + low) / 2))
                {
                    low = (high + low) / 2;
                }
                else // last_guess < midpoint, move away from last guess
                {
                    high = (high + low) / 2;
                }
                // Regardless of outcome, we must update our last_guess
                cur_guess = (high + low) - last_guess;
            }
            else if (strcmp(buffer, "No. Colder.") == 0)
            {
                if (last_guess > ((high + low) / 2))
                {
                    high = (high + low) / 2;
                }
                else // last_guess > midpoint
                {
                    low = (high + low) / 2;
                }
                cur_guess = (high + low) - last_guess;
            }
            else if (strcmp(buffer, "No. No change.") == 0)
            {
                cur_guess = (high + low) / 2; // Exact midpoint
            }
            else // "No."
            {
                cur_guess = (high + low) - last_guess;
            }
        }

    } while((high - low) > 1);
    // As explained above, fails when there are only 2 numbers left


    // Now that we've reduced the range to two numbers,
    // we can safely print the secret number.
    printf("%d\n", low);
    fflush(stdout);

    getline(&buffer, &buf_size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    // if low value wasn't it, then high value MUST be it.
    if (buffer[0] != 'Y')
    {
        printf("%d\n", high);
        fflush(stdout);
    }

    // Because we know that the response will be Yes, the eval is unnecessary
    getchar();

    // Free our allocated memory
    free(buffer);
    return 0;
}
