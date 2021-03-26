// Justice Smith
// 2021 - 03 - 21
// Copied, for practice, from:
// https://www.geeksforgeeks.org/
// search-an-element-in-a-linked-list-iterative-and-recursive/
          
// This program searches a given key 'x' in a given singly linked list.
// The function should return true if x is present in the linked list and false
// otherwise.

// Iterative solution:
// 1. Initialize a node pointer, current = head.
// 2. Do following while current is not NUL
//    a. if current->key equals searchKey return True
//    b. current = current->next
// 3. Return false
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;

struct Node
{
    int data;
    Node* next;
};

bool search(Node* head, int x);
void push(Node** head_ref, int new_data);

void push(Node** head_ref, int new_data)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

bool search(Node* head, int x)
{
    Node* current = head;
    while (current != NULL)
    {
        if (current->data == x)
            return true;
        current = current->next;
    }
    return false;
}

bool searchRecursive(Node* head, int x)
{
    if (head == NULL)
        return false;
    if (head->data == x)
        return true;
    return searchRecursive(head->next, x);
}

// Driver
int main()
{
    Node* head = NULL;
    int x = 21;
    
    // Use push to construct below list
    push(&head, 10);
    push(&head, 30);
    push(&head, 11);
    push(&head, 21);
    push(&head, 14);
    
    search(head, 21) ? printf("Yes") : printf("No");
    return 0;
}
