# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct binTree binTree;

struct binTree {
    binTree* leftNode;
    binTree* rightNode;
    int key;
};

void Insert(binTree* Node, int item);
void InOrder(binTree* Node);
void TreeSort(int* numberArr, int length);
binTree* createNode();
int* fillArray(int length);

int main() {

    int* numberArray;
    int lengthArray;

    printf("Length of array of items: ");
    scanf("%d", &lengthArray);

    numberArray = fillArray(lengthArray);

    TreeSort(numberArray, lengthArray);

    free(numberArray);

    return 0;
}

int* fillArray(int length) {

    time_t t;
    int* array = malloc(length * sizeof(int));

    srand((unsigned) time(&t));

    for(int i = 0; i < length; ++i) {
        *(array + i) =  (rand() % 50) + 1; //random num 1-50
    }

    for(int i = 0; i < length; ++i) {
        printf("%d ", *(array + i));
    }
    printf("\n");

    return array;
}

void TreeSort(int* array, int length) {
    binTree* root = calloc(1, sizeof(binTree)); // root

    for(int i = 0; i < length; ++i) {
        Insert(root, *(array + i));
    }

    InOrder(root);
}

void Insert(binTree* Node, int item) {
    if(Node->key == 0) {
        Node->key = item;
    }
    else {
        if(item < Node->key) {
            if(Node->leftNode == NULL) {
                Node->leftNode = createNode();
                Insert(Node->leftNode, item);
            }
            else {
                Insert(Node->leftNode, item);
            }
        }
        else {
            if(Node->rightNode == NULL) {
                Node->rightNode = createNode();
                Insert(Node->rightNode, item);
            }
            else {
                Insert(Node->rightNode, item);
            }
        }
    }
}

void InOrder(binTree* Node) {
    if (!Node) {
        return;
    }
    else {
        InOrder(Node->leftNode);
        printf("Node: %d\n", Node->key);
        InOrder(Node->rightNode);
    }
}

binTree* createNode() {
    binTree* Node;

    Node = calloc(1, sizeof(binTree));

    return Node;
}

