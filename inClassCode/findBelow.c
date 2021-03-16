#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;

struct Node {
    Node* left;
    Node* right;
    Node* data;
};

int find_below(Node* root, int val)
{
    int largestChild;

    if (root == NULL)
    {
        return val;
    }

    if ((root->data > find_below(root->left, val)) && root->data < val)
    {
        return root->data;
    }

    largestChild = find_below(root->left, val);
    find_below(root->right, val);

    return val;
}

int main()
{

}