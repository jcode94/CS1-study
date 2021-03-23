// Justice Smith 3.5.21
// Dr. Meade - COP3502C - CS1 
// Assignment 5 - Arcade mgmt regular

// Theory:
//     On 1, we add either: 
//         new player info iff numTokens >= MVP->numTokens 
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
typedef struct Stack Stack;

struct Node 
{
    char* name;
    int tokens;
    Node* next;
};

struct Stack
{
    Node* head;
};

Node* createNode(char* S, int M);
void pop(Stack* Stack);
void push(Stack* Stack, char* S, int M);
char* peek(Stack* Stack);
void printList(Stack* Stack);
void destroyStack(Stack* Stack);

int main()
{
    int t, M;
    // S is buffer, program specs ask for S
    char* S;
    char* MVP;
    
    Stack* Stack = malloc(sizeof(Stack));
    Stack->head = NULL;

    // lenName specifications + 1 spot for NTC
    S = malloc((LEN_NAME + 1) * sizeof(char));

    scanf("%d", &t);
    
    while (t != 0)
    {
        if (t == 1) // enter(push) player
        {
            scanf("%d %s", &M, S);
            push(Stack, S, M);
        }
        else if (t == 2) // exit(pop) player
        {
            pop(Stack);
        }
        else // peek MVP
        {   
            // Don't segfault when attempting access top of stack
            if (peek(Stack) == NULL) {
                scanf("%d", &t);
                continue;
            }
            MVP = strdup(peek(Stack));
            printf("%s\n", MVP);
            free(MVP);
        }

        // printList(head); 
        scanf("%d", &t);
    }

    // Freeing the name buffer
    free(S);
    destroyStack(Stack);

    return 0;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: head points to the new head of the linked list, 
// after removal of head and previous head pointer memory freed.
void pop(Stack* Stack)
{
    Node* tempNode;

    //  Empty list
    if (Stack->head == NULL)
    {
        return;
    }

    // Grabbing address to head element to free later
    tempNode = Stack->head;

    // Closing the gap between head pointer and second element
    Stack->head = Stack->head->next;
  
    free(tempNode->name);
    free(tempNode);

    return;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: either a new MVP has been added to the list or 
//                 a duplicate of the current MVP has been added
//                 to the head.
void push(Stack* Stack, char* S, int M)
{
    Node* tempNode;
    
    // List empty
    if (Stack->head == NULL)
    {
        Stack->head = createNode(S, M);
        return;
    }
    // New MVP
    if (M >= Stack->head->tokens)
        tempNode = createNode(S, M);

    // Same MVP
    else
        // Create duplicate of current MVP
        tempNode = createNode(Stack->head->name, Stack->head->tokens); 

    tempNode->next = Stack->head;
    Stack->head = tempNode;  

    return;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: list is same, name of element at top of stack is returned
char* peek(Stack* Stack)
{
    if (Stack->head == NULL)
        return NULL;

    return Stack->head->name;
}

// Pre-condition: head points to the head of a linked list
// Post-condition: no change, list nodes outputted to console
void printList(Stack* Stack)
{
    if (Stack->head == NULL)
    {
        printf("List empty\n");
        return;
    }
    while (Stack->head != NULL)
    {
        printf("%s(%d)->", Stack->head->name, Stack->head->tokens);
        Stack->head = Stack->head->next;
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

void destroyStack(Stack* Stack) {
    while (peek(Stack) != NULL)
        pop(Stack);
    free(Stack);
}
