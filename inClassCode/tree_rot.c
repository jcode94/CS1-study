#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node * l, * r, * p;
    int value;
};

Node * createNode(int value);
Node * insertRight(Node * root, int value);
void rotateLeft(Node * node);
Node * findRoot(Node * node);
void post(Node * root);

int main() {
    Node * root = createNode(0);
    for (int i = 1; i < 5; ++i) {
        root = insertRight(root, i);
    }
    while (root->r != NULL) {
        printf("The root is $d\n", root->value);
        post(root);
        printf("\n\n");
        rotateLeft(root);
        root = findRoot(root);
    }

    // Leak memory :(

        return 0;
}

Node * createNode(int value) {
    Node * ret = calloc(1, sizeof(Node));
    ret->value = value;
    ret->p = ret->l = ret->r = NULL;
    return ret;
}

Node * insertRight(Node * root, int value) {
    if (root == NULL)
        return createNode(value);
    Node * retvalue = 

    while (root->r != NULL) {
        root = root->r;
    }
    root->r = createNode(value);
    root->r->p = root;

    return root;
}

void rotateLeft(Node * node) {
    Node * parent = node->p;
    Node * child = node->r;
    Node * grandChild = child->l;

    // Edge 1
    child->p = parent;
    if (parent  != NULL) {
        if (parent->r == node)
            parent->r = child;
        else
            parent->l = child;
    }

    // Edge 2
    child->l = node;
    node->p = child;
    
    // Edge 3
    node->l = grandChild;
    if (grandChild != NULL)
        grandChild->p = node;
}

Node * findRoot(Node * node) {
    if (node == NULL)
        return NULL;
    if (node->p == NULL)
        return node;
    return findRoot(node->p);
}


void post(Node * root) {
    if (root == NULL)
        return;
    post(root->l);
    post(root->r);
    printf("%d ", root->value);
}