// Justice Smith
// 2021-03-20
// Program to demonstrate deletion from linked list
// Copied, for practice, from :
// https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

// LL node
struct Node
{
    int data;
    Node* next;
};


void push(Node** head_ref, int new_data);
void deleteNode(Node** head_ref, int key);
void deleteNodeAt(Node **head_ref, int position);
void printList(Node* node);


// Given a reference (pointer to pointer) to the head of a list and an int, 
// inserts a new node on the front of the list.   
void push(Node** head_ref, int new_data)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Given a reference (pointer to pointer) to the head of a list and a key, 
// deletes the first occurrence of key in linked list    
void deleteNode(Node** head_ref, int key)
{
    // Store head node address
    Node* temp = *head_ref;
    Node* prev;
    
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next; // Changed head
        free(temp); // Free old head mem
        return;
    }
    
    // Search for the key to be deleted, keep track of the previous node as we 
    // need to change 'prev->next'
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
    
    // If key was not present in linked list
    if (temp == NULL)
        return;
        
    // Unlink the node from linked list
    prev->next = temp->next;
    
    free(temp); // Free memory
}

// Given a reference (pointer to pointer ) to the head of a list and a position,
// deletes the node at the tiven position
void deleteNodeAt(Node **head_ref, int position)
{
    // If linked list is empty
    if (*head_ref == NULL)
        return;
        
    // Store head node
    Node* temp = *head_ref;
    
    // If head needs to be removed
    if (position == 0)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    
    // Find the previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < position - 1; ++i)
    {
        temp = temp->next;
    }
    
    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL)
        return;
        
    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    Node* next = temp->next->next;
    
    // Unlink the node from the list
    free(temp->next);
    
    temp->next = next;
}

// Function prints contents of linked list starting 
// from the given node        
void printList(Node* node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
}

// Driver
int main()
{
    // Start with empty list
    Node* head = NULL;
    
    push(&head, 7);
    push(&head, 1);
    push(&head, 3);
    push(&head, 2);
    
    puts("Created Linked List: ");
    printList(head);
    
    deleteNode(&head, 1);
    puts("\nLinked List after Deletion of 1: ");
    printList(head);
    
    deleteNodeAt(&head, 2);
    puts("\nLinked list after deletion at index 2: ");
    printList(head);
    
    return 0;
}        
        
