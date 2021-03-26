// Justice Smith
// Circular linked list implementation based on code from:
// https://www.geeksforgeeks.org/circular-linked-list-set-2-traversal/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int data;
    Node *next;
};

void printList(Node *head);
void push(Node **head_ref, int data);


// Function to traverse a given circular linked list and print nodes
void printList(Node *head) {
    Node *temp = head;
    if (head != NULL) {
        do {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        while (temp != head);
    }
}

void push(Node **head_ref, int data) {
    // Creating new node
    Node *newNode = malloc(sizeof(Node));
    Node *temp = *head_ref;
    newNode->data = data;
    newNode->next = *head_ref;

    // If linked list is not NULL then set the next of last node
    if (*head_ref != NULL) {
        while (temp->next != *head_ref)
            temp = temp->next;
        temp->next = newNode;
    }
    else
        newNode->next = newNode; // For the first node

    // Setting the new head mem
    *head_ref = newNode;
}

// Driver code
int main() {
    // Init list empty
    Node *head = NULL;

    // 3->0->1->9->5->4->6
    push(&head, 6);
    push(&head, 4);
    push(&head, 5);
    push(&head, 9);
    push(&head, 1);
    push(&head, 0);
    push(&head, 3);

    printf("Contents of circular linked list\n");
    printList(head);

    return 0;
}

