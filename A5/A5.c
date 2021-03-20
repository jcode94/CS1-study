// Justice Smith 3.5.21
// Dr. Meade - COP3502C - CS1 
// Assignment 5 - Arcade mgmt regular

// Theory:
//     On 1, we add either: 
//         new player info iff numTokens > MVP->numTokens 
//         OR 
//         a duplicate(placeholder) MVP node
//
//     On 2, we remove one node from our MVP stack
//
//     On 3, we peek the top of the stack,
//     which holds the current MVP. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_NAME 20

typedef struct Node Node;

struct Node 
{
    char* name;
    int tokens;
    Node* next;
};

Node* createNode(char* S, int M);
Node* pop(Node* head);
Node* push(Node* head, char* S, int M);
char* peek(Node* head);
void printList(Node* node);

int main()
{
    int t, M;
    // S is buffer
    char* S, MVP;
    Node* head = NULL;

    // lenName specifications + 1 spot for NTC
    S = malloc((LEN_NAME + 1) * sizeof(char));

    scanf("%d", &t);
    
    while (t != 0)
    {
        if (t == 1) // enter(push) player
        {
            scanf("%d %s", &M, S);
            head = push(head, S, M);
        }
        else if (t == 2) // exit(pop) player
        {
            head = pop(head);
        }
        else // peek MVP
        {   
            S = strdup(peek(head));
            printf("%s\n", S);
        }

        // printList(head);
        scanf("%d", &t);
    }

    head = destroyStack(head);
    free(S);

    return 0;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: head points to the new head of the linked list, after removal of head
//                 and previous head pointer memory freed.
Node* pop(Node* head)
{
    Node* tempNode;

    //  Empty list
    if (head == NULL)
    {
        return NULL;
    }

    // Grabbing address to head element to free later
    tempNode = head;

    // Closing the gap between head pointer and second element
    head = head->next;

    free(tempNode);

    return head;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: either a new MVP has been added to the list or 
//                 a duplicate of the current MVP has been added
//                 to the head.
Node* push(Node* head, char* S, int M)
{
    Node* tempNode;
    
    // List empty
    if (head == NULL)
    {
        head = createNode(S, M);
        return head;
    }
    // New MVP
    if (M >= head->tokens)
        tempNode = createNode(S, M);

    // Same MVP
    else
        // Create duplicate of current MVP
        tempNode = createNode(head->name, head->tokens); 

    tempNode->next = head;
    head = tempNode;  

    return head;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: list is same, name of element at top of stack is returned
char* peek(Node* head)
{
    if (head == NULL)
        return NULL;

    return head->name;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: no change, list nodes outputted to console
void printList(Node* head)
{
    if (head == NULL)
    {
        printf("List empty\n");
        return;
    }
    while (head != NULL)
    {
        printf("%s(%d)->", head->name, head->tokens);
        head = head->next;
    }
    printf("\n");
}

// Pre-condition: S points to a name, M contains an integer
// Post-condition: returns a node pointer to a newly-minted player Node
Node* createNode(char* S, int M)
{
    Node* ret = malloc(sizeof(Node));
    ret->name = strdup(S);
    ret->tokens = M;
    ret->next = NULL;

    return ret;
}

Node *destroyStack(Node *head) {
    while (peek(head) != NULL)
        head = pop(head);
    return NULL;
}
