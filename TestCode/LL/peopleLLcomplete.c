

// Insert many nodes into the head of a linked list

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct LL LL;
typedef struct Node Node;

struct LL {
    Node * head;
    Node * tail;
};

struct Node {
	char * name;
	Node * next;
};

LL *   createLL();
Node * createNode(char * name);
void destroyNode(Node * garbage);
void addToHead(LL * list, char * name);
void addToTail(LL * list, char * name);
void removeHead(LL * list);
void removeTail(LL * list);
void printList(LL * list);
void freeList(LL * list);
// void addAtIndex(LL * list, char * name, int location);

// Add a lot of alices and bobs to a list
int main() {
    // Create the list
	LL * person_list = createLL();

    // Add the nodes to the list
	for (int i = 0; i < 1000000; i++) {
		addToHead(person_list, "Alice");
        addToTail(person_list, "Bob");
	}
	
    // Freeing the list (and all it's nodes)
	freeList(person_list);
	
    // Exit the program
	return 0;
}

LL * createLL() {
    LL * ret = calloc(1, sizeof(LL));
    ret->head = ret->tail = NULL;
    return ret;
}

// Good enough
Node * createNode(char * name) {
	Node * ret = calloc(1, sizeof(Node));
	ret->name = strdup(name);
	ret->next = NULL; // redundant because of calloc
	return ret;
}

// Good enough
void destroyNode(Node * garbage) {
	free(garbage->name);
	free(garbage);
}

// Add to the head
// Modify the list and ensure invariants are held
void addToHead(LL * list, char * name) {
	Node * newHead = createNode(name);
	
	newHead->next = list->head;

    // adjust the tail potentially
    // what if the list was empty
    // head = non-null ; tail = null
    // violating an invariant
    // head (list is not empty) ; tail (list is empty)
    if (list->tail == NULL) // list is empty we need to satisfy the invariant
        list->tail = newHead;

    // adjust the head of the list
    list->head = newHead;
}

// Add to the tail
// ensure that the list satisifies the invariants
void addToTail(LL * list, char * name) {
    // Create the node
    Node * newTail = createNode(name);

    // Find the old tail
    Node * oldTail = list->tail;

    // Point the old tail's next node to the new one
    oldTail->next = newTail;

    // Ensure that the list ends at the new tail
    newTail->next = NULL;

    // Fix the tail pointer in the list linked
    list->tail = newTail;

    // Check if the list list was empty
    if (list->head == NULL) {
        // List was empty
        // set the head to point to the first and last element of the list
        list->head = newTail;
    }
}

// return the head of the list
void removeHead(LL * list) {
    // Check if removing from empty list
    if (list->head == NULL) 
        return;

    // Find the node to replace the removed node
	Node * newHead = list->head->next;

    // Remove said node
	destroyNode(list->head);

    // Adjust the head of the linked list
    list->head = newHead;
    
    // What if new head was null???
    // then the list is empty (does the tail agree?)
    // tail is pointing to some non-null value
    if (newHead == NULL) {
        // The list is now empty
        list->tail = NULL;
    }
}

// remove the tail and return the head of the list
void removeTail(LL * list) {
    // Handle special if no second to last case
    //  1. empty list 
    if (list->tail == NULL) {
        // Don't do anything else we already have nothing left to offer :(
        return;
    }
    //  2. there is only one element
    if (list->tail == list->head) {
        destroyNode(list->tail);
        list->tail = list->head = NULL;
        return;
    }

    // Find the second to last element of the linked list
    Node * secondToLast = list->head;
    while (secondToLast->next->next != NULL) {
        // Move down the list
        secondToLast = secondToLast->next; 
    }
    
    Node * newTail = secondToLast;
    Node * oldTail = list->tail;

    // Adjust the tail pointer of our list
    list->tail = newTail;

    // Remove the old tail
    destroyNode(oldTail);

    // Set the tail to point to null
    newTail->next = NULL;
}

void printList(LL * list) {
    // Start at the beginning
    Node * current = list->head;

    // Loop to the end
    while (current != NULL) {
        // print the current node
        printf("%s -> ", current->name);
        
        // Move to the next node
        current = current->next;
    }

    // Print a new line for format
	printf("NULL\n");
}

void freeList(LL * list) {
    // Loop to the end
    while (list->head != NULL) {
        removeHead(list);
    }

    free(list);
}

