// Arup Guha
// 3/7/2017
// Written in COP 3502 class - Linked List implementation of a stack.

#include <stdio.h>
#include <stdlib.h>

// A linked list node.
typedef struct node {
    int data;
    struct node* next;
} node;

// A struct for the stack.
typedef struct stack {
    struct node* top;
    int size;
} stack;

void init(stack* myStack);
int push(stack* myStack, int item);
node* pop(stack* myStack);
int top(stack* myStack);
int size(stack* myStack);

int main() {

    // Test to fail...
    stack myStack;
    init(&myStack);
    int i = 0;

    // Push lots of stuff until the push fails.
    while (1) {
        int tmp = push(&myStack, i);
        if (tmp == 0) break;
        i++;
    }

    // See how much memory we had!
    printf("We failed after %d pushes.\n", i);

    // Pop everything off.
    while (size(&myStack) > 0) {
        node* ret = pop(&myStack);
        free(ret);
    }

    // Smaller test cases.

    // Get 10 things onto the stack.
    for (i=0; i<10; i++)
        push(&myStack, i);

    // Pop 5 of them.
    for (i=0; i<5; i++) {
        node* ret = pop(&myStack);
        printf("Just popped %d\n", ret->data);
        free(ret);
        printf("Top of the stack is now %d\n", top(&myStack));
    }

    // Get rid of everything else.
    while (size(&myStack) > 0) {
        printf("There are %d items in the stack.\n", size(&myStack));
        node* ret = pop(&myStack);
        printf("Just popped %d\n", ret->data);
        free(ret);
    }

    return 0;
}

// Initializes the stack pointed to by myStack to be empty.
void init(stack* myStack) {
    myStack->top = NULL;
    myStack->size = 0;
}

// Pushes item onto the stack pointed to by myStack. Returns 1 if the push
// succeeded, 0 if it failed.
int push(stack* myStack, int item) {

    node* tmp = malloc(sizeof(node));

    // malloc failed.
    if (tmp == NULL) {
        return 0;
    }

    // Create node link to old front.
    tmp->data = item;
    tmp->next = myStack->top;

    // Reset front and size.
    myStack->top = tmp;
    myStack->size++;
    return 1;
}

// Pops the top node off the stack pointed to by myStack and returns a pointer
// to the node.
node* pop(stack* myStack) {

    // Take care of empty case.
    if (myStack->size == 0) return NULL;

    // Store return node.
    node* retval = myStack->top;

    // Update new top.
    myStack->top = myStack->top->next;

    // To be safe, NULL this out.
    retval->next = NULL;

    // Update this.
    myStack->size--;

    return retval;
}

// Returns the integer at the top of the stack pointed to by myStack without
// popping it. Returns -1 if the stack is empty.
int top(stack* myStack) {
    if (myStack->size == 0) return -1;
    return myStack->top->data;
}

// Returns the size of the stack.
int size(stack* myStack) {
    return myStack->size;
}
