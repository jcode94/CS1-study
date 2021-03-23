/***********************************************
* Filename: SLL.c
* Author: Justice Smith
* Date: 2021 - 03 - 21
* Description: Program implementating various 
*     operations on a singly-linked list
* *********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct LL LL;
typedef struct Node Node;

struct LL
{
    Node* head;
};

struct Node
{
    int data;
    Node* next;
};


// Prototypes
LL* createList();
Node* createNode(int data);
void addToHead(LL* list, int data);
void addToTail(LL* list, int data);
void removeFromHead(LL* list);
void removeFromTail(LL* list);
void printList(LL* list);
void freeList(LL* list);
int peekHead(LL* list);
int peekTail(LL* list);
void printReverse(LL* list);

int main()
{
    LL* list = createList();
    
    return 0;    
}

LL* createList()
{ 
    // Allocate list
    LL* newList = malloc(sizeof(LL));
    // Resolve dangling pointer
    newList->head = NULL;
    
    // Return newly-created list
    return newList;
}

Node* createNode(int data)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}

// void addToHead(LL* list, int data)
    
