
// Program to test rotations
//
// Insert 10 random nodes into a tree
// Randomly rotate

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node * l, * r, * p;
    int value;
};

int containsValue(Node * root, int x);
Node * createNode(int value);
Node * insertNode(Node * root, int value);
Node * randomNode(Node * root);
void rotateLeft(Node * node);
void rotateRight(Node * node);
Node * findRoot(Node * node);
void pre(Node * root);

int main() {
    Node * root = NULL;

    // Insert 10 random nodes
    for (int i = 1; i <= 10; i++) {
        // Ensure the value is unique
        int value = rand() % 20 + 1;
        while (containsValue(root, value))
            value = rand() % 20 + 1;

        // Use the insertion method to inser the value
        root = insertNode(root, value);
    }
    
    // Do some random rotates
    for (int i = 1; i <= 10; i++) {
        Node * toRot = randomNode(root);

        // Rotate left or right 50% of the time each
        if (rand() & 1) {
            // Rotate left
            printf("Rotating %d left...\n", toRot->value);
            rotateLeft(toRot);
        } else {
            // Rotate right
            printf("Rotating %d right...\n", toRot->value);
            rotateRight(toRot);
        }

        // Adjust the root if necessary
        root = findRoot(root);

        // Print the resulting tree
        pre(root);
        printf("\n\n");
    }

    // Leak memory :(
    
    return 0;
}

// Method to create a node for a BST
Node * createNode(int value) {
    Node * ret = calloc(1, sizeof(Node));
    ret->value = value;
    ret->p = ret->l = ret->r = NULL;
    return ret;
}

// Return 1 if a given value (x) is contained in the BST
// Return 0 otherwise
int containsValue(Node * root, int x) {
    if (root == NULL) return 0;
    if (root->value == x) return 1;

    // Check which direction we need to visit
    if (root->value < x)
        return containsValue(root->r, x); // GO RIGHT

    // The root is larger we need to go into the smaller sub-tree
    return containsValue(root->l, x);// GO LEFT
}

// Insert a node into a BST and return the root
Node * insertNode(Node * root, int value) {
    // Check if the tree is empty
    if (root == NULL)
        return createNode(value);

    // root value is smaller than value
    // GO RIGHT
    if (root->value < value) {
        root->r = insertNode(root->r, value);
        root->r->p = root; // Correct the parent of any potential new node
    } else {
        root->l = insertNode(root->l, value);
        root->l->p = root; // Correct the parent pointer...
    }

    // Return the root of the tree
    return root;
}

// Select a random node from a BST
Node * randomNode(Node * root) {
    // Roll some random value in range of 0 to 99
    int v = rand() % 100;

    // 40% chance select the right side (if it exists)
    if (root->r != NULL) {
        if (v < 40) {
            return randomNode(root->r);
        }
        v -= 40;
    }

    // 40% chance select the left side (if it exists)
    if (root->l != NULL) {
        if (v < 40)
            return randomNode(root->l);
    }

    // Remainder of the chance select the root
    return root;
}

// Method to rotate some node to the right and down
void rotateRight(Node * me) {
    Node * parent = me->p;
    Node * child = me->l;

    // Check that the replacement node exists
    if (child == NULL) {
        fprintf(stderr, "Invalid Rotation!\n");
        return;
    }
    
    // Don't deref NULL
    Node * grandChild = child->r;

    // Edge 1
    child->p = parent;
    if (parent != NULL) {
        if (parent->r == me)
            parent->r = child;
        else
            parent->l = child;
    }

    // Edge 2
    child->r = me;
    me->p = child;

    // Edge 3
    me->l = grandChild;
    if (grandChild != NULL)
        grandChild->p = me;
}

// Method to rotate some node to the left and down
void rotateLeft(Node * me) {
    Node * parent = me->p;
    Node * child = me->r;
    
    // Check that the replacement node exists
    if (child == NULL) {
        fprintf(stderr, "Invalid Rotation!\n");
        return;
    }
    
    // Don't deref NULL
    Node * grandChild = child->l;

    // Edge 1
    child->p = parent;
    if (parent != NULL) {
        if (parent->r == me)
            parent->r = child;
        else
            parent->l = child;
    }

    // Edge 2
    child->l = me;
    me->p = child;

    // Edge 3
    me->r = grandChild;
    if (grandChild != NULL)
        grandChild->p = me;
}

// Method to find the root of some BST
Node * findRoot(Node * node) {
    if (node == NULL)
        return NULL;
    if (node->p == NULL)
        return node;
    return findRoot(node->p);
}

// Method to print the pre order of a BST
void pre(Node * root) {
    if (root == NULL)
        return;
    printf("  %d\n", root->value);
    pre(root->l);
    pre(root->r);
}


