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
    // ll victor;
    Node* left;
    Node* right;
};

Node* createNode(ll identifier);
Node* insert(Node* Node, ll identifier);
ll max(ll a, ll b);
ll simGames(Node* root);
void destroyTree(Node* root);
void destroyNode(Node* Node);

ll main()
{
    Node* root = NULL;
    
    ll n, i = 0;
    // Get number of nodes
    scanf("%lld", &n);
    
    if (n == 1) // Single player edge case
    {
        printf("%lld", totalExcitement);
        return 0;
    }
        
    // init array to hold table activation order
    ll* activationOrder = NULL;
    
    // allocate space for arrays
    activationOrder = calloc(n - 1, sizeof(ll));
    skills = calloc(n, sizeof(ll));
    
    // get table order
    for (i = 0; i < n - 1; ++i)
        scanf("%lld", &activationOrder[i]);
    
    // traverse table array in reverse to construct tree
    for (i = n - 2; i >= 0; i--)
        root = insert(root, activationOrder[i]);
    
    // get skills
    for (i = 0; i < n; ++i)
        scanf("%lld", &skills[i]);

    // Running the matches and summing excitement
    simGames(root);    

    printf("%lld", totalExcitement);
    
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
    // newNode->victor = 0;
    newNode->left = newNode->right = NULL;
    
    return newNode;
}

Node* insert(Node* root, ll identifier)
{
    
    // Empty tree
    if (root == NULL)
        return createNode(identifier);
    
    // no dupes
    else if (root->identifier == identifier)
        return root;
    
    // traverse right
    if (root->identifier < identifier)
        root->right = insert(root->right, identifier);
    
    // traverse left
    else
        root->left = insert(root->left, identifier);
        
    return root;
}

// Pre-condition: Assumes not equal (problem spec)
ll max(ll a, ll b){
    // returns larger of two values
    return a > b ? a : b;
}

ll simGames(Node* root)
{
    // When we hit a null node, we pull from skills array
    // and increment our nullCounter/index/position
    if (root == NULL)
        return skills[nulls++];
    
    // Simulates left and right tree games 
    ll leftPlayer = simGames(root->left);
    ll rightPlayer = simGames(root->right);
    
    // Sums difference to global excitement
    totalExcitement += abs(leftPlayer - rightPlayer);
    
    // this represents the victor from the game
    return max(leftPlayer, rightPlayer);
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

