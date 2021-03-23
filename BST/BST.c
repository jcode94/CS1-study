// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Structs
typedef struct Node Node;
struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
};

// Functions
Node* createNode(int value);
Node* insert(Node* root, int value);
Node* delete(Node* root, int value);
void postOrder(Node* root);
void inOrder(Node* root);
void preOrder(Node* root);
int sumOfAllNodes(Node* root);
int sumOfAllLeaves(Node* root);
bool contains(Node* root, int value);
void destroyNode(Node* root);
Node* findSmallest(Node* root);

// Driver
int main()
{
    Node* root = NULL;
    
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 2);
    
    printf("\n PreOrder: ");
    preOrder(root);
    
    printf("\n InOrder: ");
    inOrder(root);
    
    printf("\n PostOrder: ");
    postOrder(root);

    printf("\n The sum of all nodes is: %d\n", sumOfAllNodes(root));
    printf(" The sum of all leaves is: %d\n", sumOfAllLeaves(root));
    
    root = delete(root, 3);
    
    printf("\n PreOrder: ");
    preOrder(root);
    
    printf("\n InOrder: ");
    inOrder(root);
    
    printf("\n PostOrder: ");
    postOrder(root);

    printf("\n The sum of all nodes is: %d\n", sumOfAllNodes(root));
    printf(" The sum of all leaves is: %d\n", sumOfAllLeaves(root));
    
    contains(root, 6) ? printf(" Yes!\n") : printf(" No!\n");
    
    return 0;
}

bool contains(Node* root, int data)
{
    if (root == NULL) return false;
    if (root->data == data) return true;    
    
    if (root->data < data) return contains(root->right, data);
    if (root->data > data) return contains(root->left, data);
}
        

Node* findSmallest(Node* root)
{
    if (root->left == NULL)
        return root;
    return findSmallest(root->left);
}

void destroyNode(Node* root)
{
    free(root);
}

Node* delete(Node* root, int data)
{
    // Empty tree or node doesn't exist
    if (root == NULL)
        return NULL;
        
    // At least one node in the tree
    if (root->data < data)
        root->right = delete(root->right, data);
        
    if (root->data > data)
        root->left = delete(root->left, data);
        
    if (root->data == data)
    {   
        // No children
        if (root->left == NULL && root->right == NULL)
        {
            destroyNode(root);
            return NULL;
        }
        
        // 1 child
        if (root->left == NULL || root->right == NULL)
        {
            Node* temp = root->left;
            if(temp == NULL) temp = root->right;
            
            destroyNode(root);
            return temp;
        }
        
        // 2 children
        // 1. We found the current node we are looking to delete
        // 2. Find the right smallest value
        // 3. Swap the current node and the right smallest value
        // 4. call delete again on the right side of the tree 
        //        (recursively) until we find the value again
        // 5. Delete the node using the case where we have zero children.
        
        // Finds the smallest number larger than root
        Node* smallest = findSmallest(root->right);
        
        // Swap the values
        int tempValue = root->data;
        root->data = smallest->data;
        smallest->data = tempValue;
        
        root->right = delete(root->right, tempValue);
    }
    return root;       
}

Node* insert(Node* root, int data)
{
    if (root == NULL)
        return createNode(data);
        
    if (root->data == data)
        return root;
        
    if (root->data < data)
    {
        root->right = insert(root->right, data);
        root->right->parent = root;
        printf(" %d gets %d as parent...\n", root->right->data, root->data);
    }
    
    if (root->data > data)
    {
        root->left = insert(root->left, data);
        root->left->parent = root;
        printf(" %d gets %d as parent...\n", root->left->data, root->data);
    }
    return root;
}

int sumOfAllNodes(Node* root)
{
    int sum = 0;
    if (root == NULL)
        return 0;
        
    return root->data + sumOfAllNodes(root->left) + sumOfAllNodes(root->right);
}

int sumOfAllLeaves(Node* root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return root->data;
        
    return sumOfAllLeaves(root->left) + sumOfAllLeaves(root->right);
}

Node* createNode(int data)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    
    return newNode;
}

void inOrder(Node* root)
{
    if (root == NULL)
        return;
        
    inOrder(root->left);
    printf(" %d ", root->data);
    inOrder(root->right);
}

void preOrder(Node* root)
{
    if (root == NULL)
        return;

    printf(" %d ", root->data);        
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root)
{
    if (root == NULL)
        return;
        
    postOrder(root->left);
    postOrder(root->right);
    printf(" %d ", root->data);
}
