// Justice Smith 3.5.2021
// COP3502C - CS1 Assignment 5 (Linked List and Stack)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max name length
#define LEN_NAME 20

typedef struct Node Node;

struct Node 
{
    char* name;
    int tokens;
    Node* next;
};

Node* push(Node* head, char* S, int M);
Node* pop(Node* head);
Node* createNode(char* name, int tokens);
void findMVP(Node* head);
void printList(Node* head);

int main() 
{
    int lineType, M;
    char* S; // buffer
    Node* head = NULL;

    // allocate name input buffer
    S = malloc((LEN_NAME + 1) * sizeof(char));
    
    // get first input type
    scanf("%d", &lineType);

    while (lineType != 0)
    {
        if (lineType == 1) 
        {
            // process player entering, "push"
            scanf("%d %s", &M, S);

            head = push(head, S, M);
        } 
        else if (lineType == 2) 
        {
            // process player leaving, "pop"
            head = pop(head);
        } 
        else // lineType == 3 
        { 
            findMVP(head);
        }

        // printList(head);
        scanf("%d", &lineType);
    }

    // Received 0
    // You don't have to go home, but you can't stay here
    return 0;
}

// Adds node to head of list
Node* push(Node* head, char* S, int M)
{
    Node* newNode;

    // Empty list
    if (head == NULL)
    {
        head = createNode(S, M);
        return head;
    }

    // Create new node 
    newNode = createNode(S, M);

    // Insert newNode to front of linked list(top of stack)
    newNode->next = head;

    return newNode;
}

// Removes node from head of list
Node* pop(Node* head)
{
    Node* prevHead;

    // List is empty
    if (head == NULL)
    {
        return head; // Nothing to pop
    }

    // Grabbing address of headNode
    prevHead = head;

    // Setting head ptr to second Node
    head = prevHead->next;

    // Freeing removed node
    free(prevHead);

    return head;
}

// Creates and returns new node with name and numTokens of arcader
Node* createNode(char* S, int M)
{
    Node* ret;
    ret = malloc(sizeof(Node));
    ret->name = strdup(S);
    ret->tokens = M;
    ret->next = NULL;

    return ret;
}

// One-way trip to the end of the line, holding largest found
void findMVP(Node* head)
{
    char* tempS;
    int tempM;

    // Empty list
    if (head == NULL)
    {
        // Crickets
        return;
    }

    // To hold the name of the visitor with most tokens so far
    tempS = strdup(head->name);
    // To hold the max value found so far
    tempM = head->tokens;

    while (head->next != NULL)
    {
        head = head->next;
        // Only change held max if greater than
        // This will keep the earliest max found 
        // if duplicates in list
        if (head->tokens > tempM)
        {
            tempS = head->name;
            tempM = head->tokens;
        }
    }

    printf("%s\n", tempS);

}

/*
// prints the complete list for reference
void printList(Node* head)
{
    if (head == NULL)
        printf("List empty\n");
    while (head != NULL)
    {
        printf("%s(%d)->", head->name, head->tokens);
        head = head->next;
    }
    printf("\n");
}
*/
