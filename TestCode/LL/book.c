
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct book book;

struct book {
    book * pointer;
    char title[MAX + 1];
};

// Recursive function to print out a list of books
// Input is a pointer to a head of some list
void printList(book * current) {
    if (current != NULL) {
        printf("%s -> ", current->title);
        printList(current->pointer); // Recurse if we are not a NULL (the end)
    } else {
        printf("NULL\n\n"); // print a new line to make things fancy!
        return; // do nothing
    }
}

// Mtehod to create a book of a particular name DYNAMICALLY
book * createBook(char * word) {
    book * ret = calloc(1, sizeof(book));
    ret->pointer = NULL;
    strcpy(ret->title, word);
    return ret;
}

// insert begin
// insert end RECURSIVELY
// insert a node at the end of a linked list defined by the head
// the return of this function will be the resulting head of linked list
book * addToEnd(book * head, char * title) {
    if (head == NULL) { // list is empty
        book * newNode = createBook(title);
        return newNode; // returning NULL would leak the newNode
    }

    // Non empty list (head != NULL)
    book * aThing = addToEnd(head->pointer, title);
    head->pointer = aThing;
    return head;
}



// Recursive method to free the list
// we free the rest of the list
// THEN free the head to avoid a use after free
void freeTheList(book * head) {
    if (head == NULL) return;

    book * newHead = head->pointer; // write the address on a scrap of paper
    free(head); // blow up the original
    freeTheList(newHead); // use your scrap to terminate the remaining books
}


// The main method that adds books to a list
int main() {

    book * head = NULL;
    head = addToEnd(head, "Hello");
    head = addToEnd(head, "There");
    head = addToEnd(head, "World");
    printList(head);
    freeTheList(head);

    /*
    // Code snippet that prints a list of books using a loop (non-recursive)
    // iterate through that linked list
    for (book * current = HEAD; // start at the head of our linked list
            current != NULL; // loop until we are NULL (last book followed the pointer
            current = current->pointer) // moving to the next book in our linked by following
                                        // the pointer
    {
        printf("The title of some book is %s\n", current->title);
    }
    */


    return 0;
}
