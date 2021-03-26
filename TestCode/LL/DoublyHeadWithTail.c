/**
 * @file DoublyHeadWithTail.c
 * @author Travis M Wise
 * @brief Create a program that will use a doubly linked list with a head and tail pointer
 * @version 0.1
 * @date 2021-03-13
 */

//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>

//structs
typedef struct Node Node;
struct Node {
    int value;
    Node * next, * prev;
};

typedef struct LL LL;
struct LL {
    Node * head;
    Node * tail;
};

//Prototypes
LL * createLL();
Node * createNode(int value);
void destroyNode(Node * someNode);
void push(LL * list, int value);
void pop(LL * list);
void addToTail(LL * list, int value);
void removeFromTail(LL * list);
void printList(LL * list);
void freeList(LL * list);
int peakEnd(LL * list);
int peakStart(LL * list);
void printBackwards(LL * list);

//Main function
int main(){
    LL * list = createLL();
    
    //Add the values 1-5
    for(int i = 0; i < 5; i++){
        printList(list);
        push(list, i + 1);
        if(i == 4) printList(list);
    }

    //Peek the last value and output
    int curNum = peakEnd(list);
    printf("\nCurrent tail value: %d\n", curNum);
    
    //Print backwards using the prev pointers
    printf("\nThe list backwards is: \n");
    printBackwards(list);

    //Add to the tail
    printf("\n\n\n");
    for(int i = 11; i <= 15; i++){
        addToTail(list, i);
        printList(list);
    }
    //Remove all values in the list
    while(list->head != NULL){
        removeFromTail(list);
        printList(list);
    }

    
    freeList(list);
    return 0;
}

LL * createLL(){
    LL * list = (LL*)calloc(1, sizeof(LL));
    list->head = NULL;
    list->tail = NULL;
    return list;
}
Node * createNode(int value){
    Node * newNode = (Node*)calloc(1, sizeof(Node));
    newNode->value = value;
    newNode->next = newNode->prev = NULL;
}
void destroyNode(Node * someNode){
    free(someNode);
}
//Add the new value to the beginning of the list
void push(LL * list, int value){
    Node * newNode = createNode(value);

    //Special case for if the list is empty
    if(list->head == NULL && list->tail == NULL){
        list->head = list->tail = newNode;
        return;
    }

    //Add the value to the head as the list is not empty
    //The tail should not be changed
    newNode->next = list->head; //Set the new head's next point to the old head
    list->head->prev = newNode; //Set the previous pointer to the new head
    list->head = newNode; //Set the head pointer to the new head    
}
//Remove a value from the head
void pop(LL * list){
    //Check if the head is null
    if(list->head == NULL)
        return;
    
    Node * newHead = list->head->next;
    destroyNode(list->head);
    list->head = newHead;

    //Check if the new head is null, the tail should agree with it if so
    if(list->head == NULL){
        //The list is now empty
        list->tail = NULL;
    }
}
void addToTail(LL * list, int value){
    Node * newNode = createNode(value);

    //Special case for if the list is empty
    if(list->head == NULL && list->tail == NULL){
        list->head = list->tail = newNode;
        return;
    }

    //List is not empty, add to the tail
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}
void removeFromTail(LL * list){
    //If our list is empty then return
    if(list->tail == NULL)
        return;
    
    //If there is only one last element
    if(list->tail == list->head){
        destroyNode(list->tail);
        list->tail = list->head = NULL;
        return;
    }

    Node * oldTail = list->tail;
    list->tail = list->tail->prev;
    destroyNode(oldTail);
    list->tail->next = NULL;
}
void printList(LL * list){
    Node * temp = list->head;
    while(temp != NULL){
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
    return;
}
void freeList(LL * list){
    while(list->head != NULL){
        Node * temp = list->head;
        list->head = list->head->next;
        destroyNode(temp);
    }
    free(list);
    return;
}
int peakEnd(LL * list){
    int ret = list->tail->value;
    return ret;
}
int peakStart(LL * list){
    int ret = list->head->value;
    return ret;
}
void printBackwards(LL * list){
    Node * temp = list->tail;
    while(temp != NULL){
        printf("%d -> ", temp->value);
        temp = temp->prev;
    }
    printf("NULL\n");
    return;
}