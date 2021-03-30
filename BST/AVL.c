/***************************************
 * @file AVL.c
 * @author Travis Wise, Justice Smith
 * @brief How To Code an AVL
 * @version 0.1
 * @date 2021-03-23
 * @copyright Copyright (c) 2021
 **************************************/

//Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IMPOSSIBLE -999999

//Structs
typedef struct Node Node;
struct Node {
    int value;
    Node * right;
    Node * left;
    Node * parent;
    int height; //depth, the number of nodes in the largest sub-tree
};

//Prototypes
Node * createNode(int value);
Node * insert(Node * root, int value);
Node* delete(Node* root, int value);
int reheightify(Node * root);
int getMax(Node * left, Node * right);
int getBF(Node * root);
int getHeight(Node * root);
void postOrder(Node * root);
void preOrder(Node * root);
void inOrder(Node * root);
void destroyTree(Node * root);
void destroyNode(Node * root);
Node* leftRot(Node* cur);
Node* rightRot(Node* cur);
Node* findSmallest(Node* root);

//Main
int main(){
    Node * root = NULL;
    int num;
    scanf("%d", &num);
    while(num != -1){
        root = insert(root, num);
        scanf("%d", &num);
    }
    
    root = delete(root, 2);
    
    printf("Pre-order:");
    preOrder(root);
    printf("\nPost-order:");
    postOrder(root);
    printf("\nIn-order:");
    inOrder(root);
    
    printf("\n");

    destroyTree(root);
    return 0;
}


//Functions
Node * createNode(int value){
    Node * ret = (Node*)malloc(sizeof(Node));
    ret->value = value;
    ret->left = ret->right = ret->parent = NULL;
    ret->height = 0;
    return ret;
}


Node * insert(Node * root, int value){
    if(root == NULL) {
        return createNode(value);
    }
    else if (root->value == value) {
        return root;
    }
    else if(root->value < value) {
        root->right = insert(root->right, value);
        root->right->parent = root;
        // printf("%d gets %d as parent...\n", root->right->value, root->value);
    }
    else if(root->value > value) {
        root->left = insert(root->left, value);
        root->left->parent = root;
        // printf("%d gets %d as parent...\n", root->left->value, root->value);

    }
    root->height = reheightify(root);
    
    // Get balance factor for current node
    int bf = getBF(root);

    //Rotate as needed
    //LL case
    if (bf < -1 && getBF(root->left) < 0){
        root = rightRot(root);
        root->right->height = reheightify(root->right);    
    }
    //LR case
    else if (bf < -1 && getBF(root->left) > 0){
        // Do the left rotation
        root->left = leftRot(root->left);
        root->left->left->height = reheightify(root->left->left);
        root->left->height = reheightify(root->left);        
        
        // Do the right rotation
        root = rightRot(root);
        root->right->height = reheightify(root->right);
    }
    //RR case
    else if (bf > 1 && getBF(root->right) > 0){
        root = leftRot(root);
        root->right->height = reheightify(root->left);
    }
    //RL case
    else if (bf > 1 && getBF(root->right) < 0){
        // Do the right rotation
        root->right = rightRot(root->right);
        root->right->right->height = reheightify(root->right->right);
        root->right->height = reheightify(root->right);
        
        // Do the left rotation
        root = leftRot(root);
        root->left->height = reheightify(root->left);
    }
    
    // Rotate as needed
    return root;
}

Node* delete(Node* root, int value)
{
    // Empty tree or node doesn't exist
    if (root == NULL)
        return NULL;
        
    // At least one node in the tree
    if (root->value < value)
    {
        root->right = delete(root->right, value);
    }
        
    if (root->value > value)
    {
        root->left = delete(root->left, value);
    }
        
    if (root->value == value)
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
            temp->parent = root->parent;
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
        int tempValue = root->value;
        root->value = smallest->value;
        smallest->value = tempValue;
        
        root->right = delete(root->right, tempValue);
    }
    
    root->height = reheightify(root);
    return root;       
}

Node* findSmallest(Node* root)
{
    if (root->left == NULL)
        return root;
    return findSmallest(root->left);
}

Node * rightRot(Node * cur){
    //Make refrence nodes to parent
    Node * parent = cur->parent; //Get the current node's parent and store it
    Node * child = cur->left; //Get the current node's left child and store it (this will be the new papa)

    //We cannot rotate if the child is NULL
    if(child == NULL) return cur;
    
    //Get the child's right
    Node * grandchild = child->right;

    //Swap the child with cur
    child->parent = parent;
    if(parent != NULL) {
        if(parent->left == cur) 
            parent->left = child; //We are on the left side of the parent (swap the current with child)
        else
            parent->right = child; //We are on the right side of the parent (swap the current with child)
    }

    //Set the pointers of child and current to point to each other
    child->right = cur;
    cur->parent = child;
    
    cur->left = grandchild; //If grandchild is NULL than cur->left will simply point to NULL
    if(grandchild != NULL)
        grandchild->parent = cur;
    
    return child;
}
Node * leftRot(Node* cur){
// Make reference nodes to parent
    Node * parent = cur->parent; //Get the current node's parent and store it
    Node * child = cur->right; //Get the current node's left child and store it (this will be the new papa)
  
    //We cannot rotate if the child is NULL
    if(child == NULL) return cur;

    Node * grandchild = child->left; //Get the child's right
    child->parent = parent; //Swap the child with cur

    if(parent != NULL) {
        if(parent->left == cur) 
            parent->left = child; //We are on the left side of the parent (swap the current with child)
        else
            parent->right = child; //We are on the right side of the parent (swap the current with child)
    }
    //Set the pointers of child and current to point to each other
    child->left = cur;
    cur->parent = child;
    
    cur->right = grandchild; //If grandchild is NULL than cur->left will simply point to NULL
    if(grandchild != NULL)
        grandchild->parent = cur;

    return child;
}


int reheightify(Node * root){
    if(root == NULL) return -1;
    else if(root->left == NULL && root->right == NULL) return 0;
    else if(root->left == NULL || root->right == NULL) {
        if(root->left == NULL) return root->right->height + 1;
        if(root->right == NULL) return root->left->height + 1;
    }
    else if(root->left != NULL && root->right != NULL) {
        return getMax(root->left, root->right) + 1;
    }
}


int getMax(Node * left, Node * right){ //Pre-condition: Assumes left and right nodes are not NULL
    if(left->height > right->height) return left->height;
    else return right->height;
}


int getBF(Node * root){
    if(root == NULL) return 0;
    int rightHeight = getHeight(root->right);
    int leftHeight = getHeight(root->left);
    return rightHeight - leftHeight;
}


int getHeight(Node * root){
    if(root == NULL) return -1;
    return root->height;
}


void postOrder(Node * root){ //Print the tree in post-order
    if(root == NULL) return;

    postOrder(root->left);
    postOrder(root->right);
    printf(" %d:%d:%d ", root->value, root->height, getBF(root));
}


void preOrder(Node * root){ //Print the tree in pre-order
    if(root == NULL) return;
    printf(" %d:%d:%d ", root->value, root->height, getBF(root));
    preOrder(root->left);
    preOrder(root->right);
}


void inOrder(Node * root){ //Print the tree in in-order

    if(root == NULL) return;
    inOrder(root->left);
    printf(" %d:%d:%d ", root->value, root->height, getBF(root));
    inOrder(root->right);
}


void destroyTree(Node * root){
    if(root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    destroyNode(root);
}


void destroyNode(Node * root){
    free(root);
}
