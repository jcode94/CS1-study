// Justice Smith 2/2021
// Program recursively brute-force permutes
// through a list of words to "pretty print"
// them. A sequence of words is "pretty" if
// the final letter of each word is the same
// as the first letter of the subsequent word,
// excepting the final word in the sequence.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN_WORD 21

int isPretty(char** wordPermutations, int numberOfWords) {
    for (int i = 0; i < numberOfWords - 1; ++i) {
        if (wordPermutations[i][strlen(wordPermutations[i]) - 1] != wordPermutations[i + 1][0])
            return 0;
    }
    return 1; // all consecutive words are pretty
}

int rec(char** words, char** wordPermutations, int n, int numberOfWords, int* used) {
    if (n == numberOfWords) {
        if (isPretty(wordPermutations, numberOfWords)) {
            for (int i = 0; i < numberOfWords; ++i) {
                printf("%s ", wordPermutations[i]);
            }
            printf("\n");
            return 1; // sorted stop our search
        }
        return 0; // unsorted
    }

    // Look at every possible spot in the input
    for (int i = 0; i < numberOfWords; ++i) {
        if (used[i] == 0) {
            // Store in the permutation
            wordPermutations[n] = words[i];
            used[i] = 1; // use the value
            if (rec(words, wordPermutations, n + 1, numberOfWords, used))
                return 1;
            used[i] = 0; // unuse the value
        }
    }

    return 0;
}

void destroyWordList(char** words, int numberOfWords) {
    for (int i = 0; i < numberOfWords; ++i)
        free(words[i]);
    free(words);
}

int main() {
    int numberOfWords;
    scanf("%d", &numberOfWords);
    char** words, ** wordPermutations;
    int* used;

    words = malloc(numberOfWords * sizeof(char*));
    wordPermutations = malloc(numberOfWords * sizeof(char*));
    used = calloc(numberOfWords, sizeof(int));

    for (int i = 0; i < numberOfWords; ++i) {
        words[i] = malloc(LEN_WORD * sizeof(char));
        scanf("%s", words[i]);
    }

    rec(words, wordPermutations, 0, numberOfWords, used);

    destroyWordList(words, numberOfWords);
    free(wordPermutations);
    free(used);

    return 0;
}
