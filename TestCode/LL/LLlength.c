// Justice Smith
// 2021 - 03 - 21
// Copied, for practice, from:
// https://www.geeksforgeeks.org/
// find-length-of-a-linked-list-iterative-and-recursive/
          
// This program counts the number of nodes in a given singly linked list

// Iterative solution:
// 1. Initialize count as 0
// 2. Initialize a node pointer, current = head
// 3. Do following while current is not NULL
//    a. current = current -> next
//    b. count++;
// 4. Return count

// Iterative C program to find length or count of nodes in a linked list
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

typedef struct Node Node;

// Linked list node
struct Node
{
    int data;
    Node* next;
};

// Given a reference (pointer to pointer) to the head
// of a list and an int, push a new node on the front of the list

void push(Node** head_ref, int new_data)
{
    // Allocate node
    Node* new_node = malloc(sizeof(Node));
    
    // Store data
    new_node->data = new_data;
    
    // Link the old list off the new node;
    new_node->next = (*head_ref);
    
    // Move the head to point to the new node
    (*head_ref) = new_node;
}

// Counts number of nodes in linked list
int getCount(Node* head)
{
    int count = 0; // Initialize count
    Node* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

// Recursively sums the number of nodes in a linked list
int getCountRecursive(Node* head)
{
    // Base case
    if (head == NULL)
        return 0;
    
    // count is 1 + count of remaining list
    return 1 + getCountRecursive(head->next);
}

// Driver program to test count function
int main()
{
    // Start with the empty list
    Node* head = NULL;
    
    // user push() to construct below list
    push(&head, 1);
    push(&head, 3);
    push(&head, 1);
    push(&head, 2);
    push(&head, 1);
    
    // Check the count function
    printf("count of nodes is %d\n", getCount(head));
    return 0;
}
    




