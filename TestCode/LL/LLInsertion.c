// Demonstrating all insertion methods on linked list
// Taken for practice from:
// https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
// Justice Smith
// 2021-03-20

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

// linked list node
struct Node
{
    int data;
    Node* next;
}

void push(Node** head_ref, int new_data);
void insertAfter(Node* prev_node, int new_data);
void append(Node** head_ref, int new_data);
void printList(Node* node);

// Given a reference (pointer to pointer) to the head of a list and an int, 
// inserts a new node at the front of the list.
void push(Node** head_ref, int new_data)
{
    // 1. Allocate node
    Node* new_node = malloc(sizeof(Node));
    
    // 2. Put in the data
    new_node->data = new_data;
    
    // 3. Set new_node next to head
    new_node->next = (*head_ref);
    
    // 4. Point head to the new node
    (*head_ref) = new_node;
}

// Given a node prev_node, insert a new node after the given prev_node

void insertAfter(Node* prev_node, int new_data)
{
    // 1. check if the given prev_node is NULL
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }
    // 2. allocate new node
    Node* new_node = malloc(sizeof(Node));
    
    // 3. put in the data
    new_node->data = new_data;
    
    // 4. Make next of new node as next of prev_node
    new_node->next = prev_node->next;
    
    // 5. Move the next of prev_node as new_node
    prev_node->next = new_node;
}

// Given a reference (pointer to pointer) to the head of a list and an int,
// appends a new node at the end
void append(Node** head_ref, int new_data)
{
    // 1. Allocate node
    Node* new_node = malloc(sizeof(Node));
    
    Node* last = *head_ref; // used in step 5
    
    // 2. Store data
    new_node->data = new_data;
    
    // 3. This new node is going to be the last node, so set next of to NULL
    new_node->next = NULL;
    
    // 4. If the linked list is empty, then make the new node head
    if (*head_ref = NULL)
    {
        *head_ref = new_node;
        return;
    }
    
    // 5. Traverse until the last node
    while (last->next != NULL)
        last = last->next;
        
    // 6. Change the next of last node
    last->next = new_node;
    return;
}

// Prints the contents of a linked list starting from the head
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
    // Start with the emtpy list
    Node* head = NULL;
    
    // Insert 6. List: 6->NULL
    append(&head, 6);
    
    // Insert 7 at the beginning. LL: 7->6->NULL
    push(&head, 7);
    
    // Insert 1 at the beginning. LL: 1->7->6->NULL
    push(&head, 1);
    
    // Insert 1 at the end. LL: 1->7->6->NULL
    append(&head, 4);
    
    // Insert 8, after 7. So list becomes 1->7->8->6->4->NULL
    insertAfter(head->next, 8);
    
    printf("\n Created Linked List is: ");
    printList(head);
    
    return 0;
}
    
