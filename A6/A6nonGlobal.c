/**************************************************
* Filename: A6.c
* Author: Justice Smith
* Date: March 28, 2021
* Description: Given the table activation order 
*     and the skill order of the players determine
*     the sum of the excitement across all games 
*     in the tournament.
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#define ll long long

ll nulls = 0;
ll* skills = NULL;
ll totalExcitement = 0;

typedef struct Node Node;

struct Node
{
    ll identifier;
    ll victor;
    Node* left;
    Node* right;
};

Node* createNode(ll identifier);
Node* insert(Node* Node, ll identifier);
void destroyTree(Node* root);
void destroyNode(Node* Node);
void postOrder(Node* root);
ll max(ll a, ll b);
ll simGames(Node* root);

ll main()
{
    Node* root = NULL;
    
    // Get number of nodes
    ll n, i = 0;
    scanf("%lld", &n);
    
    if (n == 1) // Single player edge case
    {
        printf("%d\n", 0);
        return 0;
    }
        
    // init array to hold table activation order
    ll* activationOrder = NULL;
    
    activationOrder = calloc(n - 1, sizeof(ll));
    skills = calloc(n, sizeof(ll));
    
    // get table order
    for (i = 0; i < n - 1; ++i)
        scanf("%lld", &activationOrder[i]);
    
    // traverse table array in reverse to
    // construct tree in post-order
    for (i = n - 2; i >= 0; i--)
        root = insert(root, activationOrder[i]);
        
    for (i = 0; i < n; ++i)
        scanf("%lld", &skills[i]);
    
    // puts("The post order traversal is:");
    simGames(root);
    // postOrder(root);
    // printf("\n");
    

    printf("Total excitement is %lld\n", totalExcitement);
    
    
    return 0;
}

Node* createNode(ll identifier)
{
    Node* newNode = malloc(sizeof(Node));
    
    // Error check
    if (newNode == NULL)
    {
        printf("Memory for Node not allocated.\n");
        exit(0);
    }
    
    newNode->identifier = identifier;
    newNode->victor = 0;
    newNode->left = newNode->right = NULL;
    
    return newNode;
}

Node* insert(Node* root, ll identifier)
{
    
    // Empty tree
    if (root == NULL)
        // printf("This node was empty so we made it %d\n", identifier);
        return createNode(identifier);
    
    else if (root->identifier == identifier)
        // printf("%d already existed in the tree, so we didn't add it\n", identifier);
        return root;
    
    // traverse right
    if (root->identifier < identifier)
        // printf("%d > %d, so we're going DR\n", identifier, root->identifier);
        root->right = insert(root->right, identifier);
    
    // traverse left
    else
        // printf("%d < %d, so we're going DL\n", identifier, root->identifier);
        root->left = insert(root->left, identifier);
        
    return root;
}

void destroyTree(Node* root)
{
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);  
    destroyNode(root);
}
    
void destroyNode(Node* Node)
{
    free(Node);
}

void postOrder(Node* root)
{
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    // printf("%d ", root->identifier);
}

// Pre-condition: Assumes not equal (problem spec)
ll max(ll a, ll b){
    return a > b ? a : b;
}

ll simGames(Node* root)
{
    if (root == NULL)
        return skills[nulls++];
    
    ll leftPlayer = simGames(root->left);
    ll rightPlayer = simGames(root->right);
    totalExcitement += abs(leftPlayer - rightPlayer);
    
    root->victor = max(leftPlayer, rightPlayer);
    
    return root->victor;
}


// This is the non-global version
/*
ll excite(Node* root, ll* skills)
{
    if (root == NULL)
    {
        printf("nulls = %d, returning %d\n", nulls, skills[nulls]);
        return skills[nulls++];
    }
    
    // pull two skills and return the absolute difference    
    if (root->left == NULL && root->right == NULL)
    {
        return abs(excite(root->right, skills) - excite(root->left));
    }
    
    else if (root->left == NULL && root->right != NULL)
    {
        leftExcite = excite(root->left); // returns from array
        rightExcite = excite(root->right); 
        
        return rightExcite + abs(root->left->victor - rightExcite);  
    }
    
    else if (root->right == NULL && root->left != NULL)
    {
        leftExcite = excite(root->left);
        rightExcite = excite(root->right); // returns from array
        
        return leftExcite + abs(root->right->victor - leftExcite);        
    }
    
    else // Neither child null
    {
        leftExcite = excite(root->left);
        rightExcite = excite(root->right);
        return abs(root->left->victor - root->right->victor);
    }  
}
*/
