// Arup Guha
// 2/23/2016, added delete, reverse on 2/25/2016
// Written in COP 3502 Class

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void print(struct node* ptrList);
void printRec(struct node* ptrList);
struct node* insertToFront(struct node* ptrList, int newval);
void freeList(struct node* ptrList);
int sum(struct node* ptrList);
void printBackwardsRec(struct node* ptrList);
int isSorted(struct node* ptrList);
struct node* insertRec(struct node* ptrList, int newval);

// Two different delete functions.
struct node* deleteRec(struct node* ptrList, int val);
struct node* deleteAllRec(struct node* ptrList, int val);

// Reversing a linked list iteratively.
struct node* reverseFriends(struct node* rachel);
struct node* reverse(struct node* front);

/*** Main to test Tuesday's functions

int main() {

    // Test insertToFront, print and printRec.
    struct node* mylist = NULL;
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 3);
    print(mylist);
    mylist = insertToFront(mylist, 6);
    mylist = insertToFront(mylist, 5);
    mylist = insertToFront(mylist, 12);
    printRec(mylist);

    // Test sum and printBackwardsRec.
    printf("The sum of these items is %d\n", sum(mylist));
    printBackwardsRec(mylist);

    // Test isSorted.
    int sorted = isSorted(mylist);
    printf("This is sorted: %d\n", sorted);

    // Test isSorted again.
    struct node* inorder = NULL;
    inorder = insertToFront(inorder, 100);
    inorder = insertToFront(inorder, 80);
    sorted = isSorted(inorder);
    printf("This is sorted: %d\n", sorted);
    inorder = insertToFront(inorder, 80);
    inorder = insertToFront(inorder, 80);
    inorder = insertToFront(inorder, 80);
    inorder = insertToFront(inorder, 79);
    inorder = insertToFront(inorder, 70);
    inorder = insertToFront(inorder, 60);
    print(inorder);
    sorted = isSorted(inorder);
    printf("This is sorted: %d\n", sorted);

    // Test insertRec.
    struct node* lastlist = NULL;
    lastlist = insertRec(lastlist, 3);
    lastlist = insertRec(lastlist, 12);
    lastlist = insertRec(lastlist, 99);
    lastlist = insertRec(lastlist, 5);
    lastlist = insertRec(lastlist, 18);
    lastlist = insertRec(lastlist, 27);
    lastlist = insertRec(lastlist, 1);
    lastlist = insertRec(lastlist, 58);
    print(lastlist);
    if (isSorted(lastlist))
        printf("This list is sorted!\n");

    // Free all the lists.
    freeList(lastlist);
    freeList(inorder);
    freeList(mylist);
    return 0;
}

***/

// This main tests the deletes and reversals.

int main() {

    struct node* mylist = NULL;
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 3);
    mylist = insertToFront(mylist, 20);
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 16);
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 19);
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 28);
    mylist = insertToFront(mylist, 7);
    mylist = insertToFront(mylist, 13);
    print(mylist);
    mylist = deleteAllRec(mylist, 7);
    print(mylist);
    mylist = deleteRec(mylist, 200);
    print(mylist);
    mylist = reverse(mylist);
    print(mylist);
    mylist = reverseFriends(mylist);
    print(mylist);

    freeList(mylist);
    return 0;
}

// Non-recursive print - typical way to iterate through a linked list.
void print(struct node* ptrList) {

    // Go until there are no more elements.
    while (ptrList != NULL) {
        printf("%d ", ptrList->data);

        // Go to the next node.
        ptrList = ptrList->next;
    }
    printf("\n");
}

// Recursive print.
void printRec(struct node* ptrList) {
    if (ptrList != NULL) {

        // Print first item.
        printf("%d ", ptrList->data);

        // Let recursion print the rest of the list!
        printRec(ptrList->next);
    }
}

// Prints list backwards, recursively.
void printBackwardsRec(struct node* ptrList) {
    if (ptrList != NULL) {

        // First, we must print the rest of the list backwards.
        printBackwardsRec(ptrList->next);

        // Then we print our first item, at the end...
        printf("%d ", ptrList->data);
    }
}

// Inserts a node with newval to the front of the list pointed to by ptrList and
// returns a pointer to the new list.
struct node* insertToFront(struct node* ptrList, int newval) {

    // Create the node and fill it.
    struct node* newnode = malloc(sizeof(struct node));
    newnode->data = newval;

    // Attach to the rest of the list and return this pointer (new front).
    newnode->next = ptrList;
    return newnode;
}

// Frees each node in the list pointed to ptrList, recursively.
void freeList(struct node* ptrList) {
    if (ptrList != NULL) {
        freeList(ptrList->next);
        free(ptrList);
    }
}

// Recursively sums all the values in the list pointed to by ptrList.
int sum(struct node* ptrList) {

    // Nothing to add here.
    if (ptrList == NULL)
        return 0;

    // Add first term to the sum of the rest.
    return ptrList->data + sum(ptrList->next);
}

int isSorted(struct node* ptrList) {

    // Lists of size 0 and 1 are already sorted.
    if (ptrList == NULL || ptrList->next == NULL) return 1;

    // Store first item.
    int cur = ptrList->data;

    // Get to next item.
    ptrList = ptrList->next;

    // Go through the whole list.
    while (ptrList != NULL) {

        // Last two items are out of order.
        if (ptrList->data < cur) return 0;

        // Update current and ptrList.
        cur = ptrList->data;
        ptrList = ptrList->next;
    }

    return 1;
}


struct node* insertRec(struct node* ptrList, int newval) {

    // Inserting into an empty list, or first item in the list.
    if (ptrList == NULL || newval < ptrList->data) {
        struct node* newnode = malloc(sizeof(struct node));
        newnode->data = newval;
        newnode->next = ptrList;
        return newnode;
    }

    // insert newval into the rest of the list, and then reassign the
    // next point to this new list.
    ptrList->next = insertRec(ptrList->next, newval);
    return ptrList;
}

// Delete the first instance (if one exists) of val in the list
// pointed to by ptrList and return a pointer to the front of the
// resulting list.
struct node* deleteRec(struct node* ptrList, int val) {

    // Just in case our list is NULL...
    if (ptrList == NULL) return NULL;

    // Base case - first node is to be deleted.
    if (ptrList->data == val) {

        // Save a pointer to the new front of the list.
        struct node* newfront = ptrList->next;

        // Free this first node.
        free(ptrList);

        // This is the new front of the list.
        return newfront;
    }

    // Delete val from the rest of the list and then reattach this
    // first node to the front of the resulting list from the delete.
    ptrList->next = deleteRec(ptrList->next, val);

    // Return our front of the list.
    return ptrList;
}

// Delete all instances of val in the list pointed to by
// ptrList and return a pointer to the front of the
// resulting list.
struct node* deleteAllRec(struct node* ptrList, int val) {

    // Just in case our list is NULL...
    if (ptrList == NULL) return NULL;

    // This is no longer a base case - we must delete and then
    // recursively delete...
    if (ptrList->data == val) {

        // Store the rest of the list.
        struct node* newfront = ptrList->next;

        // Go ahead and free this node.
        free(ptrList);

        // Save a pointer to the new front of the list.
        return deleteAllRec(newfront, val);
    }

    // Delete val from the rest of the list and then reattach this
    // first node to the front of the resulting list from the delete.
    ptrList->next = deleteAllRec(ptrList->next, val);

    // Return our front of the list.
    return ptrList;
}

// Reverses the contents pointed to by ptrList and returns the new front
// of the resulting list.
struct node* reverse(struct node* ptrList) {

    // No work is needed to reverse lists of size 0 or 1.
    if (ptrList == NULL || ptrList->next == NULL) return ptrList;

    // Set up pointer to second item, put NULL to indicate end of our
    // final list.
    struct node* second = ptrList->next;
    ptrList->next = NULL;

    // Keep on going until we've gotten all the way through, reversing
    // individual pointers.
    while (second != NULL) {

        // This is a pointer to the third node in the list.
        struct node* third = second->next;

        // Here is the reversal of this link.
        second->next = ptrList;

        // Move each ptr over one spot.
        ptrList = second;
        second = third;
    }

    // This is the new front of the list.
    return ptrList;
}

// Same as reverse, written in class...variable names changed to
// be some of the Friends characters...
struct node* reverseFriends(struct node* rachel) {

    // No work is needed to reverse lists of size 0 or 1.
    if (rachel == NULL || rachel->next == NULL) return rachel;

    // Set up pointer to second item, put NULL to indicate end of our
    // final list.
    struct node* chandler = rachel->next;
    rachel->next = NULL;

    // Keep on going until we've gotten all the way through, reversing
    // individual pointers.
    while (chandler != NULL) {

        // This is a pointer to the third node in the list.
        struct node* joey = chandler->next;
        chandler->next = rachel;

        // Move rachel over one spot.
        rachel = chandler;
        chandler = joey;
    }

    // This is the new front of the list.
    return rachel;
}
