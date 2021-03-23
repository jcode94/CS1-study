// Justice Smith
// 2021 - 03 - 21
// Copied, for practice, from:
// https://www.geeksforgeeks.org/
// write-a-function-to-get-nth-node-in-a-linked-list/
          
// Write a GetNth() function that takes a linked list and an integer index and
// returns the data value stored in the ndoe at that index position.

// Iterative solution:
// 1. Initialize count = 0
// 2. Loop through the Linked List
//    a. If count is equal to the passed index, return current node
//    b. Increment count
//    c. change current to point to the next node

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node Node;

struct Node
{
    int data;
    Node* next;
};

void push(Node** head_ref, int new_data);

void push(Node** head_ref, int new_data)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int GetNth(Node* head, int data)
{
    Node* current = head;
    int count = 0;
    
    while (current != NULL)
    {
        if (count == data)
            return current->data;
        count++;
        current = current->next;
    }
    
    assert(0);
}

int GetNthRecursive(Node* head, int N)
{
    int count = 0;
    
    if (head == NULL)
        return -1;
        
    if (N == 0)
        return head->data;
        
    return GetNthRecursive(head->next, N - 1);
}

// Driver
int main()
{
    // Start with the empty list
    Node* head = NULL;
    
    // use push() to contruct the below list
    push(&head, 1);
    push(&head, 4);
    push(&head, 1);
    push(&head, 12);
    push(&head, 1);
    
    // check the count function
    printf("Element at index 3 is %d", GetNth(head, 3));
    getchar();
}
