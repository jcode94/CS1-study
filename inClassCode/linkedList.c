#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int data;
    Node* next;
};

Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));        
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

Node* append(Node* node, int data) {
    // Empty list
    if (node == NULL) 
        return createNode(data);
    
    node->next = append(node->next, data);
    
    return node;
}

void printNodes(Node* node) {
    // Empty list
    if (node == NULL) {
        return;
    }

    printf("Data = %d\n", node->data);
    printNodes(node->next);        
}

void printNodesReverse(Node* node) {
    // Empty list
    if (node == NULL) {
        return;
    }

    printNodes(node->next);        
    printf("Data = %d\n", node->data);
}

Node* destroyNode(Node* node) {
    // Last element
    if (node->next == NULL)
        return node;
    // Recursive free
    free(destroyNode(node->next));
    return node;
}

int main() {
    Node* head = NULL;
    int numNodes;
    int data;

    printf("Input the number of nodes : ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; ++i) {
        printf("Input data for node %d : ", i + 1);
        scanf("%d", &data);   
        head = append(head, data);
    }

    printf("\nData entered in the list :\n");
    printNodes(head);

    printf("\nData entered in the list, but in reverse :\n");
    printNodesReverse(head);

    free(destroyNode(head));    

    return 0;
}