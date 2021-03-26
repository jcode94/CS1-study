/**
 * @file AVL.c
 * @author Travis and Justice
 * @brief How To Code an AVL
 * @version 0.1
 * @date 2021-03-23
 * @copyright Copyright (c) 2021
 */

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
Node * delete(Node * root, int value);
void destroyNode(Node * root);
Node * findSmallest(Node * root);
int balanceFactor(Node * root); //Returns the differenct between the left and right child
int max(Node * leftRoot, Node * rightRoot); //Find the largest child
int getHeight(Node * root);
Node * rightRot(Node * root);
Node * leftRot(Node * root);
void destroyTree(Node * root);

//Traversal functions
void postOrder(Node * root);
void preOrder(Node * root);
void inOrder(Node * root);
bool contains(Node * root, int value);
void destroyTree(Node * root);

//Main
int main(){
    Node * root = NULL;
    root = insert(root, 9);
    root = insert(root, 8);
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 100);
    root = insert(root, 75);

    printf("Pre order:");
    preOrder(root);
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
    //If our tree is empty
    if(root == NULL) return createNode(value);

    //traverse
    if(root->value == value){
        return root;
    }
    if(root->value < value){
        root->right = insert(root->right, value);
    }
    if(root->value > value){
        root->left = insert(root->left, value);
    }
    
    root->height = max(root->left, root->right) + 1;

    int bf = balanceFactor(root);
    // LL case
    if (bf < -1 && balanceFactor(root->left) < 0){
        //Do a right rotation
        root = rightRot(root);
    }
    
    // LR case
    else if (bf < -1 && balanceFactor(root->right) > 0){

    }
    
    // RR case
    else if (bf > 1 && balanceFactor(root->left) < 0){
        //Do a left rotation
        root = leftRot(root);
    }
    
    // RL case
    else if (bf > 1 && balanceFactor(root->right) > 0){
        root = rightRot(root->right);
        root = leftRot(root);
    }
    return root;
}
Node * rightRot(Node * root){
    //Swap nodes
    Node * temp = root->left;
    temp->right = root;
    root->left = NULL;
    return temp;
}
Node * leftRot(Node * root){
    //Swap nodes
    Node * temp = root->right;
    temp->left = root;
    root->right = NULL;
    
    //Change height
    root->height -= 2;
    return temp;
}
Node * delete(Node * root, int value);
Node * findSmallest(Node * root);
void destroyNode(Node * root){
    free(root);
}
int getHeight(Node * root){
    if(root == NULL) return 0;
    return root->height;
}
int balanceFactor(Node * root){ //Returns the differenct between the left and right child
    if(root == NULL) return IMPOSSIBLE;
    if(root->left == NULL && root->right == NULL)
        return 0;
    if(root->left == NULL || root->right == NULL){
        if(root->left == NULL) return balanceFactor(root->right) + 1;
        if(root->right == NULL) return balanceFactor(root->left) - 1;
    }
    return getHeight(root->right) - getHeight(root->left);
}
int max(Node * leftRoot, Node * rightRoot){ //Find the largest child and return the height
    //The node has no children
    if(leftRoot == NULL && rightRoot == NULL) return 0;
    
    //The node hase one child:
    if(leftRoot == NULL || rightRoot == NULL) {
        if(leftRoot == NULL)
            return rightRoot->height;
        else
            return leftRoot->height;
    }
    
    //The node has two children, do this stuff:
    int left = max(leftRoot->left, leftRoot->right) + 1;
    int right = max(rightRoot->left, rightRoot->right) + 1;
    
    //Return the largest height between the left and right sub tree
    if(left > right) return left;
    else return right;
}
//Traversal functions
void postOrder(Node * root);
void preOrder(Node * root){
    if(root == NULL) return;
    printf(" %d:%d:%d ", root->value, root->height, balanceFactor(root));
    // printf(" %d:%d ", root->value, root->height);

    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(Node * root);
bool contains(Node * root, int value);
void destroyTree(Node * root);
void destroyTree(Node * root){
    if(root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    destroyNode(root);
}
