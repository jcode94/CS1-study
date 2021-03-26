
// circular double linked for fast insert remove from both ends

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node * prev, * next;
    int data;
};

void destroyNode(Node * node);
Node * createNode(int value);
Node * insertFront(Node * head, int value);
Node * insertBack(Node * head, int value);
Node * removeFront(Node * head);
Node * removeBack(Node * head);
void   printList(Node * head);
void   freeList(Node * head);

int main() {
    Node * head = NULL;
    for (int i = 0; i < 10000000; i++) {
        if (rand()&3) {
            // 3/4 for insertion
            if (rand()&1) // 1/2 for insert back
                head = insertBack(head, rand()%100);
            else
                head = insertFront(head, rand()%100);
        } else {
            if (rand()&1)
                head = removeBack(head);
            else
                head = removeFront(head);
        }
    }
    freeList(head);
    return 0;
}


void destroyNode(Node * node) {
    free(node);
}

Node * createNode(int value) {
    Node * ret = calloc(1, sizeof(Node));
    ret->next = ret->prev = ret;
    ret->data = value;
}

// tail->next = head;
// head->prev = tail
Node * insertFront(Node * head, int value) {
    Node * newHead = createNode(value);

    // Special case
    if (head == NULL)
        return newHead;

    // all other cases
    // Find the end points of the list
    Node * oldHead = head;
    Node * oldTail = head->prev;

    // adjust points :(
    newHead->next = oldHead;
    newHead->prev = oldTail;
    oldTail->next = newHead;
    oldHead->prev = newHead;

    return newHead;
}


// Insert to the back of the LL and return the head
Node * insertBack(Node * head, int value) {
    Node * newTail = createNode(value);

    // Special case
    if (head == NULL)
        return newTail;

    // all other cases
    // Find the end points of the list
    Node * oldHead = head;
    Node * oldTail = head->prev;

    // adjust points :(
    newTail->next = oldHead;
    newTail->prev = oldTail;
    oldTail->next = newTail;
    oldHead->prev = newTail;

    return oldHead;
}

// tail->next = head;
// head->prev = tail

// Remove the head and return the resulting head of the LL
Node * removeFront(Node * head) {
    // what if the list is empty
    if (head == NULL)
        return NULL; // the list will stay empty

    Node * oldHead = head;
    Node * oldTail = head->prev;
    // what if the list has only 1 element
    if (oldHead == oldTail) {
        destroyNode(head);
        return NULL; // all gone! bye bye list
    }

    // Find the new head
    Node * newHead = head->next;

    // Destroy the old head
    destroyNode(oldHead);

    // Adjust pointers
    oldTail->next = newHead;
    newHead->prev = oldTail;

    return newHead;
}

Node * removeBack(Node * head) {
    // what if the list is empty
    if (head == NULL)
        return NULL; // the list will stay empty

    Node * oldHead = head;
    Node * oldTail = head->prev;
    // what if the list has only 1 element
    if (oldHead == oldTail) {
        destroyNode(head);
        return NULL; // all gone! bye bye list
    }

    // Find the new head
    Node * newTail = oldTail->prev;

    // Destroy the old head
    destroyNode(oldTail);

    // Adjust pointers
    newTail->next = oldHead;
    oldHead->prev = newTail;

    return oldHead;
}

void printList(Node * head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    Node * cur = head;
    // loop up to but excluding the tail
    while (cur->next != head) {
        printf("%d <-> ", cur->data); // print the current location's value
        cur = cur->next; // move to the next location in the list
    }

    // cur should be at the tail (unprinted
    printf("%d <-> front\n", cur->data);
}


void freeList(Node * head) {
    while(head) head = removeFront(head); // :(
}

