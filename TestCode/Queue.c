#include <stdio.h>
#include <stdlib.h>

typedef struct Queue Queue;
typedef struct Node Node;

struct Node
{
    int data;
    Node* next;
};

struct Queue
{
    Node* front;
    Node* back;
};

Queue* createQueue();
Node* createNode(int data);
void enqueue(Queue* Queue, int data);
void dequeue(Queue* Queue);
void printQ(Queue* Queue);
void front(Queue* Queue);
Queue* deleteQueue(Queue* Queue);

int main()
{
    Queue* myQ = createQueue();
    
    enqueue(myQ, 3);
    printQ(myQ);
    enqueue(myQ, 6);
    printQ(myQ);
    dequeue(myQ);
    printQ(myQ);
    front(myQ);
    enqueue(myQ, 21);
    printQ(myQ);
    enqueue(myQ, 22);
    printQ(myQ);
    
    myQ = deleteQueue(myQ);
    printQ(myQ);
    
    return 0;
}

Queue* createQueue()
{
    Queue* newQ = malloc(sizeof(Queue));
    newQ->front = newQ->back = NULL;
    return newQ;
}
    
Node* createNode(int data)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}

void enqueue(Queue* Queue, int data)
{
    Node* newNode = createNode(data);
    
    if (Queue->front == NULL) // Queue empty
    {
        Queue->front = Queue->back = newNode;
        return;
    }
    
    // Attaching new node to back of Queue
    Queue->back->next = newNode;
    // Adjusting our backptr
    Queue->back = newNode;
}        
    
void dequeue(Queue* Queue)
{
    if (Queue->front == NULL)
        return;
        
    Node* temp = Queue->front;
    Queue->front = Queue->front->next;
    
    if (Queue->front == NULL)
        Queue->back = NULL;
    
    free(temp);
}

void printQ(Queue* Queue)
{
    if (Queue == NULL)
    {
        printf("No Queue!\n");
        return;
    }
        
    Node* current = Queue->front;
    printf("Queue: ");
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");
}
    
void front(Queue* Queue)
{
    printf("Element at front of Queue: %d\n", Queue->front->data);
}

Queue* deleteQueue(Queue* Queue)
{
    while (Queue->front != NULL)
        dequeue(Queue);
    free(Queue);
    return NULL;
}
